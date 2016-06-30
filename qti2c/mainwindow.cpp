#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hwth = new I2C_Thread;
    connect(hwth, SIGNAL(finished()), this, SLOT(I2C_Set()));
    hwth->start();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
     hwth->start();
}
void MainWindow::I2C_Set()
{



        // Voltage Infomation
        ui->lblLocalTemp->setText(hwth->LocalTemp);
        ui->lblRemoteTemp->setText(hwth->RemoteTemp);



}
