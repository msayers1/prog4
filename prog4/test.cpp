#include <vector>
#include <stdio.h>
#include "filemanagement.h"


int main(){
    std::string filename = "housever2.obj";
    ObjectFile data = readfile(filename);

    std::cout << "Vertexes:\n";
    for (const auto& entry : data.vertexList) {
        std::cout << entry.point3D.X << ',' <<   entry.point3D.Y << ',' << entry.point3D.Z << ',' << "\n";
    }

    std::cout << "Faces:\n";
    for (const auto& entry : data.faceList) {
        std::cout << "These are the vertices for a face" << "'\n";
        for (const auto& item : entry) {
                Point3D vertex = data.vertexList[item];
                std::cout << vertex.point3D.X << ',' <<   vertex.point3D.Y << ',' << vertex.point3D.Z << ',' << "\n";
        }
        std::cout << "----------------------\n";
    }
    return 0;
}
    