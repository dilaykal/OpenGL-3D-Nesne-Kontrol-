#include "statemanager.hpp"
#include <fstream>
#include <iostream>
#include <cstring>  
#include <glm/vec3.hpp> 

void saveObjectStates(const std::string& filename, 
                     const int* shapes, 
                     const float* angles, 
                     const float* scales,
                     const glm::vec3* positions,
                     const int* textures,
                     int numObjects) {
   
    std::ofstream file;
    file.open(filename, std::ios::out);

    if (file.is_open()) {
       
        for(int i = 0; i < numObjects; i++) {
            file << shapes[i] << " " 
                 << angles[i] << " " 
                 << scales[i] << " "
                 << positions[i].x << " " 
                 << positions[i].y << " " 
                 << positions[i].z << " "
                 << textures[i] << std::endl;
        }
        
        file.close();
       
    } 
}

void loadObjectStates(const std::string& filename, 
                     int* shapes, 
                     float* angles, 
                     float* scales,
                     glm::vec3* positions,
                     int* textures,
                     int numObjects) {
    std::ifstream file(filename);
    
    for(int i = 0; i < numObjects; i++) {
        if(file >> shapes[i] 
              >> angles[i] 
              >> scales[i] 
              >> positions[i].x 
              >> positions[i].y 
              >> positions[i].z 
              >> textures[i]) {
           
        } 
    }
    file.close();
}