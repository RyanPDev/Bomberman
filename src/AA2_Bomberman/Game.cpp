#include "Game.h"

Game::Game()
{
	gameScene = EGameScene::MENU;
	scene = new Menu();
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
		_input = &InputManager::GetInstance()->GetInput();
		if (_input->IsPressed(EInputKeys::QUIT)) gameScene = EGameScene::EXIT;

		switch (gameScene)
		{
		case EGameScene::MENU:		
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
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::EXIT;
				break;
			case ESceneState::RUNNING:
				scene->Update(_input);
				scene->Draw();
				break;
			}
			break;
		case EGameScene::GAME:
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			case ESceneState::RUNNING:
				scene->Update(_input);
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
				break;
			case ESceneState::RUNNING:
				scene->Update(_input);
				scene->Draw();
				break;
			}
			break;
		default:
			break;
		}
		//---FRAME CONTROL---
		_input->UpdateDeltaTime();
	}
}