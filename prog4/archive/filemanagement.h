// Michael Sayers created. 

#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <map>
#include <string>
#include "common.h"
namespace graphics3d
{
    // struct MaterialData;
    // union RGB;
    // struct ObjectFile;

    // inline std::map<std::string, MaterialData> processMaterialDataFile(std::string filename);

    inline float returnValue(std::ifstream& inputFile, std::string& line);

    inline std::string returnString(std::ifstream& inputFile, std::string& line);

    inline RGB returnRGB(std::ifstream& inputFile, std::string& line);

    inline  void reportError(std::string message);

    // inline ObjectFile readFile(std::string filename, std::string directory = "./");

    inline ObjectFile readFile(std::string filename, std::string directory);


    inline std::map<std::string, MaterialData> processMaterialDataFile(std::string filename);

    GLuint LoadTexture( const char * filename );

}
#endif //	FILE_MANAGEMENT_H
