#include "objListWidget.h"
#include <qtablewidget.h>
#include "qheaderview.h"
#include "qlabel.h"
#include <qtoolbutton.h>
#include <qlayout.h>
#include "qmessagebox.h"
#include <qaction.h>
#include "object.h"
ObjListWidget::ObjListWidget(QWidget *parent) :QWidget(parent)
{
	this->tableWidget = new QTableWidget(0, 3);
	this->objPtrQMapPtr = NULL;

	//����
	//�����ͷ
	QTableWidgetItem *nameHeader = new QTableWidgetItem;
	nameHeader->setText("Name");
	nameHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QTableWidgetItem *visibleHeader = new QTableWidgetItem;
	visibleHeader->setText("Visible");
	visibleHeader->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	QTableWidgetItem *qualityHeader = new QTableWidgetItem;
	qualityHeader->setText("Quality");
	qualityHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	//�󶨵�tableWidget��
	this->tableWidget->setHorizontalHeaderItem(0, nameHeader);
	this->tableWidget->setHorizontalHeaderItem(1, visibleHeader);
	this->tableWidget->setHorizontalHeaderItem(2, qualityHeader);

	//��������
	this->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //����ѡ����Ϊʱÿ��ѡ��һ��
	this->tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	//this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭
	this->tableWidget->verticalHeader()->setVisible(false);//���ô�ֱͷ���ɼ�
	this->tableWidget->setShowGrid(false); //���ò���ʾ������
	this->tableWidget->verticalHeader()->setDefaultSectionSize(20); //�趨�и�
	this->tableWidget->horizontalHeader()->setDefaultSectionSize(80); //�趨�п�

	//Table��Ӧ
	connect(this->tableWidget, SIGNAL(cellChanged(int, int)),
		this, SLOT(setChanges(int, int)));
	connect(this->tableWidget, SIGNAL(cellClicked(int, int)),
		this, SLOT(updateCurrentNameAndObject(int, int)));

	//action
	this->deleteAction = new QAction(tr("Delete Object"));
	this->deleteAction->setShortcut(QKeySequence::Delete);
	connect(this->deleteAction, SIGNAL(triggered()), this, SLOT(deleteObject()));

	//Label
	this->label = new QLabel("3D Object:");

	//button
	this->deleteButton = new QToolButton(this);
	this->deleteButton->setDefaultAction(this->deleteAction);
	this->deleteButton->setText("D");
	this->exportButton = new QToolButton(this);

	//����
	QHBoxLayout *topLayout = new QHBoxLayout;
	topLayout->addWidget(this->label);
	topLayout->addStretch();

	QHBoxLayout *bottomLayout = new QHBoxLayout;
	bottomLayout->addStretch();
	bottomLayout->addWidget(this->deleteButton);
	bottomLayout->addWidget(this->exportButton);

	//QGridLayout *bottomLayout = new QGridLayout();
	//bottomLayout->addWidget(this->deleteButton,0,2,1,1);
	//bottomLayout->addWidget(this->exportButton,0,3,1,1);

	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addLayout(topLayout);
	mainLayout->addWidget(this->tableWidget);
	mainLayout->addLayout(bottomLayout);

	setLayout(mainLayout);
}
ObjListWidget::~ObjListWidget()
{

}
void ObjListWidget::addRow()  //�ᴥ��cellchanges
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

	QTableWidgetItem *qualityItem = new QTableWidgetItem;
	qualityItem->setFlags(qualityItem->flags() ^ Qt::ItemIsEditable);   //�ӵ�ǰitem�������г�ȥQt::ItemIsEditable����
	qualityItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->tableWidget->setItem(row, 2, qualityItem);

	this->tableWidget->setCurrentItem(nameItem);

	this->createItemFlag = false;
}
void ObjListWidget::updateObjectList(const QString &newObjectName)
{

	//int row = this->maskPtrQListPtr->size()-1;

	std::shared_ptr<Object> currentObject;
	if (this->objPtrQMapPtr->find(newObjectName) != this->objPtrQMapPtr->end())
		currentObject = (*this->objPtrQMapPtr)[newObjectName];  //��ȡ����ӵ�mask
	else
		return;

	addRow();//�������е�item

	this->createItemFlag = true;  //������ӦcellChange

	int row = this->tableWidget->rowCount() - 1;
	this->tableWidget->item(row, 0)->setText(currentObject->name);

	QPixmap colorPixmap = QPixmap(100, 100);
	colorPixmap.fill(
		QColor(
			currentObject->color[0] * 255,
			currentObject->color[1] * 255,
			currentObject->color[2] * 255
		)
	);
	this->tableWidget->item(row, 0)->setIcon(colorPixmap);
	if (currentObject->getVisible() == true)
	{
		this->tableWidget->item(row, 1)->setCheckState(Qt::Checked);
	}
	else
	{
		this->tableWidget->item(row, 1)->setCheckState(Qt::Unchecked);
	}
	//this->tableWidget->item(row, 1)->setBackgroundColor(QColor(254,0,254));
	this->tableWidget->item(row, 2)->setText(currentObject->quality);
	this->createItemFlag = false;

}
void ObjListWidget::setExportButtonAction(QAction *action)
{
	this->exportButton->setDefaultAction(action);
	this->exportButton->setText("E");
}
void ObjListWidget::setChanges(int row, int column)
{
	//name����
	if (!createItemFlag)
	{
		if (column == 0)
		{
			if (this->tableWidget->item(row, column)->text() == "")//��ֹ��itemʱ��Ӧ
			{
				QMessageBox::warning(this, "Warning", "Can not use empty name!", QMessageBox::Ok);
				this->createItemFlag = true;
				this->tableWidget->item(row, column)->setText(this->currentName);//set ����change��������
				this->createItemFlag = false;
			}
			else
			{
				//QMessageBox::warning(this, "Tip", "Change!", QMessageBox::Ok);
				QString changedName = this->tableWidget->item(row, column)->text();
				if (this->objPtrQMapPtr->find(changedName) != this->objPtrQMapPtr->end())
				{
					QMessageBox::warning(this, "Warning", "Can not use same names in the Object list!", QMessageBox::Ok);
					this->tableWidget->item(row, column)->setText(this->currentName);
				}
				else
				{
					std::shared_ptr<Object> currentObject = (*this->objPtrQMapPtr)[this->currentName];
					currentObject->name = changedName;   //�󶨣�setitem����ʱ��Ҳ�ᴥ��change��������
					this->objPtrQMapPtr->erase(this->objPtrQMapPtr->find(this->currentName));
					this->objPtrQMapPtr->insert(currentObject->name, currentObject);
					this->currentName = currentObject->name;
				}
			}
		}
		//visible����
		if (column == 1)
		{
			QString name = this->tableWidget->item(row, 0)->text();
			std::shared_ptr<Object> currentObject = (*this->objPtrQMapPtr)[name];
			if (this->tableWidget->item(row, column)->checkState() == Qt::Checked)
			{
				currentObject->setVisible(true);
			}
			else if (this->tableWidget->item(row, column)->checkState() == Qt::Unchecked)
			{
				currentObject->setVisible(false);
			}
		}
	}
}
void ObjListWidget::updateCurrentNameAndObject(int row, int column)
{
	this->currentName = this->tableWidget->item(row, 0)->text();
	//*this->currentMaskPtr = (*this->maskPtrQMapPtr)[this->currentName];
}
void ObjListWidget::deleteObject()
{
	QList<QTableWidgetItem*> selectedItems = this->tableWidget->selectedItems();
	QVector<QTableWidgetItem*> eraseItems;
	int selectedCount = selectedItems.count();
	for (int i = 0; i<selectedCount; ++i)
	{
		//int row = this->tableWidget->row(selectedItems.at(i));//��ȡѡ�е���  
		int column = this->tableWidget->column(selectedItems.at(i));
		if (column == 0)
		{
			QTableWidgetItem *item = selectedItems.at(i);
			eraseItems.push_back(item);
		}
	}
	int eraseCount = eraseItems.size();
	for (int i = 0; i != eraseCount; ++i)
	{
		(*this->objPtrQMapPtr)[eraseItems[i]->text()]->deleteObject();//ɾ��mask�ͷſռ�
		this->objPtrQMapPtr->erase(this->objPtrQMapPtr->find(eraseItems[i]->text()));//ɾ��mask������
		this->tableWidget->removeRow(this->tableWidget->row(eraseItems[i]));//ɾ����
	}
}

void ObjListWidget::setObjectMap(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objectMapPtr)
{
	this->objPtrQMapPtr = objectMapPtr;
}