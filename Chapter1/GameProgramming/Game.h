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
	//����������
	bool Initialize();
	//���[�v�A�X�V����
	void Update();
	//�I������
	void ShutDown();
private:
	//�Q�[�����[�v�Ɏg�p����w���p�[�֐�
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	float DeltaTime();
	void PaddleUpdate(float deltaTime);
	void BallUpdate(float deltaTime);
private:
	//SDL���쐬����E�B���h�E
	SDL_Window* mWindow;
	//Renderer�N���X
	SDL_Renderer* renderer;

	Uint32 ticksCount;

	bool mIsRunning;

	//�i�s����
	int paddleDir;
	//�̈ʒu
	Vector2 paddlePosition;
	//�{�[���̈ʒu
	Vector2 ballPosition;
	//�{�[���̉����x
	Vector2 ballVelocity;

	//����
	const int thickness = 15;
	//�̍���(�v���C���[��)
	const float paddleH = 100.0f;
};

#endif
