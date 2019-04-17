/********************************************************************************
** Form generated from reading UI file 'qvtkimageviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QVTKIMAGEVIEWER_H
#define UI_QVTKIMAGEVIEWER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QVTKImageViewer
{
public:

    void setupUi(QWidget *QVTKImageViewer)
    {
        if (QVTKImageViewer->objectName().isEmpty())
            QVTKImageViewer->setObjectName(QStringLiteral("QVTKImageViewer"));
        QVTKImageViewer->resize(400, 300);

        retranslateUi(QVTKImageViewer);

        QMetaObject::connectSlotsByName(QVTKImageViewer);
    } // setupUi

    void retranslateUi(QWidget *QVTKImageViewer)
    {
        QVTKImageViewer->setWindowTitle(QApplication::translate("QVTKImageViewer", "QVTKImageViewer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QVTKImageViewer: public Ui_QVTKImageViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QVTKIMAGEVIEWER_H
