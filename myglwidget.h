#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>
#include "GL/glut.h"

#include "opencv/cv.h"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"

#include "OpenGLProjector.h"

class MyGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();
signals:

public slots:

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
	//void keyPressEvent(QKeyEvent * e);
	void wheelEvent(QWheelEvent * e);

private:
    QPoint lastPos;
	OpenGLProjector projector;

	// For rotation control
    int xRot;
    int yRot;
    int zRot;

	// For translation control
	double xTran;
	double yTran;
	double zTran;

private:
   void setXRotation(int angle);
   void setYRotation(int angle);
   void setZRotation(int angle);
   void setXTranslation(double offset);
   void setYTranslation(double offset);
   void setZTranslation(double offset);
   void draw();

public:
	std::vector<trimesh::point> getCurrent2DProjection();
};

#endif // MYGLWIDGET_H
