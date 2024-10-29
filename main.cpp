
#include "OpenApplicaiton.h"
#include "MainWindow.h"

#include "webgpu/webgpu.h"
#include "wgpu/wgpu.h"

#include <iostream>

int main() {
  OpenApplicaiton app;

  // Init WebGPU
  WGPUInstanceDescriptor desc;
  desc.nextInChain = NULL;
  WGPUInstance instance = wgpuCreateInstance(&desc);

  WGPUGlobalReport report;
  wgpuGenerateReport(instance, &report);

  MainWindow window;
  window.showFPS(true);
  app.registerWindow(&window);

  // WGPUSurface surface =  glfwCreateWindowWGPUSurface(instance, window.getWindow());
  //  WGPUSurface surface = glfwCreateWindowWGPUSurface(instance, m_window);
  // std::cout << "surface = " << (void*)surface;
  (void)instance;

  app.exec();
  return 0;
}