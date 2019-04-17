#include "calculateObjDialog.hpp"
#include "mask.h"
#include "object.h"
#include <memory>
#include <qtablewidget.h>
#include <qbuttongroup.h>
#include <qmessagebox.h>
#include <qprogressdialog.h>
#include <QVTKWidget.h>
#include <qVtk3dWidget.hpp>
#include <qprogressdialog.h>

#include <vtkMarchingCubes.h>
#include <vtkImageData.h>
#include <vtkWindowedSincPolyDataFilter.h>
#include <vtkQuadricDecimation.h>
#include <vtkPolyDataNormals.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkOBJExporter.h>

CalculateObjDialog::CalculateObjDialog(QWidget * parent) : QDialog(parent) {
	//ui.setupUi(this);
	setupUi(this);
	this->verticalLayout_3->setContentsMargins(11, 11, 11, 11);
	this->setLayout(verticalLayout_3);
	//this->setFixedSize(this->size());
	
	//setLayout(this->verticalLayout_3);
	//QMessageBox::warning(this, "1", "ted.", QMessageBox::Ok);

	initMaskTableWidget();
	
	//QMessageBox::warning(this, "2", " calculated.", QMessageBox::Ok);

	initButton();

	//设置进度条
	//this->calculateProgressBar->setValue(0);
	//this->calculateProgressBar->setRange(0, 100);
	//dialog初始化
	this->progressDialog = 0;
																																//this->calThread = new calculateObjThread();
	/*this->progressDialog = new QProgressDialog(this);
	this->progressDialog->setRange(0, 100);
	this->progressDialog->setValue(0);
	this->progressDialog->setCancelButton(0);
	this->progressDialog->setLabelText("please wait!");
	this->progressDialog->setModal(true);
	
	
	this->calThread = new calculateObjThread();
	connect(this->calThread, SIGNAL(changeProcess(const QString& a, int value)), this, SLOT(updateProcessDialog(const QString& a, int value)));*/

}
void CalculateObjDialog::updateProcessDialog(const QString& a, int value)
{
	//QMessageBox::warning(this, "2", " calculated.", QMessageBox::Ok);

	this->progressDialog->setLabelText(a);
	this->progressDialog->setValue(value);
	if (value == 100)
	{
		this->widget_3dViewer->GetRenderWindow()->Render();
		this->progressDialog->close();
		this->close();
	}
}


void CalculateObjDialog::initMaskTableWidget()
{
	this->maskTableWidget->setColumnCount(3);
	this->maskTableWidget->setRowCount(0);

	QTableWidgetItem *nameHeader = new QTableWidgetItem;
	nameHeader->setText("Name");
	nameHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QTableWidgetItem *lowerHeader = new QTableWidgetItem;
	lowerHeader->setText("Lower threshold");
	lowerHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	QTableWidgetItem *higherHeader = new QTableWidgetItem;
	higherHeader->setText("Higher threshold");
	higherHeader->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);

	//绑定到tableWidget上
	this->maskTableWidget->setHorizontalHeaderItem(0, nameHeader);
	this->maskTableWidget->setHorizontalHeaderItem(1, lowerHeader);
	this->maskTableWidget->setHorizontalHeaderItem(2, higherHeader);

	//属性设置
	//this->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);   //设置选择的模式为单选择
	this->maskTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //设置选择行为时每次选择一行
	//this->maskTableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
	this->maskTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	this->maskTableWidget->verticalHeader()->setVisible(false);//设置垂直头不可见
	this->maskTableWidget->setShowGrid(false); //设置不显示格子线
	this->maskTableWidget->verticalHeader()->setDefaultSectionSize(20); //设定行高
	this->maskTableWidget->horizontalHeader()->setDefaultSectionSize(80); //设定列宽

	connect(this->maskTableWidget, SIGNAL(cellClicked(int, int)),
		this, SLOT(updateCurrentMaskName(int, int)));

}
void CalculateObjDialog::closeEvent(QCloseEvent *event)
{
	while (this->maskTableWidget->rowCount() != 0)
		this->maskTableWidget->removeRow(0);
	//this->calculateProgressBar->setValue(0);
}
void CalculateObjDialog::updateTableWidget()
{
	QMap<QString, std::shared_ptr<Mask>>::const_iterator map_iterator;
	auto begin = this->maskPtrQMapPtr->constBegin();
	auto end = this->maskPtrQMapPtr->constEnd();
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
		this->maskTableWidget->item(row, 0)->setText(map_iterator.value()->name);
		this->maskTableWidget->item(row, 0)->setIcon(colorPixmap);
		this->maskTableWidget->item(row, 1)->setText(QString::number(map_iterator.value()->thresholdRange[0]));
		this->maskTableWidget->item(row, 2)->setText(QString::number(map_iterator.value()->thresholdRange[1]));
		++row;
	}
}

void CalculateObjDialog::initButton()
{
	//radio button
	this->radioButtonGroup = new QButtonGroup(this);
	this->radioButtonGroup->addButton(this->lowRadioButton,0);
	this->radioButtonGroup->addButton(this->middleRadioButton, 1);
	this->radioButtonGroup->addButton(this->highRadioButton, 2);
	this->radioButtonGroup->addButton(this->originalRadioButton, 3);
	this->middleRadioButton->setChecked(true);
	//other
	connect(this->calculateButton, SIGNAL(clicked()), this, SLOT(calculateObj()));
	connect(this->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void CalculateObjDialog::addRow()  //会触发cellchanges
{
	//this->createItemFlag = true;
	//QMessageBox::warning(this, "2.0", "what happend?", QMessageBox::Ok);

	int row = this->maskTableWidget->rowCount();
	this->maskTableWidget->insertRow(row);
	
	//QMessageBox::warning(this, "2.1", "what happend?", QMessageBox::Ok);

	QTableWidgetItem *nameItem = new QTableWidgetItem;  //name
	nameItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
	this->maskTableWidget->setItem(row, 0, nameItem);

	QTableWidgetItem *lowerThresholdItem = new QTableWidgetItem;
	lowerThresholdItem->setFlags(lowerThresholdItem->flags() ^ Qt::ItemIsEditable);   //从当前item的特征中除去Qt::ItemIsEditable特征
	lowerThresholdItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->maskTableWidget->setItem(row, 1, lowerThresholdItem);

	QTableWidgetItem *higherThresholdItem = new QTableWidgetItem;
	higherThresholdItem->setFlags(higherThresholdItem->flags() ^ Qt::ItemIsEditable);
	higherThresholdItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
	this->maskTableWidget->setItem(row, 2, higherThresholdItem);

	this->maskTableWidget->setCurrentItem(nameItem);
	//QMessageBox::warning(this, "2.2", "what happend?", QMessageBox::Ok);
	//this->createItemFlag = false;
}

void CalculateObjDialog::updateCurrentMaskName(int row, int column)
{
	this->currentMaskName = this->maskTableWidget->item(row, 0)->text();
}

//void calculateObjDialog::setStatusProgressBarAndLabel(QProgressBar* pBar, QLabel* pLabel)
//{
//	this->statusProgressBar = pBar;
//	this->statusProgressBarLabel = pLabel;
//}

CalculateObjDialog::~CalculateObjDialog() {
	
}
const CalculateObjThread* CalculateObjDialog::getCalculateObjThreadPtr()
{
	return &this->calThread;
}
void CalculateObjDialog::calculateObj()
{
	if (this->currentMaskName != "")
	{
		if (this->progressDialog == 0)
		{
			this->progressDialog = new QProgressDialog(this);
			this->progressDialog->setRange(0, 100);
			this->progressDialog->setCancelButton(0);

			connect(&this->calThread, SIGNAL(changeProcess(const QString&, int)), this, SLOT(updateProcessDialog(const QString&, int)));//connect不要加常量！！！
		}
		this->progressDialog->setValue(0);
		this->progressDialog->setModal(true);
		this->progressDialog->setLabelText("please wait!");

		auto mask =(*this->maskPtrQMapPtr)[this->currentMaskName];
		this->calThread.setCalMaskAndCheckedId(mask, this->radioButtonGroup->checkedId());
		this->progressDialog->show();
		this->progressDialog->activateWindow();//激活状态
		this->calThread.start();

		//this->calThread->setObjPtrQMapPtrAndRenAndVTKWidget(this->objPtrQMapPtr, this->ren_3dViewer, this->widget_3dViewer);
		//QProgressDialog progress(this);
		//progress.setLabelText(tr("Calculate %1").arg(mask->name));
		//progress.setRange(0, 100);
		//progress.setModal(true);
		//this->calculateProgressBar->setValue(10);
		//this->tipLabel->setText("create model...");
		//vtkSmartPointer<vtkMarchingCubes> marchingcube = vtkSmartPointer<vtkMarchingCubes>::New();
		//marchingcube->SetInputData(mask->imageData);//头文件包含
		//marchingcube->ComputeNormalsOn();
		//marchingcube->SetValue(0, 1);
		//marchingcube->ReleaseDataFlagOn();
		//marchingcube->Update();
		////this->calculateProgressBar->setValue(10);
		//this->calculateProgressBar->setValue(10);
		//this->tipLabel->setText("smooth model...");
		//vtkSmartPointer<vtkWindowedSincPolyDataFilter> smooth = vtkSmartPointer<vtkWindowedSincPolyDataFilter>::New(); //使图像更加光滑
		//smooth->SetInputConnection(marchingcube->GetOutputPort());
		//smooth->SetNumberOfIterations(300);
		//smooth->ReleaseDataFlagOn();
		//smooth->Update();
		//this->calculateProgressBar->setValue(20);
		//this->tipLabel->setText("optimization model...");
		//vtkSmartPointer<vtkQuadricDecimation> deci = vtkSmartPointer<vtkQuadricDecimation>::New();
		//deci->SetInputConnection(smooth->GetOutputPort());
		//int radioId = this->radioButtonGroup->checkedId();
		//if(radioId ==0)
		//	deci->SetTargetReduction(0.9);
		//else if(radioId==1)
		//	deci->SetTargetReduction(0.6);
		//else if(radioId==2)
		//	deci->SetTargetReduction(0.3);
		//else if(radioId==3)
		//	deci->SetTargetReduction(0);
		//deci->ReleaseDataFlagOn();
		//deci->Update();
		//this->calculateProgressBar->setValue(30);
		//this->tipLabel->setText("calculate normals...");
		//vtkSmartPointer<vtkPolyDataNormals> skinNormals = vtkSmartPointer<vtkPolyDataNormals>::New();//绘制法线
		//skinNormals->SetInputConnection(deci->GetOutputPort());
		//skinNormals->ReleaseDataFlagOn();
		//skinNormals->Update();
		//this->calculateProgressBar->setValue(40);
		//this->tipLabel->setText("stripper model...");
		//vtkSmartPointer<vtkStripper>skinStripper = vtkSmartPointer<vtkStripper>::New(); //三角带连接
		//skinStripper->SetInputConnection(skinNormals->GetOutputPort());
		//skinStripper->ReleaseDataFlagOn();
		//skinStripper->Update();
		//this->calculateProgressBar->setValue(50);
		//this->tipLabel->setText("mapper...");
		//vtkSmartPointer<vtkPolyDataMapper> skinMapper =
		//	vtkSmartPointer<vtkPolyDataMapper>::New();
		//skinMapper->SetInputConnection(skinStripper->GetOutputPort());
		//skinMapper->ReleaseDataFlagOn();
		//skinMapper->Update();
		////skinMapper->ScalarVisibilityOff();
		//this->calculateProgressBar->setValue(60);
		//this->tipLabel->setText("create obj...");
		//vtkSmartPointer<vtkActor> objActor =
		//	vtkSmartPointer<vtkActor>::New();
		//objActor->SetMapper(skinMapper);
		////创建Object对象存入管理对象
		//this->calculateProgressBar->setValue(70);
		//this->tipLabel->setText("save obj...");
		//std::shared_ptr<Object> newObj = std::make_shared<Object>(mask->name,objActor);
		//this->objPtrQMapPtr->insert(newObj->name, newObj);
		////显示在第四个窗口上
		//this->calculateProgressBar->setValue(80);
		//this->tipLabel->setText("show obj...");
		//this->ren_3dViewer->AddActor(objActor);
		//this->ren_3dViewer->Modified();
		//this->widget_3dViewer->GetRenderWindow()->Render();
		//导出obj
		//this->calculateProgressBar->setValue(95);
		//this->tipLabel->setText("export obj...");
		//vtkSmartPointer<vtkRenderer> outputRenderer = vtkSmartPointer<vtkRenderer>::New();
		//outputRenderer->AddActor(objActor);
		//vtkSmartPointer<vtkRenderWindow> outputRenWin = vtkSmartPointer<vtkRenderWindow>::New();
		//outputRenWin->AddRenderer(outputRenderer);
		//vtkSmartPointer<vtkOBJExporter> porter = vtkSmartPointer<vtkOBJExporter>::New();
		//porter->SetFilePrefix("D:\\mimics_damo");
		//porter->SetInput(outputRenWin);
		//porter->Write();
		//progress.setValue(100);
		//qApp->processEvents();
		//this->calculateProgressBar->setValue(100);
		//this->tipLabel->setText("over!...");
		//QDialog::accept();
	}
	else
	{
		QMessageBox::warning(this, "Tip", "please select a mask for 3d calculated.", QMessageBox::Ok);
	}

}

void CalculateObjDialog::setRen3dViewer(vtkSmartPointer<vtkRenderer> ren)
{
	//this->ren_3dViewer = ren;
	this->calThread.setRen(ren);
}

void CalculateObjDialog::setMaskPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtr)
{
	this->maskPtrQMapPtr = maskPtr;
}

void CalculateObjDialog::setObjPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtr)
{
	//this->objPtrQMapPtr = objPtr;
	this->calThread.setObjPtrQMapPtr(objPtr);
}

void CalculateObjDialog::setViewWidget(QVTK3DWidget *widget)
{
	this->widget_3dViewer = widget;
	//this->calThread.setVTKWidget(widget);
}