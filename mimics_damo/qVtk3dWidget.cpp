#include "qVtk3dWidget.hpp"
#include "qevent.h"
const int ZOOM = 1;
const int RECOVER = 0;
QVTK3DWidget::QVTK3DWidget(QWidget *parent) : QVTKWidget(parent),
	index(0),
	middleButtonPressEvent(false),
	widgetZoomEvent(false)
{	
}

QVTK3DWidget::~QVTK3DWidget() {
	
}

void QVTK3DWidget::setIndex(int index)
{
	this->index = index;
}

void QVTK3DWidget::mouseMoveEvent(QMouseEvent * event)
{
	this->setFocus();
	QVTKWidget::mouseMoveEvent(event);
}
void QVTK3DWidget::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Space&&this->widgetZoomEvent == false)
	{
		this->widgetZoomEvent = true;
		emit spaceKeyPressEvent(this->index, ZOOM);
	}
	else if (event->key() == Qt::Key_Space&&this->widgetZoomEvent == true)
	{
		this->widgetZoomEvent = false;
		emit spaceKeyPressEvent(this->index, RECOVER);
	}
}
//void QVTK3DWidget::mousePressEvent(QMouseEvent * event)
//{
//	this->middleButtonPressEvent = true;
//	QVTKWidget::mousePressEvent(event);
//}
//void QVTK3DWidget::mouseReleaseEvent(QMouseEvent * event)
//{
//	this->middleButtonPressEvent = false;
//	QVTKWidget::mousePressEvent(event);
//}