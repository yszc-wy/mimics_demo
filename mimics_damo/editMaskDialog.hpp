#pragma once
#include <QDialog>
//#include "ui_editmaskdialog.h"

class EditMaskDialog : public QDialog {
	Q_OBJECT

public:
	EditMaskDialog(QWidget * parent = Q_NULLPTR);
	~EditMaskDialog();

private:
	//Ui::editMaskDialog ui;
};
