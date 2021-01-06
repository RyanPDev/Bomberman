#include "Menu.h"

Menu::Menu()
{
	//Background
	renderer->LoadTexture(T_BG_MENU, "../../res/img/bgGame.jpg");
	renderer->LoadRect(T_BG_MENU, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//Audio
	/*if(!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ "../../res/au/menu.mp3" });*/

	//Title
	renderer->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 200 });
	VEC2 vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_TITLE, "BOMBERMAN", {0, 0, 0, 255}, 0, 0 });
	renderer->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vtmp.x / 2, 130, vtmp.x, vtmp.y });

	//Buttons
	renderer->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 150 });
	//Play
	vtmp = renderer->LoadTextureText(F_GAMEOVER, Text{ T_PLAY_N, "Play", {0,0,0,255}, 0, 0 });

	renderer->LoadTextureText(F_GAMEOVER, Text{ T_PLAY_H, "Play", {200,100,0,255}, 0, 0 });

	texturePlay = T_PLAY_N;

	renderer->LoadRect(T_PLAY, { SCREEN_WIDTH / 2 - vtmp.x / 2, 250, vtmp.x, vtmp.y });

	//Ranking
	VEC2 vtmp2 = renderer->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_N, "Ranking", {0,0,0,255}, 0, 0 });

	renderer->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_H, "Ranking", {200,100,0,255}, 0, 0 });

	textureRanking = T_RANKING_N;

	renderer->LoadRect(T_RANKING, { SCREEN_WIDTH / 2 - vtmp2.x / 2, 350, vtmp2.x, vtmp2.y });

	//Sound On/off
	renderer->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_ON_N, "Sound on", {0,0,0,255}, 0, 0 });

	renderer->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_ON_H, "Sound on", {200,100,0,255}, 0, 0 });

	renderer->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_OFF_N, "Sound off", {0,0,0,255}, 0, 0 });

	renderer->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_OFF_H, "Sound off", {200,100,0,255}, 0, 0 });

	textureSound = T_SOUND_ON_N;

	renderer->LoadRect(T_SOUND, { SCREEN_WIDTH / 2 - vtmp.x, 450, vtmp.x * 2, vtmp.y });

	//Exit
	renderer->LoadTextureText(F_GAMEOVER, Text{ T_EXIT_N, "Exit", {0,0,0,255}, 0, 0 });

	renderer->LoadTextureText(F_GAMEOVER, Text{ T_EXIT_H, "Exit", {200,100,0,255}, 0, 0 });

	textureExit = T_EXIT_N;

	renderer->LoadRect(T_EXIT, { SCREEN_WIDTH / 2 - vtmp.x / 2, 550, vtmp.x, vtmp.y });
}

Menu::~Menu()
{
}

void Menu::Update(InputData* _input)
{
	if (_input->JustPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	//Button Collisions
	if (Collisions::ExistCollision(_input->GetMouseCoords(), renderer->GetRect(T_PLAY)))
	{
		SetTexturePlay(T_PLAY_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_PLAY); }
	}
	else SetTexturePlay(T_PLAY_N);

	if (Collisions::ExistCollision(_input->GetMouseCoords(), renderer->GetRect(T_RANKING)))
	{
		SetTextureRanking(T_RANKING_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_RANKING); }
	}
	else SetTextureRanking(T_RANKING_N);

	if (Collisions::ExistCollision(_input->GetMouseCoords(), renderer->GetRect(T_SOUND)))
	{
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT))
		{
			if (!AudioManager::GetInstance()->PausedMusic())
				AudioManager::GetInstance()->PauseMusic();

			else
				AudioManager::GetInstance()->ResumeMusic();
		}

		if (AudioManager::GetInstance()->PausedMusic())
			SetTextureSound(T_SOUND_OFF_H);
		else
			SetTextureSound(T_SOUND_ON_H);
	}
	else
	{
		if (AudioManager::GetInstance()->PausedMusic())
			SetTextureSound(T_SOUND_OFF_N);
		else
			SetTextureSound(T_SOUND_ON_N);
	}

	if (Collisions::ExistCollision(_input->GetMouseCoords(), renderer->GetRect(T_EXIT)))
	{
		SetTextureExit(T_EXIT_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_EXIT); }
	}
	else SetTextureExit(T_EXIT_N);
}

void Menu::Draw()
{
	renderer->Clear();

	//Background
	renderer->PushImage(T_BG_MENU, T_BG_MENU);

	//Title
	renderer->PushImage(T_TITLE, T_TITLE);

	//Buttons
	renderer->PushImage(texturePlay, T_PLAY);
	renderer->PushImage(textureRanking, T_RANKING);
	renderer->PushImage(textureSound, T_SOUND);
	renderer->PushImage(textureExit, T_EXIT);

	renderer->Render();
}