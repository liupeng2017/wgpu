//
// Created by ws on 2024/9/26.
//

#include "OpenApplicaiton.h"
#include <GLFW/glfw3.h>

OpenApplicaiton::OpenApplicaiton() {

}

OpenApplicaiton::OpenApplicaiton(int argc, char** argv) {
    (void)argc;
    (void)argv;
}

OpenApplicaiton::~OpenApplicaiton() {}

void OpenApplicaiton::registerWindow(BaseWindow* window) {
  m_windows.insert(window);
}

int OpenApplicaiton::exec() {
  while (true) {
    for (auto iter = m_windows.begin(); iter != m_windows.end();) {
        if((*iter)->needClose()) {
          iter = m_windows.erase(iter);
        } else {
          (*iter)->update();
          ++iter;
        }
    }
    if(m_windows.empty())
      break;
    glfwPollEvents();
  }
  glfwTerminate();
  return 0;
}

int OpenApplicaiton::exit(int code) {
  (void)code;
  return 0;
}