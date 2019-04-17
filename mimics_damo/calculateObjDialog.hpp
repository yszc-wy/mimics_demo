#pragma once
#include <QDialog>
#include "ui_calculateObjDialog.h"
#include <memory>
#include <vtkSmartPointer.h>
#include "calculateObjThread.hpp"
class Mask;
class Object;
class QButtonGroup;
class vtkRenderer;
class QVTKWidget;
class QProgressDialog;
class QVTK3DWidget;
class CalculateObjDialog : public QDialog, public Ui::calculateObjDialog {
	Q_OBJECT

public:
	CalculateObjDialog(QWidget * parent = Q_NULLPTR);
	~CalculateObjDialog();
	void setMaskPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtr);
	void setObjPtrQMapPtr(std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtr);
	void setRen3dViewer(vtkSmartPointer<vtkRenderer> ren);
	void setViewWidget(QVTK3DWidget *widget);
	const CalculateObjThread* getCalculateObjThreadPtr();
	//void setStatusProgressBarAndLabel(QProgressBar* pBar, QLabel* pLabel);
	void updateTableWidget();
private slots:
	void calculateObj();
	void updateProcessDialog(const QString& a, int value);
	void updateCurrentMaskName(int, int);
protected:
	void closeEvent(QCloseEvent *event);
private:
	void addRow();
	void initMaskTableWidget();
	void initButton();
	std::shared_ptr<QMap<QString, std::shared_ptr<Mask>>> maskPtrQMapPtr;
	//std::shared_ptr<QMap<QString, std::shared_ptr<Object>>> objPtrQMapPtr;//obj资源管理
	//vtkSmartPointer<vtkRenderer> ren_3dViewer;
	QVTK3DWidget *widget_3dViewer;
	//QProgressBar *statusProgressBar;
	//QLabel *statusProgressBarLabel;

	QString currentMaskName;
	QButtonGroup *radioButtonGroup;
	QProgressDialog *progressDialog;

	CalculateObjThread calThread;
	//Ui::calculateObjDialog ui;
};
