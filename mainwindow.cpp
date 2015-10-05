#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
//#include "./headers/CurvesDialog.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    frm = new Frame;
   // frm->resize(10,10);333333333333333333333
    setCentralWidget(frm);
    connect(ui->actionLAB_RGB, SIGNAL(activated()), SLOT(Curve()));
 */
}

MainWindow::~MainWindow()
{
    delete ui;
   // delete frm;
}

void MainWindow::Curve()
{
/*
    CurvesDialog *xxx = new CurvesDialog();
    connect(xxx,SIGNAL(MySetValueSignal(int)), frm, SLOT(redraw()));
    xxx->setImage(*(frm->image));
    xxx->exec();
*/

}
