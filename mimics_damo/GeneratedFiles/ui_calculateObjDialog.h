/********************************************************************************
** Form generated from reading UI file 'calculateObjDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCULATEOBJDIALOG_H
#define UI_CALCULATEOBJDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_calculateObjDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QLabel *tipLabel;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QTableWidget *maskTableWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *lowRadioButton;
    QRadioButton *middleRadioButton;
    QRadioButton *highRadioButton;
    QRadioButton *originalRadioButton;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *calculateButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *calculateObjDialog)
    {
        if (calculateObjDialog->objectName().isEmpty())
            calculateObjDialog->setObjectName(QStringLiteral("calculateObjDialog"));
        calculateObjDialog->resize(494, 353);
        layoutWidget = new QWidget(calculateObjDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 441, 291));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        tipLabel = new QLabel(layoutWidget);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));

        verticalLayout_3->addWidget(tipLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        maskTableWidget = new QTableWidget(layoutWidget);
        maskTableWidget->setObjectName(QStringLiteral("maskTableWidget"));

        horizontalLayout->addWidget(maskTableWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lowRadioButton = new QRadioButton(layoutWidget);
        lowRadioButton->setObjectName(QStringLiteral("lowRadioButton"));

        verticalLayout->addWidget(lowRadioButton);

        middleRadioButton = new QRadioButton(layoutWidget);
        middleRadioButton->setObjectName(QStringLiteral("middleRadioButton"));

        verticalLayout->addWidget(middleRadioButton);

        highRadioButton = new QRadioButton(layoutWidget);
        highRadioButton->setObjectName(QStringLiteral("highRadioButton"));

        verticalLayout->addWidget(highRadioButton);

        originalRadioButton = new QRadioButton(layoutWidget);
        originalRadioButton->setObjectName(QStringLiteral("originalRadioButton"));

        verticalLayout->addWidget(originalRadioButton);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        calculateButton = new QPushButton(layoutWidget);
        calculateButton->setObjectName(QStringLiteral("calculateButton"));

        horizontalLayout_2->addWidget(calculateButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(calculateObjDialog);

        QMetaObject::connectSlotsByName(calculateObjDialog);
    } // setupUi

    void retranslateUi(QDialog *calculateObjDialog)
    {
        calculateObjDialog->setWindowTitle(QApplication::translate("calculateObjDialog", "calculateObjDialog", Q_NULLPTR));
        tipLabel->setText(QApplication::translate("calculateObjDialog", "please select series mask to calculte.", Q_NULLPTR));
        lowRadioButton->setText(QApplication::translate("calculateObjDialog", "Low obj", Q_NULLPTR));
        middleRadioButton->setText(QApplication::translate("calculateObjDialog", "Middle obj", Q_NULLPTR));
        highRadioButton->setText(QApplication::translate("calculateObjDialog", "High obj", Q_NULLPTR));
        originalRadioButton->setText(QApplication::translate("calculateObjDialog", "Original obj", Q_NULLPTR));
        calculateButton->setText(QApplication::translate("calculateObjDialog", "Calculate", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("calculateObjDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class calculateObjDialog: public Ui_calculateObjDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCULATEOBJDIALOG_H
