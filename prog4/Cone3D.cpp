//
//  Cone3D.cpp
//

#include "Cone3D.h"
#include <cmath>


using namespace std;
// using namespace graphics3d;
			
Cone3D::Cone3D(float radiusX, float radiusY, float height,
						unsigned int numRings, unsigned int numCirclePts,
						const Pose& pose, const Motion& motion)
	:	GraphicObject3D(pose, motion),
		//
		radiusX_(radiusX),
		radiusY_(radiusY),
		height_(height),
		numRings_(numRings),
		numCirclePts_(numCirclePts),
		XYZ_(nullptr),
		normals_(nullptr),
		topNormal_(nullptr),
		bottomNormal_(nullptr)
{
	initMeshAndNormals_();
}

Cone3D::Cone3D(float radius,
						unsigned int numRingsXY, unsigned int numRingsYZ,
						const Pose& pose, const Motion& motion)
	:	Cone3D(radius, radius, radius, numRingsXY, numRingsYZ, pose, motion)
{}

Cone3D::~Cone3D()
{
	for (unsigned int i=0; i<numRings_; i++)
	{
		for (unsigned int j=0; j<numCirclePts_; j++)
		{
			delete []XYZ_[i][j];
		}
		delete []XYZ_[i];
	}
	delete []XYZ_;

	for (unsigned int j=0; j<numCirclePts_; j++)
	{
		delete []normals_[j];
	}
	delete []normals_;

}


void Cone3D::draw() const
{
// std::cout << "79 Cylinder3d.cpp:" << std::endl; 
	
	glPushMatrix();
	applyPose();

	setCurrentMaterial(getMaterial());

		//	top
		//-----------------------------------
		glBegin(GL_TRIANGLE_FAN);
			//	center
			glNormal3fv(topNormal_);
			glVertex3f(0.f, 0.f, height_);

			glNormal3fv(topNormal_);
			glVertex3fv(XYZ_[numRings_][0]);

			//	For whatever reason, fans list vertices in clockwise order [???]
			for (unsigned int j=0, jp=numCirclePts_-1; j<numCirclePts_; j++, jp--)
			{
				glNormal3fv(topNormal_);
				glVertex3fv(XYZ_[numRings_][jp]);
			}
		glEnd();

	//	draw all the rings
	for (unsigned int i=1; i<numRings_; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
			for (unsigned int j=0; j<numCirclePts_; j++)
			{
				glNormal3fv(normals_[j]);
				glVertex3fv(XYZ_[i][j]);
				glNormal3fv(normals_[j]);
				glVertex3fv(XYZ_[i+1][j]);
			}
			// close the ring
			glNormal3fv(normals_[0]);
			glVertex3fv(XYZ_[i][0]);
			glNormal3fv(normals_[0]);
			glVertex3fv(XYZ_[i+1][0]);
			
		glEnd();
	}
	
	//	If the cylinder is closed, we have to draw the top and bottom sides
	if (isClosed_)
	{
		
		
		//	bottom
		//-----------------------------------
		glBegin(GL_TRIANGLE_FAN);
			//	center
			glNormal3fv(bottomNormal_);
			glVertex3f(0.f, 0.f, 0.f);
			for (unsigned int j=0; j<numCirclePts_; j++)
			{
				glNormal3fv(bottomNormal_);
				glVertex3fv(XYZ_[0][j]);
			}
			glNormal3fv(bottomNormal_);
			glVertex3fv(XYZ_[0][0]);
		glEnd();
	}

	glPopMatrix();
}

void Cone3D::initMeshAndNormals_()
{
	//	Allocate arraus of vertex coordinates and normals
	XYZ_ = new GLfloat**[numRings_+1];
	for (unsigned int i=0; i<=numRings_; i++)
	{
		XYZ_[i] = new GLfloat*[numCirclePts_];
		for (unsigned int j=0; j<numCirclePts_; j++)
		{
			XYZ_[i][j] = new GLfloat[3];
		}
	}
	normals_ = new GLfloat*[numCirclePts_];
	for (unsigned int j=0; j<numCirclePts_; j++)
	{
		normals_[j] = new GLfloat[3];
	}
	
	//	Now initialize the vertex and normal coordinates
	//	Here I work with the ring as outer loop
	for (unsigned int j=0; j<numCirclePts_; j++)
	{
		float theta = 2*j*M_PI/numCirclePts_;
		float ct = cosf(theta), st = sinf(theta);

		XYZ_[0][0][0] = 0;
		XYZ_[0][0][1] = 0;
		XYZ_[0][0][2] = height_;


		for (unsigned int i=1; i<=numRings_; i++)
		{
			XYZ_[i][j][0] = radiusX_*ct*i/numRings_;
			XYZ_[i][j][1] = radiusY_*st*i/numRings_;
			XYZ_[i][j][2] = height_*i/numRings_;
		}
		
		//	the normals are constant along a slab
		normals_[j][0] = ct*radiusY_;
		normals_[j][1] = -st*radiusX_;
		normals_[j][2] = 0.f;
	}
	
	//	And take care of top and bottom sides if the cylinder is closed
	if (isClosed_)
	{
		bottomNormal_ = new GLfloat[3];
		bottomNormal_[2] = -1.f;
	}

}
