#include "Scene.h"

Scene::~Scene()
{
	renderer->DestroyTextures();
	_players.clear();
	delete p;
}