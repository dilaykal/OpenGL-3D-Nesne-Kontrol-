#define GLM_FORCE_CTOR_INIT
#define GLFW_INCLUDE_NONE
#define STB_IMAGE_IMPLEMENTATION
#include "glwindow.hpp"
#include "shaderprogram.hpp"
#include "vertexarrayobject.hpp"
#include "texturemanager.hpp"
#include "shapecreator.hpp"
#include "statemanager.hpp"
#include <cstdlib> // Rastgele sayı üretmek için
#include <ctime>   // Zaman için (std::srand)
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

using namespace std;

void printMatrix(const glm::mat4& mtx)
{
    cout << setw(10) << mtx[0][0] << setw(10) << mtx[1][0] << setw(10) << mtx[2][0] << setw(10) << mtx[3][0] << endl;
    cout << setw(10) << mtx[0][1] << setw(10) << mtx[1][1] << setw(10) << mtx[2][1] << setw(10) << mtx[3][1] << endl;
    cout << setw(10) << mtx[0][2] << setw(10) << mtx[1][2] << setw(10) << mtx[2][2] << setw(10) << mtx[3][2] << endl;
    cout << setw(10) << mtx[0][3] << setw(10) << mtx[1][3] << setw(10) << mtx[2][3] << setw(10) << mtx[3][3] << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
}

int main(int arc, char** argv)
{

    
    const std::string STATE_FILE = "object_states.txt";
    
    std::srand(static_cast<unsigned int>(std::time(0)));

    const int NUM_OBJECTS = 9; 
    int activeObject = 4;      
    int currentShapes[NUM_OBJECTS] = {0}; 
    float angles[NUM_OBJECTS] = {0.0f};    
    float scales[NUM_OBJECTS] = {1.0f};    
    glm::vec3 positions[NUM_OBJECTS];     
    int currentTextures[NUM_OBJECTS]; 

    
    // Pozisyonları ayarla
    const float spacing = 2.5f; 
    for(int i = 0; i < NUM_OBJECTS; i++) {
        int row = i / 3;   
        int col = i % 3;    
        positions[i] = glm::vec3(
            (col - 1) * spacing,         
            (1 - row) * spacing,           
            -4.0f                         
        );
        currentShapes[i] = 0;  
        scales[i] = 1.0f;      
        angles[i] = 0.0f;    
        // Rastgele texture seçimi
        currentTextures[i] = std::rand() % 4; 

    }

    if (std::ifstream(STATE_FILE)) {
        // Dosya varsa yükle
        loadObjectStates(STATE_FILE, currentShapes, angles, scales, positions, currentTextures, NUM_OBJECTS);
    } 
    // Texture yolları
    const string textures[] = {
        "../images/mosaic.jpg",
        "../images/brick_wall.jpg",
        "../images/container-crate.jpg",
        "../images/stone_floor.jpg"
    };
    

    // OpenGL penceresi oluştur
    graf::GLWindow glwindow;
    glwindow.create(800, 800);
    // Sticky keys modunu etkinleştir
    glfwSetInputMode(glwindow.getWindow(), GLFW_STICKY_KEYS, GLFW_TRUE);

    // Shape'leri oluştur
    graf::ShapeCreator shapeCreator;
    graf::VertexArrayObject* cube = shapeCreator.create(graf::ShapeTypes::Cube);
    graf::VertexArrayObject* pyramid = shapeCreator.create(graf::ShapeTypes::Pyramid);
    graf::VertexArrayObject* circle = shapeCreator.create(graf::ShapeTypes::Circle);
    graf::VertexArrayObject* square = shapeCreator.create(graf::ShapeTypes::Square);
    graf::VertexArrayObject* truncatedPyramid = shapeCreator.create(graf::ShapeTypes::TruncatedPyramid);


    // Shader programını hazırla
    graf::ShaderProgram program;
    program.create();

    program.attachShader("../shaders/vertex.glsl", GL_VERTEX_SHADER);
    program.attachShader("../shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    program.link();
   
    program.addUniform("uWorldTransform");

    
    // Texture yükleme
    for(int i = 0; i < 4; i++) {
        graf::TextureManager::addTextureFromFile(textures[i]);
    }

    glm::mat4 mtxProj = glm::perspective(glm::radians(90.0f), 1.0f, 1.0f, 100.0f);
    glm::mat4 mtxWorld(1);


    glwindow.setKeyboardFunction([&](int key, int scancode, int action)
    {

        if (action == GLFW_PRESS) {
            int numKey = key - GLFW_KEY_0;
            if (numKey >= 0 && numKey < NUM_OBJECTS) {
                activeObject = numKey;
            }
            
        }
 
        if (action == GLFW_PRESS || action == GLFW_REPEAT) {
            if (key == GLFW_KEY_RIGHT) {
                positions[activeObject].x += 0.1f;
            }
            else if (key == GLFW_KEY_LEFT) {
                positions[activeObject].x -= 0.1f;
            }
            else if (key == GLFW_KEY_UP) {
                positions[activeObject].y += 0.1f;
            }
            else if (key == GLFW_KEY_DOWN) {
                positions[activeObject].y -= 0.1f;
            }
            else if (key == GLFW_KEY_SPACE) { 
                currentShapes[activeObject] = (currentShapes[activeObject] + 1) % 5;
            
            }
        }
    });
    glwindow.setRenderFunction([&]()
    {
        glClearColor(0.0f, 0.4f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        program.use();
        
        // Tüm objeleri çiz
        for(int i = 0; i < NUM_OBJECTS; i++) {
            
            // Her objeye bir kez rastgele texture atanır
            graf::TextureManager::activateTexture(textures[currentTextures[i]]);

            glm::mat4 mtxTranslate = glm::translate(glm::mat4(1), positions[i]);
            glm::mat4 mtxRotation = glm::rotate(glm::mat4(1), glm::radians(angles[i]), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 mtxScale = glm::scale(glm::mat4(1), glm::vec3(scales[i], scales[i], 1.0f));
            
            mtxWorld = mtxTranslate * mtxRotation * mtxScale;
            program.setMat4("uWorldTransform", mtxProj * mtxWorld);
            
            switch(currentShapes[i]) {
                case 0:
                    cube->bind();
                    cube->draw();
                    cube->unbind();
                    break;
                case 1:
                    pyramid->bind();
                    pyramid->draw();
                    pyramid->unbind();

                    break;
                case 2:
                    circle->bind();
                    circle->draw();
                    circle->unbind();
                    
                    break;
                case 3:
                    square->bind();
                    square->draw();
                    square->unbind();

                    break;
                case 4:
                    truncatedPyramid->bind();
                    truncatedPyramid->draw();
                    truncatedPyramid->unbind();
                    break;
            }
        }
        // Aktif objenin sürekli dönmesi
        if (activeObject >= 0 && activeObject < NUM_OBJECTS) {
            angles[activeObject] += 0.01f;
        }
         // ESC tuşuna basıldığında veya pencere kapatılmak istendiğinde
        if (glfwGetKey(glwindow.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS || 
            glfwWindowShouldClose(glwindow.getWindow())) {
            
            saveObjectStates(STATE_FILE, currentShapes, angles, scales, positions, currentTextures, NUM_OBJECTS);

            glfwSetWindowShouldClose(glwindow.getWindow(), GLFW_TRUE);
        }
    });

    glwindow.render();
   
    exit(EXIT_SUCCESS);
}
