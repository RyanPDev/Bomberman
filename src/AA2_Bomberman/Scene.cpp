#include "Scene.h"

Scene::~Scene()
{
	Renderer::GetInstance()->DestroyTextures();
}