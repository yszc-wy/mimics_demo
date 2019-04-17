#ifndef MIMICS_DAMO_H
#define MIMICS_DAMO_H

#include <QtWidgets/QMainWindow>
//#include "ui_mimics_damo.h"
#include <vtkSmartPointer.h>
#include <itkImage.h>
#include <list>
#include <memory>

//itk声明
#include <itkImage.h>
#include <itkImageSeriesReader.h>
#include <itkGDCMImageIO.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkThresholdImageFilter.h>
#include <itkVTKImageToImageFilter.h>
#include <itkImageToVTKImageFilter.h>


class QVTKWidget;
class QVTKImageWidget;
class vtkImageViewer2;
class vtkRenderer;
class vtkEventQtSlotConnect;
class QVTKMainViewer;
class vtkResliceImageViewer;
class vtkImagePlaneWidget;
class QLabel;
class vtkObject;
class QToolBar;
class QScrollBar;
class vtkImageData;
class vtkActor;
class ThresholdValueDialog;
class RegionGrowingDialog;
class CalculateObjDialog;
class ExportObjDialog;
class CreateMaskDialog;
class ImageProcessingDialog;
class QAction;
class QMenu;
class vtkLookupTable;
class vtkResliceCursorCallback;
class Mask;
class Object;
class vtkResliceCursorBasicCallback;
class vtkCellPicker;
class vtkImageActor;
class vtkImageViewer2;
class vtkRenderWindowInteractor;
class MaskListWidget;
class QProgressBar;
class ObjListWidget;
class EditMaskToolBar;
class vtkRegularPolygonSource;
class vtkEllipseArcSource;
class vtkMouseWheelBackwardCallback;
class vtkMouseWheelForwardCallback;
class vtkMouseWheelInteractorStyle;
class QVTK3DWidget;
class QFourViewWidget;
class RegionGrowingToolBar;


//edit mask工具类
class EllipseMsg {
public:
	EllipseMsg(int a, int b) :a(a), b(b) {}
	int a;//长
	int b;//短
};
class SquareMsg {
public:
	SquareMsg(int wr, int hr) :wr(wr), hr(hr) {}
	int wr;
	int hr;
};

//itk声明
static const unsigned int Dimension = 3;
typedef short InputPixelType;  //读取的时候确定的类型
typedef itk::Image<InputPixelType, Dimension>  //格式一定要准确，否则就会显示异常
InputImageType;
typedef itk::ImageSeriesReader<InputImageType>
ReaderType;
typedef itk::GDCMImageIO
ImageIOType;
typedef itk::GDCMSeriesFileNames
InputNamesGeneratorType;
typedef itk::ThresholdImageFilter< InputImageType >
FilterType;
typedef itk::ImageToVTKImageFilter<InputImageType>
ConnectorType;


typedef unsigned char DisplayPixelType;    //itk读取的unsigned char的二值化数据
typedef itk::Image< DisplayPixelType, Dimension > DisplayImageType;
typedef DisplayImageType::IndexType PixelIndexType;

//所有有关数据的操作全部在Main_window中进行，其他窗口只提供交互
//to do 数据存储在mainwindow中，数据的处理放到各个对话框中，各种必要的交互由各widget实现
class mimics_damo : public QMainWindow
{
	Q_OBJECT
		friend class vtkResliceCursorBasicCallback;
public:

	mimics_damo(QWidget *parent = 0);
	~mimics_damo();
protected:
	//void closeEvent(QCloseEvent *event);
private slots :
	//dialog
	void ShowCreateMaskDialog();
	void ShowOpenDialog();
	void ShowRegionGrowingDialog();
	void ShowCalculateObjDialog();
	void ShowImageProcessingDialog();
	void ShowExportObjDialog();
	void ShowEditMaskToolBar();

	//void showOrHidePlaneWidget();
	//void volumeRender();
	//vtk-itk响应槽
	//void updateAllWidgetCurrentMask(std::weak_ptr<Mask> mask);
	/*void updateLookUpTable(int min, int max);*/
	//void updateCurrentMask(std::shared_ptr<Mask> mask);

	void createMaskDataFromTresholdValue(int min, int max);
	void deleteMask(QString mask_name);
	void changeCurrentMaskName(QString mask_name,int row,int column);
	void setMaskVisible(QString mask_name, bool visible);
	//其他widget改变当前currentmask的方法
	void setCurrentMask(QString mask);

	void closeRegionGrowing(std::shared_ptr<Mask> newMask);
	void closeEditMask();
	//vtk响应模式切换
	//void switchVtkClickModel(int model);
	//edit mask 处理
	void changeEditMaskPenMsg(int type, int width, /*int height,*/ int model);

	//区域增长数据处理模块
	void regionGrowing(QVector<int> dims);
private:
	//数据处理函数区域增长
	DisplayImageType::Pointer constructITKImage(vtkImageData* originalImageData);
	//editmask数据处理函数
private slots :
	void BresenhamFill(int viewIndex, QVector<int>beforeImagePointDims, QVector<int> currentImagePointDims);//绘制直线
	void OnePointFill(int viewIndex, QVector<int> middleDims);
private:
	void drawWholePixel(int viewIndex, int x, int y, int slice, vtkSmartPointer<vtkImageData> imageData);//绘制一个像素
	void drawWholePixel(int viewIndex, const int middlePixelDims[3], vtkSmartPointer<vtkImageData> imageData);

	inline int pythagorean(int i, int radius);
	bool drawOnePixel(int pixDims[3], int model, vtkSmartPointer<vtkImageData> imageData);
	inline int getXFromEllipseY(int a, int b, int y);
	inline int round(double count);
	EllipseMsg getPixelEllipseMsg(int index, int width, double *spacing);
	SquareMsg getPixelSquareMsg(int index, int width, double *spacing);
	int getPixelYFromLine(int x, double k, const int point[2]);
	int getPixelXFromLine(int y, double k, const int point[2]);
private slots :
	//图像处理相关类
	void ImageProcessing(QString mask_name, QVector<QString> processing_order);
	//ITK总处理
	DisplayImageType::Pointer ITKSelectAlgorithm(QString processing_name, DisplayImageType::Pointer image);
	//拉普拉斯锐化
	DisplayImageType::Pointer ITKLaplacianSharpening(DisplayImageType::Pointer image);
	//高斯滤波
	DisplayImageType::Pointer ITKDiscreteGaussianFilter(DisplayImageType::Pointer image);
private:
	void createActions();
	//void createViewActions();
	//void setViewToolBars();
	void createMenus();
	void createToolBars();
	void createStatusBar();
	void createDockWidget();
	void createMainWidget();
	void createDataList();
	void initializeDialogAndToolBar();
	//void setRenderForMaskAndObject();

	//vtk数据读取,为ctimagedata赋值数据处理模块
	void loadCTImageData(const QString & path);
	//vtk响应函数

	//vtk-itk处理函数
	//ImageType::Pointer constructITKImage(vtkImageData* originalImageData);
	//void addMaskToMaskListAndShow(std::shared_ptr<Mask> newMask);
private:
	//action
	QAction *openAction;
	QAction *createMaskAction;
	QAction *regionGrowingAction;
	QAction *calculateObjAction;
	QAction *testAction;
	QAction *exportObjAction;
	QAction *editMaskAction;
	QAction *imageProcessingAction;
	//view action
	QAction *planeWidgetVisibleAction;
	QAction *volumeRenderAction;
	//dialog
	CreateMaskDialog *createMaskDialog;
	RegionGrowingDialog *regionGrowingDialog;
	CalculateObjDialog *calculateObjDialog;
	ExportObjDialog *exportObjDialog;
	ImageProcessingDialog *imageProcessingDialog;
	//function toolbar
	EditMaskToolBar* editMaskToolBar;
	RegionGrowingToolBar *regionGrowingToolBar;
	//menu
	QMenu *fileMenu;
	QMenu *editMenu;
	//statusBar widget
	QLabel *statusBarLabel;
	QLabel *progressLabel;
	QProgressBar *progressBar;

	//main tool bar
	QToolBar *fileToolBar;
	QToolBar *editToolBar;
	//主窗口布局
	QFourViewWidget* mainWidget;

	MaskListWidget *maskListWidget;
	QDockWidget *maskListDockWidget;
	ObjListWidget* objListWidget;
	QDockWidget *objListDockWidget;
	//vtkSmartPointer<vtkEventQtSlotConnect> connections;

	//数据集合
	vtkSmartPointer<vtkImageData> ctImageData;//ctimagedata
	//用指针的原因是要实现数据共享，在mainwindow中的更新（mask的添加或删除）可以随时反映到fourwidget中
	//但用指针共享的缺点就是数据删除困难，因为只要有一个共享指针没有被删除就会一直存在，所以有些共享量用weak_ptr来防止增加引用计数
	std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr;//管理mask资源的只有这个类
	QString currentMaskName;//当前处理的mask,这个怎么理解？一旦新建
	QString currentRegionGrowingMask;//区域增长用到的mask
	std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrMapPtr;//obj资源管理
	//用时间命名

	//edit Mask
	enum PenType { CIRCLE, SQUARE, LASSO, LIVEWIRE }penType;
	int penWidth;
	enum PenModel { DRAW, ERASE }penModel;
};

inline int mimics_damo::pythagorean(int i, int radius)
{
	return sqrt(pow(radius, 2) - pow(i, 2));
}
inline int mimics_damo::getXFromEllipseY(int a, int b, int y)
{
	return sqrt(pow(a, 2)*(1 - pow(y, 2) / (double)pow(b, 2)));
}
inline int mimics_damo::round(double count)
{
	if (count + 0.5 > (int)count + 1)
	{
		return (int)count + 1;
	}
	else {
		return (int)count;
	}
}

#endif // MIMICS_DAMO_H
