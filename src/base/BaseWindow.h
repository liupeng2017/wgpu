//
// Created by ws on 2024/10/8.
//

#ifndef OPENUI_BASEWINDOW_H
#define OPENUI_BASEWINDOW_H

class BaseWindow {
public:
  BaseWindow();
  virtual ~BaseWindow();

  virtual bool needClose() = 0;
  virtual bool update() = 0;
private:

};

#endif // OPENUI_BASEWINDOW_H
