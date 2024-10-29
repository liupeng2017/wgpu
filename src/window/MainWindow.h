//
// Created by ws on 2024/10/8.
//

#ifndef OPENUI_MAINWINDOW_H
#define OPENUI_MAINWINDOW_H

#include "BaseWindow.h"

class GLFWmonitor;
class GLFWwindow;
class MainWindow : public BaseWindow {
public:
  MainWindow();
  ~MainWindow();

  GLFWwindow* getWindow() const;

  void showFPS(bool flag);
  void showMaximize();
  void showMinimize();

  // A function called when the window is resized.
  void onResize();

  // Mouse events
  void onMouseMove(double xpos, double ypos);
  void onMouseButton(int button, int action, int mods);
  void onScroll(double xoffset, double yoffset);

private:
  void drawFPS();

private:
  bool needClose() override;
  bool update() override;

private:
  int m_width = 1280;
  int m_height = 720;
  bool m_fullScreen = false;
  bool m_isResizable = true;
  bool m_limitFrameRate = true;
  bool m_showFPS = false;

  const char* m_title = "OpenUI";
  GLFWmonitor* m_monitor = nullptr;
  GLFWwindow* m_window = nullptr;
};

#endif // OPENUI_MAINWINDOW_H
