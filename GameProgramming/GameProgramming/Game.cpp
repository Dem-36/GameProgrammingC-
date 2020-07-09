#include "Game.h"

Game::Game()
	:mWindow(),mIsRunning(true)
{
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	//�������ɐ���������
	if (sdlResult != 0) {
		SDL_Log("SDL���������ł��܂���ł���:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programing",    //�^�C�g��
		100,                  //�E�B���h�E�����x���W
		100,                  //�E�B���h�E�����y���W
		1024,                 //�E�B���h�E�̕�
		768,                  //�E�B���h�E�̍���
		0);

	//�E�B���h�E�̐����ɐ���������
	if (!mWindow) {
		SDL_Log("�E�B���h�E�̐����Ɏ��s���܂���:%s", SDL_GetError());
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
	//�E�B���h�E�̔j��
	SDL_DestroyWindow(mWindow);
	//SDL�̏I��
	SDL_Quit();
}

//�L�[����
void Game::ProcessInput()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		//�C�x���g�̎��
		switch (sdlEvent.type) {
			//�~�{�^�����V���[�g�J�b�g�ŕ����Ƃ�
		case SDL_QUIT:
			mIsRunning = false;
		}
	}
	//�L�[�̏�Ԃ��擾
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//ESC�L�[�ł��I��������
	if (state[SDL_SCANCODE_ESCAPE])
		mIsRunning = false;
}

void Game::UpdateGame()
{
}

void Game::GenerateOutput()
{
}
