#include "qVtkImageWidget.hpp"
#include "qevent.h"
#include <vtkImageViewer2.h>
#include <qmessagebox.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
const int ZOOM = 1;
const int RECOVER = 0;
QVTKImageWidget::QVTKImageWidget(QWidget *parent) : QVTKWidget(parent),
	imageViewer(nullptr),
	//originTransformMatrix(nullptr),
	rightButtonPressEvent(false),
	leftButtonPressEvent(false),
	widgetZoomEvent(false),
	ctrlKeyPressEvent(false),
	middleButtonPressEvent(false),
	index(0)
{
	WindowLevelStartPosition[0] = 0;
	WindowLevelStartPosition[1] = 0;
	WindowLevelCurrentPosition[0] = 0;
	WindowLevelCurrentPosition[1] = 0;
	WindowLevelInitial[0] = 0;
	WindowLevelInitial[1] = 0;
	lastMouseMovePosition[0]=0;
	lastMouseMovePosition[1] = 0;
	currentMouseMovePosition[0]=0;
	currentMouseMovePosition[1] = 0;
}
void QVTKImageWidget::setIndex(int index)
{
	this->index = index;
}

QVTKImageWidget::~QVTKImageWidget() {
	
}

void QVTKImageWidget::enterEvent(QEvent *event)
{
	emit showCursorActor();
}
void QVTKImageWidget::leaveEvent(QEvent *event)
{
	emit hideCursorActor();
}
void QVTKImageWidget::wheelEvent(QWheelEvent *event)
{
	if (this->ctrlKeyPressEvent)
	{
		//图像放大缩小,ctrl+鼠标滚轮
		int delta = event->delta();

		if (delta > 0)
		{
			this->imageViewer->GetRenderer()->GetActiveCamera()->Zoom(1.05);
		}
		else if (delta < 0)
		{
			this->imageViewer->GetRenderer()->GetActiveCamera()->Zoom(0.95);
		}
		this->imageViewer->GetRenderer()->GetActiveCamera()->Modified();
		this->imageViewer->Render();
	}
	else
		emit mouseWheelEvent(event->delta());
	//QVTKWidget::wheelEvent(event);
}
void QVTKImageWidget::mousePressEvent(QMouseEvent * event)
{
	//QMessageBox::warning(NULL, "what happen1?", "1", QMessageBox::Ok);
	if (Qt::RightButton == event->button())
	{
		this->rightButtonPressEvent = true;
		this->WindowLevelStartPosition[0] = event->x();
		this->WindowLevelStartPosition[1] = event->y();
		//QMessageBox::warning(NULL, "what happen2?", "2", QMessageBox::Ok);
		this->WindowLevelInitial[0] = this->imageViewer->GetColorWindow();
		this->WindowLevelInitial[1] = this->imageViewer->GetColorLevel();
		//QMessageBox::warning(NULL, "what happen3?", "3", QMessageBox::Ok);

	}
	else if (Qt::MiddleButton == event->button())
	{
		this->middleButtonPressEvent = true;
	}
	else if (Qt::LeftButton == event->button())
	{
		this->currentMouseMovePosition[0] = event->x();
		this->currentMouseMovePosition[1] = event->y();
		this->leftButtonPressEvent = true;

		if(!ctrlKeyPressEvent)
			emit leftButtonPressHappend(event->x(),event->y());
	}
	//QVTKWidget::mousePressEvent(event);如果再次使用此函数会使得vtkinteractor起效结果不可控制
}

void QVTKImageWidget::mouseReleaseEvent(QMouseEvent * event)
{
	if (Qt::RightButton == event->button())
	{
		this->rightButtonPressEvent = false;
	}
	else if (Qt::MiddleButton == event->button())
	{
		this->middleButtonPressEvent = false;
	}
	else if (Qt::LeftButton == event->button())
	{
		this->leftButtonPressEvent = false;
	}
	//QVTKWidget::mouseReleaseEvent(event);
}
void QVTKImageWidget::mouseMoveEvent(QMouseEvent * event)
{
	this->setFocus();
	if (this->rightButtonPressEvent==true&&this->ctrlKeyPressEvent==false)
	{
		this->WindowLevelCurrentPosition[0] = event->x();
		this->WindowLevelCurrentPosition[1] = event->y();

		emit rightButtonPress_MouseMoveHappend(
			this->WindowLevelStartPosition[0],
			this->WindowLevelStartPosition[1],
			this->WindowLevelCurrentPosition[0],
			this->WindowLevelCurrentPosition[1],
			this->WindowLevelInitial[0],
			this->WindowLevelInitial[1]);
	}
	//else if (this->rightButtonPressEvent == true && this->ctrlKeyPressEvent == true)
	//{
	//	this->lastMouseMovePosition[0]= this->currentMouseMovePosition[0];
	//	this->lastMouseMovePosition[1] = this->currentMouseMovePosition[1];
	//	this->currentMouseMovePosition[0]=event->x();
	//	this->currentMouseMovePosition[1] = event->y();
	//	int dy = currentMouseMovePosition[1] - lastMouseMovePosition[1];
	//	if (dy > 0)
	//	{
	//		this->imageViewer->GetRenderer()->GetActiveCamera()->Zoom(1.05);
	//	}
	//	else if (dy < 0)
	//	{
	//		this->imageViewer->GetRenderer()->GetActiveCamera()->Zoom(0.95);
	//	}
	//	this->imageViewer->GetRenderer()->GetActiveCamera()->Modified();
	//	this->imageViewer->Render();
	//}
	else if (this->ctrlKeyPressEvent&&this->leftButtonPressEvent)
	{
		////ctrl+鼠标左键 图像平移
		//vtkInteractorStyleImage *style = this->imageViewer->GetInteractorStyle();
		//if (style)
		//{
		//	QVTKWidget::mouseMoveEvent(event);
		//	style->OnMouseMove();//利用vtk执行图片移动的响应
		//}
		//QMessageBox::warning(this, tr("..."), tr("ok?"), QMessageBox::Yes);

		this->lastMouseMovePosition[0]= this->currentMouseMovePosition[0];
		this->lastMouseMovePosition[1] = this->currentMouseMovePosition[1];
		this->currentMouseMovePosition[0]=event->x();
		this->currentMouseMovePosition[1] = event->y();

		int dx = currentMouseMovePosition[0] - lastMouseMovePosition[0];
		int dy = currentMouseMovePosition[1] - lastMouseMovePosition[1];
	
		vtkSmartPointer<vtkCamera> camera = this->imageViewer->GetRenderer()->GetActiveCamera();
		
		double up[3];
		camera->GetViewUp(up);
		double pos[3];
		camera->GetPosition(pos);
		double focus[3];
		camera->GetFocalPoint(focus);
		double dir[3];
		for (int i = 0; i != 3; ++i)
		{
			dir[i] = pos[i] - focus[i];
		}
		double right[3];
		vtkMath::Cross(dir, up, right);

		vtkMath::Normalize(up);
		vtkMath::Normalize(dir);
		vtkMath::Normalize(right);

		for (int i = 0; i != 3; ++i)
		{
			focus[i] += 0.5*(dx*right[i] + dy*up[i]);
		}

		camera->SetFocalPoint(focus);
		camera->Modified();
		this->imageViewer->Render();
	}
	emit leftButtonPressOrNot_MouseMoveHappend(this->leftButtonPressEvent,event->x(),event->y());

	//QVTKWidget::mouseMoveEvent(event);
}
void QVTKImageWidget::setImageViewer(vtkSmartPointer<vtkImageViewer2> imageViewer)
{
	this->imageViewer = imageViewer;
	this->imageViewer->GetRenderer()->ResetCameraClippingRange();
	//this->originTransformMatrix = this->imageViewer->GetRenderer()->GetActiveCamera()->GetModelTransformMatrix();
}
void QVTKImageWidget::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Space&&this->widgetZoomEvent==false)
	{
		this->widgetZoomEvent = true;
		emit spaceKeyPressEvent(this->index, ZOOM);
	}
	else if (event->key() == Qt::Key_Space&&this->widgetZoomEvent == true)
	{
		this->widgetZoomEvent = false;
		emit spaceKeyPressEvent(this->index, RECOVER);
	}
	else if (event->key() == Qt::Key_Control)
	{
		this->ctrlKeyPressEvent = true;
	}
	else if (event->key() == Qt::Key_R)
	{	//按R恢复
		//QMessageBox::warning(this, tr("..."), tr("ok?"), QMessageBox::Yes);
		this->imageViewer->GetRenderer()->ResetCamera();
		this->imageViewer->Render();
	}
	//QVTKWidget::keyPressEvent(event);
}

void QVTKImageWidget::keyReleaseEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Control)
	{
		this->ctrlKeyPressEvent = false;
	}
	//QVTKWidget::keyReleaseEvent(event);
}

//void QVTKImageWidget::RecoverCamera()
//{
//
//}
//void QVTKImageWidget::ZoomCamera(double factor)
//{
//	
//}