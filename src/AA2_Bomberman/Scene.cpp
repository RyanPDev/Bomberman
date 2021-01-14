#include "Scene.h"

Scene::~Scene()
{
	Renderer::GetInstance()->DestroyTextures();
	for (std::vector<Player*>::iterator i = _players.begin(); i != _players.end(); ++i) {
		delete* i;
	}
	_players.clear();
	playerTexture.clear();
	hpTexture.clear();
}