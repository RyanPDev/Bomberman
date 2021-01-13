#pragma once
#include <SDL.h>
#include <map>
#include <unordered_map>

//SCREEN MEASUREMENTS
const int SCREEN_WIDTH{ 720 };
const int SCREEN_HEIGHT{ 704 };
const int VERTICAL_SCREEN_OFFSET{ 576 };

#pragma region TIMERS

//TOTAL GAME TIME
const float GAME_TIMER{ 500.f }; //seconds

//BOMB TIMER
const float BOMB_TIMER{ 3.f };

//EXPLOSION TIMER
const float EXPLOSION_TIMER{ 1.f };

//IMMUNITY TIMER
const float IMMUNITY_TIMER{ 2.f };

//DEATH TIMER
const float DEATH_TIMER{ 1.f };

#pragma endregion

//FPS
const int FPS{ 60 };

//SPRITE AND TILE SIZE)
const int FRAME_SIZE{48};

//MAP FOR TEXTURES AND RECTS
using MTextures = std::unordered_map<std::string, SDL_Texture*>;
using MRects = std::unordered_map<std::string, SDL_Rect>;

#pragma region TEXTURES/RECTS
const std::string T_BG_MENU = "BackgroundMenu";
const std::string T_BG_INGAME = "BackgroundInGame";
const std::string T_BG_RANKING = "BackgroundRanking";
const std::string T_CURSOR = "Cursor";
const std::string T_PLAYER1 = "Player0";
const std::string T_PLAYER2 = "Player1";
const std::string T_PLAYERS_POS = "PlayersPos";
const std::string T_WALL = "Wall";
const std::string T_DESTRUCTIBLE_WALL = "DestructibleWall";
const std::string T_DESTROYED_WALL = "DestroyedWall";
const std::string T_BOMB = "Bomb";
const std::string T_EXPLOSION = "Explosion";

//FONT
const std::string F_GAMEOVER = "FontGameOver";

//MENU
const std::string T_TITLE = "TxtTitle";
const std::string T_PLAY = "BtnPlay";
const std::string T_PLAY_N = "BtnPlayN";
const std::string T_PLAY_H = "BtnPlayH";
const std::string T_RANKING = "BtnRanking";
const std::string T_RANKING_N = "BtnRankingN";
const std::string T_RANKING_H = "BtnRankingH";
const std::string T_SOUND = "BtnSound";
const std::string T_SOUND_ON_N = "BtnSoundOnN";
const std::string T_SOUND_ON_H = "BtnSoundOnH";
const std::string T_SOUND_OFF_N = "BtnSoundOffN";
const std::string T_SOUND_OFF_H = "BtnSoundOffH";
const std::string T_EXIT = "BtnExit";
const std::string T_EXIT_N = "BtnExitN";
const std::string T_EXIT_H = "BtnExitH";

//GAME
const std::string T_TIME = "TxtTime";
const std::string T_SC_PL1 = "TxtScPl1";
const std::string T_SC_PL2 = "TxtScPl2";
const std::string T_SC_NUM_PL1 = "TxtScNumPl1";
const std::string T_SC_NUM_PL2 = "TxtScNumPl2";
const std::string T_LIVES_PL1 = "LivesPl1";
const std::string T_LIVES_PL2 = "LivesPl2";
#pragma endregion