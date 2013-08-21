#ifndef SCENE_H
#define SCENE_H

#include "Label.h"

class Scene
{
public:
    void render();
    static Scene * getInstance();

private:
    Scene();
    static Scene * instance;


};

#endif // SCENE_H
