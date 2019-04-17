#pragma once
#include <QDialog>
#include <qmainwindow.h>
#include <memory>

#include "mask.h"
#include "ui_regionGrowingDialog.h"

class RegionGrowingDialog : public QDialog, public Ui::RegionGrowingDialog {
	Q_OBJECT
public:
	RegionGrowingDialog(QMainWindow * parent = Q_NULLPTR);
	~RegionGrowingDialog();
	//void setRegionGrowingModelPtr(int *xB,int *yB,int *zB);
	//void changeModelToRegionRrowing();
	void setNewMask(std::shared_ptr<Mask> m);
signals:
	void maskResult(std::shared_ptr<Mask> newMask);
	//void changeVtkClickModel(int model);
protected:
	void closeEvent(QCloseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	void keyReleaseEvent(QKeyEvent *event);
private:
	//int *regionGrowingModelPtr[3];
	std::shared_ptr<Mask> regionRrowingMask;//这个临时保存的Mask要在最后reset以免增加引用计数
	QMainWindow *mainWindow;
};
