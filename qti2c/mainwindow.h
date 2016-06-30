#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "I2C_Thread.h"

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
    I2C_Thread *hwth;
private slots:
    void update();
    void I2C_Set();
};

#endif // MAINWINDOW_H
