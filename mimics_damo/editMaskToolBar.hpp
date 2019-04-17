#pragma once
#include <qtoolbar.h>
class QLabel;
class QComboBox;
class QSpinBox;
class QRadioButton;
class QCheckBox;
class QPushButton;
class QButtonGroup;
class EditMaskToolBar : public QToolBar {
	Q_OBJECT

public:
	EditMaskToolBar(const QString &title,QWidget * parent = Q_NULLPTR);
	void changeModelToEditMask();
	~EditMaskToolBar();
protected:
	void showEvent(QShowEvent* event);
	void closeEvent(QCloseEvent *event);
signals:
	//void changeVtkClickModel(int model);
	void editMaskPenMsg(int type, int width, /*int height,*/ int model);
	void closeToolBar();
private slots:
	//void synchronizeSpinBox(int value);
	void emitEditMaskPenMsg();
private:
	bool recursion;

	QWidget* penSettingWidget;
	QLabel* typeLabel;
	QComboBox*typeComboBox;
	QLabel* widthLabel;
	QSpinBox*widthSpinBox;
	QLabel* heightLabel;
	QSpinBox*heightSpinBox;

	QWidget* penModelWidget;
	QButtonGroup *radioButtonGroup;
	QRadioButton *drawButton;
	QRadioButton *eraseButton;
	QCheckBox* sameWHCheckBox;
	
	QPushButton*closeButton;
};
