#include "Ranking.h"
#include <algorithm>

Ranking::Ranking()
{
	//BACKGROUND
	Renderer::GetInstance()->LoadTexture(T_BG_RANKING, P_BG_GAME);
	Renderer::GetInstance()->LoadRect(T_BG_RANKING, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//TITLE
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, P_GAME_OVER_FONT, 200 });
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_TITLE, "RANKING", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_RANKING_TITLE, { SCREEN_WIDTH / 2 - vtmp.x / 2, -25, vtmp.x, vtmp.y });

	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, P_GAME_OVER_FONT, 100 });

	//RANK BOARD
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANK, "RANK", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_RANK, { SCREEN_WIDTH / 2 - vtmp.x / 2 - 200, 150, vtmp.x, vtmp.y });

	//SCORE BOARD
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SCORE, "SCORE", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SCORE, { SCREEN_WIDTH / 2 - vtmp.x / 2, 150, vtmp.x, vtmp.y });

	//NAME BOARD
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_NAME, "NAME", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_NAME, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 200, 150, vtmp.x, vtmp.y });

	//Back Button 
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_BACK_N, "RETURN TO MAIN MENU", {250,128,114,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_BACK_H, "RETURN TO MAIN MENU", {220,220,220,255}, 0, 0 });
	textureBackToMenu = T_BACK_N;
	Renderer::GetInstance()->LoadRect(T_BACK, { SCREEN_WIDTH / 2 - vtmp.x / 2, 580, vtmp.x, vtmp.y });

	ReadFile();
}

Ranking::~Ranking() {}

void Ranking::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	//Button Collisions
	if (Collisions::ExistCollision(_input->GetMouseCoords(), Renderer::GetInstance()->GetRect(T_BACK)))
	{
		SetTextureBackToMenu(T_BACK_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_EXIT); }
	}
	else SetTextureBackToMenu(T_BACK_N);
}

void Ranking::Draw()
{
	Renderer::GetInstance()->Clear();

	//BACKGROUND
	Renderer::GetInstance()->PushImage(T_BG_RANKING, T_BG_RANKING);

	//TITLE
	Renderer::GetInstance()->PushImage(T_RANKING_TITLE, T_RANKING_TITLE);

	//RANK BOARD
	Renderer::GetInstance()->PushImage(T_RANK, T_RANK);

	//SCORE BOARD
	Renderer::GetInstance()->PushImage(T_SCORE, T_SCORE);

	//NAME BOARD
	Renderer::GetInstance()->PushImage(T_NAME, T_NAME);

	//RANK, SCORE AND NAME VALUES FOR EACH PLAYER IN THE RANKING
	for (int i = 0; i < rank.size() && i < 10; i++)
	{
		Color color = {0, 0, 0, 0};
		if (i == 0) color = { 255, 215, 0, 255 };
		else if (i == 1) color = { 211, 211, 211, 255 };
		else if (i == 2) color = { 205, 127, 50, 255 };
		else color = { 0, 0, 0, 255 };

		VEC2 vtmp = Renderer::GetInstance()->UpdateTextureText(F_GAMEOVER, Text{ T_PL_NAMES, rank[i].name, color, 0, 0 });
		Renderer::GetInstance()->UpdateRect(T_PL_NAMES, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 200, 200 + (35 * i), vtmp.x, vtmp.y });
		Renderer::GetInstance()->PushImage(T_PL_NAMES, T_PL_NAMES);
		vtmp = Renderer::GetInstance()->UpdateTextureText(F_GAMEOVER, Text{ T_PL_SCORES, std::to_string(rank[i].score), color, 0, 0 });
		Renderer::GetInstance()->UpdateRect(T_PL_SCORES, { SCREEN_WIDTH / 2 - vtmp.x / 2, 200 + (35 * i), vtmp.x, vtmp.y });
		Renderer::GetInstance()->PushImage(T_PL_SCORES, T_PL_SCORES);
		vtmp = Renderer::GetInstance()->UpdateTextureText(F_GAMEOVER, Text{ T_PL_RANK, std::to_string(i + 1), color, 0, 0 });
		Renderer::GetInstance()->UpdateRect(T_PL_RANK, { SCREEN_WIDTH / 2 - vtmp.x / 2 - 200, 200 + (35 * i), vtmp.x, vtmp.y });
		Renderer::GetInstance()->PushImage(T_PL_RANK, T_PL_RANK);
	}

	//Button
	Renderer::GetInstance()->PushImage(textureBackToMenu, T_BACK);

	Renderer::GetInstance()->Render();
}

void Ranking::ReadFile()
{
	Winner aux;
	std::ifstream fentrada;
	fentrada.open(P_RANKING, std::ios::in | std::ios::binary);

	while (fentrada)
	{
		fentrada.read(reinterpret_cast<char*>(&aux.score), sizeof(int));
		size_t len;
		fentrada.read(reinterpret_cast<char*>(&len), sizeof(size_t));
		char* temp = new char[len + 1];
		fentrada.read(temp, len);
		temp[len] = '\0';
		aux.name = temp;
		delete[]temp;
		rank.push_back(aux);
	}
	if (!rank.empty())
	{
		rank.pop_back();
		std::sort(rank.begin(), rank.end(), std::greater<Winner>());
	}
	fentrada.close();
}