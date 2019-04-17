#include "createMaskDialog.hpp"
#include <QtWidgets>
CreateMaskDialog::CreateMaskDialog(QWidget * parent) : QDialog(parent) {
	setupUi(this);
	this->verticalLayout->setContentsMargins(11, 11, 11, 11);//控制与周围控件或对话框的间距
	this->setLayout(this->verticalLayout);
	this->setFixedHeight(sizeHint().height());
	this->setFixedWidth(650);
	//this->layout()->setSizeConstraint(QLayout::SetFixedSize);

	connect(minThresholdSpinBox,SIGNAL(valueChanged(int)), minThresholdSlider,SLOT(setValue(int)));
	connect(maxThresholdSpinBox, SIGNAL(valueChanged(int)), maxThresholdSlider, SLOT(setValue(int)));
	connect(minThresholdSlider, SIGNAL(valueChanged(int)), minThresholdSpinBox, SLOT(setValue(int)));
	connect(maxThresholdSlider, SIGNAL(valueChanged(int)), maxThresholdSpinBox, SLOT(setValue(int)));

	connect(minThresholdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(emitValueChangedSignal()));
	connect(maxThresholdSpinBox, SIGNAL(valueChanged(int)), this, SLOT(emitValueChangedSignal()));
	connect(minThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(emitValueChangedSignal()));
	connect(maxThresholdSlider, SIGNAL(valueChanged(int)), this, SLOT(emitValueChangedSignal()));

	connect(applyButton, SIGNAL(clicked()), this, SLOT(Accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

CreateMaskDialog::~CreateMaskDialog() {

}

void CreateMaskDialog::setScalarRange(int min, int max)
{
	this->minThresholdSpinBox->setRange(min, max);
	this->maxThresholdSpinBox->setRange(min, max);
	this->minThresholdSlider->setRange(min, max);
	this->maxThresholdSlider->setRange(min, max);
}

void CreateMaskDialog::initDialog(int minScalar, int maxScalar)
{
	this->setScalarRange(minScalar, maxScalar);

	this->minThresholdSpinBox->setValue(293);  //这个最低阈值待定
	this->minThresholdSlider->setValue(293);

	this->maxThresholdSpinBox->setValue(maxScalar);
	this->maxThresholdSlider->setValue(maxScalar);

	emitValueChangedSignal();
}

void CreateMaskDialog::emitValueChangedSignal()
{
	thresholdValueRange[0] = minThresholdSpinBox->text().toInt();
	thresholdValueRange[1] = maxThresholdSpinBox->text().toInt();
	if (thresholdValueRange[0] < thresholdValueRange[1])
	{
		emit thresholdValueChanged(thresholdValueRange[0], thresholdValueRange[1]);
	}
	//emitValueChangedSignal();
}

//int* thresholdValueDialog::getThresholdValue()
//{
//	thresholdValueRange[0] = minThresholdSpinBox->text().toInt();
//	thresholdValueRange[1] = maxThresholdSpinBox->text().toInt();
//
//	if (thresholdValueRange[0] < thresholdValueRange[1])
//	{
//		return thresholdValueRange;
//	}
//	else
//	return nullptr;
//}

//void thresholdValueDialog::closeEvent(QCloseEvent *event)
//{
//	//先关闭恢复功能测试区域增长
//	//emit thresholdValueChanged(0, 0);  
//	event->accept();
//}

void CreateMaskDialog::Accept()
{
	//QMessageBox::warning(this, "Accept", "illegal threshold value Range!", QMessageBox::Ok);
	emit thresholdValueChanged(0, 0);//关闭lookTable
	if (thresholdValueRange[0] < thresholdValueRange[1])
	{
		emit thresholdValueResult(thresholdValueRange[0], thresholdValueRange[1]);
	}
	else
	{
		QMessageBox::warning(this, "error", "illegal threshold value Range!", QMessageBox::Ok);
		return;
	}
	QDialog::accept();
}

void CreateMaskDialog::Close()
{
	//QMessageBox::warning(this, "Close", "illegal threshold value Range!", QMessageBox::Ok);
	emit thresholdValueChanged(0, 0);//关闭lookuptable...
	QDialog::close();
}

void CreateMaskDialog::closeEvent(QCloseEvent *event)
{
	this->Close();
}