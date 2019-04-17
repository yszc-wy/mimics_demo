#pragma once
#include <QWidget>
#include <vtkSmartPointer.h>
#include <memory>

//#include <itkImage.h>
//#include <itkImageSeriesReader.h>
//#include <itkGDCMImageIO.h>
//#include <itkGDCMSeriesFileNames.h>
//#include <itkThresholdImageFilter.h>
//#include <itkVTKImageToImageFilter.h>
//#include <itkImageToVTKImageFilter.h>

class vtkImageData;
class vtkRenderer;
class vtkRegularPolygonSource;
class vtkActor;
class vtkCellPicker;
class vtkResliceCursorCallback;
class vtkImageViewer2;
class vtkRenderWindowInteractor;
class vtkImagePlaneWidget;
class QVTKImageWidget;
class QVTK3DWidget;
class QVTKWidget;
class QScrollBar;
class QToolBar;
class Object;
class Mask;
class vtkEventQtSlotConnect;
class vtkObject;



////itk声明
//static const unsigned int Dimension = 3;
//typedef short InputPixelType;  //读取的时候确定的类型
//typedef itk::Image<InputPixelType, Dimension>  //格式一定要准确，否则就会显示异常
//InputImageType;
//typedef itk::ImageSeriesReader<InputImageType>
//ReaderType;
//typedef itk::GDCMImageIO
//ImageIOType;
//typedef itk::GDCMSeriesFileNames
//InputNamesGeneratorType;
//typedef itk::ThresholdImageFilter< InputImageType >
//FilterType;
//typedef itk::ImageToVTKImageFilter<InputImageType>
//ConnectorType;
//
//
//typedef unsigned char DisplayPixelType;    //itk读取的unsigned char的二值化数据
//typedef itk::Image< DisplayPixelType, Dimension > DisplayImageType;
//typedef DisplayImageType::IndexType PixelIndexType;

//该类只负责交互不负责数据的加工,数据加工放在mainview中
class QFourViewWidget : public QWidget {
	Q_OBJECT
	//////
public:
	QFourViewWidget(QWidget * parent = Q_NULLPTR);
	~QFourViewWidget();
	void setModel(int model);
	//只要setctimagedata没运行过就锁定响应
	void setCTImageData(vtkSmartPointer<vtkImageData> ctImageData);
	//void setCurrentMask(std::weak_ptr<Mask>);
	void getImageScalarRange(double *scalarRange);
	void setMaskPtrMapPtr(std::weak_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr);
	void setObjPtrMapPtr(std::weak_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrMapPtr);
	void setCurrentMaskPtr(std::weak_ptr<Mask> );
	//mask改为实时显示
	//void showMask(const QString& name,const Mask& mk);
	//void clearMask(const QString& name, const Mask& mk);
	//void clearAllMask();

	//为mask创建actor并导入显示
	void createActorForMask(std::weak_ptr<Mask> );
	void reRender();

	//editmask改变光标性质
	void changeEditMaskCursorSize(int type, int realWidth);

	//calculateobj需要的值
	vtkSmartPointer<vtkRenderer> getRen3dViewer();
	QVTK3DWidget* get3DViewWidget();
signals:
	void currentMaskChanged(std::weak_ptr<Mask>);
	void changeStatusLabelText(const QString&);
	void updateMaskListWidget(const QString&);
	void pickImageDims(QVector<int>);
	void editMaskClick(int,QVector<int>);
	void editMaskClickMove(int, QVector<int>, QVector<int>);
private slots:
	//void createMaskFromTresholdValue(int min, int max);
	//在createmaskdialog打开时实时更新颜色映射表
	void updateLookUpTableForCreateMaskDialog(int min,int max);
	void OnFourViewSpaceKeyPressEvent(int viewIndex, int model);
	void updateSliceFromImagePlaneWidget0();
	void updateSliceFromImagePlaneWidget1();
	void updateSliceFromImagePlaneWidget2();
	

	//action slot
	void showOrHidePlaneWidget();
	void volumeRender();

	/*void synchronizeCursorRenderCamera(vtkObject *caller);*/
	//void updateThreeViewSliceFromImagePlaneWidget(vtkObject *obj);
private:
	//void updateCurrentMask(std::weak_ptr<Mask>);
	void setRenderForMaskAndObjectType();
	void initVariable();
	void updateThreeViewSliceFromImagePlaneWidget(int index);
	void createWidget();
	void initScrollBar();
	void createVTKFourImageView();
	void updateVTKImageSliceFormScrollBar(int viewIndex, int scrollIndex);
	void updateCursor(int viewIndex, int slice);
	void updatePlaneWidget(int viewIndex, int slice);
	void updataMaskSlice(int viewIndex, int slice);
	void updateScrollBar(int viewIndex, int slice);
	void updateImageViewSlice(int viewIndex, int slice);
	void updateFourViewSlice(int viewIndex, int slice);
	void imageEnlarge(int viewIndex, int enlargeFactor);

	//将三视图的响应处理全部放到四视图中
	void OnThreeViewLeftButtonPressOrNot_MouseMoveEvent(int viewIndex,bool leftButtonPressEvent,int x,int y);
	void OnThreeViewLeftButtonPressEvent(int viewIndex,int x,int y);
	void OnThreeViewMouseWheelEvent(int viewIndex, int delta);
	//void OnThreeViewRPressEvent(int viewIndex); //将缩放的图片恢复到初始缩放状态
	//void OnThreeViewCtrlMouseWhellEvent(int viewIndex, int delta);//缩放图片
	void OnThreeViewRightButtonPress_MouseMoveEvent(int viewIndex, int startPositionX, int startPositionY,
		int currentPositionX, int currentPositionY, double initalW, double initalL);


	void updateWindowLevel(int index, int startPositionX, int startPositionY,
		int currentPositionX, int currentPositionY, double initalW, double initalL);
	void zoomOrRecoverWidget(int viewIndex, int model);
	vtkSmartPointer<vtkEventQtSlotConnect> imagePlaneWidgetEventToQSLOTConnections;


private:
	QWidget* viewWidget[4];
	//vtkimagewidget是qt widget用于保存vtk 组件
	QVTKImageWidget *vtkImageWidget[3];
	QVTK3DWidget *vtk3DWidget;
	QScrollBar* viewScrollBar[3];
	QToolBar* viewToolBar;
	//3dview action
	QAction *planeWidgetVisibleAction;
	bool planeWidgetVisible;
	QAction *volumeRenderAction;
	bool volumeRenderClose;

	vtkSmartPointer< vtkImageViewer2 > imageViewer[3];
	vtkSmartPointer<vtkRenderer> ren_3dWidget;
	vtkSmartPointer <vtkRenderWindowInteractor> rwi_vtkImageWidget[3];//此interactor来源于VTKWidget
	vtkSmartPointer<vtkImagePlaneWidget> imagePlaneWidget[3];

	vtkSmartPointer<vtkImageData> ctImageData;//ctimagedata是main中ctimagedata的指针
	vtkSmartPointer<vtkActor> crossCursorActor[3];
	vtkSmartPointer<vtkRenderer> cursorRen[3];
	vtkSmartPointer<vtkRegularPolygonSource> circleCursorSource[3];
	vtkSmartPointer<vtkActor> circleCursorActor[3];//改位置
	vtkSmartPointer<vtkCellPicker> picker;  //图像拾取器							
	vtkSmartPointer<vtkResliceCursorCallback> viewerCallback[3];//callback类对象

	
	std::weak_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr;//管理mask资源的只有这个类
	std::weak_ptr<Mask> currentMask;//保存currentMask的指针 to check currentMask前有*,为啥？
	std::weak_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrMapPtr;//obj资源管理

	
private:
	enum Model { NORMAL, REGIONGROWING, EDITMASK } displayModel;
	void crossCursorLocateModel(int viewIndex,int x,int y);
	void regionRrowingModel(int viewIndex,int x,int y);
	void editMaskModel_click(int viewIndex,int x,int y);
	void editMaskModel_mouseMove(int viewIndex, bool leftButtonPressEvent,int x,int y);
	//各种点击模式处理的函数和变量
	int setCurrentImagePositionAndDims(double *precisePosition);
	int setCurrentCoordsMsg(int viewIndex,int x,int y);

	//inline int pythagorean(int i, int radius);
	//bool drawOnePixel(int pixDims[3], int model, vtkSmartPointer<vtkImageData> imageData);
	//inline int getXFromEllipseY(int a, int b, int y);
	//inline int round(double count);
	//EllipseMsg getPixelEllipseMsg(int index, int width, double *spacing);
	//SquareMsg getPixelSquareMsg(int index, int width, double *spacing);
	//int getPixelYFromLine(int x, double k, const int point[2]);
	//int getPixelXFromLine(int y, double k, const int point[2]);

	//void drawWholePixel(int viewIndex, int x, int y, int slice, vtkSmartPointer<vtkImageData> imageData);
	//void drawWholePixel(int viewIndex, const int middlePixelDims[3], vtkSmartPointer<vtkImageData> imageData);
	//void BresenhamFill(int viewIndex, const int beforeImagePointDims[3], const int currentImagePointDims[3]);


	int imagePickPointDims[3]; //图像index
	double imagePickPointPosition[3];//图像picker出来的实际坐标
	double cursorPickPosition[3];//光标的坐标

	//edit Mask
	//enum PenType { CIRCLE, SQUARE, LASSO, LIVEWIRE }penType;
	//int penWidth;
	//enum PenModel { DRAW, ERASE }penModel;
	//才没有数据时冻结响应
	bool is_freeze;
	//region grown
	//std::weak_ptr<Mask> sourceMask;//to check使用弱指针也有风险，可能导致访问为空域
	//std::shared_ptr<Mask> targetMask;//区域增长使用的mask

};
//inline int QFourViewWidget::pythagorean(int i, int radius)
//{
//	return sqrt(pow(radius, 2) - pow(i, 2));
//}
//inline int QFourViewWidget::getXFromEllipseY(int a, int b, int y)
//{
//	return sqrt(pow(a, 2)*(1 - pow(y, 2) / (double)pow(b, 2)));
//}
//inline int QFourViewWidget::round(double count)
//{
//	if (count + 0.5 > (int)count + 1)
//	{
//		return (int)count + 1;
//	}
//	else {
//		return (int)count;
//	}
//}

