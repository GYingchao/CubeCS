#include "myimagewidget.h"

MyImageWidget::MyImageWidget(QWidget *parent)
	: QWidget(parent)
{
	//// Initialize background to white board
	//QImage white(360, 340, QImage::Format_RGB32);
	//white.fill(QColor(1, 1, 1));
	//background = white;
}

MyImageWidget::~MyImageWidget()
{
}

void MyImageWidget::Draw2dProjection(std::vector<trimesh::point>& model_pts)
{
	QPainter pixPaint(&background);
	for (int i = 0; i < model_pts.size()-1; i++) {
		trimesh::point p1 = model_pts[i];
		trimesh::point p2 = model_pts[i + 1];

		pixPaint.setPen(Qt::blue);
		pixPaint.drawLine(p1[0], p1[1], p2[0], p2[1]);
		pixPaint.setPen(Qt::red);
		pixPaint.drawPoint(p1[0], p1[1]);
	}
	return;
}

void MyImageWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QRect imageRect(background.rect());
	QRect devRect(0, 0, painter.device()->width(), painter.device()->height());
	//imageRect.moveCenter(devRect.center());
	painter.drawImage(devRect, background, imageRect);
	//painter.drawImage(QPoint(0, 0), background);
}

void MyImageWidget::setBackgroundImage(std::string image_dir)
{
	background.load(QString(image_dir.c_str()));
	this->repaint();
}