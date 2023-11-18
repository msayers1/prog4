#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include "common.h"



ObjectFile readFile(std::string filename) {
    //Open the file. 
    std::ifstream inputFile(filename);
    std::vector<Point3D> coords;
    std::vector<std::vector<int>> faceList;
    // std::vector<Point3D> textureCoords;
    // std::vector<Point3D> normalCoords;
    
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open file." << std::endl;
        exit(1);
    }

    std::string line;
    std::string word;
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
        std::vector<int> face;
        int word_length;
        float x, y, z;
        char firstLetter = std::tolower(word[0]);
        if (std::isalpha(firstLetter)) {
            switch(firstLetter) {
                case 'f':
                    face.clear();
                    //length of word
                    while(iss >> word){
                    //Push each index of  the vertex on the face. 
                        face.push_back(stol(word));                        
                    }
                    // add the face to the list of faces. 
                    faceList.push_back(face);
                    break;
                case 'v':
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
                    Point3D coord = {{x,y,z}};
                    coords.push_back(coord);
                    break;
            }
        }
    }

    inputFile.close();
    ObjectFile data = {coords, faceList, {}, {}};
    return data;

}