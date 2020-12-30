#include "Menu.h"

Menu::Menu()
{
	//Background
	Renderer::GetInstance()->LoadTexture(T_BG_MENU, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_MENU, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//Audio
	if(!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ "../../res/au/menu.mp3" });


	//Title
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 200 });
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_TITLE, "BOMBERMAN", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vtmp.x / 2, 130, vtmp.x, vtmp.y });

	//Buttons
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 150 });
	//Play
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_PLAY_N, "Play", {0,0,0,255}, 0, 0 });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_PLAY_H, "Play", {200,100,0,255}, 0, 0 });

	texturePlay = T_PLAY_N;

	Renderer::GetInstance()->LoadRect(T_PLAY, { SCREEN_WIDTH / 2 - vtmp.x / 2, 250, vtmp.x, vtmp.y });

	//Ranking
	VEC2 vtmp2 =Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_N, "Ranking", {0,0,0,255}, 0, 0 });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_H, "Ranking", {200,100,0,255}, 0, 0 });

	textureRanking = T_RANKING_N;

	Renderer::GetInstance()->LoadRect(T_RANKING, { SCREEN_WIDTH / 2 - vtmp2.x / 2, 350, vtmp2.x, vtmp2.y });

	//Sound On/off
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_ON_N, "Sound on", {0,0,0,255}, 0, 0 });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_ON_H, "Sound on", {200,100,0,255}, 0, 0 });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_OFF_N, "Sound off", {0,0,0,255}, 0, 0 });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_OFF_H, "Sound off", {200,100,0,255}, 0, 0 });

	textureSound = T_SOUND_ON_N;

	Renderer::GetInstance()->LoadRect(T_SOUND, { SCREEN_WIDTH / 2 - vtmp.x, 450, vtmp.x * 2, vtmp.y });

	//Exit
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_EXIT_N, "Exit", {0,0,0,255}, 0, 0 });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_EXIT_H, "Exit", {200,100,0,255}, 0, 0 });

	textureExit = T_EXIT_N;

	Renderer::GetInstance()->LoadRect(T_EXIT, { SCREEN_WIDTH / 2 - vtmp.x / 2, 550, vtmp.x, vtmp.y });
	//Play
}

Menu::~Menu()
{
	AudioManager::GetInstance()->~AudioManager();
}

void Menu::Update(InputManager* input)
{
	input->GetInput().GetScreenSize();
}

void Menu::Draw()
{
	Renderer::GetInstance()->Clear();

	//Background
	Renderer::GetInstance()->PushImage(T_BG_MENU, T_BG_MENU);

	//Title
	Renderer::GetInstance()->PushImage(T_TITLE, T_TITLE);
	//Buttons
	Renderer::GetInstance()->PushImage(texturePlay, T_PLAY);
	Renderer::GetInstance()->PushImage(textureRanking, T_RANKING);
	Renderer::GetInstance()->PushImage(textureSound, T_SOUND);
	Renderer::GetInstance()->PushImage(textureExit, T_EXIT);



	Renderer::GetInstance()->Render();
}