#pragma once

#include <QVTKWidget.h>
class QVTK3DWidget : public QVTKWidget {
	Q_OBJECT

public:
	QVTK3DWidget(QWidget *parent = Q_NULLPTR);
	void setIndex(int index);
	~QVTK3DWidget();
signals:
	void spaceKeyPressEvent(int index,int model);
protected:
	void mouseMoveEvent(QMouseEvent * event);
	void keyPressEvent(QKeyEvent * event);
	/*void mousePressEvent(QMouseEvent * event);
	void mouseReleaseEvent(QMouseEvent * event);*/
private:
	int index;
	bool middleButtonPressEvent;
	bool widgetZoomEvent;
};
