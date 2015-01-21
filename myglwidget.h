#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QGLWidget>

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

private:
    QPoint lastPos;

    int xRot;
    int yRot;
    int zRot;

private:
   void setXRotation(int angle);
   void setYRotation(int angle);
   void setZRotation(int angle);
   void draw();
};

#endif // MYGLWIDGET_H
