#include "Game.h"

Game::Game(InputData input)
{
	gameScene = EGameScene::MENU;
	scene = new Menu();
	int a = input.GetScreenSize()->x;
	input.SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));
	int b = input.GetScreenSize()->x;
}

Game::~Game()
{
	delete scene;
}

void Game::Run(InputManager input)
{
	while (gameScene != EGameScene::EXIT)
	{
		input.Update();

		if (input.GetInput().IsPressed(EInputKeys::QUIT)) gameScene = EGameScene::EXIT;

		switch (gameScene)
		{
		case EGameScene::MENU:
			//Input Control
			if (input.GetInput().JustPressed(EInputKeys::ESC)) gameScene = EGameScene::EXIT;
			//Button Collisions
			if (Collisions::ExistCollision(input.GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_PLAY)))
			{

				if (input.GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { scene->SetSceneState(ESceneState::CLICK_PLAY); }
			}
			if (Collisions::ExistCollision(input.GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_EXIT)))
			{
				
				if (input.GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { gameScene = EGameScene::EXIT; }
			}
			if (Collisions::ExistCollision(input.GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_SOUND)))
			{
				if (input.GetInput().JustPressed(EInputKeys::MOUSE_LEFT))
				{
					if (!AudioManager::GetInstance()->PausedMusic())
					{
						AudioManager::GetInstance()->PauseMusic();
					}
					else AudioManager::GetInstance()->ResumeMusic();
				}
			}

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
				scene->Update(input);
				scene->Draw();
				break;
			}
			break;
		case EGameScene::GAME:
			if (input.GetInput().IsPressed(EInputKeys::ESC)) scene->SetSceneState(ESceneState::CLICK_EXIT);

			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			default:
				scene->Update(input);
				scene->Draw();
				break;
			}
			break;
		case EGameScene::RANKING:
			if (input.GetInput().IsPressed(EInputKeys::ESC)) gameScene = EGameScene::MENU;
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			default:
				scene->Update(input);
				scene->Draw();
				break;
			}
			break;
		default:
			break;
		}
		//---FRAME CONTROL---
		input.GetInput().UpdateDeltaTime();
	}
}