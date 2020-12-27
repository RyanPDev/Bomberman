#include "Gameplay.h"

Gameplay::Gameplay()
{
	//Background
	Renderer::GetInstance()->LoadTexture(T_BG_INGAME, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_INGAME, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//Players
	InitPlayers();
}

Gameplay::~Gameplay()
{

}

void Gameplay::Update()
{

}

void Gameplay::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_INGAME, T_BG_INGAME);

	//Players
	for (Player* p : _players)
	{
		Renderer::GetInstance()->PushSprite(T_PLAYERS, p->GetFrame(), p->GetPosition());
	}

	Renderer::GetInstance()->Render();
}

void Gameplay::InitPlayers()
{
	Renderer::GetInstance()->LoadTexture(T_PLAYERS, "../../res/img/player1.png");
	AddPlayers(Renderer::GetInstance()->GetTextureSize(T_PLAYERS).x, Renderer::GetInstance()->GetTextureSize(T_PLAYERS).y, Player::EPlayerType::PL1);

	Renderer::GetInstance()->LoadTexture(T_PLAYERS, "../../res/img/player2.png");
	AddPlayers(Renderer::GetInstance()->GetTextureSize(T_PLAYERS).x, Renderer::GetInstance()->GetTextureSize(T_PLAYERS).y, Player::EPlayerType::PL2);
}

void Gameplay::AddPlayers(int texWidth, int texHeight, Player::EPlayerType type)
{
	Player* p = new Player();
	p->SetPlayerValues(texWidth, texHeight, 3, 4, type);
	_players.push_back(std::move(p));
}