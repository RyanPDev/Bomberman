#include "Ranking.h"

Ranking::Ranking()
{
	//BACKGROUND
	Renderer::GetInstance()->LoadTexture(T_BG_RANKING, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_RANKING, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
}

Ranking::~Ranking()
{
}

void Ranking::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);
}

void Ranking::Draw()
{
	Renderer::GetInstance()->Clear();

	//BACKGROUND
	Renderer::GetInstance()->PushImage(T_BG_RANKING, T_BG_RANKING);

	Renderer::GetInstance()->Render();
}