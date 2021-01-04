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
}

Gameplay::~Gameplay()
{
	_players.clear();
	delete p;
}

void Gameplay::Update(InputManager* input)
{
	for (Player* p : _players)
		p->Update(&input->GetInput());
}

void Gameplay::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_INGAME, T_BG_INGAME);

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