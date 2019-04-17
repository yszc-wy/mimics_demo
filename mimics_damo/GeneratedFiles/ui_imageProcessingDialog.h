/********************************************************************************
** Form generated from reading UI file 'imageProcessingDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSINGDIALOG_H
#define UI_IMAGEPROCESSINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageProcessingDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *maskComboBox;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter_3;
    QLabel *label_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *deleteButton;
    QPushButton *deleteBottomButton;
    QListWidget *orderListWidget;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QTabWidget *algorithmWidget;
    QWidget *Sharpening;
    QWidget *layoutWidget3;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout;
    QLabel *gaussFilterLabel;
    QPushButton *gaussFilterAddButton;
    QWidget *Filtering;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *laplacianSharpenerLabel;
    QPushButton *laplacianSharpenerAddButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *applicationButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *ImageProcessingDialog)
    {
        if (ImageProcessingDialog->objectName().isEmpty())
            ImageProcessingDialog->setObjectName(QStringLiteral("ImageProcessingDialog"));
        ImageProcessingDialog->resize(993, 647);
        gridLayout = new QGridLayout(ImageProcessingDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_2 = new QLabel(ImageProcessingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_4->addWidget(label_2);

        maskComboBox = new QComboBox(ImageProcessingDialog);
        maskComboBox->setObjectName(QStringLiteral("maskComboBox"));

        horizontalLayout_4->addWidget(maskComboBox);


        verticalLayout_5->addLayout(horizontalLayout_4);

        splitter_2 = new QSplitter(ImageProcessingDialog);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        splitter->setOpaqueResize(false);
        splitter->setChildrenCollapsible(false);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        splitter_3 = new QSplitter(layoutWidget);
        splitter_3->setObjectName(QStringLiteral("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        label_3 = new QLabel(splitter_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        splitter_3->addWidget(label_3);
        layoutWidget1 = new QWidget(splitter_3);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        deleteButton = new QPushButton(layoutWidget1);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));

        horizontalLayout_5->addWidget(deleteButton);

        deleteBottomButton = new QPushButton(layoutWidget1);
        deleteBottomButton->setObjectName(QStringLiteral("deleteBottomButton"));

        horizontalLayout_5->addWidget(deleteBottomButton);

        splitter_3->addWidget(layoutWidget1);

        verticalLayout_4->addWidget(splitter_3);

        orderListWidget = new QListWidget(layoutWidget);
        orderListWidget->setObjectName(QStringLiteral("orderListWidget"));

        verticalLayout_4->addWidget(orderListWidget);

        splitter->addWidget(layoutWidget);
        layoutWidget2 = new QWidget(splitter);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        algorithmWidget = new QTabWidget(layoutWidget2);
        algorithmWidget->setObjectName(QStringLiteral("algorithmWidget"));
        Sharpening = new QWidget();
        Sharpening->setObjectName(QStringLiteral("Sharpening"));
        layoutWidget3 = new QWidget(Sharpening);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(20, 20, 379, 54));
        verticalLayout = new QVBoxLayout(layoutWidget3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gaussFilterLabel = new QLabel(layoutWidget3);
        gaussFilterLabel->setObjectName(QStringLiteral("gaussFilterLabel"));

        horizontalLayout->addWidget(gaussFilterLabel);

        gaussFilterAddButton = new QPushButton(layoutWidget3);
        gaussFilterAddButton->setObjectName(QStringLiteral("gaussFilterAddButton"));

        horizontalLayout->addWidget(gaussFilterAddButton);


        verticalLayout->addLayout(horizontalLayout);

        algorithmWidget->addTab(Sharpening, QString());
        Filtering = new QWidget();
        Filtering->setObjectName(QStringLiteral("Filtering"));
        layoutWidget4 = new QWidget(Filtering);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(20, 20, 364, 54));
        verticalLayout_2 = new QVBoxLayout(layoutWidget4);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget4);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        laplacianSharpenerLabel = new QLabel(layoutWidget4);
        laplacianSharpenerLabel->setObjectName(QStringLiteral("laplacianSharpenerLabel"));

        horizontalLayout_2->addWidget(laplacianSharpenerLabel);

        laplacianSharpenerAddButton = new QPushButton(layoutWidget4);
        laplacianSharpenerAddButton->setObjectName(QStringLiteral("laplacianSharpenerAddButton"));

        horizontalLayout_2->addWidget(laplacianSharpenerAddButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        algorithmWidget->addTab(Filtering, QString());

        verticalLayout_3->addWidget(algorithmWidget);

        splitter->addWidget(layoutWidget2);
        splitter_2->addWidget(splitter);

        verticalLayout_5->addWidget(splitter_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        applicationButton = new QPushButton(ImageProcessingDialog);
        applicationButton->setObjectName(QStringLiteral("applicationButton"));

        horizontalLayout_3->addWidget(applicationButton);

        cancelButton = new QPushButton(ImageProcessingDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);


        verticalLayout_5->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);


        retranslateUi(ImageProcessingDialog);

        algorithmWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(ImageProcessingDialog);
    } // setupUi

    void retranslateUi(QDialog *ImageProcessingDialog)
    {
        ImageProcessingDialog->setWindowTitle(QApplication::translate("ImageProcessingDialog", "Image Processing", Q_NULLPTR));
        label_2->setText(QApplication::translate("ImageProcessingDialog", "Current Mask:", Q_NULLPTR));
        label_3->setText(QApplication::translate("ImageProcessingDialog", "Processing Order:", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("ImageProcessingDialog", "Delete", Q_NULLPTR));
        deleteBottomButton->setText(QApplication::translate("ImageProcessingDialog", "Delete Bottom", Q_NULLPTR));
        label->setText(QApplication::translate("ImageProcessingDialog", "Processing Algorithm:", Q_NULLPTR));
        label_4->setText(QApplication::translate("ImageProcessingDialog", "Filters:", Q_NULLPTR));
        gaussFilterLabel->setText(QApplication::translate("ImageProcessingDialog", "Gauss Filter:", Q_NULLPTR));
        gaussFilterAddButton->setText(QApplication::translate("ImageProcessingDialog", "Add", Q_NULLPTR));
        algorithmWidget->setTabText(algorithmWidget->indexOf(Sharpening), QApplication::translate("ImageProcessingDialog", "Tab 1", Q_NULLPTR));
        label_5->setText(QApplication::translate("ImageProcessingDialog", "Sharpeners:", Q_NULLPTR));
        laplacianSharpenerLabel->setText(QApplication::translate("ImageProcessingDialog", "Laplacian Sharpener:", Q_NULLPTR));
        laplacianSharpenerAddButton->setText(QApplication::translate("ImageProcessingDialog", "Add", Q_NULLPTR));
        algorithmWidget->setTabText(algorithmWidget->indexOf(Filtering), QApplication::translate("ImageProcessingDialog", "Tab 2", Q_NULLPTR));
        applicationButton->setText(QApplication::translate("ImageProcessingDialog", "Application", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("ImageProcessingDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ImageProcessingDialog: public Ui_ImageProcessingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSINGDIALOG_H
