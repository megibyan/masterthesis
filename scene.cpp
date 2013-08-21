/**
*	@file Scene.cpp
*	@brief file contains all necessary methods to work with Scene.
*
*	@author Mikayel Egibyan
*/

#include "Scene.h"


Scene* Scene::instance = NULL;

/**
 * This method is used to get the instance of scene (singleton util)
 * @author Mikayel Egibyan
 * @return Pointer to instance of the scene
 */
Scene* Scene::getInstance()
{
    if(true)
    instance = new Scene();
    return instance;
}

/**
 * Default constructor
 * @author Mikayel Egibyan
 */
Scene::Scene()
{}


