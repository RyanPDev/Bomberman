#include "Ranking.h"
#include <algorithm>

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

	//RANK BOARD
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANK, "RANK", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_RANK, { SCREEN_WIDTH / 2 - vtmp.x / 2 - 200, 150, vtmp.x, vtmp.y });

	//SCORE BOARD
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SCORE, "SCORE", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SCORE, { SCREEN_WIDTH / 2 - vtmp.x / 2, 150, vtmp.x, vtmp.y });

	//NAME BOARD
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_NAME, "NAME", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_NAME, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 200, 150, vtmp.x, vtmp.y });

	ReadFile();

	//NAMES VALUES
	std::string tmp = "";
	/*for (int i = 0; i < rank.size(); i++)
	{
		tmp += rank[i].name;
	}*/
	//for (int i = 0; i < rank.size() && i < 10; i++)
	//{
	//	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_PL_NAMES, rank[i].name, {0, 0, 0, 255}, 0, 0 });
	//	Renderer::GetInstance()->LoadRect(T_PL_NAMES, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 200, 150 + (50 * i), vtmp.x, vtmp.y });
	//	//results[i] = rank[i];
	//}
}

Ranking::~Ranking() {}

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

	//RANK BOARD
	Renderer::GetInstance()->PushImage(T_RANK, T_RANK);

	//SCORE BOARD
	Renderer::GetInstance()->PushImage(T_SCORE, T_SCORE);

	//NAME BOARD
	Renderer::GetInstance()->PushImage(T_NAME, T_NAME);

	//NAME VALUES
	for (int i = 0; i < rank.size() && i < 10; i++)
	{
		VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_PL_NAMES, rank[i].name, {0, 0, 0, 255}, 0, 0 });
		Renderer::GetInstance()->LoadRect(T_PL_NAMES, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 200, 200 + (35 * i), vtmp.x, vtmp.y });
		Renderer::GetInstance()->PushImage(T_PL_NAMES, T_PL_NAMES);
		vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_PL_SCORES, std::to_string(rank[i].score), {0, 0, 0, 255}, 0, 0 });
		Renderer::GetInstance()->LoadRect(T_PL_SCORES, { SCREEN_WIDTH / 2 - vtmp.x / 2, 200 + (35 * i), vtmp.x, vtmp.y });
		Renderer::GetInstance()->PushImage(T_PL_SCORES, T_PL_SCORES);
		vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_PL_RANK, std::to_string(i + 1), {0, 0, 0, 255}, 0, 0 });
		Renderer::GetInstance()->LoadRect(T_PL_RANK, { SCREEN_WIDTH / 2 - vtmp.x / 2 - 200, 200 + (35 * i), vtmp.x, vtmp.y });
		Renderer::GetInstance()->PushImage(T_PL_RANK, T_PL_RANK);
	}

	Renderer::GetInstance()->Render();
}

//bool Ranking::operator==(const Winner& w1)const
//{
//	return (w1.name == w2.name && w1.score == w2.score);
//}

void Ranking::ReadFile()
{
	Winner aux;
	std::ifstream fentrada("../../res/files/ranking.bin", std::ios::in | std::ios::binary);

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
	rank.pop_back();
	std::sort(rank.begin(), rank.end(), std::greater<Winner>());
	/*auto last = std::unique(rank.begin(), rank.end());
	rank.erase(last, rank.end());*/
	//std::erase(std::unique(myvec.begin(), myvec.end()), myvec.end());
	fentrada.close();
}