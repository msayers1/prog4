#include <vector>
#include <stdio.h>
#include "filemanagement.h"


int main(){
    // std::string filename = "../houseOutofBlenderWithTexture.mtl";
    // std::map<std::string, MaterialData> data = processMaterialDataFile(filename);
    // // std::cout << "here: " << data.size() << std::endl;
    // for(auto& entry : data){
    //     entry.print();
    // }
    std::string filename = "houseOutofBlender.obj";
    // std::string filename = "houseOutofBlenderWithTexture.obj";
    ObjectFile data = readFile(filename, "../");

    // std::cout << "Vertexes:\n";
    // for (const auto& entry : data.vertexList) {
    //     std::cout << entry.point3D.X << ',' <<   entry.point3D.Y << ',' << entry.point3D.Z << ',' << "\n";
    // }
    // std::cout << "Materials: (" << data.materialMap.size() << ")\n";
    for (auto& pair : data.materialMap) {
       MaterialData& entry = pair.second;
       entry.print();
    }


    // std::cout << "Faces:\n";
    // for (const auto& entry : data.faceList) {
    //     // std::cout << "These are the vertices for a face" << "'\n";
    //         for(int i = 0; i < entry.vertexList.size(); i++){
    //             if(entry.vertexList[i] != -1){
    //                 Point3D vertex = data.vertexList[(entry.vertexList[i]-1)];
    //                 // std::cout << vertex.point3D.X << ',' <<   vertex.point3D.Y << ',' << vertex.point3D.Z << ',' << "\n";
    //             }
    //             if(entry.textureList[i] != -1){
    //                 std::pair<float,float> textureCoord = data.textureCoords[(entry.textureList[i]-1)];
    //                 // std::cout <<  "    " <<   textureCoord.first << ',' <<   textureCoord.second <<  "\n";
    //             }
    //             if(entry.normalList[i] != -1){
    //                 Point3D normal = data.normalCoords[(entry.normalList[i]-1)];
    //                 // std::cout <<  "    " << "    " << normal.point3D.X << ',' <<   normal.point3D.Y << ',' << normal.point3D.Z << ',' << "\n";
    //             }
    //         }
    //     // std::cout << "----------------------\n";
    // }
    std::string message;
    FaceIDs face;
    FaceLiteral faceLiteral;
    std::vector<FaceLiteral> faceList;
    for (const auto& entry : data.groupList) {
        // std::cout << "g " <<   entry.name << "\n";
        // std::cout << "usemtl " <<   entry.material << "\n";
        for(int i = entry.FaceIndexStart; i < entry.FaceIndexEnd; i++){
            face = data.faceList[i];
            message += "f \n";
            // std::cout << "f ";
            for(int j = 0; j < face.vertexList.size(); j++){
                // std::cout <<  face.vertexList[j] << "/" << face.textureList[j] << "/" <<  face.normalList[j] << " ";
                if(face.vertexList[j] != -1){
                    Point3D vertex = data.vertexList[(face.vertexList[j]-1)];
                    faceLiteral.vertexList.push_back(vertex);
                    message += "v " +  std::to_string(vertex.point3D.X) + ' ' +   std::to_string(vertex.point3D.Y) + ' ' + std::to_string(vertex.point3D.Z) + "\n";
                }
                if(face.textureList[j] != -1){
                    std::pair<float,float> textureCoord = data.textureCoords[(face.textureList[j]-1)];
                    faceLiteral.textureList.push_back(textureCoord);
                    // message += "vt "  + std::to_string(textureCoord.first) + ' ' + std::to_string(textureCoord.second) + "\n";
                }
                if(face.normalList[j] != -1){
                    Point3D normal = data.normalCoords[(face.normalList[j]-1)];
                    faceLiteral.normalList.push_back(normal);
				    // message += "vn "  + std::to_string(normal.point3D.X) + ' ' + std::to_string(normal.point3D.Y) +  std::to_string(normal.point3D.Z) + "\n";
                }
                faceList.push_back(faceLiteral);
            }
            std::cout << "\n";
            message += "\n";
        }
    std::cout << "Faces for this group: \n" << message;
    }


    return 0;
}
    