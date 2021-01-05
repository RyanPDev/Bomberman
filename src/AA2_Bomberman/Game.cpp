#include "Game.h"

Game::Game()
{
	gameScene = EGameScene::MENU;
	scene = new Menu();
	//InputManager::GetInstance()->GetInput().SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));
}

Game::~Game()
{
	delete scene;
}

void Game::Run()
{
	while (gameScene != EGameScene::EXIT)
	{
		InputManager::GetInstance()->Update();

		if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::QUIT)) gameScene = EGameScene::EXIT;

		switch (gameScene)
		{
		case EGameScene::MENU:
			#pragma region INPUTS
			//Input Control
			if (InputManager::GetInstance()->GetInput().JustPressed(EInputKeys::ESC)) gameScene = EGameScene::EXIT;
			//Button Collisions
			if (Collisions::ExistCollision(InputManager::GetInstance()->GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_PLAY)))
			{
				scene->SetTexturePlay(T_PLAY_H);  //SetTexturePlay(T_PLAY_H);
				if (InputManager::GetInstance()->GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { scene->SetSceneState(ESceneState::CLICK_PLAY); }
			}
			else
			{
				scene->SetTexturePlay(T_PLAY_N);
			}
			if (Collisions::ExistCollision(InputManager::GetInstance()->GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_RANKING)))
			{
				scene->SetTextureRanking(T_RANKING_H);
				if (InputManager::GetInstance()->GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { scene->SetSceneState(ESceneState::CLICK_RANKING); }
			}
			else
			{
				scene->SetTextureRanking(T_RANKING_N);
			}
			if (Collisions::ExistCollision(InputManager::GetInstance()->GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_SOUND)))
			{
				if (InputManager::GetInstance()->GetInput().JustPressed(EInputKeys::MOUSE_LEFT))
				{
					if (!AudioManager::GetInstance()->PausedMusic())
					{
						AudioManager::GetInstance()->PauseMusic();
					}
					else AudioManager::GetInstance()->ResumeMusic();
				}
				if (AudioManager::GetInstance()->PausedMusic()) {
					scene->SetTextureSound(T_SOUND_OFF_H);
				}
				else {
					scene->SetTextureSound(T_SOUND_ON_H);
				}
			}
			else {
				if (AudioManager::GetInstance()->PausedMusic()) {
					scene->SetTextureSound(T_SOUND_OFF_N);
				}
				else {
					scene->SetTextureSound(T_SOUND_ON_N);
				}
			}

			if (Collisions::ExistCollision(InputManager::GetInstance()->GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_EXIT)))
			{
				scene->SetTextureExit(T_EXIT_H);
				if (InputManager::GetInstance()->GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { gameScene = EGameScene::EXIT; }
			}
			else
			{
				scene->SetTextureExit(T_EXIT_N);
			}
			#pragma endregion
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_PLAY:
				gameScene = EGameScene::GAME;
				delete scene;
				scene = new Gameplay();
				break;
			case ESceneState::CLICK_RANKING:
				gameScene = EGameScene::RANKING;
				delete scene;
				scene = new Ranking();
				break;
			default:
				scene->Update();
				scene->Draw();
				break;
			}
			break;
		case EGameScene::GAME:
			if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::ESC)) scene->SetSceneState(ESceneState::CLICK_EXIT);
			
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			default:
				scene->Update();
				scene->Draw();
				break;
			}
			break;
		case EGameScene::RANKING:
			if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::ESC)) scene->SetSceneState(ESceneState::CLICK_EXIT);
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			default:
				scene->Update();
				scene->Draw();
				break;
			}
			break;
		default:
			break;
		}
		//---FRAME CONTROL---
		InputManager::GetInstance()->GetInput().UpdateDeltaTime();
	}
}