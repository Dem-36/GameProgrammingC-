#include "Game.h"

Game::Game()
	:mWindow(),mIsRunning(true)
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
		1024,                 //ウィンドウの幅
		768,                  //ウィンドウの高さ
		0);

	//ウィンドウの生成に成功したか
	if (!mWindow) {
		SDL_Log("ウィンドウの生成に失敗しました:%s", SDL_GetError());
		return false;
	}

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

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
