#include "regionGrowingToolbar.hpp"
#include <qlabel.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <mask.h>
RegionGrowingToolBar::RegionGrowingToolBar(const QString &title, QWidget * parent) : QToolBar(title, parent), recursion(false){
	mainWidget = new QWidget(this);
	
	this->sourceLabel=new QLabel("Source:", mainWidget);
	this->sourceComboBox=new QComboBox(mainWidget);

	this->arrowLabel=new QLabel("<-->");

	this->targetLabel=new QLabel("Target:", mainWidget);
	this->targetComboBox=new QComboBox(mainWidget);

	this->closeButton=new QPushButton("Close", mainWidget);
	connect(this->closeButton, SIGNAL(clicked()), this, SLOT(close()));

	QVBoxLayout* sourceLayout = new QVBoxLayout;
	sourceLayout->addWidget(sourceLabel);
	sourceLayout->addWidget(sourceComboBox);

	QVBoxLayout* arrowLayout = new QVBoxLayout;
	arrowLayout->addStretch();
	arrowLayout->addWidget(arrowLabel);

	QVBoxLayout* targetLayout = new QVBoxLayout;
	targetLayout->addWidget(targetLabel);
	targetLayout->addWidget(targetComboBox);

	QHBoxLayout* mainLayout = new QHBoxLayout;
	mainLayout->addLayout(sourceLayout);
	mainLayout->addLayout(arrowLayout);
	mainLayout->addLayout(targetLayout);

	mainWidget->setLayout(mainLayout);
	this->addWidget(mainWidget);
}

RegionGrowingToolBar::~RegionGrowingToolBar() {
	
}

void RegionGrowingToolBar::updateComboBox()
{
	this->sourceComboBox->clear();
	this->targetComboBox->clear();

	this->targetComboBox->addItem("<New Mask>");

	QMap<QString, std::shared_ptr<Mask>>::const_iterator map_iterator;
	auto begin = this->maskPtrMapPtr.lock()->constBegin();
	auto end = this->maskPtrMapPtr.lock()->constEnd();
	for (map_iterator = begin; map_iterator != end; ++map_iterator) {
		this->sourceComboBox->addItem(map_iterator.key());
		this->targetComboBox->addItem(map_iterator.key());
	}
	
}

bool RegionGrowingToolBar::initToolBar(std::weak_ptr<const Mask> currentMask)
{
	updateComboBox();
	int index = this->sourceComboBox->findText(currentMask.lock()->name);
	if (index == -1)
	{
		return false;
	}
	this->sourceComboBox->setCurrentIndex(index);
	this->targetComboBox->setCurrentIndex(0);
	emit sourceOrTargetMaskChanged(this->sourceComboBox->currentText(), this->targetComboBox->currentText());
	return true;
}


void RegionGrowingToolBar::setMaskPtrMapPtr(std::weak_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrMapPtr)
{
	this->maskPtrMapPtr = maskPtrMapPtr;
}

void RegionGrowingToolBar::showEvent(QShowEvent* event)
{
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