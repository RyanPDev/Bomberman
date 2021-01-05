#include "Gameplay.h"

Gameplay::Gameplay()
{
	//Background
	Renderer::GetInstance()->LoadTexture(T_BG_INGAME, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//Map
	map.AddWalls();

	//Players
	InitPlayers();

	//Audio
	/*if (!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ "../../res/au/game_theme.mp3" });*/

	//HUD
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 90 });
	//Player 1
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL1, "PL1: ", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_NUM_PL1, { 30, 5, vtmp.x, vtmp.y });

	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL1, "000", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });

	//Player 2
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL2, "PL2: ", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_NUM_PL2, { 550, 5, vtmp.x, vtmp.y });

	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL2, "000", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });

	//Timer
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 120 });
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_TIME, "00:00", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_TIME, { SCREEN_WIDTH/2 - vtmp.x/2, 0, vtmp.x, vtmp.y });
}

Gameplay::~Gameplay()
{
	_players.clear();
	delete p;
}

void Gameplay::Update()
{
	for (Player* p : _players)
		p->Update(&map);

	UpdateScoreText();
}

void Gameplay::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_INGAME, T_BG_INGAME);

	//HUD
	Renderer::GetInstance()->PushImage(T_SC_NUM_PL1, T_SC_NUM_PL1);
	Renderer::GetInstance()->PushImage(T_SC_PL1, T_SC_PL1);
	Renderer::GetInstance()->PushImage(T_SC_NUM_PL2, T_SC_NUM_PL2);
	Renderer::GetInstance()->PushImage(T_SC_PL2, T_SC_PL2);
	Renderer::GetInstance()->PushImage(T_TIME, T_TIME);

	//Map	
	map.Draw();

	//Players
	_players[0]->Draw(T_PLAYER1, _players[0]);
	_players[1]->Draw(T_PLAYER2, _players[1]);

	Renderer::GetInstance()->Render();
}

void Gameplay::AddPlayer(int texWidth, int texHeight, Player::EPlayerType type)
{
	p = new Player();
	p->SetPlayerValues(texWidth, texHeight, 3, 4, type);
	_players.push_back(std::move(p));
}

void Gameplay::InitPlayers()
{
	Renderer::GetInstance()->LoadTexture(T_PLAYER1, "../../res/img/player1.png");
	Renderer::GetInstance()->LoadTexture(T_PLAYER2, "../../res/img/player2.png");
	AddPlayer(Renderer::GetInstance()->GetTextureSize(T_PLAYER1).x, Renderer::GetInstance()->GetTextureSize(T_PLAYER1).y, Player::EPlayerType::PL1);
	AddPlayer(Renderer::GetInstance()->GetTextureSize(T_PLAYER2).x, Renderer::GetInstance()->GetTextureSize(T_PLAYER2).y, Player::EPlayerType::PL2);
}

void Gameplay::UpdateScoreText()
{
	std::string scoreStringPl1, scoreStringPl2;
	scoreStringPl1 = std::to_string(_players[0]->GetScore());
	scoreStringPl2 = std::to_string(_players[1]->GetScore());


	//Aixó Provoca una Memory Leak
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 90 });
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL1, scoreStringPl1, {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL2, scoreStringPl2, {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });

	
}