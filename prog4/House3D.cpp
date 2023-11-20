//
//  House3D.cpp
//  Week 09 - 3D Objects
//
//  Created by Jean-Yves Hervé on 2023-11-07.
//

#include <string>
#include "glPlatform.h"
#include "House3D.h"
#include "filemanagement.h"

using namespace std;
// using namespace graphics3d;



			
House3D::House3D(string filename, string directory, float scaleX, float scaleY, float scaleZ,
						const Pose& pose, const Motion& motion)
	:	GraphicObject3D(pose, motion),
		//
		scaleX_(scaleX),
		scaleY_(scaleY),
		scaleZ_(scaleZ)
{
	ObjectFile mesh = readFile(filename, directory);
	initHouseMeshAndNormals_(mesh);
}

House3D::House3D(string filename, float scaleX, float scaleY, float scaleZ,
						const Pose& pose, const Motion& motion)
	:	GraphicObject3D(pose, motion),
		//
		scaleX_(scaleX),
		scaleY_(scaleY),
		scaleZ_(scaleZ)
{
	ObjectFile mesh = readFile(filename, "./");
	initHouseMeshAndNormals_(mesh);
}


House3D::~House3D()
{
}

void drawPoint(const FaceLiteral& face, int index){
	// std::cout << "46:" << face.vertexList[index].aPoint3D[0] << ',' <<   face.vertexList[index].aPoint3D[1] << ',' << face.vertexList[index].aPoint3D[2] << ',' << "\n"; 
	glVertex3fv(face.vertexList[index].aPoint3D);
	glNormal3fv(face.normalList[index].aPoint3D);
	glTexCoord2f(face.textureList[index].first, face.textureList[index].second);
}

void drawTriangles(const FaceLiteral& face, int groupSize){
	// std::cout << "53:" << groupSize << " | " << (groupSize == 4) << " | " << face.vertexList[1].aPoint3D[0] << ',' <<   face.vertexList[1].aPoint3D[1] << ',' << face.vertexList[1].aPoint3D[2] << ',' << "\n"; 
	
	if(groupSize == 4){
		glBegin(GL_QUADS);
			drawPoint(face, 0);
			drawPoint(face, 1);
			drawPoint(face, 2);
			drawPoint(face, 3);
		glEnd();

		// glBegin(GL_TRIANGLES);
		// 	drawPoint(face, 0);
		// 	drawPoint(face, 1);
		// 	drawPoint(face, 2);
		// glEnd();
		// glBegin(GL_TRIANGLES);
		// 	drawPoint(face, 2);
		// 	drawPoint(face, 3);
		// 	drawPoint(face, 0);
		// glEnd();

	// glVertex3f(0.0f, 1.0f, 0.0f);
    // glNormal3f(0.0f, 0.0f, 1.0f);
    // glTexCoord2f(0.0f, 1.0f);
	} else if (groupSize == 3){
	glBegin(GL_TRIANGLES);
			drawPoint(face, 0);
			drawPoint(face, 1);
			drawPoint(face, 2);
	glEnd();

	} else {
		//Create logic for greater than 4 vertices.
		// std::cout << "Problem at " << __LINE__ << " in " << __FILE__ << std::endl; 
	}
}

void House3D::draw() const
{
	// std::cout << __LINE__ << ":?" << std::endl; 
	
	int groupSize;
	glPushMatrix();
	applyPose();
	setCurrentMaterial(getMaterial());
	for(auto& group : groupList_) {
		setCurrentMaterial(group.material);

		for(const auto& face : group.faceList){
			groupSize = face.vertexList.size();
			drawTriangles(face, groupSize);
		}
	}
	glPopMatrix();
}

void House3D::initHouseMeshAndNormals_(ObjectFile mesh)
{
	// Version 3
	// std::string message;
    FaceIDs face;
    FaceLiteral faceLiteral;
    std::vector<FaceLiteral> faceList;
	GroupLiteral group;
	Point3D vertex, normal;
	std::pair<float,float> textureCoord;
	for (const auto& entry : mesh.groupList) {
        faceList.clear();
		group.name = entry.name;
		group.material = mesh.materialMap[entry.material];
		// if(group.material.map_Kd_ != ""){
		// 	const char* textureFilename = ("../" + group.material.map_Kd_).c_str();;
		// 	texture_= LoadTexture(textureFilename);
		// }
		// std::cout << "g " <<   entry.name << "\n";
        // std::cout << "usemtl " <<   entry.material << "\n";
        for(int i = entry.FaceIndexStart; i < entry.FaceIndexEnd; i++){
            face = mesh.faceList[i];
			faceLiteral.clear();

            // std::cout << "f ";
            for(int j = 0; j < face.vertexList.size(); j++){
                // std::cout <<  face.vertexList[j] << "/" << face.textureList[j] << "/" <<  face.normalList[j] << " ";
                if(face.vertexList[j] != -1){
					// std::cout << __LINE__ << " in " << __FILE__ << ":" << (face.vertexList[j]-1) << " | " << mesh.vertexList[(face.vertexList[j]-1)].point3D.X << " | " << mesh.vertexList[(face.vertexList[j]-1)].point3D.Y << " | " << mesh.vertexList[(face.vertexList[j]-1)].point3D.Z << std::endl; 
                    vertex = mesh.vertexList[(face.vertexList[j]-1)];
                    std::cout << __LINE__ << " in " << __FILE__ << ":" << (face.vertexList[j]-1) << " | " << vertex.point3D.X << " | " << vertex.point3D.Y << " | " << vertex.point3D.Z << std::endl; 
                    faceLiteral.vertexList.push_back(vertex);
                    // message += "v " +  std::to_string(vertex.point3D.X) + ' ' +   std::to_string(vertex.point3D.Y) + ' ' + std::to_string(vertex.point3D.Z) + "\n";
                }
                if(face.textureList[j] != -1){
                     textureCoord = mesh.textureCoords[(face.textureList[j]-1)];
                    faceLiteral.textureList.push_back(textureCoord);
                    // message += "vt "  + std::to_string(textureCoord.first) + ' ' + std::to_string(textureCoord.second) + "\n";
                }
                if(face.normalList[j] != -1){
                    normal = mesh.normalCoords[(face.normalList[j]-1)];
                    faceLiteral.normalList.push_back(normal);
				    // message += "vn "  + std::to_string(normal.point3D.X) + ' ' + std::to_string(normal.point3D.Y) +  std::to_string(normal.point3D.Z) + "\n";
                }
                
            }
			for(const auto& g : faceLiteral.vertexList){
				std::cout << __LINE__ << " in " << __FILE__ << ":" <<  " | " << g.point3D.X << " | " << g.point3D.Y << " | " << g.point3D.Z << std::endl; 
			}

			faceList.push_back(faceLiteral);
            // std::cout << "\n";
        }
		group.faceList = faceList;
		groupList_.push_back(group);
		// std::cout << "Faces for this group: \n" << message;
    }
    	
	// Version 2
	// FaceLiteral face;
	// materialData_ =  &mesh.materialMap;
	// for (const auto& entry : mesh.faceList) {
	// 	for(int i = 0; i < entry.vertexList.size(); i++){
	// 		if(entry.vertexList[i] != -1){
	// 			Point3D vertex = mesh.vertexList[(entry.vertexList[i]-1)];
	// 			face.vertexList.push_back(vertex);
	// 			// std::cout << vertex.point3D.X << ',' <<   vertex.point3D.Y << ',' << vertex.point3D.Z << ',' << "\n";
	// 		}
	// 		if(entry.textureList[i] != -1){
	// 			std::pair<float,float> textureCoord = mesh.textureCoords[(entry.textureList[i]-1)];
	// 			face.textureList.push_back(textureCoord);
	// 			// std::cout <<  "    " <<   textureCoord.first << ',' <<   textureCoord.second <<  "\n";
	// 		}
	// 		if(entry.normalList[i] != -1){
	// 			Point3D normal = mesh.normalCoords[(entry.normalList[i]-1)];
	// 			face.normalList.push_back(normal);
	// 			// std::cout <<  "    " << "    " << normal.point3D.X << ',' <<   normal.point3D.Y << ',' << normal.point3D.Z << ',' << "\n";
	// 		}
    //     }
	// 	faceList_.push_back(face);
	// }
	// Version 1
	// for (const auto& entry : mesh.faceList) {
    //     // std::cout << "These are the vertices for a face" << "'\n";
    //     for (const auto& item : entry) {
    //             vertex = mesh.vertexList[item];
	// 			face.push_back(vertex);
    //             // std::cout << vertex.point3D.X << ',' <<   vertex.point3D.Y << ',' << vertex.point3D.Z << ',' << "\n";
    //     }
    //     // std::cout << "----------------------\n";
    // }
}
