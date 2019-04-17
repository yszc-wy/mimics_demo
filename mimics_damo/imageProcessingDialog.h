#pragma once
#include <QDialog>
#include <qmainwindow.h>
#include "ui_imageProcessingDialog.h"
class ImageProcessingDialog : public QDialog,Ui::ImageProcessingDialog
{
	Q_OBJECT
public:
	ImageProcessingDialog(QMainWindow * parent = Q_NULLPTR);
	void Clear();
	void AddToMaskCombox(const QString& mask_name);
	void SetMaskComboxId(int id);
	~ImageProcessingDialog();
signals:
	void processingRequest(QString,QVector<QString>);
private:
	
};

