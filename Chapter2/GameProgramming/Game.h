#ifndef _GAME_H_
#define _GAME_H_

#include"SDL.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768

class Game
{
public:
	Game();
	//初期化処理
	bool Initialize();
	//ループ、更新処理
	void Update();
	//終了処理
	void ShutDown();
private:
	//ゲームループに使用するヘルパー関数
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	float DeltaTime();
private:
	//SDLが作成するウィンドウ
	SDL_Window* mWindow;
	//Rendererクラス
	SDL_Renderer* renderer;

	Uint32 ticksCount;

	bool mIsRunning;
};

#endif
