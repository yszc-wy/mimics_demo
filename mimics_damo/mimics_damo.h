#ifndef MIMICS_DAMO_H
#define MIMICS_DAMO_H

#include <QtWidgets/QMainWindow>
//#include "ui_mimics_damo.h"
#include <vtkSmartPointer.h>
#include <itkImage.h>
#include <list>
#include <memory>

//itk����
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


//edit mask������
class EllipseMsg {
public:
	EllipseMsg(int a, int b) :a(a), b(b) {}
	int a;//��
	int b;//��
};
class SquareMsg {
public:
	SquareMsg(int wr, int hr) :wr(wr), hr(hr) {}
	int wr;
	int hr;
};

//itk����
static const unsigned int Dimension = 3;
typedef short InputPixelType;  //��ȡ��ʱ��ȷ��������
typedef itk::Image<InputPixelType, Dimension>  //��ʽһ��Ҫ׼ȷ������ͻ���ʾ�쳣
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


typedef unsigned char DisplayPixelType;    //itk��ȡ��unsigned char�Ķ�ֵ������
typedef itk::Image< DisplayPixelType, Dimension > DisplayImageType;
typedef DisplayImageType::IndexType PixelIndexType;

//�����й����ݵĲ���ȫ����Main_window�н��У���������ֻ�ṩ����
//to do ���ݴ洢��mainwindow�У����ݵĴ���ŵ������Ի����У����ֱ�Ҫ�Ľ����ɸ�widgetʵ��
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
	//vtk-itk��Ӧ��
	//void updateAllWidgetCurrentMask(std::weak_ptr<Mask> mask);
	/*void updateLookUpTable(int min, int max);*/
	//void updateCurrentMask(std::shared_ptr<Mask> mask);

	void createMaskDataFromTresholdValue(int min, int max);
	void deleteMask(QString mask_name);
	void changeCurrentMaskName(QString mask_name,int row,int column);
	void setMaskVisible(QString mask_name, bool visible);
	//����widget�ı䵱ǰcurrentmask�ķ���
	void setCurrentMask(QString mask);

	void closeRegionGrowing(std::shared_ptr<Mask> newMask);
	void closeEditMask();
	//vtk��Ӧģʽ�л�
	//void switchVtkClickModel(int model);
	//edit mask ����
	void changeEditMaskPenMsg(int type, int width, /*int height,*/ int model);

	//�����������ݴ���ģ��
	void regionGrowing(QVector<int> dims);
private:
	//���ݴ�������������
	DisplayImageType::Pointer constructITKImage(vtkImageData* originalImageData);
	//editmask���ݴ�����
private slots :
	void BresenhamFill(int viewIndex, QVector<int>beforeImagePointDims, QVector<int> currentImagePointDims);//����ֱ��
	void OnePointFill(int viewIndex, QVector<int> middleDims);
private:
	void drawWholePixel(int viewIndex, int x, int y, int slice, vtkSmartPointer<vtkImageData> imageData);//����һ������
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
	//ͼ���������
	void ImageProcessing(QString mask_name, QVector<QString> processing_order);
	//ITK�ܴ���
	DisplayImageType::Pointer ITKSelectAlgorithm(QString processing_name, DisplayImageType::Pointer image);
	//������˹��
	DisplayImageType::Pointer ITKLaplacianSharpening(DisplayImageType::Pointer image);
	//��˹�˲�
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

	//vtk���ݶ�ȡ,Ϊctimagedata��ֵ���ݴ���ģ��
	void loadCTImageData(const QString & path);
	//vtk��Ӧ����

	//vtk-itk������
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
	//�����ڲ���
	QFourViewWidget* mainWidget;

	MaskListWidget *maskListWidget;
	QDockWidget *maskListDockWidget;
	ObjListWidget* objListWidget;
	QDockWidget *objListDockWidget;
	//vtkSmartPointer<vtkEventQtSlotConnect> connections;

	//���ݼ���
	vtkSmartPointer<vtkImageData> ctImageData;//ctimagedata
	//��ָ���ԭ����Ҫʵ�����ݹ�����mainwindow�еĸ��£�mask����ӻ�ɾ����������ʱ��ӳ��fourwidget��
	//����ָ�빲���ȱ���������ɾ�����ѣ���ΪֻҪ��һ������ָ��û�б�ɾ���ͻ�һֱ���ڣ�������Щ��������weak_ptr����ֹ�������ü���
	std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr;//����mask��Դ��ֻ�������
	QString currentMaskName;//��ǰ�����mask,�����ô��⣿һ���½�
	QString currentRegionGrowingMask;//���������õ���mask
	std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrMapPtr;//obj��Դ����
	//��ʱ������

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
