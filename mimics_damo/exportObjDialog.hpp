#pragma once
#include <QDialog>
#include "ui_exportobjdialog.h"
#include <memory>
#include "exportObjThread.hpp"
class Object;
class QFileDialog;
class QProgressDialog;
class ExportObjDialog : public QDialog,public Ui::exportObjDialog{
	Q_OBJECT

public:
	ExportObjDialog(QWidget * parent = Q_NULLPTR);
	~ExportObjDialog();
	void setObjPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtr);
	void updateTableWidget();
private slots:
	void browseFile();
	void exportObj();
	void updateProcessDialog(const QString&);
protected:
	void closeEvent(QCloseEvent *event);
private:
	void initObjTableWidget();
	//void exportObjActor(std::shared_ptr<Object> objPtr);
	void addRow();
	
	QFileDialog *fileDialog;
	QProgressDialog *progressDialog;
	exportObjThread exportThread;
	std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrQMapPtr;
};
