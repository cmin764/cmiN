#include <iostream>
#include <algorithm>

#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"


using namespace std;


int main()
{
    ModelAgenda modelAgenda("test");
    ViewAgenda viewAgenda(modelAgenda);
    ControllerAgenda controllerAgenda(modelAgenda, viewAgenda);
    controllerAgenda.loop();
    return 0;
}
