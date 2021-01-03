#include "Scene.h"

Scene::~Scene()
{
	Renderer::GetInstance()->DestroyTextures();
}

//void Scene::Update(InputManager* input, EDirection dir)
//{
//
//}