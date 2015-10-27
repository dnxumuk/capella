#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenuBar>
#include "./gui/toolcurvesdialog.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    frame = new FrameDisplayGL;
    setCentralWidget(frame);
    connect( ui->actionLAB_RGB, SIGNAL( triggered(bool) ), SLOT(Curve()) );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete frame;
}

void MainWindow::Curve()
{
    ToolCurvesDialog *xxx = new ToolCurvesDialog();
    connect(xxx,SIGNAL(MySetValueSignal(int)), frame, SLOT(redraw()));
    //ImageDisplay x = *(frame->image);
    xxx->setImage(*(frame->image));
    xxx->exec();
}
