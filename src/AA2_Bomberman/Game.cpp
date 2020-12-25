#include "Game.h"

Game::Game()
{
	gameScene = EGameScene::GAME;
	scene = new Menu();
	inputManager = new InputManager();
}

Game::~Game()
{
}

void Game::Run()
{
	while (gameScene != EGameScene::EXIT)
	{
		inputManager->Update();
		//UpdateInput();

		switch (gameScene)
		{
		case EGameScene::MENU:
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_PLAY:
				gameScene = EGameScene::GAME;
				delete scene;
				scene = new Gameplay();
				scene->Update();
				scene->Draw();
				break;
			case ESceneState::CLICK_RANKING:
				gameScene = EGameScene::RANKING;
				delete scene;
				scene = new Ranking();
				scene->Update();
				scene->Draw();
				break;
			}
			break;
		case EGameScene::GAME:
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::EXIT;
				delete scene;
				scene = new Menu();
				scene->Update();
				scene->Draw();
				break;
			}
			break;
		case EGameScene::RANKING:
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
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