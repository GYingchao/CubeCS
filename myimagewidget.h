#ifndef MYIMAGEWIDGET_H
#define MYIMAGEWIDGET_H

#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QPen>

#include <string>

#include "TriMesh.h"

class MyImageWidget : public QWidget
{
	Q_OBJECT

public:
	MyImageWidget(QWidget *parent);
	~MyImageWidget();

	void Draw2dProjection(std::vector<trimesh::point>& model_pts);
	void setBackgroundImage(std::string image_dir);
	void paintEvent(QPaintEvent *event);
private:
	QImage background;	// original loaded images
	QImage background_plus;	// canvas for drawing 2d features
	
};     

#endif // MYIMAGEWIDGET_H
