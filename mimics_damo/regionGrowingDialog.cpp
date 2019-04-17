#include "regionGrowingDialog.h"

#include <QtWidgets>
RegionGrowingDialog::RegionGrowingDialog(QMainWindow * parent) 
	: QDialog(parent) 
{
	setupUi(this);
	connect(this->closeButton, SIGNAL(clicked()), this, SLOT(close()));
	this->regionRrowingMask = NULL;
	this->mainWindow = parent;
	this->setFocus();
}
RegionGrowingDialog::~RegionGrowingDialog() {

}

//void regionGrowingDialog::setRegionGrowingModelPtr(int *xB, int *yB, int *zB)
//{
//	regionGrowingModelPtr[0] = xB;
//	regionGrowingModelPtr[1] = yB;
//	regionGrowingModelPtr[2] = zB;
//
//}
//void regionGrowingDialog::changeModelToRegionRrowing()
//{
//	//改变模式
//	/*for (int i = 0; i < 3; ++i)
//	{
//		*regionGrowingModelPtr[i] = 1;
//	}*/
//	//emit changeVtkClickModel(1);
//}

void RegionGrowingDialog::setNewMask(std::shared_ptr<Mask> mask)
{
	//QMessageBox::warning(this, "what happend?", "3.5", QMessageBox::Ok);
	this->regionRrowingMask = mask;
	//QMessageBox::warning(this, "what happend?", "3.6", QMessageBox::Ok);
}


void RegionGrowingDialog::closeEvent(QCloseEvent *event)  //退出的时候换模式
{
	//for (int i = 0; i < 3; ++i)
	//{
	//	*regionGrowingModelPtr[i] = 0;  //恢复正常模式
	//}
	//emit changeVtkClickModel(0);
	
	if (this->regionRrowingMask->imageData == 0)//没有生成图像
	{
		emit maskResult(NULL);
		QDialog::reject();
		this->regionRrowingMask.reset();
	}
	else
	{
		emit maskResult(this->regionRrowingMask);
		QDialog::accept();
		this->regionRrowingMask.reset();
	}
}

void RegionGrowingDialog::keyPressEvent(QKeyEvent *event)
{
	//QMessageBox::warning(this, tr("..."), tr("ok?"), QMessageBox::Yes);
	this->mainWindow->activateWindow();
}
void RegionGrowingDialog::keyReleaseEvent(QKeyEvent *event)
{
	//QMessageBox::warning(this, tr("..."), tr("ok?"), QMessageBox::Yes);
	//if (event->key() == Qt::Key_Space)
	this->mainWindow->activateWindow();
}
