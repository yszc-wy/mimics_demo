/********************************************************************************
** Form generated from reading UI file 'regionGrowingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGIONGROWINGDIALOG_H
#define UI_REGIONGROWINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegionGrowingDialog
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *tipLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeButton;

    void setupUi(QDialog *RegionGrowingDialog)
    {
        if (RegionGrowingDialog->objectName().isEmpty())
            RegionGrowingDialog->setObjectName(QStringLiteral("RegionGrowingDialog"));
        RegionGrowingDialog->resize(738, 118);
        widget = new QWidget(RegionGrowingDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 40, 714, 54));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tipLabel = new QLabel(widget);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));

        verticalLayout->addWidget(tipLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        closeButton = new QPushButton(widget);
        closeButton->setObjectName(QStringLiteral("closeButton"));

        horizontalLayout->addWidget(closeButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(RegionGrowingDialog);

        QMetaObject::connectSlotsByName(RegionGrowingDialog);
    } // setupUi

    void retranslateUi(QDialog *RegionGrowingDialog)
    {
        RegionGrowingDialog->setWindowTitle(QApplication::translate("RegionGrowingDialog", "Region Growing", Q_NULLPTR));
        tipLabel->setText(QApplication::translate("RegionGrowingDialog", "mouse click to select series of world seed points.it can be used to begin region growing.", Q_NULLPTR));
        closeButton->setText(QApplication::translate("RegionGrowingDialog", "close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RegionGrowingDialog: public Ui_RegionGrowingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGIONGROWINGDIALOG_H
