#include "Ranking.h"

Ranking::Ranking()
{
	//BACKGROUND
	Renderer::GetInstance()->LoadTexture(T_BG_RANKING, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_RANKING, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//TITLE
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 200 });
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_TITLE, "RANKING", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_RANKING_TITLE, { SCREEN_WIDTH / 2 - vtmp.x / 2, -25, vtmp.x, vtmp.y });

	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 100 });

	////RANK
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANK, "RANK", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_RANK, { SCREEN_WIDTH / 2 - vtmp.x / 2 - 200, 150, vtmp.x, vtmp.y });
	
	////SCORE
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SCORE, "SCORE", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SCORE, { SCREEN_WIDTH / 2 - vtmp.x / 2, 150, vtmp.x, vtmp.y });

	////NAME
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_NAME, "NAME", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_NAME, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 200, 150, vtmp.x, vtmp.y });
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

	//TITLE
	Renderer::GetInstance()->PushImage(T_RANKING_TITLE, T_RANKING_TITLE);

	//RANK
	Renderer::GetInstance()->PushImage(T_RANK, T_RANK);

	//SCORE
	Renderer::GetInstance()->PushImage(T_SCORE, T_SCORE);

	//NAME
	Renderer::GetInstance()->PushImage(T_NAME, T_NAME);

	Renderer::GetInstance()->Render();
}