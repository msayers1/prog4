//
//  Sphere3D.cpp
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#include "Sphere3D.h"
#include <cmath>


using namespace std;
// using namespace graphics3d;
			
Sphere3D::Sphere3D(float radiusX, float radiusY, float radiusZ,
						unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion)
	:	GraphicObject3D(pose, motion),
		//
		radiusX_(radiusX),
		radiusY_(radiusY),
		radiusZ_(radiusZ),
		numRingsXY_(numRingsXY),
		numRingsYZ_(numRingsYZ),
		XYZ_(nullptr),
		normals_(nullptr)
{
	initMeshAndNormals_();
}

Sphere3D::Sphere3D(float radius,
						unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion)
	:	Sphere3D(radius, radius, radius, numRingsXY, numRingsYZ, pose, motion)
{}

Sphere3D::~Sphere3D()
{
	for (unsigned int i=0; i<numRingsXY_; i++)
	{
		for (unsigned int j=0; j<numRingsYZ_; j++)
		{
			delete []XYZ_[i][j];
		}
		delete []XYZ_[i];
	}
	delete []XYZ_;

	for (unsigned int j=0; j<numRingsYZ_; j++)
	{
		delete []normals_[j];
	}
	delete []normals_;

}


void Sphere3D::draw() const
{
	// std::cout << "79 Sphere3d.cpp:" << std::endl; 
	
	glPushMatrix();
	applyPose();

	setCurrentMaterial(getMaterial());

	//	draw all the rings
	for (unsigned int i=0; i<numRingsXY_; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
			for (unsigned int j=0; j<numRingsYZ_; j++)
			{
				glNormal3fv(normals_[i][j]);
				glVertex3fv(XYZ_[i][j]);
				glNormal3fv(normals_[i][j]);
				glVertex3fv(XYZ_[i+1][j]);
			}
			// close the ring
			// glNormal3fv(normals_[i][0]);
			// glVertex3fv(XYZ_[i][0]);
			// glNormal3fv(normals_[i][0]);
			// glVertex3fv(XYZ_[i+1][0]);
			
		glEnd();
	}
	

	glPopMatrix();
}

void Sphere3D::initMeshAndNormals_()
{
	//	Allocate arraus of vertex coordinates and normals
	XYZ_ = new GLfloat**[numRingsXY_+2];
	normals_ = new GLfloat**[numRingsXY_+2];
	for (unsigned int i=0; i<=numRingsXY_; i++)
	{
		XYZ_[i] = new GLfloat*[numRingsYZ_];
	    normals_[i] = new GLfloat*[numRingsYZ_];
		for (unsigned int j=0; j<numRingsYZ_; j++)
		{
			XYZ_[i][j] = new GLfloat[3];
            normals_[i][j] = new GLfloat[3];
	
		}
	}
	// normals_ = new GLfloat*[numRingsYZ_];
	// for (unsigned int j=0; j<numRingsYZ_; j++)
	// {
	// 	normals_[j] = new GLfloat[3];
	// }
    //The top point. 
    XYZ_[0][0][0] = 0;
    XYZ_[0][0][1] = 0;
    XYZ_[0][0][2] = radiusZ_;
    normals_[0][0][0] = 0;
    normals_[0][0][1] = 0;
    normals_[0][0][2] = radiusZ_;
    //	Now initialize the vertex and normal coordinates
	//	Here I work with the ring as outer loop
	for (unsigned int j=1; j<numRingsYZ_; j++)
	{
		float theta = 2*j*M_PI/numRingsYZ_;
		float ct = cosf(theta), st = sinf(theta);
		
		for (unsigned int i=1; i<=numRingsXY_; i++)
		{
            float phi = M_PI/2 - M_PI*i/numRingsXY_;
    		float cp = cosf(phi), sp = sinf(phi);

			XYZ_[i][j][0] = radiusX_*ct*cp;
			XYZ_[i][j][1] = radiusY_*ct*sp;
			XYZ_[i][j][2] = radiusZ_*st;
            //	the normals are constant along a slab
            normals_[i][j][0] = cp*ct*radiusY_;
            normals_[i][j][1] = cp*-st*radiusX_;
            normals_[i][j][2] = sp*radiusZ_;

		}
		
	}
    //The bottom point. 
    XYZ_[0][0][0] = 0;
    XYZ_[0][0][1] = 0;
    XYZ_[0][0][2] = radiusZ_;
    normals_[0][0][0] = 0;
    normals_[0][0][1] = 0;
    normals_[0][0][2] = radiusZ_;
    
}
