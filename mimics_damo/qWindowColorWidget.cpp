#include "qWindowColorWidget.hpp"
#include <vtkImageViewer2.h>
#include <qspinbox.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qlayout.h>
QWindowColorWidget::QWindowColorWidget(QWidget * parent) : QWidget(parent) {
	this->colorLevelLabel=new QLabel("CT Color Level",this);

	this->colorWindowLabel=new QLabel("CT Color Window",this);

	this->grayScaleLabel = new QLabel("Grayscale:");

	this->colorWindowSpinBox = new QDoubleSpinBox(this);
	this->colorWindowSpinBox->setRange(0.01, 10000);

	this->colorLevelSpinBox=new QDoubleSpinBox(this);
	this->colorLevelSpinBox->setRange(-1024, 2893);

	this->grayScaleComboBox = new QComboBox(this);
	this->grayScaleComboBox->addItem("Custom Scale");
	this->grayScaleComboBox->addItem("Bone Scale");

	QHBoxLayout *colorLevelLayout = new QHBoxLayout;
	colorLevelLayout->addWidget(this->colorLevelLabel);
	colorLevelLayout->addWidget(this->colorLevelSpinBox);

	QHBoxLayout *colorWindowLayout = new QHBoxLayout;
	colorWindowLayout->addWidget(this->colorWindowLabel);
	colorWindowLayout->addWidget(this->colorWindowSpinBox);

	QHBoxLayout *grayScaleLayout = new QHBoxLayout;
	grayScaleLayout->addWidget(this->grayScaleLabel);
	grayScaleLayout->addWidget(this->grayScaleComboBox);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(colorWindowLayout);
	mainLayout->addLayout(colorLevelLayout);
	mainLayout->addLayout(grayScaleLayout);


}
//void setImageViewer(vtkSmartPointer<vtkImageViewer2> *imageViewer)
//{
//
//}
void QWindowColorWidget::emitWindowColorChangeMsg()
{
	emit windowColorChange(this->colorWindowSpinBox->value(),this->colorLevelSpinBox->value());
}
QWindowColorWidget::~QWindowColorWidget() {
	
}
