/********************************************************************************
** Form generated from reading UI file 'CurvesDialog.ui'
**
** Created: Tue Oct 8 13:42:59 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CURVESDIALOG_H
#define UI_CURVESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CurvesDialog
{
public:
    QDialogButtonBox *buttonBox_2;
    QGraphicsView *graphicsView;
    QPushButton *pushButton;
    QListWidget *listWidget;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;

    void setupUi(QDialog *CurvesDialog)
    {
        if (CurvesDialog->objectName().isEmpty())
            CurvesDialog->setObjectName(QString::fromUtf8("CurvesDialog"));
        CurvesDialog->resize(510, 501);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(CurvesDialog->sizePolicy().hasHeightForWidth());
        CurvesDialog->setSizePolicy(sizePolicy);
        CurvesDialog->setMinimumSize(QSize(300, 500));
        CurvesDialog->setSizeIncrement(QSize(1, 1));
        buttonBox_2 = new QDialogButtonBox(CurvesDialog);
        buttonBox_2->setObjectName(QString::fromUtf8("buttonBox_2"));
        buttonBox_2->setGeometry(QRect(160, 450, 176, 27));
        buttonBox_2->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        graphicsView = new QGraphicsView(CurvesDialog);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 40, 256, 281));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(256, 256));
        graphicsView->setFrameShape(QFrame::StyledPanel);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setInteractive(true);
        graphicsView->setAlignment(Qt::AlignCenter);
        graphicsView->setCacheMode(QGraphicsView::CacheBackground);
        graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
        graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        graphicsView->setRubberBandSelectionMode(Qt::IntersectsItemBoundingRect);
        graphicsView->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing|QGraphicsView::DontClipPainter|QGraphicsView::DontSavePainterState|QGraphicsView::IndirectPainting);
        pushButton = new QPushButton(CurvesDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 450, 98, 27));
        listWidget = new QListWidget(CurvesDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(290, 40, 131, 192));
        doubleSpinBox = new QDoubleSpinBox(CurvesDialog);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(30, 340, 62, 27));
        doubleSpinBox_2 = new QDoubleSpinBox(CurvesDialog);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(120, 340, 62, 27));

        retranslateUi(CurvesDialog);

        QMetaObject::connectSlotsByName(CurvesDialog);
    } // setupUi

    void retranslateUi(QDialog *CurvesDialog)
    {
        CurvesDialog->setWindowTitle(QApplication::translate("CurvesDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("CurvesDialog", "PushButton", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CurvesDialog: public Ui_CurvesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CURVESDIALOG_H
