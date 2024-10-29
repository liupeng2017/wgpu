#include "Example.h"

namespace tvgexam {

int selfMain(Example *example, int argc, char **argv, uint32_t width = 800,
             uint32_t height = 800, uint32_t threadsCnt = 4,
             bool print = false) {
  auto engine = tvg::CanvasEngine::Sw;

  if (argc > 1) {
    if (!strcmp(argv[1], "gl"))
      engine = tvg::CanvasEngine::Gl;
    if (!strcmp(argv[1], "wg"))
      engine = tvg::CanvasEngine::Wg;
  }

  unique_ptr<Window> window;

  if (engine == tvg::CanvasEngine::Sw) {
    window =
        unique_ptr<Window>(new SwWindow(example, width, height, threadsCnt));
  } else if (engine == tvg::CanvasEngine::Gl) {
    window =
        unique_ptr<Window>(new GlWindow(example, width, height, threadsCnt));
  } else if (engine == tvg::CanvasEngine::Wg) {
    window =
        unique_ptr<Window>(new WgWindow(example, width, height, threadsCnt));
  }

  window->print = print;

  if (window->ready()) {
    window->show();
  }

  return 0;
}


float progress(uint32_t elapsed, float durationInSec, bool rewind = false)
{
  auto duration = uint32_t(durationInSec * 1000.0f); //sec -> millisec.
  if (duration == 0.0f) return 0.0f;
  auto forward = ((elapsed / duration) % 2 == 0) ? true : false;
  auto clamped = elapsed % duration;
  auto progress = ((float)clamped / (float)duration);
  if (rewind) return forward ? progress : (1 - progress);
  return progress;
}


bool verify(tvg::Result result, string failMsg)
{
  switch (result) {
  case tvg::Result::FailedAllocation: {
    cout << "FailedAllocation! " << failMsg << endl;
    return false;
  }
  case tvg::Result::InsufficientCondition: {
    cout << "InsufficientCondition! " << failMsg << endl;
    return false;
  }
  case tvg::Result::InvalidArguments: {
    cout << "InvalidArguments! " << failMsg << endl;
    return false;
  }
  case tvg::Result::MemoryCorruption: {
    cout << "MemoryCorruption! " << failMsg << endl;
    return false;
  }
  case tvg::Result::NonSupport: {
    cout << "NonSupport! " << failMsg << endl;
    return false;
  }
  case tvg::Result::Unknown: {
    cout << "Unknown! " << failMsg << endl;
    return false;
  }
  default: break;
  };
  return true;
}

}