#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->imageWidget1->setBackgroundImage("d://rprojects//cubecs//image//bkg.jpg");
	ui->imageWidget2->setBackgroundImage("d://rprojects//cubecs//image//bkg.jpg");
	ui->imageWidget3->setBackgroundImage("d://rprojects//cubecs//image//bkg.jpg");
	ui->imageWidget4->setBackgroundImage("d://rprojects//cubecs//image//bkg.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}
