#include "editMaskToolBar.hpp"
#include "qlabel.h"
#include "qcombobox.h"
#include "qspinbox.h"
#include "qlayout.h"
#include <qbuttongroup.h>
#include <qradiobutton.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
EditMaskToolBar::EditMaskToolBar(const QString &title, QWidget * parent):QToolBar(title,parent),recursion(false)
{
	penSettingWidget = new QWidget(this);
	typeLabel = new QLabel("Type:", penSettingWidget);
	typeComboBox=new QComboBox(penSettingWidget);
	typeComboBox->addItem("Circle");
	typeComboBox->addItem("Square");
	typeComboBox->addItem("Lasso");
	typeComboBox->addItem("LiveWire");

	widthLabel=new QLabel("Pen Width:",penSettingWidget);
	widthSpinBox=new QSpinBox(penSettingWidget);
	widthSpinBox->setRange(1, 1000);
	widthSpinBox->setValue(30);

	//heightLabel= new QLabel("Height:", penSettingWidget);
	//heightSpinBox=new QSpinBox(penSettingWidget);
	//heightSpinBox->setRange(1, 1000);
	//heightSpinBox->setValue(20);

	QVBoxLayout *typeLayout = new QVBoxLayout;
	typeLayout->addWidget(typeLabel);
	typeLayout->addWidget(typeComboBox);

	QVBoxLayout *widthLayout = new QVBoxLayout;
	widthLayout->addWidget(widthLabel);
	widthLayout->addWidget(widthSpinBox);

	//QVBoxLayout *heightLayout = new QVBoxLayout;
	//heightLayout->addWidget(heightLabel);
	//heightLayout->addWidget(heightSpinBox);

	QHBoxLayout *penSettingLayout = new QHBoxLayout;
	penSettingLayout->addLayout(typeLayout);
	penSettingLayout->addLayout(widthLayout);
	//penSettingLayout->addLayout(heightLayout);

	penSettingWidget->setLayout(penSettingLayout);

	penModelWidget=new QWidget(this);

	radioButtonGroup = new QButtonGroup(penModelWidget);
	drawButton = new QRadioButton("Draw", penModelWidget);
	eraseButton = new QRadioButton("Erase", penModelWidget);
	eraseButton->setChecked(true);
	radioButtonGroup->addButton(drawButton,1);
	radioButtonGroup->addButton(eraseButton,0);

	//sameWHCheckBox = new QCheckBox("Same Width && Height", penModelWidget);
	//sameWHCheckBox->setChecked(true);

	//connect(this->widthSpinBox, SIGNAL(valueChanged(int)), this, SLOT(synchronizeSpinBox(int)));
	//connect(this->heightSpinBox, SIGNAL(valueChanged(int)), this, SLOT(synchronizeSpinBox(int)));

	QHBoxLayout* penModelLayout = new QHBoxLayout;
	penModelLayout->addWidget(drawButton);
	penModelLayout->addWidget(eraseButton);

	//QVBoxLayout*penModelLayout = new QVBoxLayout;
	//penModelLayout->addLayout(radioLayout);
	//penModelLayout->addWidget(sameWHCheckBox);

	penModelWidget->setLayout(penModelLayout);

	closeButton = new QPushButton("Close", this);
	connect(this->closeButton, SIGNAL(clicked()), this, SLOT(close()));

	connect(this->typeComboBox, SIGNAL(activated(int)),
		this, SLOT(emitEditMaskPenMsg()));
	connect(this->widthSpinBox, SIGNAL(valueChanged(int)),
		this, SLOT(emitEditMaskPenMsg()));
	//connect(this->heightSpinBox, SIGNAL(valueChanged(int)),
		//this, SLOT(emitEditMaskPenMsg()));
	connect(this->radioButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)), 
		this, SLOT(emitEditMaskPenMsg()));

	this->addWidget(penSettingWidget);
	this->addSeparator();
	this->addWidget(penModelWidget);
	this->addSeparator();
	this->addWidget(closeButton);

}
void EditMaskToolBar::showEvent(QShowEvent* event)
{
	emitEditMaskPenMsg();
	if (isFloating()) 
	{
		if (recursion)
		{
			recursion = false;
		}
		else
		{
			recursion = true;
			hide(); 
			setWindowFlags(windowFlags() & ~Qt::FramelessWindowHint); 
			setFixedSize(sizeHint()); 
			show();
		}

	}
	else
	{
		setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX); 
		setMinimumSize(0, 0);
	}

	QToolBar::showEvent(event);
}

void EditMaskToolBar::emitEditMaskPenMsg()
{
	//QMessageBox::warning(NULL, "what happen?", ".....", QMessageBox::Ok);
	emit editMaskPenMsg(
		this->typeComboBox->currentIndex(), 
		this->widthSpinBox->value(), 
		/*this->heightSpinBox->value(), */
		this->radioButtonGroup->checkedId()
	);
}
//void EditMaskToolBar::synchronizeSpinBox(int value)
//{
//	if (this->sameWHCheckBox->checkState() == Qt::Checked)
//	{
//		this->widthSpinBox->setValue(value);
//		this->heightSpinBox->setValue(value);
//	}
//}

//void EditMaskToolBar::changeModelToEditMask()
//{
//	//emit changeVtkClickModel(2);
//}

EditMaskToolBar::~EditMaskToolBar() {
	
}

void EditMaskToolBar::closeEvent(QCloseEvent *event)
{
	emit closeToolBar();
}