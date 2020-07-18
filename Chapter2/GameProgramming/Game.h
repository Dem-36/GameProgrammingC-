#ifndef _GAME_H_
#define _GAME_H_

#include"SDL.h"

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
private:
	//SDL���쐬����E�B���h�E
	SDL_Window* mWindow;
	//Renderer�N���X
	SDL_Renderer* renderer;

	Uint32 ticksCount;

	bool mIsRunning;
};

#endif
