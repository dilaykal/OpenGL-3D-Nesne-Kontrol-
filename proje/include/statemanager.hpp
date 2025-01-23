#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include <string>
#include <glm/glm.hpp>

void saveObjectStates(const std::string& filename, 
                     const int* shapes, 
                     const float* angles, 
                     const float* scales,
                     const glm::vec3* positions,
                     const int* textures,
                     int numObjects);

void loadObjectStates(const std::string& filename, 
                     int* shapes, 
                     float* angles, 
                     float* scales,
                     glm::vec3* positions,
                     int* textures,
                     int numObjects);

#endif