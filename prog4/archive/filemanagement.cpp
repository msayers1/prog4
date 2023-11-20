// Michael Sayers created. 


#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <map>
#include <string>
#include "filemanagement.h"
// using namespace graphics3d;
// inline std::map<std::string, MaterialData> processMaterialDataFile(std::string filename);

inline float returnValue(std::ifstream& inputFile, std::string& line){
    std::getline(inputFile, line);
    std::istringstream iss(line);
    float value;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ') >>  value;
    return value;
}

inline std::string returnString(std::ifstream& inputFile, std::string& line){
    std::getline(inputFile, line);
    std::istringstream iss(line);
    std::string value;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ') >>  value;
    return value;
}

inline RGB returnRGB(std::ifstream& inputFile, std::string& line){
    std::getline(inputFile, line);
    std::istringstream iss(line);
    float R,G,B;
    iss.ignore(std::numeric_limits<std::streamsize>::max(), ' ') >>  R;
    iss >> G;
    iss >> B;
    RGB value = {R,G,B};
    return value;
}

inline  void reportError(std::string message){
    std::cerr << "Error at line " << __LINE__ << " in file " << __FILE__ << ":" << message << std::endl;
    exit(1);
}
inline ObjectFile readFile(std::string filename, std::string directory) {
    std::string filenameWithDirectory = directory + filename;
    //Open the file. 
    std::ifstream inputFile(filenameWithDirectory);
    std::vector<Point3D> coords;
    std::vector<FaceIDs> faceList;
    std::vector<std::pair<float,float>> textureCoords;
    std::vector<Point3D> normalCoords;
    std::map<std::string, MaterialData> mtlData;
    std::vector<GroupData> groupList;
    
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        exit(1);
    }

    std::string line;
    std::string word;
    int vertexID, textureID,normalID;
    while (std::getline(inputFile, line)) {
        //Check if the line is a comment or whitespace. 
        if (line.empty() || line[0] == '#') {
            continue;
        }

        //Separate the line by whitespace
        std::istringstream iss(line);

        if (!(iss >> word)) {
            // Empty line, move to the next line. 
            continue;
        }
        //Slot it in the vector as a face or vertex by the v or f
        FaceIDs face;
        std::pair<float,float> textureCoord;
        float x, y, z;
        // std::cout << "Word at line beginning:" << word << " | " << ("vt" == word) << std::endl;
        if (word == "f") {
                face.clear();
                //length of word
                while(iss >> word){
                    size_t pos = 0;
                    std::string token = word;                   
                    pos = word.find("/");
                    if(pos != std::string::npos){
                        // std::cout <<  word << " | " << pos << " | " <<  word.substr(0, pos) << " | ";
                        if(0 != pos){
                            vertexID = std::stoi(word.substr(0, pos));
                        } else{
                            vertexID = -1;
                        }

                        token.erase(0, pos + 1);
                        pos = token.find("/");
                        // std::cout <<  pos << " | " << token.substr(0, pos) << " | ";
                        if(0 != pos){
                        textureID = std::stoi(token.substr(0, pos));
                        } else{
                            textureID = -1;
                        }
                        token.erase(0, pos + 1);
                        // std::cout <<  pos << " | " << token << "\n";
                        if(!token.empty()){
                            normalID = std::stoi(token);
                        } else{
                            normalID = -1;
                        }

                        face.vertexList.push_back(vertexID);
                        face.textureList.push_back(textureID);
                        face.normalList.push_back(normalID);
                    }
                }
                // add the face to the list of faces. 
                faceList.push_back(face);
        } else if (word == "v") {
                // while(iss >> word) {
                //     std::cout << word << " | ";
                // }
                // std::cout << "\n";
                iss >> word;
                x = std::stof(word);
                iss >> word;
                y = std::stof(word);
                iss >> word;    
                z = std::stof(word);
                Point3D coord = {x,y,z};
                coords.push_back(coord);
        } else if (word == "vt") {
                iss >> word;
                textureCoord.first = stof(word);
                iss >> word;
                textureCoord.second = stof(word);
                textureCoords.push_back(textureCoord);
        } else if (word == "vn") {
                iss >> word;
                x = std::stof(word);
                iss >> word;
                y = std::stof(word);
                iss >> word;    
                z = std::stof(word);
                Point3D coord = {x,y,z};
                normalCoords.push_back(coord);
        } else if (word == "mtllib") {
                iss >> word;
                std::string mtlFilename = directory + word;
                mtlData = processMaterialDataFile(mtlFilename);
                // std::cout << mtlData.size() << std::endl;
        } else if (word == "g") {
                iss >> word;
                std::string group_name = word;
                std::string group_material = returnString(inputFile, line);
                int faceIndex = faceList.size();
                if(!groupList.empty()){
                    groupList.back().FaceIndexEnd = faceIndex;
                }
                groupList.push_back({group_name, group_material, faceIndex, -1});
        } else {
            continue;
        }
    }
    if(!groupList.empty()){
        groupList.back().FaceIndexEnd = faceList.size();
    }
    inputFile.close();
    ObjectFile data = {coords, faceList, textureCoords, normalCoords, mtlData, groupList};
    return data;

}

inline std::map<std::string, MaterialData> processMaterialDataFile(std::string filename){
    // std::cout << "here" << std::endl;
            
    //Open the file. 
    std::ifstream inputFile(filename);
    
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        exit(1);
    }
    std::map<std::string,MaterialData> allMats;
    std::string line;
    std::string word;
    std::string name, map_Kd;
	float Ns, Ni, d, illum;
	RGB Ka, Kd, Ks, Ke;
    while (std::getline(inputFile, line)) {
        //Check if the line is a comment or whitespace. 
        if (line.empty() || line[0] == '#') {
            continue;
        }
        //Separate the line by whitespace
        std::istringstream iss(line);

        if (!(iss >> word)) {
            // Empty line, move to the next line. 
            continue;
        }
        if (word == "newmtl") {
            iss >> word;
            name = word;

            try{
                // std::cout << "try" << std::endl;
                Ns = returnValue(inputFile, line); 
                Ka = returnRGB(inputFile, line);
                Kd = returnRGB(inputFile, line);
                Ks = returnRGB(inputFile, line);
                Ke = returnRGB(inputFile, line);
                Ni = returnValue(inputFile, line); 
                d = returnValue(inputFile, line); 
                illum = returnValue(inputFile, line); 
                if (std::getline(inputFile, line)) {
                    iss >> word;
                    map_Kd = word;
                }
                // std::cout << "Here" << name << " | " <<  Ns << " | " <<  Ka.rgb.R << " | " << Ka.rgb.G << " | " << Ka.rgb.B << " | " 
				//   <<  Kd.rgb.R << " | " << Kd.rgb.G << " | " << Kd.rgb.B << " | " <<  Ks.rgb.R << " | " << 
				//   Ks.rgb.G << " | " << Ks.rgb.B << " | " <<  Ke.rgb.R << " | " << Ke.rgb.G << " | " << 
				//   Ke.rgb.B << " | " <<  Ni << " | " <<  d << " | " <<  illum << " | " <<  map_Kd << std::endl;
                MaterialData mat = MaterialData(name, map_Kd, Ns, Ni, d, illum, Ka, Kd, Ks, Ke);
                // mat.print();
                allMats.insert(std::make_pair(name, mat));
            }   catch (const std::exception& e) {
                // std::cout << "here" << std::endl;
                std::string message = "Problem reading material file:" + std::string(e.what());
                reportError(message);
                // // Catch and handle the exception
                // std::cerr << "Exception caught: " << e.what() << std::endl;
            }

        }
    
    }
    // std::cout << allMats.size() << std::endl;
            
    return allMats;
}

GLuint LoadTexture( const char * filename )
{
  GLuint texture;
  int width, height;
  unsigned char * data;

  FILE * file;
  file = fopen( filename, "rb" );

  if ( file == NULL ) return 0;
  width = 1024;
  height = 1024;
  data = (unsigned char *)malloc( width * height * 3 );
  //int size = fseek(file,);
  fread( data, width * height * 3, 1, file );
  fclose( file );

  for(int i = 0; i < width * height ; ++i)
  {
    int index = i*3;
    unsigned char B,R;
    B = data[index];
    R = data[index+2];

    data[index] = R;
    data[index+2] = B;
  }

  glGenTextures( 1, &texture );
  glBindTexture( GL_TEXTURE_2D, texture );
  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_DECAL); // Overwrites object color data
  // glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_MODULATE); // Modulates object color data
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );

  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_BORDER);
//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_CLAMP_TO_BORDER);
//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT );
//   glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,GL_REPEAT );
  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height,GL_RGB, GL_UNSIGNED_BYTE, data );
  free( data );

  return texture;
}
