#include "mimics_damo.h"

#include <vtkAutoInit.h>  
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);

#include <QtGui>
#include <QtWidgets>
#include "qmap.h"
#include <qaction.h>
#include <QVTKWidget.h>
#include <qmenubar.h>
#include <qlayout.h>
#include <qprogressbar.h>

#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkImageActor.h>
#include <vtkImageData.h>
#include <vtkResliceImageViewer.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkOutlineFilter.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkProperty.h>
#include <vtkCellPicker.h>
#include <vtkImagePlaneWidget.h>
#include <vtkCamera.h>
#include <vtkResliceCursorWidget.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkInteractorStyleImage.h>
#include <vtkSmartPointer.h>
#include <vtkResliceCursor.h>
#include <qmessagebox.h>
#include <vtkImageMapToColors.h>
#include <vtkLookupTable.h>
#include <vtkResliceCursorRepresentation.h>
#include <vtkImageMapToWindowLevelColors.h>
#include <vtkImageReslice.h>
#include <vtkInteractorStyleImage.h>
#include <vtkResliceImageViewerMeasurements.h>
#include <vtkAssemblyPath.h>
#include <vtkLine.h>
#include <vtkCellData.h>
#include <vtkMath.h>
#include <vtkContextKeyEvent.h>
#include <vtkRendererCollection.h>
#include <vtkImageFlip.h>
#include <vtkImageThreshold.h>
#include <vtkImageMapper3D.h>
#include <vtkSimpleImageToImageFilter.h>
#include <vtkImageCast.h>
#include <vtkImageAlgorithmFilter.h>
#include <vtkImageIterator.h>
#include <vtkSimpleImageFilterExample.h>
#include <vtkPointData.h>
#include <vtkBitArray.h>
#include <vtkBitArrayIterator.h>
#include <vtkImageMedian3D.h>
#include <vtkImageAnisotropicDiffusion3D.h>
#include <vtk3DWidget.h>
#include <vtkRegularPolygonSource.h>
#include <vtkEllipseArcSource.h>
#include <vtkImageMaskBits.h>
#include <vtkImageSeedConnectivity.h>
#include <vtkImageThresholdConnectivity.h>
#include <editMaskToolBar.hpp>
//itk头文件
#include <itkThresholdImageFilter.h>
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include "itkImage.h"
#include <itkImageToVTKImageFilter.h>
#include <itkVTKImageToImageFilter.h>
#include <itkBinaryThresholdImageFilter.h>
#include <itkConnectedThresholdImageFilter.h>
#include <itkLaplacianSharpeningImageFilter.h>
#include <itkDiscreteGaussianImageFilter.h>

//额外
#include "qVtk3dWidget.hpp"
#include "colorList.h"
#include "qFourViewWidget.hpp"
#include "createMaskDialog.hpp"
#include "regionGrowingToolbar.hpp"
#include "qVtkImageWidget.hpp"
#include "mask.h"
#include "object.h"
#include "objListWidget.h"
#include "exportObjDialog.hpp"
#include "regionGrowingDialog.h"
#include "maskListWidget.h"
#include "calculateObjDialog.hpp"
#include "imageProcessingDialog.h"
#include "imageProcessingAlgorithms.h"
mimics_damo::mimics_damo(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	//m_QVTKMainView = new QVTKMainViewer(this);
	//QMessageBox::warning(this, tr("..."), tr("ok?"), QMessageBox::Yes);
	//新建和布局部分

	createDataList();
	createMainWidget();
	createActions();
	//createViewActions();

	createDockWidget();  //listWidget需要绑定data
	initializeDialogAndToolBar();

	//设置窗口
	resize(QSize(800, 600)); //窗口大小
	//setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	setWindowState(Qt::WindowMaximized);

	
	createStatusBar();
	createMenus();
	createToolBars();
	//setViewToolBars();

	//to do 先默认读取。。并对mainwidget进行vtk初始化
	loadCTImageData("...");
}
void mimics_damo::createMainWidget()
{
	mainWidget = new QFourViewWidget(this);
	mainWidget->setMaskPtrMapPtr(this->maskPtrMapPtr);
	mainWidget->setObjPtrMapPtr(this->objPtrMapPtr);
	//mainWidget->setCurrentMaskPtr(this->currentMask);
	this->setCentralWidget(mainWidget);

	//建立连接
	connect(mainWidget, SIGNAL(pickImageDims(QVector<int>)),
		this, SLOT(regionGrowing(QVector<int>)));
	//建立editmask连接
	//void editMaskClick(int, QVector<int>);
	//void editMaskClickMove(int, QVector<int>, QVector<int>);
	connect(mainWidget, SIGNAL(editMaskClick(int, QVector<int>)),
		this, SLOT(OnePointFill(int, QVector<int>)));
	connect(mainWidget, SIGNAL(editMaskClickMove(int, QVector<int>, QVector<int>)),
		this, SLOT(BresenhamFill(int, QVector<int>, QVector<int>)));

}
//void mimics_damo::updateCurrentMask(std::shared_ptr<Mask> mask)
//{
//	
//}
void mimics_damo::initializeDialogAndToolBar()
{
	//初始化自定义dialog
	this->createMaskDialog = 0;
	this->regionGrowingDialog = 0;
	this->calculateObjDialog = 0;
	this->exportObjDialog = 0;
	this->imageProcessingDialog = 0;

	//ToolBar
	this->editMaskToolBar = 0;
	this->regionGrowingToolBar = 0;
}
void mimics_damo::createDataList()
{
	//新建mask表
	//this->maskPtrListPtr = std::make_shared<std::list<std::shared_ptr<Mask>>>();
	//this->maskPtrListPtr = std::make_shared<QList<std::shared_ptr<Mask>>>();
	this->maskPtrMapPtr = std::make_shared<QMap<QString, std::shared_ptr<Mask>>>();
	//新建obj表
	this->objPtrMapPtr = std::make_shared<QMap<QString, std::shared_ptr<Object>>>();
	//this->objPtrMapPtr->constBegin();
	//QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);
	//为currentMaskName分配内存
	this->currentMaskName = "";
	this->currentRegionGrowingMask = "";
	//this->currentMask = NULL;
}
void mimics_damo::createDockWidget()
{
	//新键3d mask list和 3d obj list 
	this->maskListWidget = new MaskListWidget();
	this->maskListWidget->setMaskMap(this->maskPtrMapPtr);
	//this->maskListWidget->setCurrentMaskPtr(&(*this->maskPtrMapPtr)this->currentMask);
	this->maskListWidget->setCurrentMaskName(this->currentMaskName);
	this->maskListWidget->setNewButtonAction(this->createMaskAction);
	this->maskListWidget->setCalculateButtonAction(this->calculateObjAction);
	this->maskListWidget->setEditButtonAction(this->editMaskAction);
	connect(this->maskListWidget, SIGNAL(changeCurrentMask(QString)),
		this, SLOT(setCurrentMask(QString)));
	connect(this->maskListWidget, SIGNAL(deleteMask(QString)),
		this, SLOT(deleteMask(QString)));
	connect(this->maskListWidget, SIGNAL(changeCurrentMaskName(QString,int,int)),
		this, SLOT(changeCurrentMaskName(QString,int,int)));
	connect(this->maskListWidget, SIGNAL(maskVisible(QString, bool)),
		this, SLOT(setMaskVisible(QString, bool)));

	this->objListWidget = new ObjListWidget();
	this->objListWidget->setObjectMap(this->objPtrMapPtr);
	this->objListWidget->setExportButtonAction(this->exportObjAction);

	//新建Dock Widget，不处于central widget里面
	this->maskListDockWidget = new QDockWidget(tr("3D Mask List"), this);
	maskListDockWidget->setFeatures(QDockWidget::DockWidgetMovable| QDockWidget::DockWidgetFloatable);
	maskListDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	maskListDockWidget->setWidget(this->maskListWidget);

	this->objListDockWidget = new QDockWidget(tr("3D Object List"), this);
	this->objListDockWidget->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	this->objListDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->objListDockWidget->setWidget(this->objListWidget);

	this->addDockWidget(Qt::RightDockWidgetArea, maskListDockWidget);
	this->addDockWidget(Qt::RightDockWidgetArea, objListDockWidget);
}
void mimics_damo::setMaskVisible(QString mask_name, bool visible)
{
	QMessageBox::warning(this, "Tip", "mimics_damo::setMaskVisible::ok?", QMessageBox::Ok);
	(*this->maskPtrMapPtr)[mask_name]->setVisible(visible);
}
void mimics_damo::deleteMask(QString mask_name)
{
	QMessageBox::warning(this, "Tip", "mimics_damo::deleteMask:ok?", QMessageBox::Ok);
	this->maskPtrMapPtr->erase(this->maskPtrMapPtr->find(mask_name));//删除mask表内容
	//QMessageBox::warning(this, "Tip", "mimics_damo::deleteMask:ok??", QMessageBox::Ok);
}
void mimics_damo::changeCurrentMaskName(QString mask_name,int row,int column)
{
	if (this->maskPtrMapPtr->find(mask_name) != this->maskPtrMapPtr->end())
	{
		QMessageBox::warning(this, "Warning", "Can not use same names in the Mask list!", QMessageBox::Ok);

		this->maskListWidget->setItemText(row, column, this->currentMaskName);
	}
	else
	{
		std::shared_ptr<Mask> currentMask = (*this->maskPtrMapPtr)[this->currentMaskName];
		currentMask->name = mask_name;   //绑定（setitem）的时候也会触发change！！！！
		this->maskPtrMapPtr->erase(this->maskPtrMapPtr->find(this->currentMaskName));
		this->maskPtrMapPtr->insert(currentMask->name, currentMask);
		this->currentMaskName = currentMask->name;
		this->maskListWidget->setCurrentMaskName(this->currentMaskName);
	}
}

void mimics_damo::loadCTImageData(const QString & path)
{
	//vtk_itk部分

	//itk读取
	ImageIOType::Pointer gdcmIO = ImageIOType::New();
	InputNamesGeneratorType::Pointer inputNames = InputNamesGeneratorType::New();
	inputNames->SetInputDirectory("W:/medical_work/medical_image/SE2");//to do 替换为	path.toStdString().c_str()

	const ReaderType::FileNamesContainer &filenames = inputNames->GetInputFileNames();

	ReaderType::Pointer itkReader = ReaderType::New();

	itkReader->SetImageIO(gdcmIO); //读取器绑定读取类型
	itkReader->SetFileNames(filenames);
	itkReader->Update();

	//typedef itk::LaplacianSharpeningImageFilter<InputImageType, InputImageType >  LaplacianSharpeningImageFilterType;
	//LaplacianSharpeningImageFilterType::Pointer laplacianSharpeningImageFilter =
	//	LaplacianSharpeningImageFilterType::New();
	//laplacianSharpeningImageFilter->SetInput(itkReader->GetOutput());

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

	this->ctImageData = flipY->GetOutput();



	//mainwidget更新
	this->mainWidget->setCTImageData(this->ctImageData);
}

//void mimics_damo::setViewToolBars()
//{
//	//this->qviewToolBar->isMovable();
//	//this->qviewToolBar->isFloatable();
//	this->qviewToolBar->addAction(this->planeWidgetVisibleAction);
//	this->qviewToolBar->addSeparator();
//	this->qviewToolBar->addAction(this->volumeRenderAction);
//}

//void mimics_damo::updateLookUpTable(int min, int max)  //接受valueChange改变映射表,这是根据阈值范围来改变映射表，对区域提取出来的图像可能无效
//{
//	//定义颜色映射表
//	vtkSmartPointer<vtkLookupTable> ctTable = vtkSmartPointer<vtkLookupTable>::New();
//	ctTable->SetTableRange(this->ctImageData->GetScalarRange());
//	ctTable->SetSaturationRange(0, 0);  //饱和度
//	ctTable->SetHueRange(0, 0);  //色调
//	ctTable->SetValueRange(0, 1); //明亮度
//	ctTable->SetNumberOfColors(256);
//	ctTable->Build();
//
//
//	if (min != max)
//	{
//		int range[2];
//		range[0] = ctTable->GetIndex(min);
//		range[1] = ctTable->GetIndex(max);
//
//		for (int i = range[0]; i < range[1]; ++i)
//		{
//			ctTable->SetTableValue(i, 0, 1, 0, 1);
//		}
//	}
//
//	for (int i = 0; i < 3; ++i)
//	{
//		riw[i]->GetWindowLevel()->SetLookupTable(ctTable);
//		//riw[i]->SetLookupTable(ctTable);
//		riw[i]->GetWindowLevel()->GetLookupTable()->Modified();
//		this->riw[i]->GetRenderWindow()->GetInteractor()->Render();
//	}
//}

//修改的
void mimics_damo::createMaskDataFromTresholdValue(int min, int max)//这个要放在mainwindow中因为要创建数据
{
	int extent[6];
	int dims[3];
	this->ctImageData->GetExtent(extent);
	this->ctImageData->GetDimensions(dims);

	vtkSmartPointer<vtkImageThreshold> thresholdFilter = vtkSmartPointer<vtkImageThreshold>::New();
	thresholdFilter->ThresholdBetween(min, max);
	thresholdFilter->SetOutValue(0);
	thresholdFilter->SetInValue(1);    //像素值和亮度有关系，应为这个关系所以lookuptable范围覆盖整个图像时，还是可以看出图像的原本样子
	thresholdFilter->SetInputData(this->ctImageData);
	thresholdFilter->ReleaseDataFlagOn();

	//vtkSmartPointer<vtkImageMedian3D> imageMedianFilter = vtkSmartPointer<vtkImageMedian3D>::New();  //中值滤波
	//imageMedianFilter->SetInputConnection(thresholdFilter->GetOutputPort());
	//imageMedianFilter->ReleaseDataFlagOn();
	//vtkImageMedian3D
	//thresholdFilter->Update();

	vtkSmartPointer<vtkImageCast> imageCast = vtkSmartPointer<vtkImageCast>::New();
	imageCast->SetOutputScalarTypeToUnsignedChar();
	imageCast->SetInputConnection(thresholdFilter->GetOutputPort());
	imageCast->Update();

	//不要随意update，占内存！！！！！！！！！！！
	//thresholdFilter->GetOutput()->Delete();
	//QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);

	//to do用时间换空间实时产生？用可见和不可见按钮来控制mask对象是否实际产生
	std::shared_ptr<Mask> newMask = std::make_shared<Mask>();
	newMask->thresholdRange[0] = min;
	newMask->thresholdRange[1] = max;
	newMask->imageData = imageCast->GetOutput();//得到渲染管线的输出指针

	//int d[3];
	//newMask->imageData->GetDimensions(d);
	//QString q = QString("%1 %2 %3").arg(d[0]).arg(d[1]).arg(d[2]);
	//QMessageBox::warning(this, "what type?", q, QMessageBox::Ok);
	//QMessageBox::warning(this, "what type?", "ok?", QMessageBox::Ok);
	//newMask->imageAlgorithmOutput = thresholdFilter->GetOutputPort();

	//bit尝试
	//newMask->imageData = vtkSmartPointer<vtkImageData>::New();
	//newMask->imageData->SetDimensions(this->ctImageData->GetDimensions());
	//newMask->imageData->SetSpacing(this->ctImageData->GetSpacing());
	//newMask->imageData->SetOrigin(this->ctImageData->GetOrigin());
	//newMask->imageData->SetExtent(this->ctImageData->GetExtent());
	//newMask->imageData->AllocateScalars(VTK_BIT, 1);
	//vtkBitArray *bitArray = vtkBitArray::SafeDownCast(newMask->imageData->GetPointData()->GetArray("ImageScalars"));
	//vtkIdType sizeOfTuples = bitArray->GetNumberOfTuples();
	//for (vtkIdType i = 0; i < sizeOfTuples; i++)
	//{
	//	short *thresholdFilterPixel = (short *)(thresholdFilter->GetOutput()->GetScalarPointer(i, j, k));
	//	bitArray->SetValue(i,)
	//}
	//QMessageBox::warning(this, "what type?", "ok!", QMessageBox::Ok);
	//for (int k = 0; k < dims[2]; ++k)
	//{
	//	for (int j = 0; j < dims[1]; ++j)
	//	{
	//		for (int i = 0; i < dims[0]; ++i)
	//		{
	//			short *thresholdFilterPixel = (short *)(thresholdFilter->GetOutput()->GetScalarPointer(i, j, k));
	//			vtkIdType id= i + j*dims[0] + k*dims[0] * dims[1];
	//			if (*thresholdFilterPixel)
	//			{
	//				bitArray->SetValue(id, 1);
	//			}
	//			else
	//			{
	//				bitArray->SetValue(id, 0);
	//			}
	//		}
	//	}
	//}

	//利用命名表命名to do防重复
	newMask->name = colorList[colorID].colorName;
	newMask->color[0] = colorList[colorID].color[0] / 255.0;
	newMask->color[1] = colorList[colorID].color[1] / 255.0;
	newMask->color[2] = colorList[colorID].color[2] / 255.0;
	colorID = (colorID + 1) % 16;

	//newMask->visible = true;

	//创建actor
	//lookuptable的用处是提供梯度值到颜色的映射，比如像素值为1表示的是绿色还是红色
	//在mainwidget中创建mask
	this->mainWidget->createActorForMask(newMask);

	this->currentMaskName = newMask->name;

	//QMessageBox::warning(this, "what happen?", newMask->name, QMessageBox::Ok);
	//this->maskPtrListPtr->push_back(newMask);//加入链表
	//this->maskListWidget->updateMaskList();
	
	this->maskPtrMapPtr->insert(newMask->name, newMask);  //只要有效就添加进去
	this->maskListWidget->updateMaskList(newMask->name);

	//this->currentMask = newMask;//当前要处理的mask
	//this->currentMaskName = newMask->name;
	//newMask->imageData->Delete();
}

//void QFourViewWidget::updateLookUpTableForCreateMaskDialog(int min, int max)  //接受valueChange改变映射表,这是根据阈值范围来改变映射表，对区域提取出来的图像可能无效
//{
//	//定义颜色映射表
//	vtkSmartPointer<vtkLookupTable> ctTable = vtkSmartPointer<vtkLookupTable>::New();
//	ctTable->SetTableRange(this->ctImageData->GetScalarRange());
//	ctTable->SetSaturationRange(0, 0);  //饱和度
//	ctTable->SetHueRange(0, 0);  //色调
//	ctTable->SetValueRange(0, 1); //明亮度
//	ctTable->SetNumberOfColors(256);
//	ctTable->Build();
//
//	if (min != max)
//	{
//		int range[2];
//		range[0] = ctTable->GetIndex(min);
//		range[1] = ctTable->GetIndex(max);
//
//		for (int i = range[0]; i < range[1]; ++i)
//		{
//			ctTable->SetTableValue(i, 0, 1, 0, 1);
//		}
//	}
//
//	for (int i = 0; i < 3; ++i)
//	{
//		this->imageViewer[i]->GetWindowLevel()->SetLookupTable(ctTable);
//		this->imageViewer[i]->GetWindowLevel()->GetLookupTable()->Modified();
//		this->imageViewer[i]->SetColorWindow(2057);
//		this->imageViewer[i]->SetColorLevel(406);
//		this->imageViewer[i]->GetRenderWindow()->GetInteractor()->Render();
//	}
//
//}
//void QFourViewWidget::regionRrowingModel(int viewIndex)
//{
//	this->setCurrentCoordsMsg(viewIndex);//获取ImagePointDims和ImagePointPosition
//										 //this->originalMask = this->currentMask;
//	DisplayImageType::Pointer itkImage = constructITKImage(this->originalMask.lock()->imageData);
//
//	//QMessageBox::warning(NULL, "what happen?", "2", QMessageBox::Ok);
//
//	typedef itk::ConnectedThresholdImageFilter< DisplayImageType, DisplayImageType >
//		ConnectedFilterType;
//	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
//	connectedThreshold->SetInput(itkImage);
//	connectedThreshold->SetLower(1);
//	connectedThreshold->SetUpper(1);
//	connectedThreshold->SetReplaceValue(1);
//	DisplayImageType::IndexType index;
//
//	index[0] = imagePickPointDims[0];
//	index[1] = imagePickPointDims[1];
//	index[2] = imagePickPointDims[2];
//
//	connectedThreshold->SetSeed(index);
//
//	typedef itk::ImageToVTKImageFilter<DisplayImageType>
//		ConnectorType;
//	ConnectorType::Pointer connector = ConnectorType::New();
//	connector->SetInput(connectedThreshold->GetOutput());
//	//connector->ReleaseDataFlagOn();
//	connector->ReleaseDataFlagOn();
//	connector->Update();  //分配了内存
//
//	vtkSmartPointer<vtkImageData> resultImage = connector->GetOutput(); //已经区域增长的
//
//	int extent[6];
//	resultImage->GetExtent(extent);
//	int dims[3];
//	this->ctImageData->GetDimensions(dims);
//
//	//判空
//	vtkImageIterator<unsigned char> emptyJudgeIter(resultImage, extent);
//	bool isEmpty = true;
//
//	while (!emptyJudgeIter.IsAtEnd())
//	{
//		unsigned char *inSI = emptyJudgeIter.BeginSpan();
//		unsigned char *inSIEnd = emptyJudgeIter.EndSpan();
//
//		while (inSI != inSIEnd)
//		{
//			if (*inSI != 0)
//			{
//				isEmpty = false;
//			}
//			++inSI;
//		}
//		emptyJudgeIter.NextSpan();
//	}
//	if (isEmpty)
//		QMessageBox::warning(NULL, "Tip", "illgal seed", QMessageBox::Ok);
//
//	//QMessageBox::warning(NULL, "what happen?", "5", QMessageBox::Ok);
//
//	//如果种子点合法，imageData为空，则新建imageData并添加到actor，并添加到map里面
//	if (regionRrowingMask.lock()->imageData == 0 && !isEmpty)
//	{
//		//QMessageBox::warning(NULL, "what happen?", "6", QMessageBox::Ok);
//		regionRrowingMask.lock()->name = colorList[colorID].colorName;
//		regionRrowingMask.lock()->color[0] = colorList[colorID].color[0] / 255.0;
//		regionRrowingMask.lock()->color[1] = colorList[colorID].color[1] / 255.0;
//		regionRrowingMask.lock()->color[2] = colorList[colorID].color[2] / 255.0;
//		colorID = (colorID + 1) % 16;
//
//		regionRrowingMask.lock()->imageData = vtkSmartPointer<vtkImageData>::New();//不分配就是空指针没用
//		regionRrowingMask.lock()->imageData->DeepCopy(resultImage);	//拷贝了resultImage用于初始化
//
//																	//新建actor
//																	//创建actor
//		vtkSmartPointer<vtkLookupTable> maskTable = vtkSmartPointer<vtkLookupTable>::New();
//		maskTable->SetNumberOfTableValues(2);
//		maskTable->SetRange(0, 1);
//		maskTable->SetNumberOfColors(2);
//		maskTable->SetTableValue(0, 0, 0, 0, 0);        //lookuptable貌似只影响颜色，
//		maskTable->SetTableValue(1, regionRrowingMask.lock()->color[0], regionRrowingMask.lock()->color[1], regionRrowingMask.lock()->color[2], 0.4);
//		maskTable->Build();
//
//		//QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);
//
//		vtkSmartPointer<vtkImageMapToColors> maskMapToColors[3];
//
//		vtkSmartPointer<vtkImageActor> maskActor[3];
//
//		vtkSmartPointer<vtkImageAlgorithmFilter> imageAlgorithm = vtkSmartPointer<vtkImageAlgorithmFilter>::New();
//		imageAlgorithm->SetInputData(regionRrowingMask.lock()->imageData);
//
//		for (int i = 0; i < 3; ++i)
//		{
//			maskMapToColors[i] = vtkSmartPointer<vtkImageMapToColors>::New();   //没有爆炸
//			maskMapToColors[i]->SetLookupTable(maskTable);
//			maskMapToColors[i]->PassAlphaToOutputOn();
//			maskMapToColors[i]->SetActiveComponent(0);
//			maskMapToColors[i]->SetInputConnection(imageAlgorithm->GetOutputPort());//不要再用Data用connection，血的教训！！！！
//			maskMapToColors[i]->SetOutputFormatToRGBA();
//
//			int sliceOrientation = i;
//			int sliceIndex = this->imageViewer[i]->GetSlice();
//
//			int extent[6];
//			resultImage->GetExtent(extent);
//			int displayExtent[6];
//			for (int i = 0; i < 6; ++i)
//			{
//				displayExtent[i] = extent[i];
//			}
//
//			displayExtent[sliceOrientation * 2] = sliceIndex;  //设置切片
//			displayExtent[sliceOrientation * 2 + 1] = sliceIndex;
//
//
//			maskActor[i] = vtkSmartPointer<vtkImageActor>::New();
//			maskActor[i]->GetMapper()->SetInputConnection(
//				maskMapToColors[i]->GetOutputPort());
//			maskActor[i]->SetDisplayExtent(displayExtent);
//			regionRrowingMask.lock()->imageActor[i] = maskActor[i];
//			this->imageViewer[i]->GetRenderer()->AddActor(maskActor[i]);  //add actor to renderer
//		}
//
//		for (int i = 0; i != 3; ++i)
//		{
//			this->rwi_vtkImageWidget[i]->Render();
//		}
//
//		////链表结构
//		//this->maskPtrListPtr->push_back(regionRrowingMask);//加入链表
//		//this->maskListWidget->updateMaskList();
//
//		//map结构
//		this->maskPtrMapPtr.lock()->insert(regionRrowingMask.lock()->name, regionRrowingMask.lock());  //只要有效就添加进去
//		this->maskListWidget->updateMaskList(regionRrowingMask.lock()->name);
//		emit updateMaskListWidget(regionRrowingMask.lock()->name);
//		this->currentMask = regionRrowingMask;//将当前mask设置为regionRrowingMask;
//		emit currentMaskChanged(regionRrowingMask);
//		//yao you originMask,fangzhicurrentMaskbianhua.
//		//this->currentMask = newMask;//当前要处理的mask
//
//	}
//	//如果种子点合法，imageData不为空，则用resultImage修改newMask中的数据并更新actor
//	else if (!isEmpty)
//	{
//
//		vtkImageIterator<unsigned char> resultImageIter(resultImage, extent);
//		vtkImageIterator<unsigned char> regionRrowingImageIter(regionRrowingMask.lock()->imageData, extent);
//		while (!resultImageIter.IsAtEnd())
//		{
//			unsigned char *resultImageInSI = resultImageIter.BeginSpan();
//			unsigned char *resultImageInSIEnd = resultImageIter.EndSpan();
//
//			unsigned char *regionRrowingImageInSI = regionRrowingImageIter.BeginSpan();
//			unsigned char *regionRrowingImageInSIEnd = regionRrowingImageIter.EndSpan();
//			while (resultImageInSI != resultImageInSIEnd)
//			{
//				if (*resultImageInSI == 1)
//				{
//					*regionRrowingImageInSI = 1;
//				}
//				++resultImageInSI;
//				++regionRrowingImageInSI;
//			}
//			resultImageIter.NextSpan();
//			regionRrowingImageIter.NextSpan();
//		}
//
//		regionRrowingMask.lock()->imageData->Modified();
//		for (int i = 0; i != 3; ++i)
//		{
//			this->rwi_vtkImageWidget[i]->Render();
//		}
//	}
//	itkImage->ReleaseData();
//}
//void mimics_damo::setCurrentMask(std::shared_ptr<Mask> newMask)
//{
//	//newMask->imageData->ReleaseData();//一旦relesas Actor就不见了
//	/*int d[3];
//	newMask->imageData->GetDimensions(d);
//	QString q = QString("%1 %2 %3").arg(d[0]).arg(d[1]).arg(d[2]);
//	QMessageBox::warning(this, "what type?", q, QMessageBox::Ok);*/
//	//QMessageBox::warning(this, "what happen?", "got it?", QMessageBox::Ok);
//	//newMask->imageData->UnRegister();
//	//this->currentMaskName = newMask->name;  //设置当前结点
//	this->currentMask = newMask;
//}
//void mimics_damo::updateCurrentMask(std::shared_ptr<Mask> mask)
//{
//	this->mainWidget->setCurrentMask(mask);
//}

mimics_damo::~mimics_damo()
{
}

void mimics_damo::setCurrentMask(QString mask)
{
	//合法性
	if (!(*this->maskPtrMapPtr).contains(mask))
	{
		QMessageBox::warning(this, "what happen?", "mimics_damo::setCurrentMask::illegal mask", QMessageBox::Ok);
		return;
	}
	this->currentMaskName = mask;
}

//void mimics_damo::volumeRender()
//{
//
//}

//void mimics_damo::createViewActions()
//{
//	this->planeWidgetVisibleAction=new QAction(tr("PW"));//Show or hide plane widget
//	connect(planeWidgetVisibleAction, SIGNAL(triggered()), this, SLOT(showOrHidePlaneWidget()));
//
//	this->volumeRenderAction=new QAction(tr("VR"));//Volume Render
//	connect(volumeRenderAction, SIGNAL(triggered()), this, SLOT(volumeRender()));
//}

void mimics_damo::createActions()
{
	createMaskAction = new QAction(tr("Create new &mask"));
	connect(createMaskAction, SIGNAL(triggered()), this, SLOT(ShowCreateMaskDialog()));

	openAction = new QAction(tr("&Open ct file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	regionGrowingAction = new QAction(tr("Region &growing"));
	connect(regionGrowingAction, SIGNAL(triggered()), this, SLOT(ShowRegionGrowingDialog()));

	calculateObjAction = new QAction(tr("Calculate &object"));
	connect(calculateObjAction, SIGNAL(triggered()), this, SLOT(ShowCalculateObjDialog()));

	exportObjAction = new QAction(tr("Export object"));
	connect(exportObjAction, SIGNAL(triggered()), this, SLOT(ShowExportObjDialog()));

	editMaskAction = new QAction(tr("Edit Mask"));
	connect(editMaskAction, SIGNAL(triggered()), this, SLOT(ShowEditMaskToolBar()));

	testAction = new QAction(tr("Test"));
	connect(testAction, SIGNAL(triggered()), this, SLOT(test()));

	imageProcessingAction = new QAction(tr("Image Processing"));
	connect(imageProcessingAction, SIGNAL(triggered()), this, SLOT(ShowImageProcessingDialog()));
}
void mimics_damo::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(createMaskAction);
	editMenu->addAction(regionGrowingAction);
	editMenu->addAction(calculateObjAction);
	editMenu->addAction(exportObjAction);
	editMenu->addAction(testAction);
}
void mimics_damo::createToolBars()
{
	fileToolBar = addToolBar("File");
	fileToolBar->setFloatable(false);
	fileToolBar->setMovable(false);
	fileToolBar->addAction(openAction);

	editToolBar = addToolBar("Edit");
	editToolBar->setFloatable(false);
	editToolBar->setMovable(false);
	editToolBar->addAction(createMaskAction);
	editToolBar->addAction(regionGrowingAction);
	editToolBar->addAction(calculateObjAction);
	editToolBar->addAction(exportObjAction);
	editToolBar->addAction(editMaskAction);
	editToolBar->addAction(testAction);
	editToolBar->addAction(imageProcessingAction);
}
void mimics_damo::createStatusBar()
{
	this->statusBarLabel = new QLabel("");
	this->statusBarLabel->setMinimumSize(this->statusBarLabel->sizeHint());
	this->statusBarLabel->setAlignment(Qt::AlignHCenter);
	
	this->progressLabel = new QLabel("");
	this->statusBarLabel->setMinimumSize(this->statusBarLabel->sizeHint());
	this->statusBarLabel->setAlignment(Qt::AlignHCenter);

	this->progressBar = new QProgressBar(this);
	this->progressBar->setRange(0, 100);
	this->progressBar->setValue(0);
	//pStatusBar->addWidget(pLabel);//添加到状态栏的左边
	//pStatusBar->addWidget(pProgressBar);
	this->statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
	this->statusBar()->addWidget(statusBarLabel);
	this->statusBar()->addPermanentWidget(this->progressLabel);//添加到状态栏的右边
	this->statusBar()->addPermanentWidget(this->progressBar);

}

void mimics_damo::ShowCreateMaskDialog()
{
	if (!createMaskDialog)
	{
		//QMessageBox::warning(this, "what happen?", "OK?", QMessageBox::Ok);
		createMaskDialog = new CreateMaskDialog(this);

		connect(createMaskDialog, SIGNAL(thresholdValueChanged(int, int)),
			this->mainWidget, SLOT(updateLookUpTableForCreateMaskDialog(int, int)));
		connect(createMaskDialog, SIGNAL(thresholdValueResult(int, int)),  //定义关闭时创建mask响应
			/*this->mainWidget*/this, SLOT(createMaskDataFromTresholdValue(int, int)));
	}
	double scalarRange[2];
	//QMessageBox::warning(this, "what happen?", "OK1", QMessageBox::Ok);
	this->mainWidget->getImageScalarRange(scalarRange);
	//QMessageBox::warning(this, "what happen?", "OK1.1", QMessageBox::Ok);
	createMaskDialog->initDialog(scalarRange[0], scalarRange[1]);//初始化标量值

	//QMessageBox::warning(this, "what happen?", "OK2", QMessageBox::Ok);
	//createMaskDialog->setModal(true);//设置为模态对话框
	createMaskDialog->show();
	createMaskDialog->raise();//顶层窗口
	createMaskDialog->activateWindow();//激活状态
}

void mimics_damo::ShowImageProcessingDialog()
{
	if (!(this->imageProcessingDialog))
	{
		this->imageProcessingDialog = new ImageProcessingDialog(this);

		connect(this->imageProcessingDialog, SIGNAL(processingRequest(QString, QVector<QString>)),
			this, SLOT(ImageProcessing(QString, QVector<QString>)));
	}
	//每次打开时读取mask表

	//清理
	this->imageProcessingDialog->Clear();

	//添加combox元素
	QMap<QString, std::shared_ptr<Mask>>::const_iterator map_iterator;
	auto begin = this->maskPtrMapPtr->constBegin();
	auto end = this->maskPtrMapPtr->constEnd();
	for (map_iterator = begin; map_iterator != end; ++map_iterator) {
		this->imageProcessingDialog->AddToMaskCombox(map_iterator.key());
	}
	this->imageProcessingDialog->SetMaskComboxId(0);

	this->imageProcessingDialog->show();
	this->imageProcessingDialog->raise();//顶层窗口
	this->imageProcessingDialog->activateWindow();//激活状态
}

//itk总处理
DisplayImageType::Pointer mimics_damo::ITKSelectAlgorithm(QString processing_name, DisplayImageType::Pointer image)
{
	if (processing_name == ImageProcessingAlgorithms::kGaussFilter)
		return ITKDiscreteGaussianFilter(image);
	else if (processing_name == ImageProcessingAlgorithms::kLaplacianSharpener)
		return ITKLaplacianSharpening(image);
	else
	{
		QMessageBox::warning(this, "Error", "No algorithm can be selected!", QMessageBox::Ok);
		return nullptr;
	}
}
//拉普拉斯锐化
DisplayImageType::Pointer mimics_damo::ITKLaplacianSharpening(DisplayImageType::Pointer image)
{
	typedef itk::LaplacianSharpeningImageFilter<DisplayImageType, DisplayImageType >  LaplacianSharpeningImageFilterType;
	LaplacianSharpeningImageFilterType::Pointer laplacianSharpeningImageFilter =
		LaplacianSharpeningImageFilterType::New();
	laplacianSharpeningImageFilter->SetInput(image);
	return laplacianSharpeningImageFilter->GetOutput();
}
//高斯滤波
DisplayImageType::Pointer mimics_damo::ITKDiscreteGaussianFilter(DisplayImageType::Pointer image)
{
	typedef itk::DiscreteGaussianImageFilter<
		DisplayImageType, DisplayImageType >  DiscreteGaussianImageFilterType;
	DiscreteGaussianImageFilterType::Pointer gaussianFilter = DiscreteGaussianImageFilterType::New();
	gaussianFilter->SetInput(image);
	gaussianFilter->SetVariance(2);
	return gaussianFilter->GetOutput();
}
void mimics_damo::ImageProcessing(QString mask_name, QVector<QString> processing_order)
{
	if (mask_name == "")
		return;
	//QMessageBox::warning(NULL, "what happen?", "regionGrowingOK?", QMessageBox::Ok);

	auto originalMask = (*this->maskPtrMapPtr)[mask_name];

	DisplayImageType::Pointer itkImage = constructITKImage(originalMask->imageData);

	//按照顺序进行算法处理
	int processing_order_size = processing_order.count();
	DisplayImageType::Pointer current_image = itkImage;
	for (int i = 0; i != processing_order_size; ++i)
	{
		current_image=ITKSelectAlgorithm(processing_order[i], current_image);
	}

	typedef itk::ImageToVTKImageFilter<DisplayImageType>
		ConnectorType;
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(current_image);
	//connector->ReleaseDataFlagOn();
	connector->ReleaseDataFlagOn();
	connector->Update();  //分配了内存

	vtkSmartPointer<vtkImageData> resultImage = connector->GetOutput(); //已经区域增长的


	//to do用时间换空间实时产生？用可见和不可见按钮来控制mask对象是否实际产生
	std::shared_ptr<Mask> newMask = std::make_shared<Mask>();
	newMask->imageData = resultImage;//得到渲染管线的输出指针



	//利用命名表命名to do防重复
	newMask->name = colorList[colorID].colorName;
	newMask->color[0] = colorList[colorID].color[0] / 255.0;
	newMask->color[1] = colorList[colorID].color[1] / 255.0;
	newMask->color[2] = colorList[colorID].color[2] / 255.0;
	colorID = (colorID + 1) % 16;

	//newMask->visible = true;

	//创建actor
	//lookuptable的用处是提供梯度值到颜色的映射，比如像素值为1表示的是绿色还是红色
	//在mainwidget中创建mask
	this->mainWidget->createActorForMask(newMask);

	this->currentMaskName = newMask->name;

	this->maskPtrMapPtr->insert(newMask->name, newMask);  //只要有效就添加进去
	this->maskListWidget->updateMaskList(newMask->name);
	
}
//void mimics_damo::updateAllWidgetCurrentMask(std::weak_ptr<Mask> mask)
//{
//	
//}

void mimics_damo::ShowCalculateObjDialog()
{
	if (!calculateObjDialog)
	{
		//QMessageBox::warning(this, "what happend?", "-1", QMessageBox::Ok);

		calculateObjDialog = new CalculateObjDialog(this);
		
		//QMessageBox::warning(this, "what happend?", "0", QMessageBox::Ok);
		calculateObjDialog->setMaskPtrQMapPtr(this->maskPtrMapPtr);
		calculateObjDialog->setObjPtrQMapPtr(this->objPtrMapPtr);
		calculateObjDialog->setRen3dViewer(this->mainWidget->getRen3dViewer());
		calculateObjDialog->setViewWidget(this->mainWidget->get3DViewWidget());

		connect(calculateObjDialog->getCalculateObjThreadPtr(),
			SIGNAL(objectListChange(const QString &)), this->objListWidget, 
			SLOT(updateObjectList(const QString &)));

		//QMessageBox::warning(this, "what happend?", "1", QMessageBox::Ok);
	}
	calculateObjDialog->updateTableWidget();
	calculateObjDialog->setModal(true);//设置为模态对话框
	calculateObjDialog->show();
	//calculateobjDialog->raise();//顶层窗口
	calculateObjDialog->activateWindow();//激活状态
}

void mimics_damo::ShowExportObjDialog()
{
	if (!exportObjDialog)
	{

		exportObjDialog = new ExportObjDialog(this);
		exportObjDialog->setObjPtrQMapPtr(this->objPtrMapPtr);

		//QMessageBox::warning(this, "what happend?", "1", QMessageBox::Ok);
	}
	exportObjDialog->updateTableWidget();
	//QMessageBox::warning(this, "what happend?", "0", QMessageBox::Ok);
	exportObjDialog->setModal(true);//设置为模态对话框
	exportObjDialog->show();
	//calculateobjDialog->raise();//顶层窗口
	exportObjDialog->activateWindow();//激活状态
}
void mimics_damo::ShowRegionGrowingDialog()
{
	if (!regionGrowingDialog)
	{

		regionGrowingDialog = new RegionGrowingDialog(this);
		//connect(regiongrowingDialog, SIGNAL(changeVtkClickModel(int)),
		//	this, SLOT(switchVtkClickModel(int)));
		connect(regionGrowingDialog, SIGNAL(maskResult(std::shared_ptr<Mask>)), //关闭时创建mask响应
			this, SLOT(closeRegionGrowing(std::shared_ptr<Mask>)));
	}

	if (currentMaskName =="")//判空
	{
		QMessageBox::warning(this, "Tips", "You have to create or select a mask as a carrier for regional growth!", QMessageBox::Ok);
	}
	else
	{
		//从此处开始区域增长模式
		//std::weak_ptr<Mask> currentMask = (*this->maskPtrMapPtr)[currentMaskName];
		std::shared_ptr<Mask> regionRrowingMask = std::make_shared<Mask>();
		
		//命名表命名 不能在这里命名因为还不确定这个mask是否有效，贸然命名会增加colorId
		//regionRrowingMask->name = colorList[colorID].colorName;
		//regionRrowingMask->color[0] = colorList[colorID].color[0] / 255.0;
		//regionRrowingMask->color[1] = colorList[colorID].color[1] / 255.0;
		//regionRrowingMask->color[2] = colorList[colorID].color[2] / 255.0;
		//colorID = (colorID + 1) % 16;
		//QMessageBox::warning(this, "what happend?", "1", QMessageBox::Ok);

		auto currentMaskPtr = (*maskPtrMapPtr)[currentMaskName];
		regionRrowingMask->thresholdRange[0] = currentMaskPtr->thresholdRange[0];//直接点击有问题
		regionRrowingMask->thresholdRange[1] = currentMaskPtr->thresholdRange[1];

		//改变主窗口模式
		this->mainWidget->setModel(1);//区域增长模式
		//switchVtkClickModel(1);//区域增长

		//改变主窗口鼠标样式
		//刷新主窗口command类
		//for (int i = 0; i != 3; ++i)
		//{
		//	this->qview[i]->setCursor(Qt::CrossCursor);

		//	viewerCallback[i]->regionRrowingMask = regionRrowingMask;
		//	viewerCallback[i]->originalMask = currentMask;//对currentMask执行区域增长
		//	viewerCallback[i]->maskListWidget = this->maskListWidget;
		//}

		regionGrowingDialog->setNewMask(regionRrowingMask);//用对话框保存这个新建的mask,用share_ptr保存，在对话框结束时导出节点
		regionGrowingDialog->show();
		//regiongrowingDialog->raise();//顶层窗口
		regionGrowingDialog->activateWindow();//激活状态
	}

	////代替的工具栏
	//if (regionGrowingToolBar ==0)
	//{

	//	regionGrowingToolBar = new RegionGrowingToolBar("Region Growing",this);
	//	regionGrowingToolBar->setMaskPtrMapPtr(this->maskPtrMapPtr);
	//	//connect(regiongrowingDialog, SIGNAL(changeVtkClickModel(int)),
	//	//	this, SLOT(switchVtkClickModel(int)));
	//	connect(regiongrowingDialog, SIGNAL(maskResult(std::shared_ptr<Mask>)), //关闭时创建mask响应
	//		this, SLOT(closeRegionGrowing(std::shared_ptr<Mask>)));
	//}

	//this->addToolBarBreak(Qt::TopToolBarArea);
	//this->addToolBar(Qt::TopToolBarArea, this->editMaskToolBar);
	//this->editMaskToolBar->show();
}
DisplayImageType::Pointer mimics_damo::constructITKImage(vtkImageData* originalImageData)
{
	//QMessageBox::warning(NULL, "what happen?", "2.1", QMessageBox::Ok);

	typedef itk::VTKImageToImageFilter<DisplayImageType> VTKImageToImageType;

	//Converting to ITK Image Format
	VTKImageToImageType::Pointer vtkImageToImageFilter = VTKImageToImageType::New();
	vtkImageToImageFilter->SetInput(originalImageData);
	//QMessageBox::warning(NULL, "what happen?", "2.2", QMessageBox::Ok);
	vtkImageToImageFilter->Update();
	//将vtk的图像转化为itk的图像，以便利用itk的分割算法进行分割.
	//QMessageBox::warning(NULL, "what happen?", "2.3", QMessageBox::Ok);
	DisplayImageType::Pointer itkImage;
	itkImage = vtkImageToImageFilter->GetOutput();

	//QMessageBox::warning(NULL, "what happen?", "2.4", QMessageBox::Ok);

	return itkImage;
}
void mimics_damo::regionGrowing(QVector<int> pickDims)
{
	if (this->currentMaskName == "")
		return;

	//QMessageBox::warning(NULL, "what happen?", "regionGrowingOK?", QMessageBox::Ok);

	auto originalMask = (*this->maskPtrMapPtr)[this->currentMaskName];

	unsigned char * pixel =(unsigned char *)(originalMask->imageData->GetScalarPointer(pickDims[0], pickDims[1], pickDims[2]));
	if (*pixel == 0)//如果pickDims在currentmask上的值是空的就返回,非法像素
		return;

	DisplayImageType::Pointer itkImage = constructITKImage(originalMask->imageData);

	//QMessageBox::warning(NULL, "what happen?", "2", QMessageBox::Ok);
	//to do https://blog.csdn.net/fengyewu12345/article/details/45952901 边缘保留平滑滤波器
	typedef itk::ConnectedThresholdImageFilter< DisplayImageType, DisplayImageType >
		ConnectedFilterType;
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();
	connectedThreshold->SetInput(itkImage);
	connectedThreshold->SetLower(1);
	connectedThreshold->SetUpper(1);
	connectedThreshold->SetReplaceValue(1);
	DisplayImageType::IndexType index;

	index[0] = pickDims[0];
	index[1] = pickDims[1];
	index[2] = pickDims[2];

	connectedThreshold->SetSeed(index);

	typedef itk::ImageToVTKImageFilter<DisplayImageType>
		ConnectorType;
	ConnectorType::Pointer connector = ConnectorType::New();
	connector->SetInput(connectedThreshold->GetOutput());
	//connector->ReleaseDataFlagOn();
	connector->ReleaseDataFlagOn();
	connector->Update();  //分配了内存

	vtkSmartPointer<vtkImageData> resultImage = connector->GetOutput(); //已经区域增长的

	int extent[6];
	resultImage->GetExtent(extent);
	int dims[3];
	this->ctImageData->GetDimensions(dims);

	//判空直接访问像素点判空
	//vtkImageIterator<unsigned char> emptyJudgeIter(resultImage, extent);
	//bool isEmpty = true;

	//while (!emptyJudgeIter.IsAtEnd())
	//{
	//	unsigned char *inSI = emptyJudgeIter.BeginSpan();
	//	unsigned char *inSIEnd = emptyJudgeIter.EndSpan();

	//	while (inSI != inSIEnd)
	//	{
	//		if (*inSI != 0)
	//		{
	//			isEmpty = false;
	//		}
	//		++inSI;
	//	}
	//	emptyJudgeIter.NextSpan();
	//}
	//if (isEmpty)
	//	QMessageBox::warning(NULL, "Tip", "illgal seed", QMessageBox::Ok);



	//QMessageBox::warning(NULL, "what happen?", "5", QMessageBox::Ok);

	//如果种子点合法，imageData为空，则新建imageData并添加到actor，并添加到map里面


	if (currentRegionGrowingMask == ""/* && !isEmpty*/)
	{
		std::shared_ptr<Mask> regionRrowingMask = std::make_shared<Mask>();
		//QMessageBox::warning(NULL, "what happen?", "6", QMessageBox::Ok);
		regionRrowingMask->name = colorList[colorID].colorName;
		regionRrowingMask->color[0] = colorList[colorID].color[0] / 255.0;
		regionRrowingMask->color[1] = colorList[colorID].color[1] / 255.0;
		regionRrowingMask->color[2] = colorList[colorID].color[2] / 255.0;
		currentRegionGrowingMask = regionRrowingMask->name;
		colorID = (colorID + 1) % 16;

		regionRrowingMask->imageData = vtkSmartPointer<vtkImageData>::New();//不分配就是空指针没用
		regionRrowingMask->imageData->DeepCopy(resultImage);	//拷贝了resultImage用于初始化

		this->mainWidget->createActorForMask(regionRrowingMask);
		////新建actor
		////创建actor
		//vtkSmartPointer<vtkLookupTable> maskTable = vtkSmartPointer<vtkLookupTable>::New();
		//maskTable->SetNumberOfTableValues(2);
		//maskTable->SetRange(0, 1);
		//maskTable->SetNumberOfColors(2);
		//maskTable->SetTableValue(0, 0, 0, 0, 0);        //lookuptable貌似只影响颜色，
		//maskTable->SetTableValue(1, regionRrowingMask->color[0], regionRrowingMask->color[1], regionRrowingMask->color[2], 0.4);
		//maskTable->Build();

		////QMessageBox::warning(this, "what happen?", ".....", QMessageBox::Ok);

		//vtkSmartPointer<vtkImageMapToColors> maskMapToColors[3];

		//vtkSmartPointer<vtkImageActor> maskActor[3];

		//vtkSmartPointer<vtkImageAlgorithmFilter> imageAlgorithm = vtkSmartPointer<vtkImageAlgorithmFilter>::New();
		//imageAlgorithm->SetInputData(regionRrowingMask->imageData);

		//for (int i = 0; i < 3; ++i)
		//{
		//	maskMapToColors[i] = vtkSmartPointer<vtkImageMapToColors>::New();   //没有爆炸
		//	maskMapToColors[i]->SetLookupTable(maskTable);
		//	maskMapToColors[i]->PassAlphaToOutputOn();
		//	maskMapToColors[i]->SetActiveComponent(0);
		//	maskMapToColors[i]->SetInputConnection(imageAlgorithm->GetOutputPort());//不要再用Data用connection，血的教训！！！！
		//	maskMapToColors[i]->SetOutputFormatToRGBA();

		//	int sliceOrientation = i;
		//	int sliceIndex = this->imageViewer[i]->GetSlice();

		//	int extent[6];
		//	resultImage->GetExtent(extent);
		//	int displayExtent[6];
		//	for (int i = 0; i < 6; ++i)
		//	{
		//		displayExtent[i] = extent[i];
		//	}

		//	displayExtent[sliceOrientation * 2] = sliceIndex;  //设置切片
		//	displayExtent[sliceOrientation * 2 + 1] = sliceIndex;


		//	maskActor[i] = vtkSmartPointer<vtkImageActor>::New();
		//	maskActor[i]->GetMapper()->SetInputConnection(
		//		maskMapToColors[i]->GetOutputPort());
		//	maskActor[i]->SetDisplayExtent(displayExtent);
		//	regionRrowingMask.lock()->imageActor[i] = maskActor[i];
		//	this->imageViewer[i]->GetRenderer()->AddActor(maskActor[i]);  //add actor to renderer
		//}

		//for (int i = 0; i != 3; ++i)
		//{
		//	this->rwi_vtkImageWidget[i]->Render();
		//}

		////链表结构
		//this->maskPtrListPtr->push_back(regionRrowingMask);//加入链表
		//this->maskListWidget->updateMaskList();

		//map结构
		this->maskPtrMapPtr->insert(regionRrowingMask->name, regionRrowingMask);  //只要有效就添加进去
		this->maskListWidget->updateMaskList(regionRrowingMask->name);
		//emit updateMaskListWidget(regionRrowingMask.lock()->name);
		//this->currentMask = regionRrowingMask;//将当前mask设置为regionRrowingMask;
		//emit currentMaskChanged(regionRrowingMask);
		//yao you originMask,fangzhicurrentMaskbianhua.
		//this->currentMask = newMask;//当前要处理的mask

	}
	//如果种子点合法，imageData不为空，则用resultImage修改newMask中的数据并更新actor
	else /*if (!isEmpty)*/
	{
		std::shared_ptr<Mask> regionRrowingMask = (*this->maskPtrMapPtr)[this->currentRegionGrowingMask];
		vtkImageIterator<unsigned char> resultImageIter(resultImage, extent);
		vtkImageIterator<unsigned char> regionRrowingImageIter(regionRrowingMask->imageData, extent);
		while (!resultImageIter.IsAtEnd())
		{
			unsigned char *resultImageInSI = resultImageIter.BeginSpan();
			unsigned char *resultImageInSIEnd = resultImageIter.EndSpan();

			unsigned char *regionRrowingImageInSI = regionRrowingImageIter.BeginSpan();
			unsigned char *regionRrowingImageInSIEnd = regionRrowingImageIter.EndSpan();
			while (resultImageInSI != resultImageInSIEnd)
			{
				if (*resultImageInSI == 1)
				{
					*regionRrowingImageInSI = 1;
				}
				++resultImageInSI;
				++regionRrowingImageInSI;
			}
			resultImageIter.NextSpan();
			regionRrowingImageIter.NextSpan();
		}

		regionRrowingMask->imageData->Modified();
		this->mainWidget->reRender();
	}
	itkImage->ReleaseData();
}

void mimics_damo::closeRegionGrowing(std::shared_ptr<Mask> newMask)
{
	//还原主窗口模式
	//switchVtkClickModel(0);//普通模式
	//还原鼠标样式
	this->mainWidget->setModel(0);
	this->currentRegionGrowingMask = "";
	//if (newMask != NULL)
	//{
	//	this->setCurrentMask(newMask);
	//}
}

void mimics_damo::ShowEditMaskToolBar()
{
	if (this->editMaskToolBar == 0)
	{
		this->editMaskToolBar = new EditMaskToolBar("Edit Mask");

		//init edit Mask
		penType=PenType::CIRCLE;
		penWidth=0;
		penModel=PenModel::DRAW;

		//connect(editMaskToolBar, SIGNAL(changeVtkClickModel(int)),
		//	this, SLOT(switchVtkClickModel(int)));
		connect(editMaskToolBar, SIGNAL(closeToolBar()),
			this, SLOT(closeEditMask()));
		connect(editMaskToolBar, SIGNAL(editMaskPenMsg(int, int, /*int,*/ int)),
			this, SLOT(changeEditMaskPenMsg(int, int, /*int,*/ int)));
	}

	if (currentMaskName =="")//判空
	{
		QMessageBox::warning(this, "Tips", "You have to create or select a mask as a carrier for edit mask!", QMessageBox::Ok);
	}
	else
	{
		//切换主窗口模式
		this->mainWidget->setModel(2);
		//switchVtkClickModel(2);//edit mask 模式
		//设置空光标
		//刷新主窗口command
		//for (int i = 0; i != 3; ++i)
		//{
		//	this->viewerCallback[i]->currentMask_editMask = this->currentMask;//当前处理的mask赋值
		//	this->qview[i]->setCursor(Qt::CrossCursor);
		//	//this->circleCursorActor[i]->SetVisibility(1);
		//	//this->circleCursorActor[i]->Modified();
		//	//this->qview[i]->GetRenderWindow()->Render();
		//	connect(qview[i], &QVTKImageWidget::showCursorActor,
		//		[=]()
		//	{
		//		this->circleCursorActor[i]->SetVisibility(true);
		//		this->cursorRen[i]->Render();
		//		this->interactor[i]->Render();
		//	});
		//	connect(qview[i], &QVTKImageWidget::hideCursorActor,
		//		[=]()
		//	{
		//		this->circleCursorActor[i]->SetVisibility(false);
		//		this->cursorRen[i]->Render();
		//		this->interactor[i]->Render();
		//	});
		//}

		//连接QMyVTKWidget与光标显示


		this->addToolBarBreak(Qt::TopToolBarArea);
		this->addToolBar(Qt::TopToolBarArea, this->editMaskToolBar);
		//this->editMaskToolBar->setFloatable(false);
		//this->editMaskToolBar->setFloatable(true);
		this->editMaskToolBar->show();
	}
}

void mimics_damo::BresenhamFill(int viewIndex, QVector<int>beforeImagePointDims, QVector<int> currentImagePointDims)//绘制直线
{
	if (this->currentMaskName == "")
		return;
	auto currentImageData = (*this->maskPtrMapPtr)[this->currentMaskName]->imageData;

	int beforeCoordinate[2];
	int currentCorrdinate[2];
	for (int i = 0, j = 0; i != 3; ++i)
	{
		if (i != viewIndex)
		{
			beforeCoordinate[j] = beforeImagePointDims[i];
			currentCorrdinate[j] = currentImagePointDims[i];
			++j;
		}
	}
	int slice = beforeImagePointDims[viewIndex];

	//bresenhamFill
	//dx>dy,bx<cx,by<cy
	int dx = abs(beforeCoordinate[0] - currentCorrdinate[0]);
	int dy = abs(beforeCoordinate[1] - currentCorrdinate[1]);

	int symbol = 8;
	int num = 0;

	if (dx >= dy&&
		beforeCoordinate[0] <= currentCorrdinate[0] &&
		beforeCoordinate[1] <= currentCorrdinate[1])
	{
		symbol = 0;
		double k = dy / (double)dx;
		for (int i = 1; i <= dx; ++i)
		{
			num++;
			int pixelX = beforeCoordinate[0] + i;
			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx >= dy&&
		beforeCoordinate[0] <= currentCorrdinate[0] &&
		beforeCoordinate[1] > currentCorrdinate[1])
	{
		symbol = 1;
		double k = 0 - dy / (double)dx;
		for (int i = 1; i <= dx; ++i)
		{
			num++;
			int pixelX = beforeCoordinate[0] + i;
			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx < dy&&
		beforeCoordinate[0] <= currentCorrdinate[0] &&  //x相等的地方要判断k的无穷情况
		beforeCoordinate[1] <= currentCorrdinate[1])
	{
		symbol = 2;
		double k = dy / (double)dx;
		for (int i = 1; i <= dy; ++i)
		{
			num++;
			int pixelY = beforeCoordinate[1] + i;
			int pixelX = dx == 0 ? beforeCoordinate[0] : getPixelXFromLine(pixelY, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx < dy&&
		beforeCoordinate[0] <= currentCorrdinate[0] && //x相等的地方要判断k的无穷情况
		beforeCoordinate[1] > currentCorrdinate[1])
	{
		symbol = 3;
		double k = 0 - dy / (double)dx;
		for (int i = 1; i <= dy; ++i)
		{
			num++;
			int pixelY = beforeCoordinate[1] - i;
			int pixelX = dx == 0 ? beforeCoordinate[0] : getPixelXFromLine(pixelY, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx >= dy&&
		beforeCoordinate[0] > currentCorrdinate[0] &&
		beforeCoordinate[1] <= currentCorrdinate[1])
	{
		symbol = 4;
		double k = 0 - dy / (double)dx;
		for (int i = 1; i <= dx; ++i)
		{
			num++;
			int pixelX = beforeCoordinate[0] - i;
			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx >= dy&&
		beforeCoordinate[0] > currentCorrdinate[0] &&
		beforeCoordinate[1] > currentCorrdinate[1])
	{
		symbol = 5;
		double k = dy / (double)dx;;
		for (int i = 1; i <= dx; ++i)
		{
			num++;
			int pixelX = beforeCoordinate[0] - i;
			int pixelY = getPixelYFromLine(pixelX, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx < dy&&
		beforeCoordinate[0] > currentCorrdinate[0] &&
		beforeCoordinate[1] <= currentCorrdinate[1])
	{
		symbol = 6;
		double k = 0 - dy / (double)dx;
		for (int i = 1; i <= dy; ++i)
		{
			num++;
			int pixelY = beforeCoordinate[1] + i;
			int pixelX = getPixelXFromLine(pixelY, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}
	else if (dx < dy&&
		beforeCoordinate[0] > currentCorrdinate[0] &&
		beforeCoordinate[1] > currentCorrdinate[1])
	{
		symbol = 7;
		double k = dy / (double)dx;
		for (int i = 1; i <= dy; ++i)
		{
			num++;
			int pixelY = beforeCoordinate[1] - i;
			int pixelX = getPixelXFromLine(pixelY, k, beforeCoordinate);
			this->drawWholePixel(viewIndex, pixelX, pixelY, slice, currentImageData);
		}
	}

	this->mainWidget->reRender();
}
void mimics_damo::OnePointFill(int viewIndex, QVector<int> middleDims)
{
	if (this->currentMaskName == "")
		return;
	int pickPointDims[3];
	pickPointDims[0] = middleDims[0];
	pickPointDims[1] = middleDims[1];
	pickPointDims[2] = middleDims[2];
	auto currentImageData = (*this->maskPtrMapPtr)[this->currentMaskName]->imageData;
	drawWholePixel(viewIndex, pickPointDims, currentImageData);

	this->mainWidget->reRender();
}
void mimics_damo::drawWholePixel(int viewIndex, int x, int y, int slice, vtkSmartPointer<vtkImageData> imageData)
{
	double spacing[3];
	imageData->GetSpacing(spacing);

	int *currentPixelXPointer = NULL;
	int *currentPixelYPointer = NULL;
	int *currentPixelSlicePointer = NULL;
	int currentPixelDims[3];
	int middlePixelSlice = slice, middlePixelX = x, middlePixelY = y;

	if (viewIndex == 0)
	{
		currentPixelSlicePointer = &currentPixelDims[0];
		currentPixelXPointer = &currentPixelDims[1];
		currentPixelYPointer = &currentPixelDims[2];
	}
	else if (viewIndex == 1)
	{
		currentPixelSlicePointer = &currentPixelDims[1];
		currentPixelXPointer = &currentPixelDims[0];
		currentPixelYPointer = &currentPixelDims[2];
	}
	else if (viewIndex == 2)
	{
		currentPixelSlicePointer = &currentPixelDims[2];
		currentPixelXPointer = &currentPixelDims[0];
		currentPixelYPointer = &currentPixelDims[1];
	}


	if (this->penWidth == 1 || this->penWidth == 2 || this->penWidth == 3)
	{
		*currentPixelSlicePointer = middlePixelSlice;
		*currentPixelXPointer = middlePixelX;
		*currentPixelYPointer = middlePixelY;
		this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
	}
	else if (this->penType == CIRCLE)
	{
		auto ellipseMsg = this->getPixelEllipseMsg(viewIndex, this->penWidth, spacing);
		for (int i = 0; i != ellipseMsg.b; ++i)
		{
			int count = getXFromEllipseY(ellipseMsg.a, ellipseMsg.b, i);
			for (int j = 0; j != count; ++j)
			{
				*currentPixelSlicePointer = middlePixelSlice;
				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
			}
		}
	}
	else if (this->penType == SQUARE)
	{
		auto squareMsg = this->getPixelSquareMsg(viewIndex, this->penWidth, spacing);
		for (int i = 0; i != squareMsg.hr; ++i)
		{
			for (int j = 0; j != squareMsg.wr; ++j)
			{
				*currentPixelSlicePointer = middlePixelSlice;
				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
			}
		}
	}



	imageData->Modified();
}
void mimics_damo::drawWholePixel(int viewIndex, const int middlePixelDims[3], vtkSmartPointer<vtkImageData> imageData)
{
	double spacing[3];
	imageData->GetSpacing(spacing);

	//QString s = QString("x: %1 y: %2 z: %3").arg(middlePixelDims[0]).arg(middlePixelDims[1]).arg(middlePixelDims[2]);
	//this->statusBarLabel->setText(s);
	//to do 用长度为半径不是像素为半径，因为像素的长宽不定
	int *currentPixelXPointer = NULL;
	int *currentPixelYPointer = NULL;
	int *currentPixelSlicePointer = NULL;
	int currentPixelDims[3];
	int middlePixelSlice, middlePixelX, middlePixelY;
	if (viewIndex == 0)
	{
		middlePixelSlice = middlePixelDims[0];
		middlePixelX = middlePixelDims[1];
		middlePixelY = middlePixelDims[2];

		currentPixelSlicePointer = &currentPixelDims[0];
		currentPixelXPointer = &currentPixelDims[1];
		currentPixelYPointer = &currentPixelDims[2];
	}
	else if (viewIndex == 1)
	{
		middlePixelSlice = middlePixelDims[1];
		middlePixelX = middlePixelDims[0];
		middlePixelY = middlePixelDims[2];

		currentPixelSlicePointer = &currentPixelDims[1];
		currentPixelXPointer = &currentPixelDims[0];
		currentPixelYPointer = &currentPixelDims[2];
	}
	else if (viewIndex == 2)
	{
		middlePixelSlice = middlePixelDims[2];
		middlePixelX = middlePixelDims[0];
		middlePixelY = middlePixelDims[1];

		currentPixelSlicePointer = &currentPixelDims[2];
		currentPixelXPointer = &currentPixelDims[0];
		currentPixelYPointer = &currentPixelDims[1];
	}

	if (this->penWidth == 1 || this->penWidth == 2 || this->penWidth == 3)
	{
		*currentPixelSlicePointer = middlePixelSlice;
		*currentPixelXPointer = middlePixelX;
		*currentPixelYPointer = middlePixelY;
		this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
	}
	else if (this->penType == CIRCLE)
	{
		auto ellipseMsg = this->getPixelEllipseMsg(viewIndex, this->penWidth, spacing);
		for (int i = 0; i != ellipseMsg.b; ++i)
		{
			int count = getXFromEllipseY(ellipseMsg.a, ellipseMsg.b, i);
			for (int j = 0; j != count; ++j)
			{
				*currentPixelSlicePointer = middlePixelSlice;
				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
			}
		}
	}
	else if (this->penType == SQUARE)
	{
		auto squareMsg = this->getPixelSquareMsg(viewIndex, this->penWidth, spacing);
		for (int i = 0; i != squareMsg.hr; ++i)
		{
			for (int j = 0; j != squareMsg.wr; ++j)
			{
				*currentPixelSlicePointer = middlePixelSlice;
				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY + i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX - j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);

				*currentPixelXPointer = middlePixelX + j;
				*currentPixelYPointer = middlePixelY - i;
				this->drawOnePixel(currentPixelDims, (int)this->penModel, imageData);
			}
		}
	}



	imageData->Modified();
}
bool mimics_damo::drawOnePixel(int pixDims[3], int model, vtkSmartPointer<vtkImageData> imageData)
{
	int dims[3];
	this->ctImageData->GetDimensions(dims);
	if (pixDims[0] >= 0 && pixDims[0] < dims[0]
		&& pixDims[1] >= 0 && pixDims[1] < dims[1]
		&& pixDims[2] >= 0 && pixDims[2] < dims[2])
	{
		unsigned char * pixel = (unsigned char *)(imageData->GetScalarPointer(pixDims));
		*pixel = model;
		return true;
	}
	return false;
	//return false;
}
EllipseMsg mimics_damo::getPixelEllipseMsg(int index, int width, double *spacing)//设定的宽度为像素椭圆的长轴
{
	int a = 0;
	int b = 0;
	if (index == 0 || index == 1)
	{
		a = width / 2.0;//长半轴
		b = (width*spacing[0]) / (2 * spacing[2]);//短半轴
	}
	else if (index == 2)
	{
		a = width / 2.0;//长半轴
		b = a;
	}
	return EllipseMsg(a, b);
}
SquareMsg mimics_damo::getPixelSquareMsg(int index, int width, double *spacing)//设定的宽度为像素椭圆的长轴
{
	int wr = 0;
	int hr = 0;
	if (index == 0 || index == 1)
	{
		wr = width / 2.0;//长半轴
		hr = (width*spacing[0]) / (2 * spacing[2]);//短半轴
	}
	else if (index == 2)
	{
		wr = width / 2.0;//长半轴
		hr = wr;
	}
	return SquareMsg(wr, hr);
}
int mimics_damo::getPixelYFromLine(int x, double k, const int point[2])
{
	double c = point[1] - k*point[0];
	double preciseY = k*x + c;
	return round(preciseY);
}
int mimics_damo::getPixelXFromLine(int y, double k, const int point[2])
{
	double c = point[1] - k*point[0];
	double preciseX = (y - c) / k;
	return round(preciseX);
}

void mimics_damo::closeEditMask()
{
	////切换普通模式
	//switchVtkClickModel(0);
	////切换光标
	////显示新光标
	////断开连接
	//for (int i = 0; i != 3; ++i)
	//{
	//	this->qview[i]->setCursor(Qt::ArrowCursor);
	//	this->circleCursorActor[i]->SetVisibility(0);
	//	this->circleCursorActor[i]->Modified();
	//	this->qview[i]->GetRenderWindow()->Render();

	//	disconnect(qview[i],0,0,0);
	//}

	this->mainWidget->setModel(0);

}


//void mimics_damo::switchVtkClickModel(int model)
//{
//	for (int i = 0; i != 3; ++i)
//		this->viewerCallback[i]->setClickModel(model);
//}

void mimics_damo::changeEditMaskPenMsg(int type, int width, /*int height,*/ int model)
{
	//for (int i = 0; i != 3; ++i)
	//	this->viewerCallback[i]->changeEditMaskPenMsg(type, width, height, model);
	//直接更新Source
	double spacing[3];
	this->ctImageData->GetSpacing(spacing);
	//先由像素宽度转为真实宽度
	double realWidth=width*spacing[0];
	this->mainWidget->changeEditMaskCursorSize(type, realWidth);
	this->penWidth = width;
	this->penType = (PenType)type;
}

void mimics_damo::ShowOpenDialog()
{

}

