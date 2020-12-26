#include "Game.h"

Game::Game()
{
	gameScene = EGameScene::MENU;
	scene = new Menu();
}

Game::~Game()
{
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
			if (input.GetInput().JustPressed(EInputKeys::ESC)) gameScene = EGameScene::EXIT;
			if (input.GetInput().IsPressed(EInputKeys::A)) scene->SetSceneState(ESceneState::CLICK_PLAY);
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
			if (input.GetInput().IsPressed(EInputKeys::ESC)) scene->SetSceneState(ESceneState::CLICK_EXIT);

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
			if (input.GetInput().IsPressed(EInputKeys::ESC)) gameScene = EGameScene::MENU;
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
	}
}