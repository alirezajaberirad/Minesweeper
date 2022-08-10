#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QIcon>
#include<QString>
#include<QDebug>
#include<string>
#include<iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pushButtonLander(int x, int y)
{
    QPushButton *button=new QPushButton(this);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/pics/pictures/gameBottons.png"), QSize(), QIcon::Normal);

    button->setIcon(icon);
    button->setFixedSize(20,20);
    button->setGeometry(20*x,20*y,20*x,20*y);
}

void MainWindow::tableMaker(int x, int y)
{
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++)
            pushButtonLander(i,j);
    }
}
