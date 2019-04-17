#pragma once
#include <QVTKWidget.h>
#include <vtkSmartPointer.h>
#include <vtkMatrix4x4.h>
class vtkImageViewer2;
class QVTKImageWidget : public QVTKWidget {
	Q_OBJECT

public:
	QVTKImageWidget(QWidget *parent = Q_NULLPTR);
	~QVTKImageWidget();
	void setIndex(int index);
	void setImageViewer(vtkSmartPointer<vtkImageViewer2> imageViewer);
signals:
	void showCursorActor();
	void hideCursorActor();
	void mouseWheelEvent(int delta);
	//相机操作
	//void R_KeyPressEvent();
	//void ctrlKeyPress_MouseWheelEvent(int delta);
	//void ctrlKeyPress_LeftButtonPress_MouseMoveEvent(int startPositionX, int startPositionY, int currentPositionX, int currentPositionY);
	
	//WindowLevel
	void rightButtonPress_MouseMoveHappend(int startPositionX,int startPositionY,int currentPositionX,int currentPositionY,double initalW,double initalL);
	void spaceKeyPressEvent(int index,int model);
	void leftButtonPressHappend(int x,int y);
	void leftButtonPressOrNot_MouseMoveHappend(bool,int x,int y);
	
protected:
	void wheelEvent(QWheelEvent * event);
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);
	void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);
	void mouseMoveEvent(QMouseEvent * event);
	void keyPressEvent(QKeyEvent * event);
	void keyReleaseEvent(QKeyEvent * event);
private:

	vtkSmartPointer<vtkImageViewer2> imageViewer;

	bool rightButtonPressEvent;
	bool leftButtonPressEvent;
	bool middleButtonPressEvent;
	bool ctrlKeyPressEvent;
	bool widgetZoomEvent;
	int index;

	int WindowLevelStartPosition[2];
	int WindowLevelCurrentPosition[2];
	double WindowLevelInitial[2];
	int lastMouseMovePosition[2];
	int currentMouseMovePosition[2];
	
};
