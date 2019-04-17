#pragma once
#include <QDialog>
#include "ui_thresholdValueDialog.h"
class CreateMaskDialog : public QDialog,public Ui::thresholdValueDialog {
	Q_OBJECT
public:
	CreateMaskDialog(QWidget * parent = Q_NULLPTR);
	~CreateMaskDialog();

	//int* getThresholdValue();
	void initDialog(int minScalar,int maxScalar);
signals:
	void thresholdValueChanged(int min, int max);
	void thresholdValueResult(int min, int max);
	//void thresholdValueChanged(int min, int max);
private slots:
	void emitValueChangedSignal();
	void Accept();
	void Close();
protected:
	void closeEvent(QCloseEvent *event);
private:
	void setScalarRange(int min, int max);

	int thresholdValueRange[2];
};
