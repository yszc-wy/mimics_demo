//qt头文件
#include "qFourViewWidget.hpp"
#include "qVtkImageWidget.hpp"
#include "qlayout.h"
#include "qscrollbar.h"
#include "qtoolbar.h"
#include "qmap.h"
#include <QVTKWidget.h>
#include <qmessagebox.h>


//itk头文件
#include <itkBinaryThresholdImageFilter.h>
#include <itkConnectedThresholdImageFilter.h>

//vtk头文件
#include <vtkImageFlip.h>
#include <vtkRenderWindow.h>
#include <vtkImageViewer2.h>
#include <vtkLookupTable.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkCamera.h>
#include <vtkInteractorStyleImage.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkCellData.h>
#include <vtkRegularPolygonSource.h>
#include <vtkProperty.h>
#include <vtkOutlineFilter.h>
#include <vtkCellPicker.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageActor.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkImageIterator.h>
#include <vtkImageMapToColors.h>
#include <vtkImageMapper3D.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImageThreshold.h>
#include <vtkImageCast.h>
#include <vtkImageAlgorithmFilter.h>
#include <vtkImageData.h>
//自定义头文件
#include "vtkSynchronizeCameraCallback.h"
#include "mask.h"
#include "object.h"
#include <qVtk3dWidget.hpp>
#include "vtkSynchronizeCameraCallback.h"
#include "vtkImageAlgorithmFilter.h"


const int ZOOM = 1;
const int RECOVER = 0;



QFourViewWidget::QFourViewWidget(QWidget * parent) : QWidget(parent) {
	this->initVariable();
	this->createWidget();
	this->setRenderForMaskAndObjectType();
}
void QFourViewWidget::setMaskPtrMapPtr(std::weak_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr)
{
	this->maskPtrMapPtr = maskPtrMapPtr;
}
void QFourViewWidget::setObjPtrMapPtr(std::weak_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrMapPtr)
{
	this->objPtrMapPtr = objPtrMapPtr;
}
void QFourViewWidget::setCurrentMaskPtr(std::weak_ptr<Mask> mask)
{
	this->currentMask = mask;
}

//void QFourViewWidget::createMaskFromTresholdValue(int min, int max)   //从阈值中创建mask
//{
//	int extent[6];
//	int dims[3];
//	this->ctImageData->GetExtent(extent);
//	this->ctImageData->GetDimensions(dims);
//
//	vtkSmartPointer<vtkImageThreshold> thresholdFilter = vtkSmartPointer<vtkImageThreshold>::New();
//	thresholdFilter->ThresholdBetween(min, max);
//	thresholdFilter->SetOutValue(0);
//	thresholdFilter->SetInValue(1);    //像素值和亮度有关系，应为这个关系所以lookuptable范围覆盖整个图像时，还是可以看出图像的原本样子
//	thresholdFilter->SetInputData(this->ctImageData);
//	thresholdFilter->ReleaseDataFlagOn();
//
//	//vtkSmartPointer<vtkImageMedian3D> imageMedianFilter = vtkSmartPointer<vtkImageMedian3D>::New();  //中值滤波
//	//imageMedianFilter->SetInputConnection(thresholdFilter->GetOutputPort());
//	//imageMedianFilter->ReleaseDataFlagOn();
//	//vtkImageMedian3D
//	//thresholdFilter->Update();
//
//	vtkSmartPointer<vtkImageCast> imageCast = vtkSmartPointer<vtkImageCast>::New();
//	imageCast->SetOutputScalarTypeToUnsignedChar();
//	imageCast->SetInputConnection(thresholdFilter->GetOutputPort());
//	imageCast->Update();
//
//	//不要随意update，占内存！！！！！！！！！！！
//	//thresholdFilter->GetOutput()->Delete();
//	//QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);
//
//	std::shared_ptr<Mask> newMask = std::make_shared<Mask>();
//	newMask->thresholdRange[0] = min;
//	newMask->thresholdRange[1] = max;
//	newMask->imageData = imageCast->GetOutput();//得到渲染管线的输出指针
//
//												//利用命名表命名
//	newMask->name = colorList[colorID].colorName;
//	newMask->color[0] = colorList[colorID].color[0] / 255.0;
//	newMask->color[1] = colorList[colorID].color[1] / 255.0;
//	newMask->color[2] = colorList[colorID].color[2] / 255.0;
//	colorID = (colorID + 1) % 16;
//
//	//newMask->visible = true;
//
//	//创建actor
//	vtkSmartPointer<vtkLookupTable> maskTable = vtkSmartPointer<vtkLookupTable>::New();
//	maskTable->SetNumberOfTableValues(2);
//	maskTable->SetRange(0, 1);
//	maskTable->SetNumberOfColors(2);
//	maskTable->SetTableValue(0, 0, 0, 0, 0);        //lookuptable貌似只影响颜色，
//	maskTable->SetTableValue(1, newMask->color[0], newMask->color[1], newMask->color[2], 0.4);
//	maskTable->Build();
//
//	//QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);
//
//	vtkSmartPointer<vtkImageMapToColors> maskMapToColors[3];
//
//	vtkSmartPointer<vtkImageActor> maskActor[3];  //Actor并不占太多的内存
//
//	vtkSmartPointer<vtkImageAlgorithmFilter> imageAlgorithm = vtkSmartPointer<vtkImageAlgorithmFilter>::New();
//	imageAlgorithm->SetInputData(newMask->imageData);
//
//	for (int i = 0; i < 3; ++i)   //切片
//	{
//		maskMapToColors[i] = vtkSmartPointer<vtkImageMapToColors>::New();   //没有爆炸
//		maskMapToColors[i]->SetLookupTable(maskTable);
//		maskMapToColors[i]->PassAlphaToOutputOn();
//		maskMapToColors[i]->SetActiveComponent(0);
//		//maskMapToColors[i]->SetInputConnection(imageCast->GetOutputPort());//不要再用Data用connection，血的教训！！！！
//		maskMapToColors[i]->SetInputConnection(imageAlgorithm->GetOutputPort());
//		maskMapToColors[i]->SetOutputFormatToRGBA();
//
//		int sliceOrientation = i;
//		int sliceIndex = this->imageViewer[i]->GetSlice();
//
//		int displayExtent[6];
//		for (int i = 0; i < 6; ++i)
//		{
//			displayExtent[i] = extent[i];
//		}
//
//		displayExtent[sliceOrientation * 2] = sliceIndex;  //设置切片
//		displayExtent[sliceOrientation * 2 + 1] = sliceIndex;
//
//
//		maskActor[i] = vtkSmartPointer<vtkImageActor>::New();
//		maskActor[i]->GetMapper()->SetInputConnection(
//			maskMapToColors[i]->GetOutputPort());
//		maskActor[i]->SetDisplayExtent(displayExtent);
//		newMask->imageActor[i] = maskActor[i];
//		this->imageViewer[i]->GetRenderer()->AddActor(maskActor[i]);  //add actor to renderer
//	}
//
//
//	//QMessageBox::warning(this, "what happen?", newMask->name, QMessageBox::Ok);
//	//this->maskPtrListPtr->push_back(newMask);//加入链表
//	//this->maskListWidget->updateMaskList();
//
//
//	this->maskPtrMapPtr.lock()->insert(newMask->name, newMask);  //只要有效就添加进去
//	this->maskListWidget->updateMaskList(newMask->name);   //mask表数据加入
//	emit updateMaskListWidget(newMask->name);
//	//this->currentMask = newMask;//当前要处理的mask
//	//this->currentMaskName = newMask->name;
//	this->currentMask = newMask;
//	//newMask->imageData->Delete();
//}

//为mask创建actor并导入显示to do vtkimagemask可以用吗，目前的mask是以imagedata为基础的
void QFourViewWidget::createActorForMask(std::weak_ptr<Mask> mask)
{
	int extent[6];
	int dims[3];
	this->ctImageData->GetExtent(extent);
	this->ctImageData->GetDimensions(dims);

	std::shared_ptr<Mask> newMask = mask.lock();
	//创建actor
	//lookuptable的用处是提供梯度值到颜色的映射，比如像素值为1表示的是绿色还是红色
	vtkSmartPointer<vtkLookupTable> maskTable = vtkSmartPointer<vtkLookupTable>::New();
	maskTable->SetNumberOfTableValues(2);
	maskTable->SetRange(0, 1);
	maskTable->SetNumberOfColors(2);
	maskTable->SetTableValue(0, 0, 0, 0, 0);        //lookuptable貌似只影响颜色，
	maskTable->SetTableValue(1, newMask->color[0], newMask->color[1], newMask->color[2], 0.4);
	maskTable->Build();

	//QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);

	vtkSmartPointer<vtkImageMapToColors> maskMapToColors[3];

	vtkSmartPointer<vtkImageActor> maskActor[3];  //Actor并不占太多的内存

	vtkSmartPointer<vtkImageAlgorithmFilter> imageAlgorithm = vtkSmartPointer<vtkImageAlgorithmFilter>::New();
	imageAlgorithm->SetInputData(newMask->imageData);
	
	for (int i = 0; i < 3; ++i)
	{
		maskMapToColors[i] = vtkSmartPointer<vtkImageMapToColors>::New();   //没有爆炸
		maskMapToColors[i]->SetLookupTable(maskTable);
		maskMapToColors[i]->PassAlphaToOutputOn();
		maskMapToColors[i]->SetActiveComponent(0);
		//maskMapToColors[i]->SetInputConnection(imageCast->GetOutputPort());//不要再用Data用connection，血的教训！！！！
		maskMapToColors[i]->SetInputConnection(imageAlgorithm->GetOutputPort());
		maskMapToColors[i]->SetOutputFormatToRGBA();

		int sliceOrientation = i;
		int sliceIndex = this->imageViewer[i]->GetSlice();

		int displayExtent[6];
		for (int i = 0; i < 6; ++i)
		{
			displayExtent[i] = extent[i];
		}

		displayExtent[sliceOrientation * 2] = sliceIndex;  //设置切片
		displayExtent[sliceOrientation * 2 + 1] = sliceIndex;


		maskActor[i] = vtkSmartPointer<vtkImageActor>::New();
		maskActor[i]->GetMapper()->SetInputConnection(
			maskMapToColors[i]->GetOutputPort());
		maskActor[i]->SetDisplayExtent(displayExtent);//在actor中设置切片
		newMask->imageActor[i] = maskActor[i];//保存actor到mask中
		this->imageViewer[i]->GetRenderer()->AddActor(maskActor[i]);  //add actor to renderer
		
	}

	this->reRender();
}
void QFourViewWidget::reRender()
{
	for (int i = 0; i != 3; ++i)
	{
		this->rwi_vtkImageWidget[i]->Render();
	}
}

void QFourViewWidget::updateLookUpTableForCreateMaskDialog(int min, int max)  //接受valueChange改变映射表,这是根据阈值范围来改变映射表，对区域提取出来的图像可能无效
{
	//QMessageBox::warning(this, "what happen?", QString("min:%1 max:%2").arg(min).arg(max), QMessageBox::Ok);
	//if(min==max)
	//	QMessageBox::warning(this, "what happen?", "OK1.2", QMessageBox::Ok);
	//定义颜色映射表
	vtkSmartPointer<vtkLookupTable> ctTable = vtkSmartPointer<vtkLookupTable>::New();
	ctTable->SetTableRange(this->ctImageData->GetScalarRange());
	ctTable->SetSaturationRange(0, 0);  //饱和度
	ctTable->SetHueRange(0, 0);  //色调
	ctTable->SetValueRange(0, 1); //明亮度
	ctTable->SetNumberOfColors(256);
	ctTable->Build();

	if (min != max)
	{
		int range[2];
		range[0] = ctTable->GetIndex(min);
		range[1] = ctTable->GetIndex(max);

		for (int i = range[0]; i < range[1]; ++i)
		{
			ctTable->SetTableValue(i, 0, 1, 0, 1); //暂定颜色为绿色
		}
	}


	for (int i = 0; i < 3; ++i)
	{
		this->imageViewer[i]->GetWindowLevel()->SetLookupTable(ctTable);
		this->imageViewer[i]->GetWindowLevel()->GetLookupTable()->Modified();
		this->imageViewer[i]->SetColorWindow(2057);
		this->imageViewer[i]->SetColorLevel(406);
		this->imageViewer[i]->GetRenderWindow()->GetInteractor()->Render();
	}
	//QMessageBox::warning(this, "what happen?", "OK1.3", QMessageBox::Ok);
}

void QFourViewWidget::getImageScalarRange(double *scalarRange)
{
	this->ctImageData->GetScalarRange(scalarRange);
}

void QFourViewWidget::setRenderForMaskAndObjectType()
{
	for (int i = 0; i < 3; ++i)
	{
		Mask::imageViewer[i] = this->imageViewer[i];
	}
	Object::viewWidget = this->vtk3DWidget;
}
void QFourViewWidget::initVariable()
{
	//默认一开始冻结窗口
	is_freeze = true;
	//3dview action
	planeWidgetVisibleAction=0;
	planeWidgetVisible=true;
	volumeRenderAction=0;
	volumeRenderClose = true;

	displayModel=Model::NORMAL;

	for (int i = 0; i != 3; ++i)
	{
		imagePickPointDims[i]=0; //图像index
		imagePickPointPosition[i]=0;//图像picker出来的实际坐标
		cursorPickPosition[i]=0;//光标的坐标
	}
	////edit Mask
	//penType=PenType::CIRCLE;
	//penWidth=0;
	//penModel=PenModel::DRAW;

}
void QFourViewWidget::setCTImageData(vtkSmartPointer<vtkImageData> ctImageData)
{
	this->ctImageData = ctImageData;
	//创建vtk四视图
	this->createVTKFourImageView();

	//对滚动条的初始化
	this->initScrollBar();

	this->is_freeze = false;//创捷四视图后解冻
}
void QFourViewWidget::createWidget()
{
	//初始化qviewWidget和qview
	for (int i = 0; i < 4; ++i)
	{
		this->viewWidget[i] = new QWidget(this);//这个widget要包含视图widget和toorbar或sroll
	}

	//三平面视图
	for (int i = 0; i != 3; ++i)
	{
		this->vtkImageWidget[i] = new QVTKImageWidget(this->viewWidget[i]);
		this->vtkImageWidget[i]->setIndex(i);
		//connect(qview[i], SIGNAL(mouseWheelEvent(int)), this, SLOT(updateSlice(int)));
	}
	//3d视图
	this->vtk3DWidget = new QVTK3DWidget(this->viewWidget[3]);
	this->vtk3DWidget->setIndex(3);

	//事件注册
	for (int i = 0; i != 3; ++i)
	{
		connect(this->vtkImageWidget[i], &QVTKImageWidget::mouseWheelEvent,
			[=](int delta)
		{
			if (this->is_freeze) return;//若窗口冻结则无操作
			OnThreeViewMouseWheelEvent(i, delta);       //vtkimagewidget鼠标滚轮切换->slice和cursor更新
		});
		
		
		connect(this->vtkImageWidget[i], &QVTKImageWidget::rightButtonPress_MouseMoveHappend,//鼠标右键按住滑动更新windowlevel
			[=](int startPositionX, int startPositionY,
				int currentPositionX, int currentPositionY, double initalW, double initalL)
		{
			if (this->is_freeze) return;
			OnThreeViewRightButtonPress_MouseMoveEvent(i, startPositionX, startPositionY,
				currentPositionX, currentPositionY, initalW, initalL);       
		});
		connect(this->vtkImageWidget[i], &QVTKImageWidget::leftButtonPressHappend,
			[=](int x,int y)
		{
			if (this->is_freeze) return;
			OnThreeViewLeftButtonPressEvent(i,x,y);       //点击定位切换响应
		});
		connect(this->vtkImageWidget[i], &QVTKImageWidget::leftButtonPressOrNot_MouseMoveHappend,
			[=](bool leftButtonPressEvent,int x,int y)
		{
			if (this->is_freeze) return;
			OnThreeViewLeftButtonPressOrNot_MouseMoveEvent(i, leftButtonPressEvent,x,y);       //用于editmask编辑模式的响应
		});
		connect(this->vtkImageWidget[i], SIGNAL(spaceKeyPressEvent(int, int)),//窗口放大缩小可以不冻结
			this, SLOT(OnFourViewSpaceKeyPressEvent(int,int)));
	}
	//控制窗口放大缩小，与其他视图关联也要写道四视图中
	connect(this->vtk3DWidget, SIGNAL(spaceKeyPressEvent(int, int)),
		this, SLOT(OnFourViewSpaceKeyPressEvent(int, int)));

	//this->createVTKFourImageView();//vtk视图创建

	QHBoxLayout *viewWidgetLayout[4];
	for (int i = 0; i != 3; ++i)
	{
		//scrollbar的connect和其他配置在有数据时再初始化
		this->viewScrollBar[i] = new QScrollBar(Qt::Vertical, this->viewWidget[i]);
		//this->crossActor[i] = this->crossActor[i];   ???

		viewWidgetLayout[i] = new QHBoxLayout;
		viewWidgetLayout[i]->addWidget(this->vtkImageWidget[i]);
		viewWidgetLayout[i]->addWidget(this->viewScrollBar[i]);

		viewWidget[i]->setLayout(viewWidgetLayout[i]);
	}



	this->viewToolBar = new QToolBar(viewWidget[3]);
	this->viewToolBar->setOrientation(Qt::Orientation::Vertical);
	//为toolbar添加action
	this->planeWidgetVisibleAction = new QAction(tr("PW"));//Show or hide plane widget
	connect(planeWidgetVisibleAction, SIGNAL(triggered()), this, SLOT(showOrHidePlaneWidget()));

	this->volumeRenderAction = new QAction(tr("VR"));//Volume Render
	connect(volumeRenderAction, SIGNAL(triggered()), this, SLOT(volumeRender()));
	this->viewToolBar->addAction(this->planeWidgetVisibleAction);
	this->viewToolBar->addSeparator();
	this->viewToolBar->addAction(this->volumeRenderAction);


	viewWidgetLayout[3] = new QHBoxLayout;
	viewWidgetLayout[3]->addWidget(this->vtk3DWidget);
	viewWidgetLayout[3]->addWidget(this->viewToolBar);

	this->viewWidget[3]->setLayout(viewWidgetLayout[3]);

	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(this->viewWidget[1]);
	topLayout->addWidget(this->viewWidget[2]);

	QHBoxLayout *downLayout = new QHBoxLayout;
	downLayout->addWidget(this->viewWidget[0]);
	downLayout->addWidget(this->viewWidget[3]);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(downLayout);

	this->setLayout(mainLayout);
}
void QFourViewWidget::initScrollBar()
{
	int dims[3];
	this->ctImageData->GetDimensions(dims);
	for (int i = 0; i != 3; ++i)
	{
		int range[2];
		this->imageViewer[i]->GetSliceRange(range);

		this->viewScrollBar[i]->setRange(range[0], range[1]);
		this->viewScrollBar[i]->setValue(dims[i] / 2);


		connect(this->viewScrollBar[i], &QScrollBar::sliderMoved,
			[=](int slice)
		{
			if (this->is_freeze) return;//被冻结时不操作
			updateVTKImageSliceFormScrollBar(i, slice);       //使用lambda超级方便，这个对vtk的事件改变value的事件也会响应
		});
	}
}
void QFourViewWidget::changeEditMaskCursorSize(int type,int realWidth)
{
	for (int i = 0; i != 3; ++i)
	{
		//显示方面
		//先由像素宽度转为真实宽度
		if (type == 1)
		{
			this->circleCursorSource[i]->SetRadius(sqrt(2)*realWidth / 2);
			this->circleCursorSource[i]->SetNumberOfSides(4);
		}
		else if (type == 0)
		{
			this->circleCursorSource[i]->SetRadius(realWidth / 2);
			this->circleCursorSource[i]->SetNumberOfSides(50);
		}
		//this->circleCursorSource[i]->SetRatio(height/width);
		//this->circleCursorSource[i]->SetMajorRadiusVector(width, height, 0);
		this->circleCursorSource[i]->Modified();
		this->vtkImageWidget[i]->GetRenderWindow()->Render();
		//响应像素方面
		//this->viewerCallback[i]->changeEditMaskPenMsg(type, width, /*height,*/ model);
	}
}
//根据ctimagedata初始化vtk各窗口
void QFourViewWidget::createVTKFourImageView()
{
	/*读取操作转移到外面
	//vtk_itk部分

	//itk读取
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	InputNamesGeneratorType::Pointer inputNames = InputNamesGeneratorType::New();
	inputNames->SetInputDirectory("W:/se2");

	const ReaderType::FileNamesContainer &filenames = inputNames->GetInputFileNames();

	ReaderType::Pointer itkReader = ReaderType::New();

	itkReader->SetImageIO(gdcmIO); //读取器绑定读取类型
	itkReader->SetFileNames(filenames);
	itkReader->Update();

	//itk图像转vtk图像
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(itkReader->GetOutput());
	connector->Update();     //需要update才可以读取



	//vtkSmartPointer< vtkDICOMImageReader > reader =
	//	vtkSmartPointer< vtkDICOMImageReader >::New();
	//reader->SetDirectoryName("W:/S70");
	//reader->Update();


	//转化itk的坐标方向到vtk的坐标方向
	vtkSmartPointer<vtkImageFlip> flipX = vtkSmartPointer<vtkImageFlip>::New();  //x坐标貌似是反的
	flipX->SetInputData(connector->GetOutput());
	flipX->SetFilteredAxis(0);
	flipX->ReleaseDataFlagOn();

	vtkSmartPointer<vtkImageFlip> flipY = vtkSmartPointer<vtkImageFlip>::New();
	flipY->SetInputConnection(flipX->GetOutputPort());
	//对平面图像来说y轴是反的，但对三维图像来说z轴也是反的
	flipY->SetFilteredAxis(1);
	//flipY->ReleaseDataFlagOn();
	flipY->Update();

	//vtkSmartPointer<vtkImageFlip> flipZ = vtkSmartPointer<vtkImageFlip>::New();
	//flipZ->SetInputData(flipY->GetOutput());
	////对平面图像来说y轴是反的，但对三维图像来说z轴也是反的
	//flipZ->SetFilteredAxis(2);
	//flipZ->Update();

	*/

	//图像信息提取
	int imageDims[3];
	double imageSpacing[3];
	double imageOrigin[3];
	double imageScalarRange[2];
	int imageExtent[6];

	//this->ctImageData = flipY->GetOutput();
	this->ctImageData->GetScalarRange(imageScalarRange);
	this->ctImageData->GetSpacing(imageSpacing);
	this->ctImageData->GetDimensions(imageDims);
	this->ctImageData->GetOrigin(imageOrigin);
	this->ctImageData->GetExtent(imageExtent);
	//绑定qt widget到三个平面视图上
	for (int i = 0; i != 3; i++)
	{
		this->imageViewer[i] = vtkSmartPointer< vtkImageViewer2 >::New();     //里面包含一个widget和一个reslicecurse对象
		this->vtkImageWidget[i]->setImageViewer(this->imageViewer[i]);
	}

	//vtkSmartPointer <vtkRenderWindowInteractor> interactor[3];

	//继续绑定
	for (int i = 0; i != 3; ++i)
	{
		//this->mouseWheelInteractorStyle[i] = vtkSmartPointer<vtkMouseWheelInteractorStyle>::New();
		vtkSmartPointer<vtkRenderWindow> renWin = this->vtkImageWidget[i]->GetRenderWindow();
		this->rwi_vtkImageWidget[i] = renWin->GetInteractor();  //此interactor来源于VTKWidget
		this->imageViewer[i]->SetupInteractor(this->rwi_vtkImageWidget[i]);
		this->imageViewer[i]->SetRenderWindow(renWin);//将qtwidget的renwindow绑定给vtk图像浏览器imageviewer
		//qview[i]->SetRenderWindow(riw[i]->GetRenderWindow());
	}

	////定义颜色映射表
	//vtkSmartPointer<vtkLookupTable> ctTable = vtkSmartPointer<vtkLookupTable>::New();
	//ctTable->SetTableRange(scalarRange);
	//ctTable->SetSaturationRange(0, 0);  //饱和度
	//ctTable->SetHueRange(0, 0);  //色调
	//ctTable->SetValueRange(0, 1); //明亮度
	//ctTable->SetNumberOfColors(256);
	//ctTable->Build();
	////table->GetNanColorAsUnsignedChars(); NanColor是当index取到非法数字时应该映射出的颜色，大多是在index<0和index>255的时候
	////vtkLookupTable::MapValue Given a scalar value v, return an rgba color value from lookup table.
	

	//定义3个imageViewer
	for (int i = 0; i < 3; i++)
	{
		// make them all share the same reslice cursor object.

		//riw[i]->SetResliceCursor(riw[0]->GetResliceCursor());  //?      //设定切分的对象为同一个对象
		this->imageViewer[i]->SetInputData(this->ctImageData);  //设定view输入数据
		this->imageViewer[i]->SetSliceOrientation(i);   //设定切割方向

		//riw[i]->SetResliceModeToAxisAligned();  //设定切割模式为轴对齐
		//riw[i]->SetLookupTable(ctTable);   //先建立颜色映射表再改变w和l，否则wl之前设置的值无效
		this->imageViewer[i]->SetColorWindow(2057);
		this->imageViewer[i]->SetColorLevel(406);
		this->imageViewer[i]->SetSlice(imageDims[i] / 2);//设定切分位置
		this->imageViewer[i]->GetRenderer()->SetBackground(0, 0, 0);

		//为定义十字线做准备
		this->imageViewer[i]->GetInteractorStyle()->AutoAdjustCameraClippingRangeOn();
		this->imageViewer[i]->GetRenderer()->SetLayer(0);
		this->imageViewer[i]->GetRenderWindow()->SetNumberOfLayers(3);

	}

	//方向调节
	this->imageViewer[1]->GetRenderer()->GetActiveCamera()->Azimuth(180);
	//this->imageViewer[1]->GetRenderer()->GetActiveCamera()->zo
	//vtkSmartPointer<vtkActor> lineActor[3];
	//vtkSmartPointer<vtkRenderer> lineRen[3];
	//vtkSmartPointer<vtkRegularPolygonSource> circleCursorSource[3];//改大小
	//vtkSmartPointer<vtkActor> circleCursorActor[3];//改位置

	double centerPosition[3];
	centerPosition[0] = imageOrigin[0] + imageSpacing[0] * (imageDims[0] / 2);
	centerPosition[1] = imageOrigin[1] + imageSpacing[1] * (imageDims[1] / 2);
	centerPosition[2] = imageOrigin[2] + imageSpacing[2] * (imageDims[2] / 2);

	//定义十字光标和circle光标
	for (int i = 0; i < 3; ++i)
	{
		//十字光标
		//只定义相对位置，真正的polydata的位置由actor定义
		vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
		int size = 2000;
		if (i == 0)//定义yz平面点的关系
		{
			pts->InsertNextPoint(0, -size / 2, 0);
			pts->InsertNextPoint(0, size / 2, 0);
			pts->InsertNextPoint(0, 0, -size / 2);
			pts->InsertNextPoint(0, 0, size / 2);
		}
		else if (i == 1)//定义xz平面点的关系
		{
			pts->InsertNextPoint(-size / 2, 0, 0);
			pts->InsertNextPoint(size / 2, 0, 0);
			pts->InsertNextPoint(0, 0, -size / 2);
			pts->InsertNextPoint(0, 0, size / 2);
		}
		else if (i == 2)//定义xy平面的点关系
		{
			pts->InsertNextPoint(-size / 2, 0, 0); 
			pts->InsertNextPoint(size / 2, 0, 0);
			pts->InsertNextPoint(0, -size / 2, 0);
			pts->InsertNextPoint(0, size / 2, 0);
		}

		//点连线
		vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
		cells->Allocate(cells->EstimateSize(2, 2));

		vtkIdType ptid[2];
		ptid[0] = 0; ptid[1] = 1;       // horizontal segment
		cells->InsertNextCell(2, ptid);
		ptid[0] = 2; ptid[1] = 3;       // vertical segment
		cells->InsertNextCell(2, ptid);

		//颜色
		unsigned char colorH[3] = { 0,0,0 };
		unsigned char colorV[3] = { 0,0,0 };
		if (i == 0)
		{
			colorH[2] = 255;  //设为i=2窗口的颜色
			colorV[1] = 255;
		}
		else if (i == 1)
		{
			colorH[2] = 255;
			colorV[0] = 255;
		}
		else if (i == 2)
		{
			colorH[1] = 255;
			colorV[0] = 255;
		}

		vtkSmartPointer<vtkUnsignedCharArray> colors =
			vtkSmartPointer<vtkUnsignedCharArray>::New();
		colors->SetNumberOfComponents(3);
		colors->InsertNextTupleValue(colorH);
		colors->InsertNextTupleValue(colorV);

		vtkSmartPointer<vtkPolyData> linePolyData = vtkSmartPointer<vtkPolyData>::New();
		linePolyData->SetLines(cells);
		linePolyData->SetPoints(pts);
		linePolyData->GetCellData()->SetScalars(colors);

		vtkSmartPointer<vtkPolyDataMapper> lineMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		lineMapper->SetInputData(linePolyData);

		this->crossCursorActor[i] = vtkSmartPointer<vtkActor>::New();
		this->crossCursorActor[i]->SetMapper(lineMapper);
		this->crossCursorActor[i]->SetOrigin(this->crossCursorActor[i]->GetOrigin());
		this->crossCursorActor[i]->SetPosition(centerPosition);

		//circle光标
		double normal[3] = { 0,0,0 };
		normal[i] = 1;//设定选择光标朝向的方向，三个视图朝向方向不一样

		this->circleCursorSource[i] = vtkSmartPointer<vtkRegularPolygonSource>::New();
		this->circleCursorSource[i]->GeneratePolygonOff();
		this->circleCursorSource[i]->SetNumberOfSides(50);
		this->circleCursorSource[i]->SetCenter(0, 0, 0);
		this->circleCursorSource[i]->SetNormal(normal);

		this->circleCursorSource[i]->SetRadius(1);  //光标半径

		vtkSmartPointer<vtkPolyDataMapper> mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(this->circleCursorSource[i]->GetOutputPort());

		this->circleCursorActor[i] = vtkSmartPointer<vtkActor>::New();
		this->circleCursorActor[i]->SetMapper(mapper);
		this->circleCursorActor[i]->SetPosition(centerPosition);
		this->circleCursorActor[i]->GetProperty()->SetColor(0.8, 0.8, 0.8);
		this->circleCursorActor[i]->SetVisibility(0);//设定actor的可视或不可视
		this->circleCursorActor[i]->RotateWXYZ(45, normal[0], normal[1], normal[2]);

		//对cursorRen进行设置
		this->cursorRen[i] = vtkSmartPointer<vtkRenderer>::New();//该渲染环境专门对十字光标和圆形光标进行渲染
		this->cursorRen[i]->AddActor(this->crossCursorActor[i]);
		this->cursorRen[i]->AddActor(this->circleCursorActor[i]);
		this->cursorRen[i]->SetInteractive(0);  //important
		this->cursorRen[i]->SetLayer(1);//透明

		this->imageViewer[i]->GetRenderWindow()->AddRenderer(this->cursorRen[i]);//在renderwindow中新加入光标渲染器

		//相机同步移动操作
		this->cursorRen[i]->GetActiveCamera()->ShallowCopy(this->imageViewer[i]->GetRenderer()->GetActiveCamera());//同步相机

		vtkSmartPointer<vtkSynchronizeCameraCallback> cameraCallback = vtkSmartPointer<vtkSynchronizeCameraCallback>::New();
		cameraCallback->cursorRen = this->cursorRen[i];

		this->imageViewer[i]->GetRenderer()->GetActiveCamera()->AddObserver(vtkCommand::ModifiedEvent, cameraCallback);//image camera更新，lineRen相机同步更新

	}

	//绑定和设置3d窗口

	this->ren_3dWidget = vtkSmartPointer< vtkRenderer >::New();
	this->vtk3DWidget->GetRenderWindow()->AddRenderer(ren_3dWidget);

	vtkSmartPointer<vtkRenderWindowInteractor> iren = this->vtk3DWidget->GetInteractor();
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	iren->SetInteractorStyle(style);//设定相机交互模式

	//定义外边框
	vtkSmartPointer<vtkOutlineFilter> outlineData = vtkSmartPointer<vtkOutlineFilter>::New();
	outlineData->SetInputData(this->ctImageData);
	vtkSmartPointer<vtkPolyDataMapper> mapOutline = vtkSmartPointer<vtkPolyDataMapper>::New();
	mapOutline->SetInputConnection(outlineData->GetOutputPort());
	vtkSmartPointer<vtkActor> outline = vtkSmartPointer<vtkActor>::New();
	outline->SetMapper(mapOutline);
	outline->GetProperty()->SetColor(0, 0, 0);

	//定义planeWidget和imageViewer的坐标拾取类
	this->picker = vtkSmartPointer<vtkCellPicker>::New();
	this->picker->SetTolerance(0.005);

	//建立vtk事件与qt slot之间的联系，用于操作planewidget来更新三视图
	this->imagePlaneWidgetEventToQSLOTConnections = vtkSmartPointer<vtkEventQtSlotConnect>::New();
	//定义planeWidget
	for (int i = 0; i < 3; ++i)
	{
		this->imagePlaneWidget[i] = vtkSmartPointer<vtkImagePlaneWidget>::New();;
		this->imagePlaneWidget[i]->DisplayTextOn();
		this->imagePlaneWidget[i]->SetInputData(this->ctImageData);
		this->imagePlaneWidget[i]->SetPlaneOrientation(i);
		this->imagePlaneWidget[i]->SetSliceIndex(imageDims[i] / 2);//?
		this->imagePlaneWidget[i]->SetPicker(this->picker);//用于点击响应
		this->imagePlaneWidget[i]->SetKeyPressActivationValue('x' + i);
		double color[3] = { 0,0,0 };
		color[i] = 1;
		this->imagePlaneWidget[i]->GetPlaneProperty()->SetColor(color);
		this->imagePlaneWidget[i]->SetInteractor(iren);//将imageplane放入iren代表的窗口
		this->imagePlaneWidget[i]->SetLookupTable(this->imagePlaneWidget[0]->GetLookupTable());  //用自己的颜色映射表
		//lut:lookuptable与windowlevel有关，共享相同的颜色映射表可以使windowlevel的表现一致
		this->imagePlaneWidget[i]->SetWindowLevel(2057, 406, 0);

	}
	
	//一旦产生交互事件就更新切片
	this->imagePlaneWidgetEventToQSLOTConnections->Connect(this->imagePlaneWidget[0], vtkCommand::InteractionEvent,
		this, SLOT(updateSliceFromImagePlaneWidget0()));
	this->imagePlaneWidgetEventToQSLOTConnections->Connect(this->imagePlaneWidget[1], vtkCommand::InteractionEvent,
		this, SLOT(updateSliceFromImagePlaneWidget1()));
	this->imagePlaneWidgetEventToQSLOTConnections->Connect(this->imagePlaneWidget[2], vtkCommand::InteractionEvent,
		this, SLOT(updateSliceFromImagePlaneWidget2()));

	ren_3dWidget->AddActor(outline);
	ren_3dWidget->SetBackground(0.1, 0.1, 0.2);

	this->imagePlaneWidget[0]->On();
	this->imagePlaneWidget[1]->On();
	this->imagePlaneWidget[2]->On();

	//对该渲染器的摄像机进行调整
	vtkSmartPointer<vtkCamera> camera = ren_3dWidget->GetActiveCamera();
	camera->Elevation(110);
	camera->SetViewUp(0, 0, -1);
	camera->Roll(180);
	camera->Azimuth(45);
	ren_3dWidget->ResetCameraClippingRange();

	//显示vtk各窗口
	for (int i = 0; i != 3; ++i)
	{
		this->vtkImageWidget[i]->show();
	}
	this->vtk3DWidget->show();
}

//void QFourViewWidget::setCurrentMask(std::weak_ptr<Mask> mask)
//{
//	this->currentMask = mask;
//}
//void QFourViewWidget::updateCurrentMask(std::weak_ptr<Mask> mask)
//{
//	this->currentMask = mask;
//	emit currentMaskChanged(this->currentMask);
//}

void QFourViewWidget::setModel(int model)
{
	//关闭edit_mask操作预处理
	if (this->displayModel==Model::EDITMASK&&this->displayModel!=model)
	{
		//切换光标
		//显示新光标
		//断开连接
		for (int i = 0; i != 3; ++i)
		{
			this->vtkImageWidget[i]->setCursor(Qt::ArrowCursor);
			this->circleCursorActor[i]->SetVisibility(0);
			this->circleCursorActor[i]->Modified();
			this->vtkImageWidget[i]->GetRenderWindow()->Render();

			disconnect(vtkImageWidget[i], 0, 0, 0);
		}
	}
	//QMessageBox::warning(NULL, "what happen?", QString("setModel::displayModel::%1").arg(displayModel), QMessageBox::Ok);
	this->displayModel = (Model)model;
	if (this->displayModel == Model::REGIONGROWING)
	{
		//this->originalMask = this->currentMask;  //originalMask以后可以自己设置
		for (int i = 0; i != 3; ++i)
		{
			this->vtkImageWidget[i]->setCursor(Qt::CrossCursor);
		}
	}
	if (this->displayModel == Model::NORMAL)
	{
		//this->originalMask = this->currentMask;  //originalMask以后可以自己设置
		for (int i = 0; i != 3; ++i)
		{
			this->vtkImageWidget[i]->setCursor(Qt::ArrowCursor);
		}
	}
	if (this->displayModel == Model::EDITMASK)
	{
		for (int i = 0; i != 3; ++i)
		{
			this->vtkImageWidget[i]->setCursor(Qt::CrossCursor);
		}

		//switchVtkClickModel(2);//edit mask 模式
		//设置空光标
		//刷新主窗口command
		for (int i = 0; i != 3; ++i)
		{
			//this->viewerCallback[i]->currentMask_editMask = this->currentMask;//当前处理的mask赋值
			//this->qview[i]->setCursor(Qt::CrossCursor);
			//this->circleCursorActor[i]->SetVisibility(1);
			//this->circleCursorActor[i]->Modified();
			//this->qview[i]->GetRenderWindow()->Render();
			connect(this->vtkImageWidget[i], &QVTKImageWidget::showCursorActor,
				[=]()
			{
				this->circleCursorActor[i]->SetVisibility(true);
				this->cursorRen[i]->Render();
				this->vtkImageWidget[i]->GetInteractor()->Render();
			});
			connect(this->vtkImageWidget[i], &QVTKImageWidget::hideCursorActor,
				[=]()
			{
				this->circleCursorActor[i]->SetVisibility(false);
				this->cursorRen[i]->Render();
				this->vtkImageWidget[i]->GetInteractor()->Render();
			});
		}
	}
}
//十字光标定位
void QFourViewWidget::crossCursorLocateModel(int viewIndex,int x,int y)
{
	this->setCurrentCoordsMsg(viewIndex,x,y);//获取ImagePointDims和ImagePointPosition
	//QString output=QString("%1 %2 %3 %4").arg(this->imagePickPointDims[0]).arg(this->imagePickPointDims[1]).arg(this->imagePickPointDims[2]).arg(viewIndex);
	//QMessageBox::warning(NULL, "what happen?", output, QMessageBox::Ok);
	//lineActor[0]->SetPosition(ImagePointPosition[0], ImagePointPosition[1], bounds[5]-ImagePointPosition[2]);//0和1上下翻转一次，真正的坐标也要翻转

	//根据ImagePointDims和ImagePointPosition更新当前切面包括光标
	for (int i = 0; i != 3; ++i)
	{
		if (i != viewIndex)
		{
			this->updataMaskSlice(i, this->imagePickPointDims[i]); //更新mask
			this->updateImageViewSlice(i, imagePickPointDims[i]);
			this->updatePlaneWidget(i, imagePickPointDims[i]);
			this->updateScrollBar(i, imagePickPointDims[i]);																					//}
		}

		//更新十字坐标
		crossCursorActor[i]->SetPosition(this->imagePickPointPosition);//每一个窗口的actor的坐标都变化
		//cursorRen[i]->Render();
		this->rwi_vtkImageWidget[i]->Render();
	}
}
void QFourViewWidget::regionRrowingModel(int viewIndex,int x,int y)
{
	this->setCurrentCoordsMsg(viewIndex,x,y);//获取ImagePointDims和ImagePointPosition
	QVector<int> dims;
	dims.append(this->imagePickPointDims[0]);
	dims.append(this->imagePickPointDims[1]);
	dims.append(this->imagePickPointDims[2]);
	emit pickImageDims(dims);
	//QMessageBox::warning(NULL, "what happen?", "regionRrowingModel", QMessageBox::Ok);
}


//响应
void QFourViewWidget::editMaskModel_click(int viewIndex,int x,int y)
{
	this->setCurrentCoordsMsg(viewIndex,x,y);//获取ImagePointDims和ImagePointPosition

	QVector<int> pickPointDims;
	pickPointDims.append({ this->imagePickPointDims[0],this->imagePickPointDims[1],this->imagePickPointDims[2] });
	emit editMaskClick(viewIndex, pickPointDims);

	//auto currentImageData = this->currentMask.lock()->imageData;
	//drawWholePixel(viewIndex,this->imagePickPointDims, currentImageData);
	//for (int i = 0; i < 3; ++i)
	//{
	//	//this->currentMask_editMask.lock()->imageActor[i]->Modified();
	//	this->imageViewer[i]->Render();
	//}

	//to do reRender要放到绘制后面
	//this->reRender();
}
void QFourViewWidget::editMaskModel_mouseMove(int viewIndex,bool leftButtonPressEvent,int x,int y)
{
	int beforeImagePointDims[3] = { imagePickPointDims[0],imagePickPointDims[1], imagePickPointDims[2] };

	this->setCurrentCoordsMsg(viewIndex,x,y);//获取ImagePointDims和ImagePointPosition


	//更新circle坐标，仅仅更新平面，circle一定要显示在3d坐标中否则放大比较困难

	this->circleCursorActor[viewIndex]->SetPosition(this->cursorPickPosition);
	this->circleCursorActor[viewIndex]->Modified();
	this->rwi_vtkImageWidget[viewIndex]->Render();

	if (leftButtonPressEvent)
	{
		QVector<int> beforePointDims;
		beforePointDims.append({ beforeImagePointDims[0],beforeImagePointDims[1],beforeImagePointDims[2] });
		QVector<int> pickPointDims;
		pickPointDims.append({ imagePickPointDims[0],imagePickPointDims[1],imagePickPointDims[2] });
		emit editMaskClickMove(viewIndex, beforePointDims, pickPointDims);
		//BresenhamFill(viewIndex,beforeImagePointDims, imagePickPointDims);//直线填充
		//this->reRender();
	}
}

void QFourViewWidget::OnThreeViewLeftButtonPressEvent(int viewIndex,int x,int y)
{
	//QMessageBox::warning(NULL, "what happen?", QString("%1").arg(displayModel), QMessageBox::Ok);
	if (this->displayModel == Model::NORMAL)  //默认的定位模式
	{
		this->crossCursorLocateModel(viewIndex,x,y);
		//this->AbortFlagOff();
	}
	//开启区域提取功能
	else if (this->displayModel == Model::REGIONGROWING)
	{
		//QMessageBox::warning(NULL, "what happen?", "displayModel regiongrowing", QMessageBox::Ok);
		this->regionRrowingModel(viewIndex,x,y);
	
	}
	//编辑mask功能
	else if (this->displayModel == Model::EDITMASK)
	{
		//QMessageBox::warning(NULL, "what happen?", "1", QMessageBox::Ok);
		this->editMaskModel_click(viewIndex,x,y);
	}
}

void QFourViewWidget::OnThreeViewLeftButtonPressOrNot_MouseMoveEvent(int viewIndex,bool leftButtonPressEvent,int x,int y)
{
	if (this->displayModel == Model::EDITMASK)
	{
		this->editMaskModel_mouseMove(viewIndex, leftButtonPressEvent,x,y);
	}
}

void QFourViewWidget::updateSliceFromImagePlaneWidget0()
{
	updateThreeViewSliceFromImagePlaneWidget(0);
}
void QFourViewWidget::updateSliceFromImagePlaneWidget1()
{
	updateThreeViewSliceFromImagePlaneWidget(1);
}
void QFourViewWidget::updateSliceFromImagePlaneWidget2()
{
	updateThreeViewSliceFromImagePlaneWidget(2);
}
void QFourViewWidget::updateThreeViewSliceFromImagePlaneWidget(int viewIndex)
{
	//int ImagePointDims[3];
	int slice;
	slice = this->imagePlaneWidget[viewIndex]->GetSliceIndex();

	//改变mask
	this->updataMaskSlice(viewIndex, slice);

	//改变imageView
	this->updateImageViewSlice(viewIndex,slice);

	this->updateScrollBar(viewIndex, slice);

	this->updateCursor(viewIndex, slice);

	//for (int i = 0; i < 3; ++i)
	//{
	//	crossCursorActor[i]->GetPosition()[index] = origin[index] + spacing[index] * sliceIndex;   //index转点要加上origin
	//	crossCursorActor[i]->Modified();
	//	cursorRen[i]->Render();
	//	//this->RIV[index]->GetRenderWindow()->GetInteractor()->Render();
	//	interactor[i]->Render();
	//}

}

void QFourViewWidget::OnFourViewSpaceKeyPressEvent(int viewIndex, int model)
{
	this->zoomOrRecoverWidget(viewIndex, model);
}

void QFourViewWidget::zoomOrRecoverWidget(int viewIndex, int model)
{

		if (model == ZOOM)
		{
			if (viewIndex >= 0 && viewIndex < 3)
			{
				this->vtk3DWidget->hide();
				this->viewToolBar->hide();
				for (int i = 0; i != 3; ++i)
				{
					if (i != viewIndex)
					{
						this->vtkImageWidget[i]->hide();
						this->viewScrollBar[i]->hide();
					}
				}
			}
			else if (viewIndex == 3)
			{
				for (int i = 0; i != 3; ++i)
				{
					this->vtkImageWidget[i]->hide();
					this->viewScrollBar[i]->hide();
				}
			}
		}
		else if (model == RECOVER)
		{
			for (int i = 0; i != 3; ++i)
			{
				this->vtkImageWidget[i]->show();
				this->viewScrollBar[i]->show();
			}
			this->vtk3DWidget->show();
			this->viewToolBar->show();
		}

}

void QFourViewWidget::updateWindowLevel(int viewIndex, int startPositionX, int startPositionY,
	int currentPositionX, int currentPositionY, double initalW, double initalL)
{
	vtkRenderWindowInteractor *rwi = this->imageViewer[viewIndex]->GetRenderWindow()->GetInteractor();
	int *size = this->imageViewer[viewIndex]->GetRenderer()->GetSize();

	double window = initalW;
	double level = initalL;

	// Compute normalized delta

	double dx = (currentPositionX -
		startPositionX) * 4.0 / size[0];
	double dy = (startPositionY -
		currentPositionY) * 4.0 / size[1];

	// Scale by current values

	if (fabs(window) > 0.01)
	{
		dx = dx * window;
	}
	else
	{
		dx = dx * (window < 0 ? -0.01 : 0.01);
	}
	if (fabs(level) > 0.01)
	{
		dy = dy * level;
	}
	else
	{
		dy = dy * (level < 0 ? -0.01 : 0.01);
	}

	// Abs so that direction does not flip

	if (window < 0.0)
	{
		dx = -1 * dx;
	}
	if (level < 0.0)
	{
		dy = -1 * dy;
	}

	// Compute new window level

	double newWindow = dx + window;
	double newLevel = level - dy;

	if (newWindow < 0.01)
	{
		newWindow = 0.01;
	}

	QString test = QString("Window: %1 Level: %2")
		.arg(newWindow)
		.arg(newLevel);
	//this->statusBarLabel->setText(test);
	for (int i = 0; i != 3; ++i)
	{
		this->imageViewer[i]->SetColorWindow(newWindow);
		this->imageViewer[i]->SetColorLevel(newLevel);
		this->imageViewer[i]->GetRenderWindow()->GetInteractor()->Render();
	}
}
void QFourViewWidget::OnThreeViewRightButtonPress_MouseMoveEvent(int viewIndex, int startPositionX, int startPositionY,
	int currentPositionX, int currentPositionY, double initalW, double initalL)
{
	this->updateWindowLevel(viewIndex, startPositionX, startPositionY,
		currentPositionX, currentPositionY, initalW, initalL);
}


void QFourViewWidget::OnThreeViewMouseWheelEvent(int viewIndex, int delta)
{
	int slice = this->imageViewer[viewIndex]->GetSlice();  //有一个函数还在响应导致+1和-1

	if (delta < 0 && slice != this->imageViewer[viewIndex]->GetSliceMin()/*&&index!=2*/)
	{
		--slice;
		this->updateFourViewSlice(viewIndex, slice);
	}
	else if (delta > 0 && slice != this->imageViewer[viewIndex]->GetSliceMax())
	{
		++slice;
		this->updateFourViewSlice(viewIndex, slice);
	}
}


void QFourViewWidget::updateCursor(int index, int slice)
{
	double spacing[3];
	double origin[3];
	ctImageData->GetSpacing(spacing);
	ctImageData->GetOrigin(origin);
	for (int i = 0; i < 3; ++i)
	{
		crossCursorActor[i]->GetPosition()[index] = origin[index] + spacing[index] * slice;
		crossCursorActor[i]->Modified();
		circleCursorActor[i]->GetPosition()[index] = origin[index] + spacing[index] * slice;
		circleCursorActor[i]->Modified();
		this->imageViewer[i]->Render();
		//interactor[i]->Render();
	}
}

void QFourViewWidget::updatePlaneWidget(int viewIndex, int slice)
{
	this->imagePlaneWidget[viewIndex]->SetSliceIndex(slice);
	this->imagePlaneWidget[0]->GetInteractor()->Render();
}
void QFourViewWidget::updataMaskSlice(int viewIndex, int slice)
{
	int extent[6];
	this->ctImageData->GetExtent(extent);
	extent[viewIndex * 2] = slice;
	extent[viewIndex * 2 + 1] = slice;

	QMap<QString, std::shared_ptr<Mask>>::const_iterator map_iterator;
	auto begin = this->maskPtrMapPtr.lock()->constBegin();
	auto end = this->maskPtrMapPtr.lock()->constEnd();
	for (map_iterator = begin; map_iterator != end; ++map_iterator) {
		map_iterator.value()->imageActor[viewIndex]->SetDisplayExtent(extent);
	}

}
void QFourViewWidget::updateImageViewSlice(int viewIndex, int slice)
{
	this->imageViewer[viewIndex]->SetSlice(slice);
}
void QFourViewWidget::updateScrollBar(int viewIndex, int slice)
{
	this->viewScrollBar[viewIndex]->setValue(this->imageViewer[viewIndex]->GetSliceMax() - slice);//scroll反馈，没发现滚动条值反向，所以手动调整
}
//根据单个窗口的slice变化改变所有窗口的slice和光标位置
void QFourViewWidget::updateFourViewSlice(int viewIndex, int slice)
{
	this->updataMaskSlice(viewIndex, slice);
	this->updateImageViewSlice(viewIndex, slice);
	this->updatePlaneWidget(viewIndex, slice);
	this->updateScrollBar(viewIndex, slice);
	this->updateCursor(viewIndex, slice);
}

void QFourViewWidget::updateVTKImageSliceFormScrollBar(int viewIndex, int scrollIndex)
{
	//QMessageBox::warning(NULL, ".", "what?", QMessageBox::Ok);
	int maxIndex = this->imageViewer[viewIndex]->GetSliceMax();   //没发现滚动条值反向，所以手动调整
	int slice = maxIndex - scrollIndex;   //计算为真正的坐标


	if (slice == this->imageViewer[viewIndex]->GetSlice())   //vtk改变scroll也会发出valuechange，这个防止无用的连续响应
	{
		return;
	}
	else
	{
		updateFourViewSlice(viewIndex, slice);
	}
}

QFourViewWidget::~QFourViewWidget() {
	
}


//bool QFourViewWidget::drawOnePixel(int pixDims[3], int model, vtkSmartPointer<vtkImageData> imageData)
//{
//	int dims[3];
//	this->ctImageData->GetDimensions(dims);
//	if (pixDims[0] >= 0 && pixDims[0] < dims[0]
//		&& pixDims[1] >= 0 && pixDims[1] < dims[1]
//		&& pixDims[2] >= 0 && pixDims[2] < dims[2])
//	{
//		unsigned char * pixel = (unsigned char *)(imageData->GetScalarPointer(pixDims));
//		*pixel = model;
//		return true;
//	}
//	return false;
//	//return false;
//}

//根据传入的精确坐标来改变imagepositon和dims
int QFourViewWidget::setCurrentImagePositionAndDims(double *precisePosition)
{
	// vtkImageData will find the nearest implicit point to q
	//
	vtkIdType ptId = this->ctImageData->FindPoint(precisePosition);//findpoint会找到距离最近的点的id
	//这个ptId是longlong型返回点集的索引

	if (ptId == -1)//没找到就返回0
	{
		return 0;
	}

	double closestPt[3];
	this->ctImageData->GetPoint(ptId, closestPt);//根据id获取最近点位置

	double origin[3];
	this->ctImageData->GetOrigin(origin);
	double spacing[3];
	this->ctImageData->GetSpacing(spacing);
	int extent[6];
	this->ctImageData->GetExtent(extent);
	int dims[3];
	this->ctImageData->GetDimensions(dims);
	double bounds[6];
	this->ctImageData->GetBounds(bounds);

	int iq[3];
	int iqtemp;
	//根据该点计算dims并更新
	for (int i = 0; i < 3; i++)
	{
		// compute world to image coords
		iqtemp = vtkMath::Round((closestPt[i] - origin[i]) / spacing[i]);

		// we have a valid pick already, just enforce bounds check
		iq[i] = (iqtemp < extent[2 * i]) ? extent[2 * i] : ((iqtemp > extent[2 * i + 1]) ? extent[2 * i + 1] : iqtemp);

		// compute image to world coords
		this->imagePickPointDims[i] = iq[i];
		this->imagePickPointPosition[i] = closestPt[i];
	}

	return 1;
}

//拾取点击坐标更新定位坐标cursorPickPosition
int QFourViewWidget::setCurrentCoordsMsg(int viewIndex,int x,int y)
{
	//初始化坐标响应，要获取被点击view的交互器
	vtkSmartPointer<vtkRenderWindowInteractor> currentInteractor =
		this->imageViewer[viewIndex]->GetRenderWindow()->GetInteractor();
	vtkRenderer* renderer = this->imageViewer[viewIndex]->GetRenderer();
	//vtkImageActor* actor = this->RIV[index]->GetImageActor();
	//vtkInteractorStyle *style = vtkInteractorStyle::SafeDownCast(
	//	currentInteractor->GetInteractorStyle());

	// Pick at the mouse location provided by the interactor
	//QString output = QString("x:%1 y:%2").arg(currentInteractor->GetEventPosition()[0]).arg(currentInteractor->GetEventPosition()[1]);
	//QMessageBox::warning(this, "what happen?", output, QMessageBox::Ok);

	//Qt:y的位置要倒置为vtk:y
	//this->vtkImageWidget[viewIndex]->height()

	this->picker->Pick(/*currentInteractor->GetEventPosition()[0]*/x,
		/*currentInteractor->GetEventPosition()[1]*/this->vtkImageWidget[viewIndex]->height()-y,
		0.0, renderer);   //获取处于该坐标点的位置信息，传到pick上，生成图像信息

	// Get the world coordinates of the pick
	this->picker->GetPickPosition(this->cursorPickPosition);
	int found;
	//根据拾取到的点的坐标修改当前拾取的位置和dims
	found = this->setCurrentImagePositionAndDims(this->cursorPickPosition);

	return found;
}



//EllipseMsg QFourViewWidget::getPixelEllipseMsg(int index, int width, double *spacing)//设定的宽度为像素椭圆的长轴
//{
//	int a = 0;
//	int b = 0;
//	if (index == 0 || index == 1)
//	{
//		a = width / 2.0;//长半轴
//		b = (width*spacing[0]) / (2 * spacing[2]);//短半轴
//	}
//	else if (index == 2)
//	{
//		a = width / 2.0;//长半轴
//		b = a;
//	}
//	return EllipseMsg(a, b);
//}
//SquareMsg QFourViewWidget::getPixelSquareMsg(int index, int width, double *spacing)//设定的宽度为像素椭圆的长轴
//{
//	int wr = 0;
//	int hr = 0;
//	if (index == 0 || index == 1)
//	{
//		wr = width / 2.0;//长半轴
//		hr = (width*spacing[0]) / (2 * spacing[2]);//短半轴
//	}
//	else if (index == 2)
//	{
//		wr = width / 2.0;//长半轴
//		hr = wr;
//	}
//	return SquareMsg(wr, hr);
//}
//
//void QFourViewWidget::drawWholePixel(int viewIndex, int x, int y, int slice, vtkSmartPointer<vtkImageData> imageData)
//{
//	double spacing[3];
//	imageData->GetSpacing(spacing);
//
//	int *currentPixelXPointer = NULL;
//	int *currentPixelYPointer = NULL;
//	int *currentPixelSlicePointer = NULL;
//	int currentPixelDims[3];
//	int middlePixelSlice = slice, middlePixelX = x, middlePixelY = y;
//
//	if (viewIndex == 0)
//	{
//		currentPixelSlicePointer = &currentPixelDims[0];
//		currentPixelXPointer = &currentPixelDims[1];
//		currentPixelYPointer = &currentPixelDims[2];
//	}
//	else if (viewIndex == 1)
//	{
//		currentPixelSlicePointer = &currentPixelDims[1];
//		currentPixelXPointer = &currentPixelDims[0];
//		currentPixelYPointer = &currentPixelDims[2];
//	}
//	else if (viewIndex == 2)
//	{
//		currentPixelSlicePointer = &currentPixelDims[2];
//		currentPixelXPointer = &currentPixelDims[0];
//		currentPixelYPointer = &currentPixelDims[1];
//	}
//
//
//	if (this->penWidth == 1 || this->penWidth == 2 || this->penWidth == 3)
//	{
//		*currentPixelSlicePointer = middlePixelSlice;
//		*currentPixelXPointer = middlePixelX;
//		*currentPixelYPointer = middlePixelY;
//		this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//	}
//	else if (this->penType == CIRCLE)
//	{
//		auto ellipseMsg = this->getPixelEllipseMsg(viewIndex, this->penWidth, spacing);
//		for (int i = 0; i != ellipseMsg.b; ++i)
//		{
//			int count = getXFromEllipseY(ellipseMsg.a, ellipseMsg.b, i);
//			for (int j = 0; j != count; ++j)
//			{
//				*currentPixelSlicePointer = middlePixelSlice;
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//			}
//		}
//	}
//	else if (this->penType == SQUARE)
//	{
//		auto squareMsg = this->getPixelSquareMsg(viewIndex, this->penWidth, spacing);
//		for (int i = 0; i != squareMsg.hr; ++i)
//		{
//			for (int j = 0; j != squareMsg.wr; ++j)
//			{
//				*currentPixelSlicePointer = middlePixelSlice;
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//			}
//		}
//	}
//
//
//
//	imageData->Modified();
//}
//void QFourViewWidget::drawWholePixel(int viewIndex, const int middlePixelDims[3], vtkSmartPointer<vtkImageData> imageData)
//{
//	double spacing[3];
//	imageData->GetSpacing(spacing);
//
//	//QString s = QString("x: %1 y: %2 z: %3").arg(middlePixelDims[0]).arg(middlePixelDims[1]).arg(middlePixelDims[2]);
//	//this->statusBarLabel->setText(s);
//	//to do 用长度为半径不是像素为半径，因为像素的长宽不定
//	int *currentPixelXPointer = NULL;
//	int *currentPixelYPointer = NULL;
//	int *currentPixelSlicePointer = NULL;
//	int currentPixelDims[3];
//	int middlePixelSlice, middlePixelX, middlePixelY;
//	if (viewIndex == 0)
//	{
//		middlePixelSlice = middlePixelDims[0];
//		middlePixelX = middlePixelDims[1];
//		middlePixelY = middlePixelDims[2];
//
//		currentPixelSlicePointer = &currentPixelDims[0];
//		currentPixelXPointer = &currentPixelDims[1];
//		currentPixelYPointer = &currentPixelDims[2];
//	}
//	else if (viewIndex == 1)
//	{
//		middlePixelSlice = middlePixelDims[1];
//		middlePixelX = middlePixelDims[0];
//		middlePixelY = middlePixelDims[2];
//
//		currentPixelSlicePointer = &currentPixelDims[1];
//		currentPixelXPointer = &currentPixelDims[0];
//		currentPixelYPointer = &currentPixelDims[2];
//	}
//	else if (viewIndex == 2)
//	{
//		middlePixelSlice = middlePixelDims[2];
//		middlePixelX = middlePixelDims[0];
//		middlePixelY = middlePixelDims[1];
//
//		currentPixelSlicePointer = &currentPixelDims[2];
//		currentPixelXPointer = &currentPixelDims[0];
//		currentPixelYPointer = &currentPixelDims[1];
//	}
//
//	if (this->penWidth == 1 || this->penWidth == 2 || this->penWidth == 3)
//	{
//		*currentPixelSlicePointer = middlePixelSlice;
//		*currentPixelXPointer = middlePixelX;
//		*currentPixelYPointer = middlePixelY;
//		this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//	}
//	else if (this->penType == CIRCLE)
//	{
//		auto ellipseMsg = this->getPixelEllipseMsg(viewIndex, this->penWidth, spacing);
//		for (int i = 0; i != ellipseMsg.b; ++i)
//		{
//			int count = getXFromEllipseY(ellipseMsg.a, ellipseMsg.b, i);
//			for (int j = 0; j != count; ++j)
//			{
//				*currentPixelSlicePointer = middlePixelSlice;
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//			}
//		}
//	}
//	else if (this->penType == SQUARE)
//	{
//		auto squareMsg = this->getPixelSquareMsg(viewIndex, this->penWidth, spacing);
//		for (int i = 0; i != squareMsg.hr; ++i)
//		{
//			for (int j = 0; j != squareMsg.wr; ++j)
//			{
//				*currentPixelSlicePointer = middlePixelSlice;
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY + i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX - j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//
//				*currentPixelXPointer = middlePixelX + j;
//				*currentPixelYPointer = middlePixelY - i;
//				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
//			}
//		}
//	}
//
//
//
//	imageData->Modified();
//}
//
//void QFourViewWidget::BresenhamFill(int viewIndex, const int beforeImagePointDims[3], const int currentImagePointDims[3])
//{
//	auto currentImageData = this->currentMask.lock()->imageData;
//	int beforeCoordinate[2];
//	int currentCorrdinate[2];
//	for (int i = 0, j = 0; i != 3; ++i)
//	{
//		if (i != viewIndex)
//		{
//			beforeCoordinate[j] = beforeImagePointDims[i];
//			currentCorrdinate[j] = currentImagePointDims[i];
//			++j;
//		}
//	}
//	int slice = beforeImagePointDims[viewIndex];
//
//	//bresenhamFill
//	//dx>dy,bx<cx,by<cy
//	int dx = abs(beforeCoordinate[0] - currentCorrdinate[0]);
//	int dy = abs(beforeCoordinate[1] - currentCorrdinate[1]);
//
//	int symbol = 8;
//	int num = 0;
//
//	if (dx >= dy&&
//		beforeCoordinate[0] <= currentCorrdinate[0] &&
//		beforeCoordinate[1] <= currentCorrdinate[1])
//	{
//		symbol = 0;
//		double k = dy / (double)dx;
//		for (int i = 1; i <= dx; ++i)
//		{
//			num++;
//			int pixelX = beforeCoordinate[0] + i;
//			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx >= dy&&
//		beforeCoordinate[0] <= currentCorrdinate[0] &&
//		beforeCoordinate[1] > currentCorrdinate[1])
//	{
//		symbol = 1;
//		double k = 0 - dy / (double)dx;
//		for (int i = 1; i <= dx; ++i)
//		{
//			num++;
//			int pixelX = beforeCoordinate[0] + i;
//			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx < dy&&
//		beforeCoordinate[0] <= currentCorrdinate[0] &&  //x相等的地方要判断k的无穷情况
//		beforeCoordinate[1] <= currentCorrdinate[1])
//	{
//		symbol = 2;
//		double k = dy / (double)dx;
//		for (int i = 1; i <= dy; ++i)
//		{
//			num++;
//			int pixelY = beforeCoordinate[1] + i;
//			int pixelX = dx == 0 ? beforeCoordinate[0] : getPixelXFromLine(pixelY, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx < dy&&
//		beforeCoordinate[0] <= currentCorrdinate[0] && //x相等的地方要判断k的无穷情况
//		beforeCoordinate[1] > currentCorrdinate[1])
//	{
//		symbol = 3;
//		double k = 0 - dy / (double)dx;
//		for (int i = 1; i <= dy; ++i)
//		{
//			num++;
//			int pixelY = beforeCoordinate[1] - i;
//			int pixelX = dx == 0 ? beforeCoordinate[0] : getPixelXFromLine(pixelY, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx >= dy&&
//		beforeCoordinate[0] > currentCorrdinate[0] &&
//		beforeCoordinate[1] <= currentCorrdinate[1])
//	{
//		symbol = 4;
//		double k = 0 - dy / (double)dx;
//		for (int i = 1; i <= dx; ++i)
//		{
//			num++;
//			int pixelX = beforeCoordinate[0] - i;
//			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx >= dy&&
//		beforeCoordinate[0] > currentCorrdinate[0] &&
//		beforeCoordinate[1] > currentCorrdinate[1])
//	{
//		symbol = 5;
//		double k = dy / (double)dx;;
//		for (int i = 1; i <= dx; ++i)
//		{
//			num++;
//			int pixelX = beforeCoordinate[0] - i;
//			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx < dy&&
//		beforeCoordinate[0] > currentCorrdinate[0] &&
//		beforeCoordinate[1] <= currentCorrdinate[1])
//	{
//		symbol = 6;
//		double k = 0 - dy / (double)dx;
//		for (int i = 1; i <= dy; ++i)
//		{
//			num++;
//			int pixelY = beforeCoordinate[1] + i;
//			int pixelX = getPixelXFromLine(pixelY, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//	else if (dx < dy&&
//		beforeCoordinate[0] > currentCorrdinate[0] &&
//		beforeCoordinate[1] > currentCorrdinate[1])
//	{
//		symbol = 7;
//		double k = dy / (double)dx;
//		for (int i = 1; i <= dy; ++i)
//		{
//			num++;
//			int pixelY = beforeCoordinate[1] - i;
//			int pixelX = getPixelXFromLine(pixelY, k, beforeCoordinate);
//			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
//		}
//	}
//
//}
//
//int QFourViewWidget::getPixelYFromLine(int x, double k, const int point[2])
//{
//	double c = point[1] - k*point[0];
//	double preciseY = k*x + c;
//	return round(preciseY);
//}
//int QFourViewWidget::getPixelXFromLine(int y, double k, const int point[2])
//{
//	double c = point[1] - k*point[0];
//	double preciseX = (y - c) / k;
//	return round(preciseX);
//}


void QFourViewWidget::showOrHidePlaneWidget()
{
	if (this->planeWidgetVisible)
	{
		this->planeWidgetVisible = false;
		for (int i = 0; i != 3; ++i)
		{
			this->imagePlaneWidget[i]->Off();
		}
	}
	else
	{
		this->planeWidgetVisible = true;
		for (int i = 0; i != 3; ++i)
		{
			this->imagePlaneWidget[i]->On();
		}
	}
}
void QFourViewWidget::volumeRender()
{
	if (this->volumeRenderClose)
	{
		this->volumeRenderClose = false;
		//to do 体绘制
	}
	else
	{
		this->volumeRenderClose = true;
		//to do 体绘制
	}
}

vtkSmartPointer<vtkRenderer> QFourViewWidget::getRen3dViewer()
{
	return this->ren_3dWidget;
}
QVTK3DWidget* QFourViewWidget::get3DViewWidget()
{
	return this->vtk3DWidget;
}