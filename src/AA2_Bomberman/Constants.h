#pragma once
#include <SDL.h>
#include <map>
#include <unordered_map>

//SCREEN MEASUREMENTS
const int SCREEN_WIDTH{ 720 };
const int SCREEN_HEIGHT{ 704 };
const int VERTICAL_SCREEN_OFFSET{ 576 };

#pragma region PATHS

//FILES
const std::string P_RANKING = "../../res/files/ranking.bin";
const std::string P_CONFIG = "../../res/files/config.xml";

//GAME
const std::string P_BG_GAME = "../../res/img/bgGame.jpg";
const std::string P_ITEMS = "../../res/img/items.png";
const std::string P_EXPLOSION = "../../res/img/explosion.png";

//PLAYERS
const std::string P_PLAYER1 = "../../res/img/player1.png";
const std::string P_PLAYER2 = "../../res/img/player2.png";

//AUDIOS
const std::string P_ST_GAME = "../../res/au/game_theme.mp3";
const std::string P_ST_MENU = "../../res/au/menu.mp3";

//FONTS
const std::string P_GAME_OVER_FONT = "../../res/ttf/game_over.ttf";
const std::string P_SAIYAN_FONT = "../../res/ttf/saiyan.ttf";

#pragma endregion

#pragma region TIMERS

//TOTAL GAME TIME
const float GAME_TIMER{ 80.f }; //seconds

//BOMB TIMER
const float BOMB_TIMER{ 3.f };

//EXPLOSION TIMER
const float EXPLOSION_TIMER{ 1.f };

//IMMUNITY TIMER
const float IMMUNITY_TIMER{ 2.f };

//DEATH TIMER
const float DEATH_TIMER{ 1.f };

//POWER UP TIMER
const float POWER_UP_TIMER{ 10.f };


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
const std::string T_ROLLERS = "Rollers";
const std::string T_SHIELD = "Shield";
const std::string T_EXPLOSION = "Explosion";

//FONT
const std::string F_GAMEOVER = "FontGameOver";

//RANKING
const std::string T_RANKING_TITLE = "TxtRankingTitle";
const std::string T_RANK = "TxtRank";
const std::string T_SCORE = "TxtScore";
const std::string T_NAME = "TxtName";
const std::string T_PL_NAMES = "TxtPlayerNames";
const std::string T_PL_SCORES = "TxtPlayerScores";
const std::string T_PL_RANK = "TxtPlayerRank";

//MENU
const std::string T_TITLE = "TxtTitle";
const std::string T_LEVEL1 = "BtnLevel1";
const std::string T_LEVEL1_N = "BtnLevel1N";
const std::string T_LEVEL1_H = "BtnLevel1H";
const std::string T_LEVEL2 = "BtnLevel2";
const std::string T_LEVEL2_N = "BtnLevel2N";
const std::string T_LEVEL2_H = "BtnLevel2H";
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
const std::string T_LIVES_PL1 = "TxtLivesPl1";
const std::string T_LIVES_PL2 = "TxtLivesPl2";
const std::string T_GAME_END_PL1 = "TxtGameEndPl1";
const std::string T_GAME_END_PL2 = "TxtGameEndPl2";
const std::string T_GAME_END_DRAW = "TxtGameEndDraw";
const std::string T_GAME_END_DRAW_ENTER = "TxtGameEndDrawEnter";
const std::string T_ENTER_NAME = "TxtEnterName";
#pragma endregion