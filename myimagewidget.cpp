#include "myimagewidget.h"

#define PIXWIDTH 6

MyImageWidget::MyImageWidget(QWidget *parent)
	: QWidget(parent)
{
	//// Initialize background to white board
	//QImage white(360, 340, QImage::Format_RGB32);
	//white.fill(QColor(0, 1, 1));
	//background = white;
	//this->repaint();
}

MyImageWidget::~MyImageWidget()
{
}

void MyImageWidget::Draw2dProjection(std::vector<trimesh::point>& model_pts)
{
	repaint();
	this->background_plus = this->background.copy();
	QPen pen(Qt::blue);
	pen.setWidth(3);
	QPainter pixPaint(&background_plus);
	pixPaint.setPen(pen);
	
	trimesh::point A = model_pts[0];
	trimesh::point B = model_pts[1];
	trimesh::point C = model_pts[2];
	trimesh::point D = model_pts[3];

	trimesh::point E = model_pts[4];
	trimesh::point F = model_pts[5];
	trimesh::point G = model_pts[6];
	trimesh::point H = model_pts[7];

	trimesh::point T = model_pts[8];

	int HEIGHT = background.height();
	pixPaint.drawLine(T[0], HEIGHT - T[1], A[0], HEIGHT - A[1]);	//TA
	pixPaint.drawLine(T[0], HEIGHT - T[1], B[0], HEIGHT - B[1]);	//TB
	pixPaint.drawLine(T[0], HEIGHT - T[1], C[0], HEIGHT - C[1]);	//TC
	pixPaint.drawLine(T[0], HEIGHT - T[1], D[0], HEIGHT - D[1]);	//TD

	pixPaint.drawLine(A[0], HEIGHT - A[1], B[0], HEIGHT - B[1]);	//AB
	pixPaint.drawLine(B[0], HEIGHT - B[1], C[0], HEIGHT - C[1]);	//BC
	pixPaint.drawLine(C[0], HEIGHT - C[1], D[0], HEIGHT - D[1]);	//CD
	pixPaint.drawLine(D[0], HEIGHT - D[1], A[0], HEIGHT - A[1]);	//DA

	pixPaint.drawLine(A[0], HEIGHT - A[1], E[0], HEIGHT - E[1]);	//AE
	pixPaint.drawLine(B[0], HEIGHT - B[1], F[0], HEIGHT - F[1]);	//BF
	pixPaint.drawLine(C[0], HEIGHT - C[1], G[0], HEIGHT - G[1]);	//CG
	pixPaint.drawLine(D[0], HEIGHT - D[1], H[0], HEIGHT - H[1]);	//DH

	pixPaint.drawLine(E[0], HEIGHT - E[1], F[0], HEIGHT - F[1]);	//EF
	pixPaint.drawLine(F[0], HEIGHT - F[1], G[0], HEIGHT - G[1]);	//FG
	pixPaint.drawLine(G[0], HEIGHT - G[1], H[0], HEIGHT - H[1]);	//GH
	pixPaint.drawLine(H[0], HEIGHT - H[1], E[0], HEIGHT - E[1]);	//HE

	pen.setColor(Qt::red);
	pen.setWidth(5);
	pixPaint.setPen(pen);
	for (int i = 0; i < model_pts.size()-1; i++) {
		pixPaint.drawPoint(model_pts[i][0], HEIGHT - model_pts[i][1]);
	}
	int last = model_pts.size() - 1;
	pen.setColor(Qt::black);
	pen.setWidth(7);
	pixPaint.setPen(pen);
	pixPaint.drawPoint(model_pts[last][0], HEIGHT - model_pts[last][1]);
	return;
}

void MyImageWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	QRect imageRect(background_plus.rect());
	QRect devRect(0, 0, painter.device()->width(), painter.device()->height());
	//imageRect.moveCenter(devRect.center());
	painter.drawImage(devRect, background_plus, imageRect);
	//painter.drawImage(QPoint(0, 0), background);
	painter.end();
}

void MyImageWidget::setBackgroundImage(std::string image_dir)
{
	background.load(QString(image_dir.c_str()));
	background_plus = background.copy();
	repaint();
}