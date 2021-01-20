#include "Gameplay.h"

Gameplay::Gameplay() : map(Menu::GetCurrentLevel())
{
	//BACKGROUND
	Renderer::GetInstance()->LoadTexture(T_BG_INGAME, P_BG_GAME);
	Renderer::GetInstance()->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//WALLS
	Renderer::GetInstance()->LoadTexture(T_WALL, P_ITEMS);
	Renderer::GetInstance()->LoadTexture(T_DESTRUCTIBLE_WALL, P_ITEMS);
	Renderer::GetInstance()->LoadTexture(T_DESTROYED_WALL, P_ITEMS);
	map.AddWalls();

	//BOMB
	Renderer::GetInstance()->LoadTexture(T_BOMB, P_ITEMS);

	//POWERUPS
	Renderer::GetInstance()->LoadTexture(T_ROLLERS, P_ITEMS);
	powerUpsTexture.push_back(T_ROLLERS);
	Renderer::GetInstance()->LoadTexture(T_SHIELD, P_ITEMS);
	powerUpsTexture.push_back(T_SHIELD);

	//EXPLOSION
	Renderer::GetInstance()->LoadTexture(T_EXPLOSION, P_EXPLOSION);

	//PLAYERS
	Renderer::GetInstance()->LoadTexture(T_PLAYER1, P_PLAYER1);
	playerTexture.push_back(T_PLAYER1);

	Renderer::GetInstance()->LoadTexture(T_PLAYER2, P_PLAYER2);
	playerTexture.push_back(T_PLAYER2);

	for (int i = 0; i < static_cast<int>(Player::EPlayerType::COUNT); i++)
	{
		Player::EPlayerType type = static_cast<Player::EPlayerType>(i);
		AddPlayer(playerTexture[i], type, map.initialPlPos[i]);
	}

	//AUDIO
	if (!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ P_ST_GAME });

	//HUD
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, P_GAME_OVER_FONT, 90 });

	//PLAYER 1
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL1, "PL1: ", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_NUM_PL1, { 30, 5, vtmp.x, vtmp.y });
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL1, "000", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });

	//PLAYER 2
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_NUM_PL2, "PL2: ", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_NUM_PL2, { 550, 5, vtmp.x, vtmp.y });
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SC_PL2, "000", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });

	//TIMER
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_TIME, "00:00", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y });

	//HP
	Renderer::GetInstance()->LoadTexture(T_LIVES_PL1, P_PLAYER1);
	hpTexture.push_back(T_LIVES_PL1);

	Renderer::GetInstance()->LoadTexture(T_LIVES_PL2, P_PLAYER2);
	hpTexture.push_back(T_LIVES_PL2);

	livesFrame.x = Renderer::GetInstance()->GetTextureSize(T_LIVES_PL1).x / 3;
	livesFrame.y = (Renderer::GetInstance()->GetTextureSize(T_LIVES_PL1).y / 4) * 2;
	livesFrame.w = Renderer::GetInstance()->GetTextureSize(T_LIVES_PL1).x / 3;
	livesFrame.h = Renderer::GetInstance()->GetTextureSize(T_LIVES_PL1).y / 4;

	//GAME END TEXT
	//PL1 WIN
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_GAME_END_PL1, "THE WINNER IS PLAYER 1", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_GAME_END_PL1, { SCREEN_WIDTH / 2 - vtmp.x / 2, 200, vtmp.x, vtmp.y });
	//PL2 WIN
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_GAME_END_PL2, "THE WINNER IS PLAYER 2", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_GAME_END_PL2, { SCREEN_WIDTH / 2 - vtmp.x / 2, 200, vtmp.x, vtmp.y });
	//DRAW
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_GAME_END_DRAW, "THE GAME IS A DRAW", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_GAME_END_DRAW, { SCREEN_WIDTH / 2 - vtmp.x / 2, 200, vtmp.x, vtmp.y });

	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_ENTER_NAME, "ENTER YOUR NAME", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_ENTER_NAME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 300, vtmp.x, vtmp.y });



	//INITIALIZE variables
	timeDown = GAME_TIMER;
	isGameEnd = false;
	winnerDeclared = false;
}

Gameplay::~Gameplay() {}

void Gameplay::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	if (timeDown <= 0)
	{
		isGameEnd = true;
		/*if(!winnerDeclared) */

		UpdateRanking();

		SetSceneState(ESceneState::CLICK_RANKING);
		/*if (_input->IsPressed(EInputKeys::RETURN))
			;*/
	}
	else {
		//UPDATE PLAYERS
		for (Player* p : _players)
		{
			p->Update(_input, &map, _powerUps);
			if (p->GetHp() <= 0)
			{
				UpdateRanking();
				SetSceneState(ESceneState::CLICK_RANKING);
				break;
			}
		}

		//BEHAVIOUR IN THE GAME WHEN PLAYERS TAKE DAMAGE
		TakeDamageBehaviour(_input);

		//TIMER
		timeDown -= *_input->GetDeltaTime();

		//UPDATE HUD
		UpdateHUDText();
	}

}

void Gameplay::Draw()
{
	Renderer::GetInstance()->Clear();

	//BACKGROUND
	Renderer::GetInstance()->PushImage(T_BG_INGAME, T_BG_INGAME);

	//HUD
	Renderer::GetInstance()->PushImage(T_SC_NUM_PL1, T_SC_NUM_PL1);
	Renderer::GetInstance()->PushImage(T_SC_PL1, T_SC_PL1);
	Renderer::GetInstance()->PushImage(T_SC_NUM_PL2, T_SC_NUM_PL2);
	Renderer::GetInstance()->PushImage(T_SC_PL2, T_SC_PL2);
	Renderer::GetInstance()->PushImage(T_TIME, T_TIME);

	//HP
	for (int i = 0; i < static_cast<int>(Player::EPlayerType::COUNT); i++)
	{
		Player::EPlayerType type = static_cast<Player::EPlayerType>(i);
		_players[i]->DrawHp(hpTexture[i], &livesFrame, type);
	}

	if (isGameEnd)
	{
		if (winner == 0)
			Renderer::GetInstance()->PushImage(T_GAME_END_DRAW, T_GAME_END_DRAW);
		else
		{
			std::string id = "TxtGameEndPl" + std::to_string(winner);
			Renderer::GetInstance()->PushImage(id, id);
			Renderer::GetInstance()->PushImage(T_ENTER_NAME, T_ENTER_NAME);
		}
	}
	else
	{
		//POWER UPS
		for (PowerUp powerUp : _powerUps)
		{
			powerUp.Draw(powerUp.GetType());
		}

		//WALLS
		for (Wall* w : map.walls)
		{
			Renderer::GetInstance()->PushSprite(T_WALL, w->GetFrame(), w->GetPosition());
		}

		//PLAYERS
		for (int i = 0; i < _players.size(); i++)
		{
			//BOMBS
			_players[i]->DrawBomb();
			_players[i]->DrawExplosion(&map);

			if (!_players[i]->GetDeath())
				_players[i]->Draw(playerTexture[i], _players[i]);
		}
	}

	Renderer::GetInstance()->Render();
}

//ADDS PLAYERS TO THE GAME
void Gameplay::AddPlayer(std::string id, Player::EPlayerType type, VEC2 initPos)
{
	p = new Player();
	p->SetPlayerValues(Renderer::GetInstance()->GetTextureSize(id).x, Renderer::GetInstance()->GetTextureSize(id).y, 3, 4, p->GetMapHp(&map, type), type, initPos);
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
					if (Collisions::ExistCollision(*pl->GetPosition(), *e.GetPosition()) && !pl->GetDeathImmunity() && !pl->GetDeath() && !pl->GetShieldImmunity())
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
		VEC2 vtmp = Renderer::GetInstance()->UpdateTextureText(F_GAMEOVER, Text{ T_SC_PL1, scoreStringPl1, {0, 0, 0, 255}, 0, 0 });
		Renderer::GetInstance()->UpdateRect(T_SC_PL1, { 100, 5, vtmp.x, vtmp.y });
	}
	if (*_players[1]->GetScore() > std::stoi(scoreStringPl2))
	{
		scoreStringPl2 = std::to_string(*_players[1]->GetScore());
		VEC2 vtmp = Renderer::GetInstance()->UpdateTextureText(F_GAMEOVER, Text{ T_SC_PL2, scoreStringPl2, {0, 0, 0, 255}, 0, 0 });
		Renderer::GetInstance()->UpdateRect(T_SC_PL2, { 627, 5, vtmp.x, vtmp.y });
	}

	//Timer
	std::string s = F2StrFormat(trunc(timeDown / 60), 0);
	if (static_cast<int>(timeDown) % 60 >= 10)
		s += ":" + F2StrFormat(static_cast<int>(timeDown) % 60, 0);
	else
		s += ":0" + F2StrFormat(static_cast<int>(timeDown) % 60, 0);

	VEC2 vtmp = Renderer::GetInstance()->UpdateTextureText(F_GAMEOVER, Text{ T_TIME, s, {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->UpdateRect(T_TIME, { SCREEN_WIDTH / 2 - vtmp.x / 2, 0, vtmp.x, vtmp.y });
}

//WRITES WINNER INFO INTO RANKING BINARY FILE
void Gameplay::UpdateRanking()
{
	system("cls");
	std::string name;
	int score = 0;
	bool isOk = false;
	do
	{
		std::cout << "Enter your name (A-Z | (3-10 characters): " << std::endl;
		std::getline(std::cin, name);
		system("cls");

		if (name.size() > 10 || name.size() < 3) { std::cout << "INAPPROPIATE NUMBER OF CHARACTERS\n" << std::endl; }
		else
		{
			for (int i = 0; i < name.size(); i++)
			{
				if ((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')) isOk = true;
				else { isOk = false; std::cout << "INVALID CHARACTER\n" << std::endl; break; }
			}
		}

	} while (!isOk);

	for (Player* p : _players)
	{
		if (p->GetHp() > 0)
		{
			if (*p->GetScore() > score)
			{
				score = *p->GetScore();
			}
		}
	}

	std::ofstream fsalida(P_RANKING, std::ios::out | std::ios::binary | std::ios::app);
	fsalida.write(reinterpret_cast<char*>(&score), sizeof(int));
	size_t len = name.size();
	fsalida.write(reinterpret_cast<char*>(&len), sizeof(size_t));
	fsalida.write(name.c_str(), name.size());

	fsalida.close();
}

void Gameplay::DeclareWinner()
{
	//HARDCODED (SHOULD FIX, LATER...?)
	int scpl1 = *_players[0]->GetScore(), scpl2 = *_players[1]->GetScore();
	int hp1 = _players[0]->GetHp(), hp2 = _players[1]->GetHp();
	if (hp1 <= 0 || scpl1 > scpl2) winner = 1;
	else if (hp2 <= 0 || scpl1 < scpl2) winner = 2;
	else winner = 0;

	winnerDeclared = true;
}