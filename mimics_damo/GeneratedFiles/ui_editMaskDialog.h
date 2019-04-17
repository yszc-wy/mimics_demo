/********************************************************************************
** Form generated from reading UI file 'editMaskDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EDITMASKDIALOG_H
#define UI_EDITMASKDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_editMaskDialog
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *typeLabel;
    QComboBox *typeComboBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *widthLabel;
    QSpinBox *widthSpinBox;
    QVBoxLayout *verticalLayout_3;
    QLabel *heightLabel;
    QSpinBox *heightSpinBox;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QRadioButton *drawRadioButton;
    QRadioButton *radioButton_2;
    QSpacerItem *horizontalSpacer;
    QCheckBox *checkBox;
    QPushButton *pushButton;

    void setupUi(QDialog *editMaskDialog)
    {
        if (editMaskDialog->objectName().isEmpty())
            editMaskDialog->setObjectName(QStringLiteral("editMaskDialog"));
        editMaskDialog->resize(616, 417);
        widget = new QWidget(editMaskDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(22, 12, 496, 52));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        typeLabel = new QLabel(widget);
        typeLabel->setObjectName(QStringLiteral("typeLabel"));

        verticalLayout->addWidget(typeLabel);

        typeComboBox = new QComboBox(widget);
        typeComboBox->setObjectName(QStringLiteral("typeComboBox"));

        verticalLayout->addWidget(typeComboBox);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        widthLabel = new QLabel(widget);
        widthLabel->setObjectName(QStringLiteral("widthLabel"));

        verticalLayout_2->addWidget(widthLabel);

        widthSpinBox = new QSpinBox(widget);
        widthSpinBox->setObjectName(QStringLiteral("widthSpinBox"));

        verticalLayout_2->addWidget(widthSpinBox);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        heightLabel = new QLabel(widget);
        heightLabel->setObjectName(QStringLiteral("heightLabel"));

        verticalLayout_3->addWidget(heightLabel);

        heightSpinBox = new QSpinBox(widget);
        heightSpinBox->setObjectName(QStringLiteral("heightSpinBox"));

        verticalLayout_3->addWidget(heightSpinBox);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        drawRadioButton = new QRadioButton(widget);
        drawRadioButton->setObjectName(QStringLiteral("drawRadioButton"));

        horizontalLayout->addWidget(drawRadioButton);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        horizontalLayout->addWidget(radioButton_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_4->addLayout(horizontalLayout);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout_4->addWidget(checkBox);


        horizontalLayout_2->addLayout(verticalLayout_4);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);


        retranslateUi(editMaskDialog);

        QMetaObject::connectSlotsByName(editMaskDialog);
    } // setupUi

    void retranslateUi(QDialog *editMaskDialog)
    {
        editMaskDialog->setWindowTitle(QApplication::translate("editMaskDialog", "editMaskDialog", Q_NULLPTR));
        typeLabel->setText(QApplication::translate("editMaskDialog", "Type:", Q_NULLPTR));
        widthLabel->setText(QApplication::translate("editMaskDialog", "Width:", Q_NULLPTR));
        heightLabel->setText(QApplication::translate("editMaskDialog", "Height", Q_NULLPTR));
        drawRadioButton->setText(QApplication::translate("editMaskDialog", "Draw", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("editMaskDialog", "Erase", Q_NULLPTR));
        checkBox->setText(QApplication::translate("editMaskDialog", "Same Width && Height", Q_NULLPTR));
        pushButton->setText(QApplication::translate("editMaskDialog", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class editMaskDialog: public Ui_editMaskDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EDITMASKDIALOG_H
