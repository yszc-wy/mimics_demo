/********************************************************************************
** Form generated from reading UI file 'ProjectMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTMAINWINDOW_H
#define UI_PROJECTMAINWINDOW_H


#include <vtkAutoInit.h>  
VTK_MODULE_INIT(vtkRenderingOpenGL2);
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"


QT_BEGIN_NAMESPACE

class Ui_ProjectMainWindow
{
public:
    QAction *actionLoadImage;
    QAction *m_OpenAction;
    QWidget *m_CentralWidget;
    QVBoxLayout *verticalLayout;
    QVTKWidget *m_QVTKWidget;
    QMenuBar *menubar;
    QMenu *m_MenuFile;
    QStatusBar *m_StatusBar;

    void setupUi(QMainWindow *ProjectMainWindow)
    {
        if (ProjectMainWindow->objectName().isEmpty())
            ProjectMainWindow->setObjectName(QStringLiteral("ProjectMainWindow"));
        ProjectMainWindow->resize(595, 482);
        actionLoadImage = new QAction(ProjectMainWindow);
        actionLoadImage->setObjectName(QStringLiteral("actionLoadImage"));
        m_OpenAction = new QAction(ProjectMainWindow);
        m_OpenAction->setObjectName(QStringLiteral("m_OpenAction"));
        m_CentralWidget = new QWidget(ProjectMainWindow);
        m_CentralWidget->setObjectName(QStringLiteral("m_CentralWidget"));
        verticalLayout = new QVBoxLayout(m_CentralWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_QVTKWidget = new QVTKWidget(m_CentralWidget);
        m_QVTKWidget->setObjectName(QStringLiteral("m_QVTKWidget"));

        verticalLayout->addWidget(m_QVTKWidget);

        ProjectMainWindow->setCentralWidget(m_CentralWidget);
        menubar = new QMenuBar(ProjectMainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 595, 21));
        m_MenuFile = new QMenu(menubar);
        m_MenuFile->setObjectName(QStringLiteral("m_MenuFile"));
        ProjectMainWindow->setMenuBar(menubar);
        m_StatusBar = new QStatusBar(ProjectMainWindow);
        m_StatusBar->setObjectName(QStringLiteral("m_StatusBar"));
        ProjectMainWindow->setStatusBar(m_StatusBar);

        menubar->addAction(m_MenuFile->menuAction());
        m_MenuFile->addAction(m_OpenAction);

        retranslateUi(ProjectMainWindow);

        QMetaObject::connectSlotsByName(ProjectMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectMainWindow)
    {
        ProjectMainWindow->setWindowTitle(QApplication::translate("ProjectMainWindow", "VTK\344\270\216Qt\346\225\264\345\220\210\347\232\204\347\244\272\344\276\213-\350\257\273\345\217\226JPG\345\233\276\345\203\217", Q_NULLPTR));
        actionLoadImage->setText(QApplication::translate("ProjectMainWindow", "\346\211\223\345\274\200\345\233\276\345\203\217", Q_NULLPTR));
        m_OpenAction->setText(QApplication::translate("ProjectMainWindow", "\346\211\223\345\274\200", Q_NULLPTR));
        m_MenuFile->setTitle(QApplication::translate("ProjectMainWindow", "\346\226\207\344\273\266", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProjectMainWindow: public Ui_ProjectMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTMAINWINDOW_H
