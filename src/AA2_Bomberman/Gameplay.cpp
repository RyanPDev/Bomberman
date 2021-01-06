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
}

Gameplay::~Gameplay()
{
}

void Gameplay::Update(InputData* _input)
{
	if (_input->IsPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	for (Player* p : _players)
		p->Update(_input, &map);
}

void Gameplay::Draw()
{
	renderer->Clear();

	//Background
	renderer->PushImage(T_BG_INGAME, T_BG_INGAME);

	//Map
	for (Wall* w : map.walls)
	{
		renderer->PushSprite(T_WALL, w->GetFrame(), w->GetPosition());
	}
	//map.Draw();

	//Players
	for (Player* p : _players)
	{
		renderer->PushSprite(T_PLAYER1, p->GetFrame(), p->GetPosition());
	}
	//_players[0]->Draw(T_PLAYER1, _players[0]);
	//_players[1]->Draw(T_PLAYER2, _players[1]);

	renderer->Render();
}

void Gameplay::AddPlayer(std::string id, Player::EPlayerType type)
{
	p = new Player();
	p->SetPlayerValues(renderer->GetTextureSize(id).x, renderer->GetTextureSize(id).y, 3, 4, type);
	_players.push_back(std::move(p));
}