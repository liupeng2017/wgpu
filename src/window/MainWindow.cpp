//
// Created by ws on 2024/10/8.
//

#include "MainWindow.h"
//#include "glfw3webgpu.h"  // https://github.com/eliemichel/glfw3webgpu

// #define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>

//Vulkan
#ifdef _WIN32                        //考虑平台是Windows的情况（请自行解决其他平台上的差异）
#define VK_USE_PLATFORM_WIN32_KHR    //在包含vulkan.h前定义该宏，会一并包含vulkan_win32.h和windows.h
#define NOMINMAX                     //定义该宏可避免windows.h中的min和max两个宏与标准库中的函数名冲突
#endif
#include <vulkan/vulkan.h>

#include <iostream>
#include <format>
#include <sstream>

MainWindow::MainWindow() : BaseWindow() {
  if (!glfwInit()) {
    std::cout << std::format("[ InitializeWindow ] ERROR\nFailed to initialize GLFW!\n");
    return;
  }
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, m_isResizable);

  m_monitor = glfwGetPrimaryMonitor();
  const GLFWvidmode* pMode = glfwGetVideoMode(m_monitor);
  m_window = m_fullScreen ?
                       glfwCreateWindow(pMode->width, pMode->height, m_title, m_monitor, nullptr) :
                       glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
  if (!m_window) {
    std::cout << std::format("[ InitializeWindow ]\nFailed to create a glfw window!\n");
    glfwTerminate();
    return;
  }

  // Add window callbacks
  glfwSetWindowUserPointer(m_window, this);
//  glfwSetFramebufferSizeCallback(m_window, /* [...] */);
  glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
    auto that = reinterpret_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    if (that != nullptr) that->onMouseMove(xpos, ypos);
  });
  glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
    auto that = reinterpret_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    if (that != nullptr) that->onMouseButton(button, action, mods);
  });
  glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
    auto that = reinterpret_cast<MainWindow*>(glfwGetWindowUserPointer(window));
    if (that != nullptr) that->onScroll(xoffset, yoffset);
  });
}

MainWindow::~MainWindow() {

}

GLFWwindow* MainWindow::getWindow() const {
  return m_window;
}

void MainWindow::showFPS(bool flag) {
  m_showFPS = flag;
}

void MainWindow::showMaximize() {
  const GLFWvidmode* pMode = glfwGetVideoMode(m_monitor);
  glfwSetWindowMonitor(m_window, m_monitor, 0, 0, pMode->width, pMode->height, pMode->refreshRate);
}

void MainWindow::showMinimize() {
  const GLFWvidmode* pMode = glfwGetVideoMode(m_monitor);
  auto x = (pMode->width - m_width) / 2;
  auto y = (pMode->height - m_height) / 2;
  glfwSetWindowMonitor(m_window, nullptr, x, y, m_width, m_height, pMode->refreshRate);
}

void MainWindow::onResize() {

}


void MainWindow::onMouseMove(double xpos, double ypos) {
  (void)xpos;
  (void)ypos;
}

void MainWindow::onMouseButton(int button, int action, int /* modifiers */) {
  if (button == GLFW_MOUSE_BUTTON_LEFT) {
    switch (action) {
    case GLFW_PRESS:

      break;
    case GLFW_RELEASE:
      break;
    }
  }
}

void MainWindow::onScroll(double /* xoffset */, double /* yoffset */) {

}

bool MainWindow::needClose() {
  return glfwWindowShouldClose(m_window);
}

void MainWindow::drawFPS() {
  static double time0 = glfwGetTime();
  static double time1;
  static double dt;
  static int dframe = -1;
  static std::stringstream info;
  time1 = glfwGetTime();
  dframe++;
  if ((dt = time1 - time0) >= 1) {
    info.precision(1);
    info << m_title << "    " << std::fixed << dframe / dt << " FPS";
    glfwSetWindowTitle(m_window, info.str().c_str());
    info.str("");//别忘了在设置完窗口标题后清空所用的stringstream
    time0 = time1;
    dframe = 0;
  }
}

bool MainWindow::update() {
  if(m_showFPS)
    drawFPS();
  return true;
}