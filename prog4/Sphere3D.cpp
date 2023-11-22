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

	glBegin(GL_TRIANGLE_STRIP);
		for (unsigned int j=0; j<numRingsYZ_; j++)
		{
			// std::cout << 1  << " | " << j  << " | x:" << XYZ_[1][j][0]  << " | y:" << XYZ_[1][j][0]  <<" | y:" << XYZ_[1][] << " | cp:" << cp << " | sa: " << sa <<  " | z:" << radiusZ_*sp << std::endl;
			glNormal3fv(normals_[0][0]);
			glVertex3fv(XYZ_[0][0]);
			glNormal3fv(normals_[1][j]);
			glVertex3fv(XYZ_[1][j]);
		}

	glEnd();
	//	draw all the rings
	for (unsigned int i=1; i<=(numRingsXY_); i++)
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
			glNormal3fv(normals_[i][0]);
			glVertex3fv(XYZ_[i][0]);
			glNormal3fv(normals_[i+1][0]);
			glVertex3fv(XYZ_[i+1][0]);
			
		glEnd();
	}
	
	glBegin(GL_TRIANGLE_STRIP);
		for (unsigned int j=0; j<numRingsYZ_; j++)
		{
			glNormal3fv(normals_[(numRingsXY_)][j]);
			glVertex3fv(XYZ_[(numRingsXY_)][j]);
			glNormal3fv(normals_[numRingsXY_+1][0]);
			glVertex3fv(XYZ_[numRingsXY_+1][0]);

		}
	glEnd();


	glPopMatrix();
}

void Sphere3D::initMeshAndNormals_()
{
	//	Allocate arraus of vertex coordinates and normals
	XYZ_ = new GLfloat**[numRingsXY_+2];
	normals_ = new GLfloat**[numRingsXY_+2];
	for (unsigned int i=0; i<(numRingsXY_+2); i++)
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
	for (unsigned int j=0; j<(numRingsYZ_); j++)
	{
		float azimuthAngle = 2*j*M_PI/numRingsYZ_;
		float ca = cosf(azimuthAngle), sa = sinf(azimuthAngle);
		
		for (unsigned int i=1; i<=(numRingsXY_+1); i++)
		{
			// I increased the rings by 2 to accomodate the north
            float polorAngle = M_PI/2 - M_PI*i/(numRingsXY_+2);
    		float cp = cosf(polorAngle), sp = sinf(polorAngle);
			XYZ_[i][j][0] = radiusX_*cp*ca;
			XYZ_[i][j][1] = radiusY_*cp*sa;
			XYZ_[i][j][2] = radiusZ_*sp;
            //	the normals are constant along a slab
            normals_[i][j][0] = cp*ca*radiusX_;
            normals_[i][j][1] = cp*-sa*radiusY_;
            normals_[i][j][2] = sp*radiusZ_;

		}
	
	}
	
	XYZ_[numRingsXY_+1][0][0] = 0;
    XYZ_[numRingsXY_+1][0][1] = 0;
    XYZ_[numRingsXY_+1][0][2] = -radiusZ_;
    normals_[numRingsXY_+1][0][0] = 0;
    normals_[numRingsXY_+1][0][1] = 0;
    normals_[numRingsXY_+1][0][2] = -radiusZ_;
    
}
