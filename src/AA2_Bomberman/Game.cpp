#include "Game.h"

Game::Game(InputManager input)
{
	gameScene = EGameScene::MENU;
	scene = new Menu();
	input.GetInput().SetScreenSize(VEC2(SCREEN_WIDTH, SCREEN_HEIGHT));
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
			#pragma region INPUTS
			//Input Control
			if (input.GetInput().JustPressed(EInputKeys::ESC)) gameScene = EGameScene::EXIT;
			//Button Collisions
			if (Collisions::ExistCollision(input.GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_PLAY)))
			{
				scene->SetTexturePlay(T_PLAY_H);  //SetTexturePlay(T_PLAY_H);
				if (input.GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { scene->SetSceneState(ESceneState::CLICK_PLAY); }
			}
			else
			{
				scene->SetTexturePlay(T_PLAY_N);
			}
			if (Collisions::ExistCollision(input.GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_RANKING)))
			{
				scene->SetTextureRanking(T_RANKING_H);
				if (input.GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { scene->SetSceneState(ESceneState::CLICK_RANKING); }
			}
			else
			{
				scene->SetTextureRanking(T_RANKING_N);
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

			if (Collisions::ExistCollision(input.GetInput().GetMouseCoords(), Renderer::GetInstance()->GetRect(T_EXIT)))
			{
				scene->SetTextureExit(T_EXIT_H);
				if (input.GetInput().JustPressed(EInputKeys::MOUSE_LEFT)) { gameScene = EGameScene::EXIT; }
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
				scene->Update(dir);
				scene->Draw();
				break;
			}
			break;
		case EGameScene::GAME:
			if (input.GetInput().IsPressed(EInputKeys::ESC)) scene->SetSceneState(ESceneState::CLICK_EXIT);
			
			if (input.GetInput().IsPressed(EInputKeys::LEFT)) {
				dir = EDirection::LEFT;
			}
			else if (input.GetInput().IsPressed(EInputKeys::RIGHT)) {
				dir = EDirection::RIGHT;
			}
			else if (input.GetInput().IsPressed(EInputKeys::UP)) {
				dir = EDirection::UP;
			}
			else if (input.GetInput().IsPressed(EInputKeys::DOWN)) {
				dir = EDirection::DOWN;
			}
			else
				dir = EDirection::NONE;

			//if (input.GetInput().IsPressed(EInputKeys::A)) {
			//	dir = EDirection::LEFT;
			//}
			//else if (input.GetInput().IsPressed(EInputKeys::D)) {
			//	dir = EDirection::RIGHT;
			//}
			//else if (input.GetInput().IsPressed(EInputKeys::W)) {
			//	dir = EDirection::UP;
			//}
			//else if (input.GetInput().IsPressed(EInputKeys::S)) {
			//	dir = EDirection::DOWN;
			//}
			//else
			//	dir = EDirection::NONE;

			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			default:
				scene->Update(dir);
				scene->Draw();
				break;
			}
			break;
		case EGameScene::RANKING:
			if (input.GetInput().IsPressed(EInputKeys::ESC)) scene->SetSceneState(ESceneState::CLICK_EXIT);
			switch (scene->GetSceneState())
			{
			case ESceneState::CLICK_EXIT:
				gameScene = EGameScene::MENU;
				delete scene;
				scene = new Menu();
				break;
			default:
				scene->Update(dir);
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