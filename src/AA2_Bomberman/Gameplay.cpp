#include "Gameplay.h"

Gameplay::Gameplay()
{
	//Background
	Renderer::GetInstance()->LoadTexture(T_BG_INGAME, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}

Gameplay::~Gameplay()
{

}

void Gameplay::Update()
{

}

void Gameplay::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_INGAME, T_BG_INGAME);

	Renderer::GetInstance()->Render();
}