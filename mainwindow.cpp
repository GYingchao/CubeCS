#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->imageWidget1->setBackgroundImage("D://rProjects//cubeCS//image//v1.JPG");
	ui->imageWidget2->setBackgroundImage("D://rProjects//cubeCS//image//v2.JPG");
	ui->imageWidget3->setBackgroundImage("D://rProjects//cubeCS//image//v3.JPG");
	ui->imageWidget4->setBackgroundImage("D://rProjects//cubeCS//image//v4.JPG");
}

MainWindow::~MainWindow()
{
    delete ui;
}
