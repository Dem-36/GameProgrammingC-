#ifndef _GAME_H_
#define _GAME_H_

#include"SDL.h"
#include"Vector2.h"

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
	void PaddleUpdate(float deltaTime);
	void BallUpdate(float deltaTime);
private:
	//SDLが作成するウィンドウ
	SDL_Window* mWindow;
	//Rendererクラス
	SDL_Renderer* renderer;

	Uint32 ticksCount;

	bool mIsRunning;

	//進行方向
	int paddleDir;
	//板の位置
	Vector2 paddlePosition;
	//ボールの位置
	Vector2 ballPosition;
	//ボールの加速度
	Vector2 ballVelocity;

	//厚さ
	const int thickness = 15;
	//板の高さ(プレイヤーの)
	const float paddleH = 100.0f;
};

#endif
