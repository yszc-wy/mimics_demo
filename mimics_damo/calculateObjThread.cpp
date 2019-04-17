#include "calculateObjThread.hpp"
#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkQuadricDecimation.h>
#include <vtkPolyDataNormals.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOBJExporter.h>
#include "mask.h"
#include "object.h"
#include <QVTKWidget.h>
#include <qmap.h>
#include <qmessagebox.h>
#include <vtkProperty.h>


#include <vtkImageResample.h>
#include <vtkImageAnisotropicDiffusion3D.h>
#include <vtkImageMedian3D.h>
#include <vtkLinkEdgels.h>
CalculateObjThread::CalculateObjThread() {
	
}
CalculateObjThread::~CalculateObjThread()
{
	this->wait();
}
void CalculateObjThread::setCalMaskAndCheckedId(std::weak_ptr<Mask> mask,int id)
{
	this->calMask = mask;
	this->checkedId = id;
}

void CalculateObjThread::setObjPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objMapPtr)
{
	this->objPtrQMapPtr = objMapPtr;
}
void CalculateObjThread::setRen(vtkSmartPointer<vtkRenderer> ren)
{
	this->ren_3dViewer = ren;
}
//void calculateObjThread::setVTKWidget(QVTKWidget *widget)
//{
//	this->widget_3dViewer = widget;
//}
void CalculateObjThread::run()
{

	//利用setinputData，不要让其建立渲染管线，以免占用内存
	emit changeProcess("create model...", 0);

	vtkSmartPointer<vtkImageResample> resample = vtkSmartPointer<vtkImageResample>::New();
	resample->SetInputData(this->calMask.lock()->imageData);
	resample->SetAxisMagnificationFactor(0, 0.7);
	resample->SetAxisMagnificationFactor(1, 0.7);
	resample->SetAxisMagnificationFactor(2, 0.7);
	resample->SetOutputSpacing(this->calMask.lock()->imageData->GetSpacing());
	resample->ReleaseDataFlagOn();
	resample->Update();

	vtkSmartPointer<vtkImageMedian3D> imageMedianFilter = vtkSmartPointer<vtkImageMedian3D>::New();  //中值滤波
	imageMedianFilter->SetInputData(resample->GetOutput());
	imageMedianFilter->ReleaseDataFlagOn();
	imageMedianFilter->Update();

	//vtkSmartPointer<vtkImageAnisotropicDiffusion3D> diffusion = vtkSmartPointer<vtkImageAnisotropicDiffusion3D>::New();
	//diffusion->SetInputData(resample->GetOutput);
	//diffusion->SetNumberOfIterations(10);
	//diffusion->SetDiffusionThreshold(1);

	vtkSmartPointer<vtkMarchingCubes> marchingcube = vtkSmartPointer<vtkMarchingCubes>::New();
	marchingcube->SetInputData(imageMedianFilter->GetOutput());//头文件包含
	marchingcube->ComputeNormalsOn();
	marchingcube->SetValue(0, 1);
	marchingcube->ReleaseDataFlagOn();
	marchingcube->Update();

	//this->calculateProgressBar->setValue(10);
	

	emit changeProcess("smooth model...", 10);
	vtkSmartPointer<vtkWindowedSincPolyDataFilter> smooth = vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New(); //使图像更加光滑
	//smooth->SetInputConnection(marchingcube->GetOutputPort());
	smooth->SetInputData(marchingcube->GetOutput());
	smooth->SetNumberOfIterations(300);
	smooth->NormalizeCoordinatesOn();
	smooth->ReleaseDataFlagOn();
	smooth->Update();

	emit changeProcess("optimization model...", 20);
	//this->calculateProgressBar->setValue(20);
	//this->tipLabel->setText("optimization model...");
	vtkSmartPointer<vtkQuadricDecimation> deci = vtkSmartPointer<vtkQuadricDecimation>::New();
	//deci->SetInputConnection(smooth->GetOutputPort());
	deci->SetInputData(smooth->GetOutput());
	deci->ReleaseDataFlagOn();
	if (this->checkedId == 0)
		deci->SetTargetReduction(0.90);
	else if (this->checkedId == 1)
		deci->SetTargetReduction(0.6);
	else if (this->checkedId == 2)
		deci->SetTargetReduction(0.3);
	else if (this->checkedId == 3)
		deci->SetTargetReduction(0);
	deci->ReleaseDataFlagOn();
	deci->Update();

	emit changeProcess("calculate normals...", 30);
	//this->calculateProgressBar->setValue(30);
	//this->tipLabel->setText("calculate normals...");
	vtkSmartPointer<vtkPolyDataNormals> skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//绘制法线
	//skinNormals->SetInputConnection(deci->GetOutputPort());
	skinNormals->SetInputData(deci->GetOutput());
	skinNormals->ReleaseDataFlagOn();
	skinNormals->Update();

	emit changeProcess("stripper model...", 40);
	//this->calculateProgressBar->setValue(40);
	//this->tipLabel->setText("stripper model...");
	vtkSmartPointer<vtkStripper>skinStripper = vtkSmartPointer<vtkStripper>::New(); //三角带连接
	//skinStripper->SetInputConnection(skinNormals->GetOutputPort());
	skinStripper->SetInputData(skinNormals->GetOutput());
	skinStripper->ReleaseDataFlagOn();
	skinStripper->Update();

	emit changeProcess("mapper...", 50);
	//this->calculateProgressBar->setValue(50);
	//this->tipLabel->setText("mapper...");
	vtkSmartPointer<vtkPolyDataMapper> skinMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	//skinMapper->SetInputConnection(skinStripper->GetOutputPort());
	skinMapper->SetInputData(skinStripper->GetOutput());
	skinMapper->ScalarVisibilityOff();
	skinMapper->ReleaseDataFlagOn();
	skinMapper->Update();
	//skinMapper->ScalarVisibilityOff();

	emit changeProcess("create obj...", 60);
	//this->calculateProgressBar->setValue(60);
	//this->tipLabel->setText("create obj...");
	vtkSmartPointer<vtkActor> objActor =
		vtkSmartPointer<vtkActor>::New();
	objActor->SetMapper(skinMapper);
	objActor->GetProperty()->SetColor(
		this->calMask.lock()->color[0],
		this->calMask.lock()->color[1],
		this->calMask.lock()->color[2]);

	//创建Object对象存入管理对象
	emit changeProcess("save obj...", 70);
	//this->calculateProgressBar->setValue(70);
	//this->tipLabel->setText("save obj...");
	QString quality;
	switch (checkedId)
	{
	case 0:
		quality = "low";
		break;
	case 1:
		quality = "middle";
		break;
	case 2:
		quality = "high";
		break;
	case 3:
		quality = "original";
		break;
	}
	
	std::shared_ptr<Object> newObj = std::make_shared<Object>(this->calMask.lock()->name, objActor, quality);
	newObj->color[0] = this->calMask.lock()->color[0];
	newObj->color[1] = this->calMask.lock()->color[1];
	newObj->color[2] = this->calMask.lock()->color[2];
	this->objPtrQMapPtr->insert(newObj->name, newObj);
	emit objectListChange(this->calMask.lock()->name);

	//显示在第四个窗口上
	emit changeProcess("show obj...", 80);
	//this->calculateProgressBar->setValue(80);
	//this->tipLabel->setText("show obj...");
	this->ren_3dViewer->AddActor(objActor);
	this->ren_3dViewer->Modified();
	//this->widget_3dViewer->GetRenderWindow()->Render();

	emit changeProcess("complete!", 100);
	
}