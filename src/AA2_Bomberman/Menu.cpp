#include "Menu.h"

Menu::Menu()
{
	//BACKGROUND
	Renderer::GetInstance()->LoadTexture(T_BG_MENU, "../../res/img/bgGame.jpg");
	Renderer::GetInstance()->LoadRect(T_BG_MENU, { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });

	//AUDIO
	if (!AudioManager::GetInstance()->PausedMusic())
		AudioManager::GetInstance()->LoadSoundtrack(Soundtrack{ "../../res/au/menu.mp3" });

	//TITLE
	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 200 });
	VEC2 vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_TITLE, "BOMBERMAN", {0, 0, 0, 255}, 0, 0 });
	Renderer::GetInstance()->LoadRect(T_TITLE, { SCREEN_WIDTH / 2 - vtmp.x / 2, 130, vtmp.x, vtmp.y });

#pragma region BUTTONS

	Renderer::GetInstance()->LoadFont(Font{ F_GAMEOVER, "../../res/ttf/game_over.ttf", 150 });
	//PLAY BUTTON
	vtmp = Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_LEVEL1_N, "Level 1", {0,0,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_LEVEL1_H, "Level 1", {200,100,0,255}, 0, 0 });
	textureLevel1 = T_LEVEL1_N;
	Renderer::GetInstance()->LoadRect(T_LEVEL1, { SCREEN_WIDTH / 2 - vtmp.x / 2 - 150, 250, vtmp.x, vtmp.y });

	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_LEVEL2_N, "Level 2", {0,0,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_LEVEL2_H, "Level 2", {200,100,0,255}, 0, 0 });
	textureLevel2 = T_LEVEL2_N;
	Renderer::GetInstance()->LoadRect(T_LEVEL2, { SCREEN_WIDTH / 2 - vtmp.x / 2 + 150, 250, vtmp.x, vtmp.y });

	//RANKING BUTTON
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_N, "Ranking", {0,0,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_RANKING_H, "Ranking", {200,100,0,255}, 0, 0 });
	textureRanking = T_RANKING_N;
	Renderer::GetInstance()->LoadRect(T_RANKING, { SCREEN_WIDTH / 2 - vtmp.x / 2, 350, vtmp.x, vtmp.y });

	//EXIT
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_EXIT_N, "Exit", {0,0,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_EXIT_H, "Exit", {200,100,0,255}, 0, 0 });
	textureExit = T_EXIT_N;
	Renderer::GetInstance()->LoadRect(T_EXIT, { SCREEN_WIDTH / 2 - vtmp.x / 2, 550, vtmp.x, vtmp.y });

	//SOUND ON/OFF
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_ON_N, "Sound on", {0,0,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_ON_H, "Sound on", {200,100,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_OFF_N, "Sound off", {0,0,0,255}, 0, 0 });
	Renderer::GetInstance()->LoadTextureText(F_GAMEOVER, Text{ T_SOUND_OFF_H, "Sound off", {200,100,0,255}, 0, 0 });
	textureSound = T_SOUND_ON_N;
	Renderer::GetInstance()->LoadRect(T_SOUND, { SCREEN_WIDTH / 2 - vtmp.x + 100, 450, vtmp.x, vtmp.y });


#pragma endregion
}

Menu::~Menu() {}

std::string Menu::level;

//UPDATES AUDIO AND BUTTONS BASED ON MOUSE INPUT AND COLLISION
void Menu::Update(InputData* _input)
{
	if (_input->JustPressed(EInputKeys::ESC)) SetSceneState(ESceneState::CLICK_EXIT);

	//Button Collisions
	if (Collisions::ExistCollision(_input->GetMouseCoords(), Renderer::GetInstance()->GetRect(T_LEVEL1)))
	{
		SetTextureLevel1(T_LEVEL1_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_PLAY); SetCurrentLevel("Level1"); }
	}
	else SetTextureLevel1(T_LEVEL1_N);

	if (Collisions::ExistCollision(_input->GetMouseCoords(), Renderer::GetInstance()->GetRect(T_LEVEL2)))
	{
		SetTextureLevel2(T_LEVEL2_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_PLAY); SetCurrentLevel("Level2");
		}
	}
	else SetTextureLevel2(T_LEVEL2_N);

	if (Collisions::ExistCollision(_input->GetMouseCoords(), Renderer::GetInstance()->GetRect(T_RANKING)))
	{
		SetTextureRanking(T_RANKING_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_RANKING); }
	}
	else SetTextureRanking(T_RANKING_N);

	if (Collisions::ExistCollision(_input->GetMouseCoords(), Renderer::GetInstance()->GetRect(T_SOUND)))
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

	if (Collisions::ExistCollision(_input->GetMouseCoords(), Renderer::GetInstance()->GetRect(T_EXIT)))
	{
		SetTextureExit(T_EXIT_H);
		if (_input->JustPressed(EInputKeys::MOUSE_LEFT)) { SetSceneState(ESceneState::CLICK_EXIT); }
	}
	else SetTextureExit(T_EXIT_N);
}

void Menu::Draw()
{
	Renderer::GetInstance()->Clear();

	//BACKGROUND
	Renderer::GetInstance()->PushImage(T_BG_MENU, T_BG_MENU);

	//TITLE
	Renderer::GetInstance()->PushImage(T_TITLE, T_TITLE);

	//BUTTONS
	Renderer::GetInstance()->PushImage(textureLevel1, T_LEVEL1);
	Renderer::GetInstance()->PushImage(textureLevel2, T_LEVEL2);
	Renderer::GetInstance()->PushImage(textureRanking, T_RANKING);
	Renderer::GetInstance()->PushImage(textureSound, T_SOUND);
	Renderer::GetInstance()->PushImage(textureExit, T_EXIT);

	Renderer::GetInstance()->Render();
}