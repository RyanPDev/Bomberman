#include "Scene.h"

Scene::~Scene()
{
	renderer->DestroyTextures();
	for (std::vector<Player*>::iterator i = _players.begin(); i != _players.end(); ++i) {
		delete* i;
	}
	_players.clear();
}