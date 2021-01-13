#include "Ranking.h"

Ranking::Ranking()
{
	//BACKGROUND
	renderer->LoadTexture(T_BG_RANKING, "../../res/img/bgGame.jpg");
	renderer->LoadRect(T_BG_RANKING, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	AudioManager::GetInstance()->StopMusic();
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
	renderer->Clear();

	//BACKGROUND
	renderer->PushImage(T_BG_RANKING, T_BG_RANKING);

	renderer->Render();
}