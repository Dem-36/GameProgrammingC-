#include "Game.h"

Game::Game()
	:mWindow(NULL), renderer(NULL), mIsRunning(true), ticksCount(0)
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
		WINDOW_WIDTH,                 //�E�B���h�E�̕�
		WINDOW_HEIGHT,                  //�E�B���h�E�̍���
		0);

	//�E�B���h�E�̐����ɐ���������
	if (!mWindow) {
		SDL_Log("�E�B���h�E�̐����Ɏ��s���܂���:%s", SDL_GetError());
		return false;
	}

	//�����_���[�̍쐬
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
	//�E�B���h�E�̔j��
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(renderer);
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

/// <summary>
/// �Q�[���X�V
/// </summary>
void Game::UpdateGame()
{
	float deltaTime = DeltaTime();
}

//�o��(�`�掞�A���オ���_)
void Game::GenerateOutput()
{
	//�w�i�F�̐ݒ�
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//��ʂ̃N���A
	SDL_RenderClear(renderer);
	//�t�����g�o�b�t�@�ƃo�b�N�o�b�t�@��؂�ւ���
	SDL_RenderPresent(renderer);
}

float Game::DeltaTime()
{
	//�O�̃t���[������16ms�o�߂���܂ő҂�
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + 16)) {}

	//�f���^�^�C�������߂�(���݂̃~���b-�ʒu�t���[���O�̃~���b)
	float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;

	//�f���^�^�C���̍ő�l�Œ�

	if (deltaTime > 0.05f)
		deltaTime = 0.05f;

	//���݂̃t���[���̃~���b�ۑ�
	ticksCount = SDL_GetTicks();

	return deltaTime;
}
