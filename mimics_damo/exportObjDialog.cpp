#include "exportObjDialog.hpp"

#include <qfiledialog.h>
#include <qfile.h>
#include <qmessagebox.h>

#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOBJExporter.h>
#include <qprogressdialog.h>

#include "object.h"
ExportObjDialog::ExportObjDialog(QWidget * parent) : QDialog(parent) {
	setupUi(this);
	this->verticalLayout->setContentsMargins(11, 11, 11, 11);
	this->setLayout(verticalLayout);

	initObjTableWidget();

	this->fileDialog = 0;//一定要初始化dialog，非常重要
	this->progressDialog = 0;

	connect(this->exportButton, SIGNAL(clicked()), this, SLOT(exportObj()));
	connect(this->browseButton, SIGNAL(clicked()), this, SLOT(browseFile()));
	connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
	
}
void ExportObjDialog::initObjTableWidget()
{
	this->tableWidget->setColumnCount(2);
	this->tableWidget->setRowCount(0);

	QTableWidgetItem *nameHeader = new QTableWidgetItem;
	nameHeader->setText("Name");
	nameHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QTableWidgetItem *qualityHeader = new QTableWidgetItem;
	qualityHeader->setText("Quality");
	qualityHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);


	//绑定到tableWidget上
	this->tableWidget->setHorizontalHeaderItem(0, nameHeader);
	this->tableWidget->setHorizontalHeaderItem(1, qualityHeader);

	//属性设置
	//this->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);   //设置选择的模式为单选择
	this->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
																				 //this->maskTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	this->tableWidget->verticalHeader()->setVisible(false);//设置垂直头不可见
	this->tableWidget->setShowGrid(false); //设置不显示格子线
	this->tableWidget->verticalHeader()->setDefaultSectionSize(20); //设定行高
	this->tableWidget->horizontalHeader()->setDefaultSectionSize(100); //设定列宽

}
void ExportObjDialog::addRow()
{
	int row = this->tableWidget->rowCount();
	this->tableWidget->insertRow(row);

	//QMessageBox::warning(this, "2.1", "what happend?", QMessageBox::Ok);

	QTableWidgetItem *nameItem = new QTableWidgetItem;  //name
	nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	nameItem->setCheckState(Qt::Unchecked);
	this->tableWidget->setItem(row, 0, nameItem);

	QTableWidgetItem *qualityItem = new QTableWidgetItem;
	qualityItem->setFlags(qualityItem->flags() ^ Qt::ItemIsEditable);   //从当前item的特征中除去Qt::ItemIsEditable特征
	qualityItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->tableWidget->setItem(row, 1, qualityItem);

	this->tableWidget->setCurrentItem(nameItem);
}
void ExportObjDialog::updateTableWidget()
{
	QMap<QString, std::shared_ptr<Object>>::const_iterator map_iterator;
	auto begin = this->objPtrQMapPtr->constBegin();
	auto end = this->objPtrQMapPtr->constEnd();
	//QMessageBox::warning(this, "2-", " calculated.", QMessageBox::Ok);

	int row = 0;
	for (map_iterator = begin; map_iterator != end; ++map_iterator)
	{
		addRow();//建立该行的item
		QPixmap colorPixmap = QPixmap(100, 100);
		colorPixmap.fill(
			QColor(
				map_iterator.value()->color[0] * 255,
				map_iterator.value()->color[1] * 255,
				map_iterator.value()->color[2] * 255
			)
		);
		this->tableWidget->item(row, 0)->setText(map_iterator.value()->name);
		this->tableWidget->item(row, 0)->setIcon(colorPixmap);
		this->tableWidget->item(row, 1)->setText(map_iterator.value()->quality);
		++row;
	}
}

void ExportObjDialog::setObjPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtr)
{
	//this->objPtrQMapPtr = objPtr;
	this->objPtrQMapPtr = objPtr;
}

void ExportObjDialog::closeEvent(QCloseEvent *event)
{
	//QMessageBox::warning(this, "Tips", "It happends? ", QMessageBox::Ok);
	while (this->tableWidget->rowCount() != 0)
		this->tableWidget->removeRow(0);
	//this->calculateProgressBar->setValue(0);
}

void ExportObjDialog::browseFile()
{
	if (this->fileDialog == 0)
	{
		this->fileDialog = new QFileDialog(this);
		this->fileDialog->setWindowTitle(tr("select export file path..."));
		this->fileDialog->setDirectory(".");
		this->fileDialog->setFileMode(QFileDialog::Directory);
		this->fileDialog->setViewMode(QFileDialog::Detail);
	}

	QString exportPath;
	if (this->fileDialog->exec() == QDialog::Accepted)
	{
		exportPath = this->fileDialog->selectedFiles()[0];
	}

	this->filePrefixLineEdit->setText(exportPath);
}
void ExportObjDialog::exportObj()
{
	QFile mFile(this->filePrefixLineEdit->text());
	if (mFile.exists())
	{
		int rowCount = this->tableWidget->rowCount();
		bool t = false;
		std::vector<std::weak_ptr<Object>> objList;
		for (int i = 0; i < rowCount; ++i)
		{
			if (this->tableWidget->item(i, 0)->checkState() == Qt::Checked)
			{
				t = true;
				QString name = this->tableWidget->item(i, 0)->text();
				objList.push_back((*this->objPtrQMapPtr)[name]);
				//QMessageBox::warning(this, "Tips", (*this->objPtrQMapPtr)[name]->name, QMessageBox::Ok);//318炸
			}
		}
		if (!t)
		{
			QMessageBox::warning(this, "Tips", "There is no obj to be selected. ", QMessageBox::Ok);
		}
		else
		{
			//QMessageBox::warning(this, "Tips", "ok!", QMessageBox::Ok);
			if (this->progressDialog == 0)
			{
				//QMessageBox::warning(this, "Tips", "ok?", QMessageBox::Ok);
				this->progressDialog = new QProgressDialog(this);
				this->progressDialog->setRange(0, 0);
				this->progressDialog->setCancelButton(0);
				connect(&this->exportThread, SIGNAL(exportingObjStatus(const QString&)), this, SLOT(updateProcessDialog(const QString&)));//connect不要加常量！！！
			
			}
			//QMessageBox::warning(this, "Tips", "ok!", QMessageBox::Ok);
			this->progressDialog->setModal(true);
			this->progressDialog->setLabelText("please wait!");
			this->exportThread.setFilePrefix(this->filePrefixLineEdit->text());
			this->exportThread.setObjList(objList);
			//this->calThread.setCalMaskAndCheckedId(mask, this->radioButtonGroup->checkedId());
			this->progressDialog->show();
			this->progressDialog->activateWindow();//激活状态
			//QMessageBox::warning(this, "Tips", "ok?", QMessageBox::Ok);
			this->exportThread.start();
		}
	}
	else
	{
		QMessageBox::warning(this, "Warning", "This directory does not exist.\nPlease enter the correct file directory. ", QMessageBox::Ok);
	}
}
void ExportObjDialog::updateProcessDialog(const QString& text)
{
	if (text != "")
	{
		this->progressDialog->setLabelText("Export "+text+"...");
	}
	else 
	{
		this->progressDialog->close();
		this->close();
	}
}
//void exportObjDialog::exportObjActor(std::shared_ptr<Object> objPtr)
//{
//	vtkSmartPointer<vtkRenderer> outputRenderer = vtkSmartPointer<vtkRenderer>::New();
//	outputRenderer->AddActor(objPtr->objActor);
//
//	vtkSmartPointer<vtkRenderWindow> outputRenWin = vtkSmartPointer<vtkRenderWindow>::New();
//	outputRenWin->AddRenderer(outputRenderer);
//
//	QString filePrefix = this->filePrefixLineEdit->text() + "/" + objPtr->name;
//	vtkSmartPointer<vtkOBJExporter> porter = vtkSmartPointer<vtkOBJExporter>::New();
//	porter->SetFilePrefix(filePrefix.toStdString().c_str());
//	porter->SetInput(outputRenWin);
//	porter->Write();
//}

ExportObjDialog::~ExportObjDialog() {
	
}
