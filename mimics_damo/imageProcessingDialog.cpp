#include "imageProcessingDialog.h"

#include <qmessagebox.h>

#include "imageProcessingAlgorithms.h"
ImageProcessingDialog::ImageProcessingDialog(QMainWindow * parent)
	: QDialog(parent)
{
	setupUi(this);
	this->orderListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	connect(this->gaussFilterAddButton, &QPushButton::clicked,
		[=]()
	{
		new QListWidgetItem(ImageProcessingAlgorithms::kGaussFilter, this->orderListWidget);
	});
	connect(this->laplacianSharpenerAddButton, &QPushButton::clicked,
		[=]()
	{
		new QListWidgetItem(ImageProcessingAlgorithms::kLaplacianSharpener, this->orderListWidget);
	});
	connect(this->deleteButton, &QPushButton::clicked,
		[=]()
	{
		auto items = this->orderListWidget->selectedItems();
		if (items.size() == 0)
			return;
		else
		{
			for (int i = 0; i<items.size(); i++)//遍历所算的ITEM
			{
				int row = this->orderListWidget->row(items[i]);
				delete this->orderListWidget->takeItem(row);//手动删除takeitem返回的不再被qt管理的item
			}
		}
	});
	connect(this->deleteBottomButton, &QPushButton::clicked,
		[=]()
	{
		this->orderListWidget->takeItem(this->orderListWidget->count() - 1);
	});
	connect(this->applicationButton,&QPushButton::clicked,
		[=]()
	{
		//QMessageBox::warning(this, "Tip", "Please choose a mask to start processing", QMessageBox::Ok);
		if (this->maskComboBox->currentText() == "")
		{
			QMessageBox::warning(this, "Tip", "Please choose a mask to start processing", QMessageBox::Ok);
			return;
		}
		QVector<QString> processing_order;
		int item_count = this->orderListWidget->count();
		for (int i = 0; i != item_count; ++i)
		{
			processing_order.push_back(this->orderListWidget->item(i)->text());
		}
		emit processingRequest(this->maskComboBox->currentText(),processing_order);
		this->close();
	});
	connect(this->cancelButton, &QPushButton::clicked,
		[=]()
	{
		this->close();
	});
	//QMessageBox::warning(this, "Tip", "Please choose a mask to start processing", QMessageBox::Ok);
}
void ImageProcessingDialog::Clear()
{
	this->maskComboBox->clear();
	this->orderListWidget->clear();
}
void ImageProcessingDialog::AddToMaskCombox(const QString& mask)
{
	this->maskComboBox->addItem(mask);
}
void ImageProcessingDialog::SetMaskComboxId(int id)
{
	this->maskComboBox->setCurrentIndex(id);
}
ImageProcessingDialog::~ImageProcessingDialog()
{

}
