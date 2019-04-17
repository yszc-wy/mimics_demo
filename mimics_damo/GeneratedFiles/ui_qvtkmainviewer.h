/********************************************************************************
** Form generated from reading UI file 'qvtkmainviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVTKMAINVIEWER_H
#define UI_QVTKMAINVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QVTKMainViewer
{
public:

    void setupUi(QWidget *QVTKMainViewer)
    {
        if (QVTKMainViewer->objectName().isEmpty())
            QVTKMainViewer->setObjectName(QStringLiteral("QVTKMainViewer"));
        QVTKMainViewer->resize(400, 300);

        retranslateUi(QVTKMainViewer);

        QMetaObject::connectSlotsByName(QVTKMainViewer);
    } // setupUi

    void retranslateUi(QWidget *QVTKMainViewer)
    {
        QVTKMainViewer->setWindowTitle(QApplication::translate("QVTKMainViewer", "QVTKMainViewer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QVTKMainViewer: public Ui_QVTKMainViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVTKMAINVIEWER_H
