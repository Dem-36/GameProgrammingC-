#include "Game.h"

Game::Game()
	:mWindow(NULL), renderer(NULL), mIsRunning(true),
	ticksCount(0), paddleDir(0)
{
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	//初期化に成功したか
	if (sdlResult != 0) {
		SDL_Log("SDLを初期化できませんでした:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programing",    //タイトル
		100,                  //ウィンドウ左上のx座標
		100,                  //ウィンドウ左上のy座標
		WINDOW_WIDTH,                 //ウィンドウの幅
		WINDOW_HEIGHT,                  //ウィンドウの高さ
		0);

	//ウィンドウの生成に成功したか
	if (!mWindow) {
		SDL_Log("ウィンドウの生成に失敗しました:%s", SDL_GetError());
		return false;
	}

	//レンダラーの作成
	renderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	//各値の初期化
	paddlePosition.x = 10.0f;
	paddlePosition.y = (float)WINDOW_HEIGHT / 2.0f;
	ballPosition.x = (float)WINDOW_WIDTH / 2.0f;
	ballPosition.y = (float)WINDOW_HEIGHT / 2.0f;
	ballVelocity.x = -20.0f;
	ballVelocity.y = 23.0f;

	return true;
}

void Game::Update()
{
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ShutDown()
{
	//ウィンドウの破棄
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(renderer);
	//SDLの終了
	SDL_Quit();
}

//キー入力
void Game::ProcessInput()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		//イベントの種類
		switch (sdlEvent.type) {
			//×ボタンかショートカットで閉じたとき
		case SDL_QUIT:
			mIsRunning = false;
		}
	}
	//キーの状態を取得
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//ESCキーでも終了させる
	if (state[SDL_SCANCODE_ESCAPE])
		mIsRunning = false;

	//板操作
	paddleDir = 0;
	if (state[SDL_SCANCODE_W])
		paddleDir = -1;
	if (state[SDL_SCANCODE_S])
		paddleDir = 1;
}

/// <summary>
/// ゲーム更新
/// </summary>
void Game::UpdateGame()
{
	float deltaTime = DeltaTime();

	PaddleUpdate(deltaTime);
	BallUpdate(deltaTime);
}

//出力(描画時、左上が原点)
void Game::GenerateOutput()
{
	//背景色の設定
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//画面のクリア
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect wall{ 0,0,1024,thickness };
	SDL_RenderFillRect(renderer, &wall);

	wall.y = WINDOW_HEIGHT - thickness;
	SDL_RenderFillRect(renderer, &wall);

	wall.x = WINDOW_WIDTH - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = WINDOW_WIDTH;

	SDL_RenderFillRect(renderer, &wall);

	SDL_Rect paddle{
		static_cast<int>(paddlePosition.x),
		static_cast<int>(paddlePosition.y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(renderer, &paddle);
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_Rect ball{
		static_cast<int>(ballPosition.x - thickness / 2),
		static_cast<int>(ballPosition.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(renderer, &ball);

	//フロントバッファとバックバッファを切り替える
	SDL_RenderPresent(renderer);
}

float Game::DeltaTime()
{
	//前のフレームから16ms経過するまで待つ
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) {}

	//デルタタイムを求める(現在のミリ秒-位置フレーム前のミリ秒)
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

	//デルタタイムの最大値固定

	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	//現在のフレームのミリ秒保存
	ticksCount = SDL_GetTicks();

	return deltaTime;
}

void Game::PaddleUpdate(float deltaTime)
{
	if (paddleDir == 0)
		return;

	paddlePosition.y += paddleDir * 300.0f * deltaTime;

	//画面外に行かないようにする
	if (paddlePosition.y < (paddleH / 2.0f + thickness))
		paddlePosition.y = paddleH / 2.0f + thickness;
	else if (paddlePosition.y > ((float)WINDOW_HEIGHT - paddleH / 2.0f - thickness))
		paddlePosition.y = (float)WINDOW_HEIGHT - paddleH / 2.0f - thickness;
}

void Game::BallUpdate(float deltaTime)
{
	//位置更新
	ballPosition.x += ballVelocity.x * deltaTime;
	ballPosition.y += ballVelocity.y * deltaTime;

	float diff = paddlePosition.y - ballPosition.y;
	diff = (diff > 0.0f) ? diff : -diff;

	if (diff <= paddleH / 2.0f &&
		ballPosition.x <= 25.0f &&
		ballPosition.x >= 20.0f &&
		ballVelocity.x < 0.0f) {
		ballVelocity.x *= -1.0f;
	}
	else if (ballPosition.x <= 0.0f) {
		mIsRunning = false;
	}
	else if (ballPosition.x >= ((float)WINDOW_WIDTH - thickness - (thickness /2)) && ballVelocity.x > 0.0f) {
		ballVelocity.x *= -1.0f;
	}

	if (ballPosition.y <= thickness + (thickness / 2) && ballVelocity.y < 0.0f) {
		ballVelocity.y *= -1;
	}
	else if (ballPosition.y >= ((float)WINDOW_HEIGHT - thickness - (thickness / 2)) && ballVelocity.y > 0.0f) {
		ballVelocity.y *= -1;
	}
}
