/********************************************************************************
** Form generated from reading UI file 'thresholdValueDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_THRESHOLDVALUEDIALOG_H
#define UI_THRESHOLDVALUEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_thresholdValueDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *tipLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *minLabel;
    QSpinBox *minThresholdSpinBox;
    QSlider *minThresholdSlider;
    QHBoxLayout *horizontalLayout_2;
    QLabel *maxLabel;
    QSpinBox *maxThresholdSpinBox;
    QSlider *maxThresholdSlider;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *applyButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *thresholdValueDialog)
    {
        if (thresholdValueDialog->objectName().isEmpty())
            thresholdValueDialog->setObjectName(QStringLiteral("thresholdValueDialog"));
        thresholdValueDialog->resize(498, 146);
        layoutWidget = new QWidget(thresholdValueDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 11, 466, 116));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tipLabel = new QLabel(layoutWidget);
        tipLabel->setObjectName(QStringLiteral("tipLabel"));

        verticalLayout->addWidget(tipLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        minLabel = new QLabel(layoutWidget);
        minLabel->setObjectName(QStringLiteral("minLabel"));

        horizontalLayout->addWidget(minLabel);

        minThresholdSpinBox = new QSpinBox(layoutWidget);
        minThresholdSpinBox->setObjectName(QStringLiteral("minThresholdSpinBox"));

        horizontalLayout->addWidget(minThresholdSpinBox);

        minThresholdSlider = new QSlider(layoutWidget);
        minThresholdSlider->setObjectName(QStringLiteral("minThresholdSlider"));
        minThresholdSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(minThresholdSlider);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        maxLabel = new QLabel(layoutWidget);
        maxLabel->setObjectName(QStringLiteral("maxLabel"));

        horizontalLayout_2->addWidget(maxLabel);

        maxThresholdSpinBox = new QSpinBox(layoutWidget);
        maxThresholdSpinBox->setObjectName(QStringLiteral("maxThresholdSpinBox"));

        horizontalLayout_2->addWidget(maxThresholdSpinBox);

        maxThresholdSlider = new QSlider(layoutWidget);
        maxThresholdSlider->setObjectName(QStringLiteral("maxThresholdSlider"));
        maxThresholdSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(maxThresholdSlider);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        applyButton = new QPushButton(layoutWidget);
        applyButton->setObjectName(QStringLiteral("applyButton"));

        horizontalLayout_3->addWidget(applyButton);

        cancelButton = new QPushButton(layoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_3->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(thresholdValueDialog);

        QMetaObject::connectSlotsByName(thresholdValueDialog);
    } // setupUi

    void retranslateUi(QDialog *thresholdValueDialog)
    {
        thresholdValueDialog->setWindowTitle(QApplication::translate("thresholdValueDialog", "Create 3D Mask", Q_NULLPTR));
        tipLabel->setText(QApplication::translate("thresholdValueDialog", "Make sure the range of threshold value to apply a 3d mask:", Q_NULLPTR));
        minLabel->setText(QApplication::translate("thresholdValueDialog", "Min threshold:", Q_NULLPTR));
        maxLabel->setText(QApplication::translate("thresholdValueDialog", "Max threshold:", Q_NULLPTR));
        applyButton->setText(QApplication::translate("thresholdValueDialog", "Apply", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("thresholdValueDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class thresholdValueDialog: public Ui_thresholdValueDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_THRESHOLDVALUEDIALOG_H
