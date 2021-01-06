#include "Gameplay.h"

Gameplay::Gameplay()
{
	//Background
	renderer->LoadTexture(T_BG_INGAME, "../../res/img/bgGame.jpg");
	renderer->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//Map
	renderer->LoadTexture(T_WALL, "../../res/img/items.png");
	map.AddWalls();

	//Players
	renderer->LoadTexture(T_PLAYER1, "../../res/img/player1.png");
	renderer->LoadTexture(T_PLAYER2, "../../res/img/player2.png");
	AddPlayer(T_PLAYER1, Player::EPlayerType::PL1);
	AddPlayer(T_PLAYER2, Player::EPlayerType::PL2);

	//Audio
	/*if (!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ "../../res/au/game_theme.mp3" });*/

	//HUD
	renderer->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 90 });

	//Player 1
	VEC2 vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL1, "PL1: ", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_NUM_PL1, { 30, 5, vtmp.x, vtmp.y });
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL1, "000", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });

	//Player 2
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL2, "PL2: ", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_NUM_PL2, { 550, 5, vtmp.x, vtmp.y });
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL2, "000", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });

	//Timer
	renderer->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 120 });
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_TIME, "00:00", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y });
}

Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	for (Player* p : _players)
		p->Update(_input, &map);

	UpdateScoreText();
}

void Gameplay::Draw()
{
	renderer->Clear();

	//Background
	renderer->PushImage(T_BG_INGAME, T_BG_INGAME);

	//HUD
	renderer->PushImage(T_SC_NUM_PL1, T_SC_NUM_PL1);
	renderer->PushImage(T_SC_PL1, T_SC_PL1);
	renderer->PushImage(T_SC_NUM_PL2, T_SC_NUM_PL2);
	renderer->PushImage(T_SC_PL2, T_SC_PL2);
	renderer->PushImage(T_TIME, T_TIME);

	//Map
	for (Wall* w : map.walls)
	{
		renderer->PushSprite(T_WALL, w->GetFrame(), w->GetPosition());
	}

	//Players
	_players[0]->Draw(T_PLAYER1, _players[0]);
	_players[1]->Draw(T_PLAYER2, _players[1]);

	renderer->Render();
}

void Gameplay::AddPlayer(std::string id, Player::EPlayerType type)
{
	p = new Player();
	p->SetPlayerValues(renderer->GetTextureSize(id).x, renderer->GetTextureSize(id).y, 3, 4, type);
	_players.push_back(std::move(p));
}

void Gameplay::UpdateScoreText()
{
	std::string scoreStringPl1, scoreStringPl2;
	scoreStringPl1 = std::to_string(_players[0]->GetScore());
	scoreStringPl2 = std::to_string(_players[1]->GetScore());

	///-------------------------------------------------MEMORY LEAK------------------------------------------------------///
	//renderer->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 90 }); //-->HA D'ANAR AL CONSTRUCTOR
	//VEC2 vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL1, scoreStringPl1, {0, 0, 0, 255}, 0, 0 }); //-->HA D'ANAR AL CONSTRUCTOR
	//renderer->LoadRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y }); //-->HA D'ANAR AL CONSTRUCTOR
	//vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL2, scoreStringPl2, {0, 0, 0, 255}, 0, 0 }); //-->HA D'ANAR AL CONSTRUCTOR
	//renderer->LoadRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y }); //-->HA D'ANAR AL CONSTRUCTOR
}