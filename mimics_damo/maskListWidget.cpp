#include "maskListWidget.h"
#include <qtablewidget.h>
#include "mask.h"
#include "qheaderview.h"
#include "qlabel.h"
#include <qtoolbutton.h>
#include <qlayout.h>
#include "qmessagebox.h"
#include "qbrush.h"
#include "qpixmap.h"
#include <vtkImageData.h>
#include <vtkRenderer.h>
#include <vtkImageActor.h>
#include <qaction.h>
MaskListWidget::MaskListWidget(QWidget *parent):QWidget(parent)
{
	this->tableWidget = new QTableWidget(0,4);
	//this->maskPtrListPtr = NULL;
	//this->maskPtrQListPtr = NULL;
	this->maskPtrQMapPtr = NULL;
	//建表
	//定义表头
	QTableWidgetItem *nameHeader = new QTableWidgetItem;
	nameHeader->setText("Name");
	nameHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QTableWidgetItem *visibleHeader = new QTableWidgetItem;
	visibleHeader->setText("Visible");
	visibleHeader->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QTableWidgetItem *lowerHeader = new QTableWidgetItem;
	lowerHeader->setText("Lower threshold");
	lowerHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QTableWidgetItem *higherHeader = new QTableWidgetItem;
	higherHeader->setText("Higher threshold");
	higherHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	//绑定到tableWidget上
	this->tableWidget->setHorizontalHeaderItem(0, nameHeader);
	this->tableWidget->setHorizontalHeaderItem(1, visibleHeader);
	this->tableWidget->setHorizontalHeaderItem(2, lowerHeader);
	this->tableWidget->setHorizontalHeaderItem(3, higherHeader);

	//属性设置
	//this->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);   //设置选择的模式为单选择
	this->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
	this->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	//this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	this->tableWidget->verticalHeader()->setVisible(false);//设置垂直头不可见
	this->tableWidget->setShowGrid(false); //设置不显示格子线
	this->tableWidget->verticalHeader()->setDefaultSectionSize(20); //设定行高
	this->tableWidget->horizontalHeader()->setDefaultSectionSize(80); //设定列宽

	//Table响应
	connect(this->tableWidget, SIGNAL(cellChanged(int, int)),
		this, SLOT(setChanges(int, int)));
	connect(this->tableWidget, SIGNAL(cellClicked(int, int)),
		this, SLOT(updateCurrentNameAndMask(int, int)));

	//action
	this->deleteAction = new QAction(tr("Delete Mask"));
	deleteAction->setShortcut(QKeySequence::Delete);
	connect(this->deleteAction, SIGNAL(triggered()), this, SLOT(deleteMask()));

	//Label
	this->label = new QLabel("3D Mask:");
	
	//button
	this->newButton = new QToolButton(this);
	this->editButton = new QToolButton(this);
	this->deleteButton = new QToolButton(this);
	this->calculateButton = new QToolButton(this);

	//绑定deleteAction
	this->deleteButton->setDefaultAction(deleteAction);
	this->deleteButton->setText("D");


	//Button响应
	//connect(this->editButton, SIGNAL(clicked()),
	//	this, SLOT(showQMap()));
	//connect(this->deleteButton, SIGNAL(clicked()),
	//	this, SLOT(deleteMask()));
	//布局
	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(this->label);
	topLayout->addStretch();

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(this->newButton);
	bottomLayout->addWidget(this->editButton);
	bottomLayout->addWidget(this->deleteButton);
	bottomLayout->addWidget(this->calculateButton);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(this->tableWidget);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
}
void MaskListWidget::setNewButtonAction(QAction *action)
{
	this->newButton->setDefaultAction(action);
	this->newButton->setText("N");
}
void MaskListWidget::setCalculateButtonAction(QAction *action)
{
	this->calculateButton->setDefaultAction(action);
	this->calculateButton->setText("C");
}
void MaskListWidget::setEditButtonAction(QAction *action)
{
	this->editButton->setDefaultAction(action);
	this->editButton->setText("E");
}
void MaskListWidget::deleteMask()
{
	//QMessageBox::warning(this, "Tip", "MaskListWidget::deleteMask:ok?", QMessageBox::Ok);

	QList<QTableWidgetItem*> selectedItems = this->tableWidget->selectedItems();
	//QVector<QTableWidgetItem*> eraseItems;
	int selectedCount = selectedItems.count();
	//for (int i = 0; i<selectedCount; ++i)
	//{
	//	//int row = this->tableWidget->row(selectedItems.at(i));//获取选中的行  
	//	int column = this->tableWidget->column(selectedItems.at(i));
	//	//QMessageBox::warning(this, "Tip", "MaskListWidget::deleteMask:ok?", QMessageBox::Ok);
	//	if (column == 0)
	//	{
	//		QTableWidgetItem *item = selectedItems.at(i);
	//		eraseItems.push_back(item);
	//	}
	//}
	//int eraseCount = eraseItems.size();

	//QMessageBox::warning(this, "Tip", "MaskListWidget::deleteMask:ok??", QMessageBox::Ok);
	for (int i = 0; i != selectedCount; ++i)
	{
		//(*this->maskPtrQMapPtr)[eraseItems[i]->text()]->imageData->ReleaseData();
		//for (int i = 0; i < 3; ++i)
		//{
		//	Mask::vtkViewRender[i]->RemoveActor((*this->maskPtrQMapPtr)[eraseItems[i]->text()]->imageActor[i]);
		//	Mask::vtkViewRender[i]->Render();
		//}
		this->tableWidget->removeRow(this->tableWidget->row(selectedItems[i]));//删除行
		emit deleteMask(selectedItems[i]->text());
		//(*this->maskPtrQMapPtr)[eraseItems[i]->text()]->deleteMask();//删除mask释放空间
		//this->maskPtrQMapPtr->erase(this->maskPtrQMapPtr->find(eraseItems[i]->text()));//删除mask表内容
		//this->tableWidget->removeRow(this->tableWidget->row(eraseItems[i]));//删除行
	}
	
}
void MaskListWidget::setMaskMap(std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskMapPtr)
{
	this->maskPtrQMapPtr = maskMapPtr;
}

//void MaskListWidget::setMaskList(std::shared_ptr<QList<std::shared_ptr<Mask>>> maskMapPtr)
//{ 
//	this->maskPtrQListPtr = maskMapPtr;
//}

//void MaskListWidget::setMaskList(std::shared_ptr<std::list<std::shared_ptr<Mask>>> maskListPtr)
//{
//	this->maskPtrListPtr = maskListPtr;
//}

//void MaskListWidget::setMaskList(std::shared_ptr<QList<std::shared_ptr<Mask>>> maskListPtr)
//{
//	this->maskPtrQListPtr = maskListPtr;
//
//	////将listptr中的内容展现到ListWidget中
//	//for (int row = 0; row < this->maskPtrQListPtr->count(); ++row)
//	//{
//	//	std::shared_ptr<Mask> currentMask = this->maskPtrQListPtr->at(row);
//	//	addRow();//建立该行的item
//
//	//	this->tableWidget->item(row, 0)->setText(currentMask->name);
//
//	//	if (currentMask->visible == true)
//	//	{
//	//		this->tableWidget->item(row, 1)->setCheckState(Qt::Checked);
//	//	}
//	//	else
//	//	{
//	//		this->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);
//	//	}
//
//	//	this->tableWidget->item(row, 2)->setText(QString::number(currentMask->thresholdRange[0]));
//	//	this->tableWidget->item(row, 3)->setText(QString::number(currentMask->thresholdRange[1]));
//	//}
//}

void MaskListWidget::updateCurrentNameAndMask(int row, int column)
{
	this->currentName = this->tableWidget->item(row, 0)->text();
	emit changeCurrentMask(this->currentName);
	//*this->currentMaskPtr = (*this->maskPtrQMapPtr)[this->currentName];
	//QMessageBox::warning(this, "Debug", this->currentName, QMessageBox::Ok);
}

void MaskListWidget::addRow()  //会触发cellchanges
{
	this->createItemFlag = true;

	int row = this->tableWidget->rowCount();
	this->tableWidget->insertRow(row);

	//QMessageBox::warning(this, "2.1", "what happend?", QMessageBox::Ok);

	QTableWidgetItem *nameItem = new QTableWidgetItem;  //name
	nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	this->tableWidget->setItem(row, 0, nameItem);

	QTableWidgetItem *visibleItem = new QTableWidgetItem;
	visibleItem->setCheckState(Qt::Checked);
	visibleItem->setFlags(visibleItem->flags() ^ Qt::ItemIsEditable);
	this->tableWidget->setItem(row, 1, visibleItem);

	QTableWidgetItem *lowerThresholdItem = new QTableWidgetItem;
	lowerThresholdItem->setFlags(lowerThresholdItem->flags() ^ Qt::ItemIsEditable);   //从当前item的特征中除去Qt::ItemIsEditable特征
	lowerThresholdItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->tableWidget->setItem(row, 2, lowerThresholdItem);

	QTableWidgetItem *higherThresholdItem = new QTableWidgetItem;
	higherThresholdItem->setFlags(higherThresholdItem->flags() ^ Qt::ItemIsEditable);
	higherThresholdItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->tableWidget->setItem(row, 3, higherThresholdItem);

	this->tableWidget->setCurrentItem(nameItem);

	this->createItemFlag = false;
}

//void MaskListWidget::setCurrentMaskPtr(std::weak_ptr<Mask>* maskPtr)
//{
//	this->currentMaskPtr = maskPtr;
//}
void MaskListWidget::setCurrentMaskName(const QString& mask)
{
	this->currentName = mask;
}
void MaskListWidget::setItemText(int row, int column, const QString& text)
{
	this->tableWidget->item(row, column)->setText(text);
}
void MaskListWidget::setChanges(int row, int column)
{
	//name部分
	if (!createItemFlag)
	{
		if (column == 0)
		{
			if (this->tableWidget->item(row, column)->text() == "")//防止建item时响应
			{
				QMessageBox::warning(this, "Warning", "Can not use empty name!", QMessageBox::Ok);
				this->createItemFlag = true;
				this->tableWidget->item(row, column)->setText(this->currentName);//set 触发change！！！！
				this->createItemFlag = false;
			}
			else
			{
				//QMessageBox::warning(this, "Tip", "Change!", QMessageBox::Ok);
				QString changedName= this->tableWidget->item(row, column)->text();

				emit changeCurrentMaskName(changedName,row,column);

				//if (this->maskPtrQMapPtr->find(changedName) != this->maskPtrQMapPtr->end())
				//{
				//	QMessageBox::warning(this, "Warning", "Can not use same names in the Mask list!", QMessageBox::Ok);
				//	this->tableWidget->item(row, column)->setText(this->currentName);
				//}
				//else
				//{
				//	std::shared_ptr<Mask> currentMask = (*this->maskPtrQMapPtr)[this->currentName];
				//	currentMask->name = changedName;   //绑定（setitem）的时候也会触发change！！！！
				//	this->maskPtrQMapPtr->erase(this->maskPtrQMapPtr->find(this->currentName));
				//	this->maskPtrQMapPtr->insert(currentMask->name, currentMask);
				//	this->currentName = currentMask->name;
				//}
			}
		}

		//visible部分
		if (column == 1)
		{
			QString name = this->tableWidget->item(row, 0)->text();
			//std::shared_ptr<Mask> currentMask = (*this->maskPtrQMapPtr)[name];
			if (this->tableWidget->item(row, column)->checkState() == Qt::Checked)
			{
				emit maskVisible(name, true);
				//currentMask->setVisible(true);
			}
			else if (this->tableWidget->item(row, column)->checkState() == Qt::Unchecked)
			{
				emit maskVisible(name, false);
				//currentMask->setVisible(false);
			}
		}
	}
}


//void MaskListWidget::showQMap()
//{
//	QMap<QString, std::shared_ptr<Mask>>::const_iterator map_iterator;
//	auto begin = this->maskPtrQMapPtr->constBegin();
//	auto end = this->maskPtrQMapPtr->constEnd();
//	for (map_iterator = begin; map_iterator != end; ++map_iterator) {
//		QString text;
//		if (map_iterator.value()->getVisible())
//		{
//			text = QString("%1 true").arg(map_iterator.value()->name);
//		}
//		else
//		{
//			text = QString("%1 false").arg(map_iterator.value()->name);
//		}
//		QMessageBox::warning(this, "tip", text, QMessageBox::Ok);
//	}
//}
//void MaskListWidget::setChanges(int row, int column)
//{
//	//name部分
//	if (!createItemFlag)
//	{
//		if (column == 0)
//		{
//			if (this->tableWidget->item(row, column)->text() == "")//防止建item时响应
//			{
//				QMessageBox::warning(this, "Warning", "Can not use empty name!", QMessageBox::Ok);
//			}
//			else
//			{
//				QMessageBox::warning(this, "Tip", "Change!", QMessageBox::Ok);
//				std::shared_ptr<Mask> currentMask = this->maskPtrQListPtr->at(row);
//				currentMask->name = this->tableWidget->item(row, column)->text();   //绑定（setitem）的时候也会触发change！！！！
//			}
//		}
//		//visible部分
//		if (column == 1)
//		{
//			std::shared_ptr<Mask> currentMask = this->maskPtrQListPtr->at(row);
//			if (this->tableWidget->item(row, column)->checkState() == Qt::Checked)
//			{
//				currentMask->visible = true;
//			}
//			else if (this->tableWidget->item(row, column)->checkState() == Qt::Unchecked)
//			{
//				currentMask->visible = false;
//			}
//		}
//	}
//}

//std::shared_ptr<Mask> MaskListWidget::maskPtrOf(int row)
//{
//	auto list_iterator = this->maskPtrListPtr->begin();
//	int count = 0;
//	for ( ; list_iterator != this->maskPtrListPtr->end(); ++list_iterator,++count)
//	{
//		if (count == row)
//		{
//			return *list_iterator;
//		}
//	}
//}

//void MaskListWidget::setChanges(int row, int column)
//{
//	//name部分
//	if (!createItemFlag)
//	{
//		if (column == 0)
//		{
//			if (this->tableWidget->item(row, column)->text() == "")//防止建item时响应
//			{
//				QMessageBox::warning(this, "Warning", "Can not use empty name!", QMessageBox::Ok);
//			}
//			else
//			{
//				QMessageBox::warning(this, "Tip", "Change!", QMessageBox::Ok);
//				std::shared_ptr<Mask> currentMask = maskPtrOf(row);
//				currentMask->name = this->tableWidget->item(row, column)->text();   //绑定（setitem）的时候也会触发change！！！！
//			}
//		}
//		//visible部分
//		if (column == 1)
//		{
//			std::shared_ptr<Mask> currentMask = maskPtrOf(row);
//			if (this->tableWidget->item(row, column)->checkState() == Qt::Checked)
//			{
//				currentMask->visible = true;
//			}
//			else if (this->tableWidget->item(row, column)->checkState() == Qt::Unchecked)
//			{
//				currentMask->visible = false;
//			}
//		}
//	}
//}

void MaskListWidget::updateMaskList(const QString &newMaskName)
{

	//int row = this->maskPtrQListPtr->size()-1;

	std::shared_ptr<Mask> currentMask;
	if (this->maskPtrQMapPtr->find(newMaskName)!= this->maskPtrQMapPtr->end())
		currentMask = (*this->maskPtrQMapPtr)[newMaskName];  //获取新添加的mask
	else
		return;

	addRow();//建立该行的item

	this->createItemFlag = true;  //避免响应cellChange

	int row = this->tableWidget->rowCount()-1;
	this->tableWidget->item(row, 0)->setText(currentMask->name);

	QPixmap colorPixmap = QPixmap(100, 100);
	colorPixmap.fill(
		QColor(
			currentMask->color[0] * 255,
			currentMask->color[1] * 255,
			currentMask->color[2] * 255
			)
	);
	this->tableWidget->item(row, 0)->setIcon(colorPixmap);
	if (currentMask->getVisible() == true)
	{
		this->tableWidget->item(row, 1)->setCheckState(Qt::Checked);
	}
	else
	{
		this->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);
	}
	//this->tableWidget->item(row, 1)->setBackgroundColor(QColor(254,0,254));
	this->tableWidget->item(row, 2)->setText(QString::number(currentMask->thresholdRange[0]));
	this->tableWidget->item(row, 3)->setText(QString::number(currentMask->thresholdRange[1]));
	this->createItemFlag = false;

}

//void MaskListWidget::updateMaskList()
//{
//
//	int row = this->maskPtrQListPtr->size()-1;
//
//	std::shared_ptr<Mask> currentMask;
//	if (row != -1)
//		currentMask = this->maskPtrQListPtr->at(row);  //获取新添加的mask
//	else
//		return;
//
//	addRow();//建立该行的item
//
//	this->createItemFlag = true;  //避免响应cellChange
//
//	this->tableWidget->item(row, 0)->setText(currentMask->name);
//
//	QPixmap colorPixmap = QPixmap(100, 100);
//	colorPixmap.fill(
//		QColor(
//			currentMask->color[0] * 255,
//			currentMask->color[1] * 255,
//			currentMask->color[2] * 255
//		)
//	);
//	this->tableWidget->item(row, 0)->setIcon(colorPixmap);
//	if (currentMask->visible == true)
//	{
//		this->tableWidget->item(row, 1)->setCheckState(Qt::Checked);
//	}
//	else
//	{
//		this->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);
//	}
//	//this->tableWidget->item(row, 1)->setBackgroundColor(QColor(254,0,254));
//	this->tableWidget->item(row, 2)->setText(QString::number(currentMask->thresholdRange[0]));
//	this->tableWidget->item(row, 3)->setText(QString::number(currentMask->thresholdRange[1]));
//	this->createItemFlag = false;
//
//}

//void MaskListWidget::updateMaskList()
//{
//
//	int row = this->maskPtrListPtr->size() - 1;
//
//	std::shared_ptr<Mask> currentMask;
//	if (row != -1)
//		currentMask = this->maskPtrListPtr->back();  //获取新添加的mask
//	else
//		return;
//
//	addRow();//建立该行的item
//
//	this->createItemFlag = true;  //避免响应cellChange
//
//	this->tableWidget->item(row, 0)->setText(currentMask->name);
//
//	QPixmap colorPixmap = QPixmap(100, 100);
//	colorPixmap.fill(
//		QColor(
//			currentMask->color[0] * 255,
//			currentMask->color[1] * 255,
//			currentMask->color[2] * 255
//		)
//	);
//	this->tableWidget->item(row, 0)->setIcon(colorPixmap);
//	if (currentMask->visible == true)
//	{
//		this->tableWidget->item(row, 1)->setCheckState(Qt::Checked);
//	}
//	else
//	{
//		this->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);
//	}
//	//this->tableWidget->item(row, 1)->setBackgroundColor(QColor(254,0,254));
//	this->tableWidget->item(row, 2)->setText(QString::number(currentMask->thresholdRange[0]));
//	this->tableWidget->item(row, 3)->setText(QString::number(currentMask->thresholdRange[1]));
//	this->createItemFlag = false;
//
//}

MaskListWidget::~MaskListWidget()
{

}