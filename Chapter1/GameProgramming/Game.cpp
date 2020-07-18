#include "Game.h"

Game::Game()
	:mWindow(NULL), renderer(NULL), mIsRunning(true),
	ticksCount(0), paddleDir(0)
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

	//�e�l�̏�����
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

	//����
	paddleDir = 0;
	if (state[SDL_SCANCODE_W])
		paddleDir = -1;
	if (state[SDL_SCANCODE_S])
		paddleDir = 1;
}

/// <summary>
/// �Q�[���X�V
/// </summary>
void Game::UpdateGame()
{
	float deltaTime = DeltaTime();

	PaddleUpdate(deltaTime);
	BallUpdate(deltaTime);
}

//�o��(�`�掞�A���オ���_)
void Game::GenerateOutput()
{
	//�w�i�F�̐ݒ�
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

	//��ʂ̃N���A
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

void Game::PaddleUpdate(float deltaTime)
{
	if (paddleDir == 0)
		return;

	paddlePosition.y += paddleDir * 300.0f * deltaTime;

	//��ʊO�ɍs���Ȃ��悤�ɂ���
	if (paddlePosition.y < (paddleH / 2.0f + thickness))
		paddlePosition.y = paddleH / 2.0f + thickness;
	else if (paddlePosition.y > ((float)WINDOW_HEIGHT - paddleH / 2.0f - thickness))
		paddlePosition.y = (float)WINDOW_HEIGHT - paddleH / 2.0f - thickness;
}

void Game::BallUpdate(float deltaTime)
{
	//�ʒu�X�V
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
