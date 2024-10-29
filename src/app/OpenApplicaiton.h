//
// Created by ws on 2024/9/26.
//

#ifndef OPENUI_OPENAPPLICAITON_H
#define OPENUI_OPENAPPLICAITON_H

#include "BaseWindow.h"
#include <set>

class OpenApplicaiton {

public:
    OpenApplicaiton();
    OpenApplicaiton(int argc, char** argv);
    ~OpenApplicaiton();

    void registerWindow(BaseWindow* window);
public:
    int exec();
    int exit(int code);

  private:
    std::set<BaseWindow*> m_windows;
};

#endif // OPENUI_OPENAPPLICAITON_H
