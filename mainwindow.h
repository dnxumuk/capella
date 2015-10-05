#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include "headers/glFrame.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    //Frame *frm;

public slots:
    void Curve();
};

#endif // MAINWINDOW_H
