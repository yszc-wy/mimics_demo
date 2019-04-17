#pragma once
#include <QWidget>
#include <vtkSmartPointer.h>
class QLabel;
class QDoubleSpinBox;
class QSlider;
class QComboBox;
class vtkImageViewer2;
class QWindowColorWidget : public QWidget {
	Q_OBJECT

public:
	QWindowColorWidget(QWidget * parent = Q_NULLPTR);
	~QWindowColorWidget();
	//void setImageViewer(vtkSmartPointer<vtkImageViewer2> *imageViewer);
signals:
	void windowColorChange(double window,double level);
private slots:
	void emitWindowColorChangeMsg();
private:
	QLabel *colorLevelLabel;
	QLabel *colorWindowLabel;
	QLabel *grayScaleLabel;
	QDoubleSpinBox *colorLevelSpinBox;
	QDoubleSpinBox *colorWindowSpinBox;
	QComboBox* grayScaleComboBox;
	
	vtkSmartPointer<vtkImageViewer2> imageViewer[3];
	//QSlider *colorLevelSlider;
	//QSlider *colorWindowSlider;
};
