#include "Gameplay.h"

Gameplay::Gameplay()
{
	//BACKGROUND
	renderer->LoadTexture(T_BG_INGAME, "../../res/img/bgGame.jpg");
	renderer->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//WALLS
	renderer->LoadTexture(T_WALL, "../../res/img/items.png");
	renderer->LoadTexture(T_DESTRUCTIBLE_WALL, "../../res/img/items.png");
	renderer->LoadTexture(T_DESTROYED_WALL, "../../res/img/items.png");
	map.AddWalls();

	//BOMB
	renderer->LoadTexture(T_BOMB, "../../res/img/items.png");

	//EXPLOSION
	renderer->LoadTexture(T_EXPLOSION, "../../res/img/explosion.png");

	//PLAYERS
	renderer->LoadTexture(T_PLAYER1, "../../res/img/player1.png");
	playerTexture.push_back(T_PLAYER1);

	renderer->LoadTexture(T_PLAYER2, "../../res/img/player2.png");
	playerTexture.push_back(T_PLAYER2);

	for (int i = 0; i < static_cast<int>(Player::EPlayerType::COUNT); i++)
	{
		Player::EPlayerType type = static_cast<Player::EPlayerType>(i);
		AddPlayer(playerTexture[i], type, map.initialPlPos[i]);
	}

	//AUDIO
	if (!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ "../../res/au/game_theme.mp3" });

	//HUD
	renderer->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 90 });

	//PLAYER 1
	VEC2 vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL1, "PL1: ", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_NUM_PL1, { 30, 5, vtmp.x, vtmp.y });
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL1, "000", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });

	//PLAYER 2
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL2, "PL2: ", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_NUM_PL2, { 550, 5, vtmp.x, vtmp.y });
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL2, "000", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });

	//TIMER
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_TIME, "00:00", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y });

	//HP
	renderer->LoadTexture(T_LIVES_PL1, "../../res/img/player1.png");
	hpTexture.push_back(T_LIVES_PL1);

	renderer->LoadTexture(T_LIVES_PL2, "../../res/img/player2.png");
	hpTexture.push_back(T_LIVES_PL2);

	livesFrame.x = renderer->GetTextureSize(T_LIVES_PL1).x / 3;
	livesFrame.y = (renderer->GetTextureSize(T_LIVES_PL1).y / 4) * 2;
	livesFrame.w = renderer->GetTextureSize(T_LIVES_PL1).x / 3;
	livesFrame.h = renderer->GetTextureSize(T_LIVES_PL1).y / 4;

	//INITIALIZE GAME TIMER
	timeDown = GAME_TIMER;
}

Gameplay::~Gameplay() {}

void Gameplay::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	//UPDATE PLAYERS
	for (Player* p : _players)
	{
		p->Update(_input, &map);
		if (p->GetHp() <= 0)
			SetSceneState(ESceneState::CLICK_RANKING);
		//p->DeathManagement(_input);
	}

	//BEHAVIOUR IN THE GAME WHEN PLAYERS TAKE DAMAGE
	TakeDamageBehaviour(_input);

	//TIMER
	timeDown -= *_input->GetDeltaTime();

	//UPDATE HUD
	UpdateHUDText();

	if (timeDown <= 0) SetSceneState(ESceneState::CLICK_RANKING);
}

void Gameplay::Draw()
{
	renderer->Clear();

	//BACKGROUND
	renderer->PushImage(T_BG_INGAME, T_BG_INGAME);

	//HUD
	renderer->PushImage(T_SC_NUM_PL1, T_SC_NUM_PL1);
	renderer->PushImage(T_SC_PL1, T_SC_PL1);
	renderer->PushImage(T_SC_NUM_PL2, T_SC_NUM_PL2);
	renderer->PushImage(T_SC_PL2, T_SC_PL2);
	renderer->PushImage(T_TIME, T_TIME);

	//HP
	for (int i = 0; i < static_cast<int>(Player::EPlayerType::COUNT); i++)
	{
		Player::EPlayerType type = static_cast<Player::EPlayerType>(i);
		_players[i]->DrawHp(hpTexture[i], &livesFrame, type);
	}

	//if (_players[0]->GetHp() > 0)
	//	renderer->PushSprite(T_LIVES_PL1, &livesFrame, &RECT{ 170, 10, livesFrame.w, livesFrame.h });
	//if (_players[0]->GetHp() > 1)
	//	renderer->PushSprite(T_LIVES_PL1, &livesFrame, &RECT{ 170 + livesFrame.w, 10, livesFrame.w, livesFrame.h });
	//if (_players[0]->GetHp() > 2)
	//	renderer->PushSprite(T_LIVES_PL1, &livesFrame, &RECT{ 170 + livesFrame.w * 2, 10, livesFrame.w, livesFrame.h });
	////Pl2
	//if (_players[1]->GetHp() > 0)
	//	renderer->PushSprite(T_LIVES_PL2, &livesFrame, &RECT{ 505, 10, livesFrame.w, livesFrame.h });
	//if (_players[1]->GetHp() > 1)
	//	renderer->PushSprite(T_LIVES_PL2, &livesFrame, &RECT{ 505 - livesFrame.w, 10, livesFrame.w, livesFrame.h });
	//if (_players[1]->GetHp() > 2)
	//	renderer->PushSprite(T_LIVES_PL2, &livesFrame, &RECT{ 505 - livesFrame.w * 2, 10, livesFrame.w, livesFrame.h });

	//WALLS
	for (Wall* w : map.walls)
	{
		renderer->PushSprite(T_WALL, w->GetFrame(), w->GetPosition());
	}

	//BOMBS
	for (Player* p : _players)
	{
		p->DrawBomb();
		p->DrawExplosion(&map);
	}

	//PLAYERS
	for (int i = 0; i < _players.size(); i++)
	{
		if (!_players[i]->GetDeath())
			_players[i]->Draw(playerTexture[i], _players[i]);
	}

	renderer->Render();
}

//ADDS PLAYERS TO THE GAME
void Gameplay::AddPlayer(std::string id, Player::EPlayerType type, VEC2 initPos)
{
	p = new Player();
	p->SetPlayerValues(renderer->GetTextureSize(id).x, renderer->GetTextureSize(id).y, 3, 4, p->GetMapHp(&map, type), type, initPos);
	_players.push_back(std::move(p));
}

//CONTROLS BEHAVIOUR OF THE GAME WHEN PLAYERS TAKE DAMAGE
void Gameplay::TakeDamageBehaviour(InputData* _input)
{
	for (Player* p : _players)
	{
		for (Explosion e : p->_explosions)
		{
			if (e.GetVisibility())
			{
				for (Player* pl : _players)
				{
					if (Collisions::ExistCollision(*pl->GetPosition(), *e.GetPosition()) && !pl->GetImmunity() && !pl->GetDeath())
					{
						if (pl != p) p->SetScore(100);
						pl->SetHp(1);
						pl->SetDeath(true);
						pl->SetDeathImmunity(true);
						pl->SetPosition(pl->GetInitialPosition());
					}
				}
			}
		}
	}
}

//UPDATES HUD TEXT/SCORE/TIMER
void Gameplay::UpdateHUDText()
{
	if (*_players[0]->GetScore() > std::stoi(scoreStringPl1))
	{
		scoreStringPl1 = std::to_string(*_players[0]->GetScore());
		VEC2 vtmp = renderer->UpdateTextureText(F_GAMEOVER, Text{ T_SC_PL1, scoreStringPl1, {0, 0, 0, 255}, 0, 0 });
		renderer->UpdateRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });
	}
	if (*_players[1]->GetScore() > std::stoi(scoreStringPl2))
	{
		scoreStringPl2 = std::to_string(*_players[1]->GetScore());
		VEC2 vtmp = renderer->UpdateTextureText(F_GAMEOVER, Text{ T_SC_PL2, scoreStringPl2, {0, 0, 0, 255}, 0, 0 });
		renderer->UpdateRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });
	}

	//Timer
	std::string s = F2StrFormat(trunc(timeDown / 60), 0);
	if (static_cast<int>(timeDown) % 60 >= 10)
		s += ":" + F2StrFormat(static_cast<int>(timeDown) % 60, 0);
	else
		s += ":0" + F2StrFormat(static_cast<int>(timeDown) % 60, 0);

	VEC2 vtmp = renderer->UpdateTextureText(F_GAMEOVER, Text{ T_TIME, s, {0, 0, 0, 255}, 0, 0 });
	renderer->UpdateRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y });
}