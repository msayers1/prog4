//
//  House3D.cpp
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#include <cmath>
#include <string>
#include "filemanagement.h"
#include "House3D.h"


using namespace std;
using namespace graphics3d;

			
House3D::House3D(string filename, float width, float height,
						const Pose& pose, const Motion& motion)
	:	GraphicObject3D(pose, motion),
		//
		width_(width),
		height_(height)
{
	ObjectFile mesh = readFile(filename);
	initMeshAndNormals_(mesh);
}

House3D::~House3D()
{
}


void House3D::draw() const
{
	glPushMatrix();
	applyPose();

	setCurrentMaterial(getMaterial());

	

	glPopMatrix();
}

void House3D::initMeshAndNormals_(ObjectFile mesh)
{
	Point3D vertex;
	for (const auto& entry : mesh.faceList) {
        // std::cout << "These are the vertices for a face" << "'\n";
        for (const auto& item : entry) {
                vertex = mesh.vertexList[item];
                // std::cout << vertex.point3D.X << ',' <<   vertex.point3D.Y << ',' << vertex.point3D.Z << ',' << "\n";
        }
        // std::cout << "----------------------\n";
    }
}
