/********************************************************************************
** Form generated from reading UI file 'mimics_damo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIMICS_DAMO_H
#define UI_MIMICS_DAMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mimics_damoClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mimics_damoClass)
    {
        if (mimics_damoClass->objectName().isEmpty())
            mimics_damoClass->setObjectName(QStringLiteral("mimics_damoClass"));
        mimics_damoClass->resize(600, 400);
        menuBar = new QMenuBar(mimics_damoClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        mimics_damoClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mimics_damoClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mimics_damoClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(mimics_damoClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mimics_damoClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(mimics_damoClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        mimics_damoClass->setStatusBar(statusBar);

        retranslateUi(mimics_damoClass);

        QMetaObject::connectSlotsByName(mimics_damoClass);
    } // setupUi

    void retranslateUi(QMainWindow *mimics_damoClass)
    {
        mimics_damoClass->setWindowTitle(QApplication::translate("mimics_damoClass", "mimics_damo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class mimics_damoClass: public Ui_mimics_damoClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIMICS_DAMO_H
