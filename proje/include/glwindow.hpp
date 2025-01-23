#ifndef GLWindow_hpp
#define GLWindow_hpp

#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include "functiontypes.hpp"

namespace graf
{
    class GLWindow
    {

        void setCloseFunction(std::function<void()> closeFunc) {
            m_closeFunc = closeFunc;
            glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
                GLWindow* glWindow = static_cast<GLWindow*>(glfwGetWindowUserPointer(window));
                if(glWindow && glWindow->m_closeFunc) {
                    glWindow->m_closeFunc();
                }
            });
        }
        public:
            GLFWwindow* getWindow() const { return m_window; }
            int create(unsigned int width,unsigned int height);
            void render();
            void setRenderFunction (RenderFunction function);
            void setKeyboardFunction(KeyboardFunction keyboardFunction);
        private:
            static void statickeyboardFunction(GLFWwindow* window, int key, int scancode, int action, int mods);
            GLFWwindow*         m_window;

            RenderFunction      m_renderFunction;
            KeyboardFunction    m_keyboardFunction;
            std::function<void()> m_closeFunc;

    };
}


#endif