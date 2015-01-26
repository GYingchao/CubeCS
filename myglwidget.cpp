#include <QtWidgets>
#include <QtOpenGL>

#include <iostream>

#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    xRot = 0;
    yRot = 0;
    zRot = 0;

	xTran = 0;
	yTran = 0;
	zTran = 0;
}

MyGLWidget::~MyGLWidget()
{
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::initializeGL()
{
    qglClearColor(Qt::black);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Set up light
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    static GLfloat lightPosition[4] = {0, 0, 10, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	//	Set up camera
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 0, 1);
}

void MyGLWidget::paintGL()
{
	glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslated(0.0 + xTran, 0.5 + yTran, -6.0 + zTran);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);
    draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
//#else
//    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
//#endif
	// Instead we use perspective projection
	GLdouble fov = 60;
	GLdouble aspect = height == 0 ? 1 : width / (GLdouble)height;
	GLdouble zNear = 1.0;
	GLdouble zFar = 20.0;
	gluPerspective(fov, aspect, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        //emit xRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        //emit yRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != zRot) {
        zRot = angle;
        //emit zRotationChanged(angle);
        updateGL();
    }
}

void MyGLWidget::setXTranslation(double offset)
{
	xTran += offset;
}

void MyGLWidget::setYTranslation(double offset)
{
	yTran += offset;
}

void MyGLWidget::setZTranslation(double offset)
{
	zTran += offset;
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
		setZRotation(zRot + 4 * dy);
		updateGL();
	}
	else if (event->buttons() & Qt::MiddleButton) {
		setXTranslation(dx/50.0);
		setYTranslation(-dy/50.0);
		updateGL();
	}
	/*else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }*/
    lastPos = event->pos();
}

//void MyGLWidget::keyPressEvent(QKeyEvent * e)
//{
//	// Didn't react if Focus Policy is by default (No Focus)
//
//	int key = e->key();
//	switch (key) {
//	case Qt::Key_Up:
//		// moving forward y direction
//		yTran += 0.1;
//		updateGL();
//		break;
//	case Qt::Key_Down:
//		// moving forward -y direction
//		yTran -= 0.1;
//		updateGL();
//		break;
//	case Qt::Key_Left:
//		// moving forward -x direction
//		xTran -= 0.1;
//		updateGL();
//		break;
//	case Qt::Key_Right:
//		// moving forward x direction
//		xTran += 0.1;
//		updateGL();
//		break;
//	case Qt::Key_1:
//		// Save the current view into image widget 1
//		
//		break;
//	default:
//		// Do nothing
//		break;
//	}
//}

void MyGLWidget::wheelEvent(QWheelEvent * e)
{
	float numSteps = e->delta() / 8 / 15;

	if (numSteps == 0) {
		e->ignore();
		return;
	}

	//zTran += numSteps/10;
	setZTranslation(numSteps / 10);
	e->accept();
	updateGL();
}

void MyGLWidget::draw()
{
    qglColor(Qt::white);
    glBegin(GL_QUADS);
        glNormal3f(0,0,-1);

        glVertex3f(-1,-1,0);	//A
        glVertex3f(-1,1,0);		//B
        glVertex3f(1,1,0);		//C
        glVertex3f(1,-1,0);		//D
    glEnd();

	// Left face
	glBegin(GL_QUADS);
	glNormal3f(-1, 0, 0);

	glVertex3f(-1, -1, 0);		//A
	glVertex3f(-1, 1, 0);		//B
	glVertex3f(-1, 1, -2);		//F
	glVertex3f(-1, -1, -2);		//E
	glEnd();

	// Up face
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);

	glVertex3f(-1, 1, 0);		//B
	glVertex3f(1, 1, 0);		//C
	glVertex3f(1, 1, -2);		//G
	glVertex3f(-1, 1, -2);		//F
	glEnd();

	// Right face
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);

	glVertex3f(1, 1, 0);		//C
	glVertex3f(1, -1, 0);		//D
	glVertex3f(1, -1, -2);		//H
	glVertex3f(1, 1, -2);		//G
	glEnd();

	// Bottom face
	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);

	glVertex3f(-1, -1, 0);		//A
	glVertex3f(-1, -1, -2);		//E
	glVertex3f(1, -1, -2);		//H
	glVertex3f(1, -1, 0);		//D
	glEnd();

	// Far face
	glBegin(GL_QUADS);
	glNormal3f(0, 0, -1);

	glVertex3f(-1, -1, -2);		//E
	glVertex3f(-1, 1, -2);		//F
	glVertex3f(1, 1, -2);		//G
	glVertex3f(1, -1, -2);		//H
	glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0,-1,0.707);
        glVertex3f(-1,-1,0);
        glVertex3f(1,-1,0);
        glVertex3f(0,0,1.2);	//T
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(1,0, 0.707);
        glVertex3f(1,-1,0);
        glVertex3f(1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(0,1,0.707);
        glVertex3f(1,1,0);
        glVertex3f(-1,1,0);
        glVertex3f(0,0,1.2);
    glEnd();
    glBegin(GL_TRIANGLES);
        glNormal3f(-1,0,0.707);
        glVertex3f(-1,1,0);
        glVertex3f(-1,-1,0);
        glVertex3f(0,0,1.2);
    glEnd();
}

std::vector<trimesh::point> MyGLWidget::getCurrent2DProjection()
{
	this->projector.UpdateMatrices();
	trimesh::point ptA(-1, -1, 0);		//A
	trimesh::point ptB(-1, 1, 0);		//B
	trimesh::point ptC(1, 1, 0);		//C
	trimesh::point ptD(1, -1, 0);		//D

	trimesh::point ptE(-1, -1, -2);		//E
	trimesh::point ptF(-1, 1, -2);		//F
	trimesh::point ptG(1, 1, -2);		//G
	trimesh::point ptH(1, -1, -2);		//H

	trimesh::point ptT(0, 0, 1.2);

	std::vector<trimesh::point> toDrawPts;
	toDrawPts.clear();

	toDrawPts.push_back(projector.Project(ptA));
	toDrawPts.push_back(projector.Project(ptB));
	toDrawPts.push_back(projector.Project(ptC));
	toDrawPts.push_back(projector.Project(ptD));
	toDrawPts.push_back(projector.Project(ptE));
	toDrawPts.push_back(projector.Project(ptF));
	toDrawPts.push_back(projector.Project(ptG));
	toDrawPts.push_back(projector.Project(ptH));
	toDrawPts.push_back(projector.Project(ptT));

	return toDrawPts;
}