/********************************************************************************
** Form generated from reading UI file 'qvtk3dviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVTK3DVIEWER_H
#define UI_QVTK3DVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <qvtkwidget.h>

QT_BEGIN_NAMESPACE

class Ui_QVTK3DViewer
{
public:

    void setupUi(QVTKWidget *QVTK3DViewer)
    {
        if (QVTK3DViewer->objectName().isEmpty())
            QVTK3DViewer->setObjectName(QStringLiteral("QVTK3DViewer"));
        QVTK3DViewer->resize(400, 300);

        retranslateUi(QVTK3DViewer);

        QMetaObject::connectSlotsByName(QVTK3DViewer);
    } // setupUi

    void retranslateUi(QVTKWidget *QVTK3DViewer)
    {
        QVTK3DViewer->setWindowTitle(QApplication::translate("QVTK3DViewer", "QVTK3DViewer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QVTK3DViewer: public Ui_QVTK3DViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVTK3DVIEWER_H
