#include "Game.h"

Game::Game()
	:mWindow(NULL), renderer(NULL), mIsRunning(true), ticksCount(0)
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
}

/// <summary>
/// ゲーム更新
/// </summary>
void Game::UpdateGame()
{
	float deltaTime = DeltaTime();
}

//出力(描画時、左上が原点)
void Game::GenerateOutput()
{
	//背景色の設定
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//画面のクリア
	SDL_RenderClear(renderer);
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
