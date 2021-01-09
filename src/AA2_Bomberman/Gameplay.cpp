#include "Gameplay.h"

Gameplay::Gameplay()
{
	//Background
	renderer->LoadTexture(T_BG_INGAME, "../../res/img/bgGame.jpg");
	renderer->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//Walls
	renderer->LoadTexture(T_WALL, "../../res/img/items.png");
	renderer->LoadTexture(T_DESTRUCTIBLE_WALL, "../../res/img/items.png");
	map.AddWalls();

	//Bomb
	renderer->LoadTexture(T_BOMB, "../../res/img/items.png");

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
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_TIME, "00:00", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y });

	//Lives
	renderer->LoadTexture(T_LIVES_PL1, "../../res/img/player1.png");
	renderer->LoadTexture(T_LIVES_PL2, "../../res/img/player2.png");
	livesFrame.x = renderer->GetTextureSize(T_LIVES_PL1).x / 3;
	livesFrame.y = (renderer->GetTextureSize(T_LIVES_PL1).y / 4) * 2;
	livesFrame.w = renderer->GetTextureSize(T_LIVES_PL1).x / 3;
	livesFrame.h = renderer->GetTextureSize(T_LIVES_PL1).y / 4;


	//time(&startingTime);
}

Gameplay::~Gameplay() {}

void Gameplay::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	for (Player* p : _players)
		p->Update(_input, &map);

	//TimerUpdate();
	UpdateHUDText();
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

	//Lives
	//Pl1
	if (_players[0]->GetHp() > 0)
		renderer->PushSprite(T_LIVES_PL1, &livesFrame, &RECT{ 170, 10, livesFrame.w, livesFrame.h });
	if (_players[0]->GetHp() > 1)
		renderer->PushSprite(T_LIVES_PL1, &livesFrame, &RECT{ 170 + livesFrame.w, 10, livesFrame.w, livesFrame.h });
	if (_players[0]->GetHp() > 2)
		renderer->PushSprite(T_LIVES_PL1, &livesFrame, &RECT{ 170 + livesFrame.w * 2, 10, livesFrame.w, livesFrame.h });
	//Pl2
	if (_players[1]->GetHp() > 0)
		renderer->PushSprite(T_LIVES_PL2, &livesFrame, &RECT{ 505, 10, livesFrame.w, livesFrame.h });
	if (_players[0]->GetHp() > 1)
		renderer->PushSprite(T_LIVES_PL2, &livesFrame, &RECT{ 505 - livesFrame.w, 10, livesFrame.w, livesFrame.h });
	if (_players[0]->GetHp() > 2)
		renderer->PushSprite(T_LIVES_PL2, &livesFrame, &RECT{ 505 - livesFrame.w * 2, 10, livesFrame.w, livesFrame.h });

	//Walls
	for (Wall* w : map.walls)
	{
		renderer->PushSprite(T_WALL, w->GetFrame(), w->GetPosition());
	}

	//Bombs
	for (Player* p : _players)
	{
		p->DrawBomb();
	}

	//Players
	for (int i = 0; i < _players.size(); i++)
	{
		_players[i]->Draw("Player" + std::to_string(i), _players[i]);
	}

	renderer->Render();
}

void Gameplay::AddPlayer(std::string id, Player::EPlayerType type)
{
	p = new Player();
	p->SetPlayerValues(renderer->GetTextureSize(id).x, renderer->GetTextureSize(id).y, 3, 4, p->GetMapPosition(&map, type), p->GetMapHp(&map, type), type);
	_players.push_back(std::move(p));
}

void Gameplay::TimerUpdate()
{
	/*time(&updatedTime);
	timer = difftime(updatedTime, startingTime);

	timerInfo = gmtime(&timer);
	strftime(timerPtr, 80, "%M:%S", timerInfo);*/

}

void Gameplay::UpdateHUDText()
{
	
	//if (*_players[0]->GetScore() > std::stoi(scoreStringPl1))
	{
		//scoreStringPl1 = std::to_string(*_players[0]->GetScore());
		VEC2 vtmp = renderer->UpdateTextureText(F_GAMEOVER, Text{ T_SC_PL1, scoreStringPl1, {0, 0, 0, 255}, 0, 0 });
		renderer->UpdateRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });
	}
	//if (*_players[1]->GetScore() > std::stoi(scoreStringPl2))
	{
		//scoreStringPl2 = std::to_string(*_players[1]->GetScore());
		VEC2 vtmp = renderer->UpdateTextureText(F_GAMEOVER, Text{ T_SC_PL2, scoreStringPl2, {0, 0, 0, 255}, 0, 0 });
		renderer->UpdateRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });
	}

	///-------------------------------------------------MEMORY LEAK------------------------------------------------------///

	////Timer
	//vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_TIME, timerPtr, {0, 0, 0, 255}, 0, 0 }); //-->HA D'ANAR AL CONSTRUCTOR
	//renderer->LoadRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y }); //-->HA D'ANAR AL CONSTRUCTOR
}