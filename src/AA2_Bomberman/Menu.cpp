#include "Menu.h"

Menu::Menu()
{
	//Background
	Renderer::GetInstance()->LoadTexture(T_BG_MENU, "../../res/img/bg.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_MENU, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}

Menu::~Menu()
{

}

void Menu::Update(InputManager input)
{
	input.GetInput().GetScreenSize();
}

void Menu::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_MENU, T_BG_MENU);

	Renderer::GetInstance()->Render();
}