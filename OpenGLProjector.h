#ifndef __OPENGLPROJECTOR__
#define __OPENGLPROJECTOR__

#ifdef WIN32
	#include <windows.h>
#endif
#include "GL/glut.h"
#include <cstdlib>
// #include "vector3.h"
#include "Vec.h"

class OpenGLProjector 
{
public:
	double modelView[16];
	double projection[16];
	int viewport[4];

    //float* depthBuffer;
    
public:
	double* ModelViewMatrix() { return modelView; }
	double* ProjectionMatrix() { return projection; }
	int* Viewport() { return viewport; }

	OpenGLProjector()
	{
		glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);
		
		/*if(viewport[2] * viewport[3]>0){
			depthBuffer = new float[viewport[2] * viewport[3]];

			glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_DEPTH_COMPONENT, GL_FLOAT, depthBuffer);
		}*/

	}
	

	trimesh::point UnProject(double inX, double inY, double inZ)
	{
		double x,y,z;
		gluUnProject(inX, inY, inZ, modelView, projection, viewport, &x, &y, &z);
		return trimesh::point(x,y,z);
	}
	trimesh::point UnProject(trimesh::point p)
	{
		double x,y,z;
		gluUnProject(p[0], p[1], p[2], modelView, projection, viewport, &x, &y, &z);
		return trimesh::point(x,y,z);
	}
	trimesh::point Project(double inX, double inY, double inZ)
	{
		double x,y,z;
		gluProject(inX, inY, inZ, modelView, projection, viewport, &x, &y, &z);
		return trimesh::point(x,y,z);
	}
	trimesh::point Project(const trimesh::point& p)
	{
		double x,y,z;
		gluProject(p[0], p[1], p[2], modelView, projection, viewport, &x, &y, &z);
		return trimesh::point(x,y,z);
	}
	trimesh::point ProjectVector(const trimesh::point& p)
	{
		double x,y,z;
		gluProject(p[0], p[1], p[2], modelView, projection, viewport, &x, &y, &z);
		double x0,y0,z0;
		gluProject(0, 0, 0, modelView, projection, viewport, &x0, &y0, &z0);
		return trimesh::point(x-x0,y-y0,z-z0);
	}
	//double GetDepthValue(int x, int y) 
	//{
	//	return depthBuffer[(y-viewport[1])*viewport[2] + (x-viewport[0])];
	//}

	
	void UpdateMatrices(){
		glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport);

		//if(depthBuffer) delete depthBuffer;
		//depthBuffer = new float[viewport[2] * viewport[3]];

		//glReadPixels(viewport[0], viewport[1], viewport[2], viewport[3], GL_DEPTH_COMPONENT, GL_FLOAT, depthBuffer);
	
	}

	~OpenGLProjector(){
		//if(depthBuffer) delete depthBuffer;
	}

};

#endif // __OPENGLPROJECTOR__