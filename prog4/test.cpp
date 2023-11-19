#include <vector>
#include <stdio.h>
#include "filemanagement.h"


int main(){
    // std::string filename = "../houseOutofBlenderWithTexture.mtl";
    // std::vector<MaterialData> data = processMaterialDataFile(filename);
    // // std::cout << "here: " << data.size() << std::endl;
    // for(auto& entry : data){
    //     entry.print();
    // }

    std::string filename = "houseOutofBlender.obj";
    ObjectFile data = readFile(filename, "../");

    // std::cout << "Vertexes:\n";
    // for (const auto& entry : data.vertexList) {
    //     std::cout << entry.point3D.X << ',' <<   entry.point3D.Y << ',' << entry.point3D.Z << ',' << "\n";
    // }
    std::cout << "Materials: (" << data.materialVector.size() << ")\n";
    for (auto& entry : data.materialVector) {
       entry.print();
    }


    std::cout << "Faces:\n";
    for (const auto& entry : data.faceList) {
        std::cout << "These are the vertices for a face" << "'\n";
            for(int i = 0; i < entry.vertexList.size(); i++){
                if(entry.vertexList[i] != -1){
                    Point3D vertex = data.vertexList[(entry.vertexList[i]-1)];
                    std::cout << vertex.point3D.X << ',' <<   vertex.point3D.Y << ',' << vertex.point3D.Z << ',' << "\n";
                }
                if(entry.textureList[i] != -1){
                    std::pair<float,float> textureCoord = data.textureCoords[(entry.textureList[i]-1)];
                    std::cout <<  "    " <<   textureCoord.first << ',' <<   textureCoord.second <<  "\n";
                }
                if(entry.normalList[i] != -1){
                    Point3D normal = data.normalCoords[(entry.normalList[i]-1)];
                    std::cout <<  "    " << "    " << normal.point3D.X << ',' <<   normal.point3D.Y << ',' << normal.point3D.Z << ',' << "\n";
                }
            }
        std::cout << "----------------------\n";
    }
    return 0;
}
    