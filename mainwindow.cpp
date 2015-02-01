#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	ui->imageWidget1->setBackgroundImage("..//image//bkg.jpg");
	ui->imageWidget2->setBackgroundImage("..//image//bkg.jpg");
	ui->imageWidget3->setBackgroundImage("..//image//bkg.jpg");
	ui->imageWidget4->setBackgroundImage("..//image//bkg.jpg");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
	int key = e->key();
	switch (key) {
	case Qt::Key_1:
		// Save the current view into image widget 1
		ui->imageWidget1->Draw2dProjection(ui->myGLWidget->getCurrent2DProjection());
		ui->myGLWidget->saveCamera(1);
		ui->imageWidget1->repaint();
		break;
	case Qt::Key_2:
		// Save the current view into image widget 1
		ui->imageWidget2->Draw2dProjection(ui->myGLWidget->getCurrent2DProjection());
		ui->myGLWidget->saveCamera(2);
		ui->imageWidget2->repaint();
		break;
	case Qt::Key_3:
		// Save the current view into image widget 1
		ui->imageWidget3->Draw2dProjection(ui->myGLWidget->getCurrent2DProjection());
		ui->myGLWidget->saveCamera(3);
		ui->imageWidget3->repaint();
		break;
	case Qt::Key_4:
		// Save the current view into image widget 1
		ui->imageWidget4->Draw2dProjection(ui->myGLWidget->getCurrent2DProjection());
		ui->myGLWidget->saveCamera(4);
		ui->imageWidget4->repaint();
		break;
	default:
		// Do nothing
		break;
	}
}

void MainWindow::Noise()
{
	ui->myGLWidget->GaussianNoise(0.0, 0.25);
	ui->imageWidget1->Draw2dProjectionWithDistortion(ui->myGLWidget->get2DProjection(1));
	ui->imageWidget2->Draw2dProjectionWithDistortion(ui->myGLWidget->get2DProjection(2));
	ui->imageWidget3->Draw2dProjectionWithDistortion(ui->myGLWidget->get2DProjection(3));
	ui->imageWidget4->Draw2dProjectionWithDistortion(ui->myGLWidget->get2DProjection(4));
}