#include "Ranking.h"

Ranking::Ranking()
{
	//Background
	Renderer::GetInstance()->LoadTexture(T_BG_RANKING, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_RANKING, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}

Ranking::~Ranking()
{

}

void Ranking::Update()
{
}

void Ranking::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_RANKING, T_BG_RANKING);

	Renderer::GetInstance()->Render();
}