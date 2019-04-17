/********************************************************************************
** Form generated from reading UI file 'exportObjDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXPORTOBJDIALOG_H
#define UI_EXPORTOBJDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_exportObjDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *tipLabel;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *textEditLabel;
    QLineEdit *filePrefixLineEdit;
    QPushButton *browseButton;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *exportButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *exportObjDialog)
    {
        if (exportObjDialog->objectName().isEmpty())
            exportObjDialog->setObjectName(QStringLiteral("exportObjDialog"));
        exportObjDialog->resize(466, 338);
        layoutWidget = new QWidget(exportObjDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 11, 381, 301));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tipLabel = new QLabel(layoutWidget);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));

        verticalLayout->addWidget(tipLabel);

        tableWidget = new QTableWidget(layoutWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textEditLabel = new QLabel(layoutWidget);
        textEditLabel->setObjectName(QStringLiteral("textEditLabel"));

        horizontalLayout->addWidget(textEditLabel);

        filePrefixLineEdit = new QLineEdit(layoutWidget);
        filePrefixLineEdit->setObjectName(QStringLiteral("filePrefixLineEdit"));

        horizontalLayout->addWidget(filePrefixLineEdit);

        browseButton = new QPushButton(layoutWidget);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout->addWidget(browseButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        exportButton = new QPushButton(layoutWidget);
        exportButton->setObjectName(QStringLiteral("exportButton"));

        horizontalLayout_2->addWidget(exportButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(exportObjDialog);

        QMetaObject::connectSlotsByName(exportObjDialog);
    } // setupUi

    void retranslateUi(QWidget *exportObjDialog)
    {
        exportObjDialog->setWindowTitle(QApplication::translate("exportObjDialog", "exportObjDialog", Q_NULLPTR));
        tipLabel->setText(QApplication::translate("exportObjDialog", "select objs to export:", Q_NULLPTR));
        textEditLabel->setText(QApplication::translate("exportObjDialog", "Export To:", Q_NULLPTR));
        browseButton->setText(QApplication::translate("exportObjDialog", "Browse", Q_NULLPTR));
        exportButton->setText(QApplication::translate("exportObjDialog", "Export", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("exportObjDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class exportObjDialog: public Ui_exportObjDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXPORTOBJDIALOG_H
