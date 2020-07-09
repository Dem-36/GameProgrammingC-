#ifndef _GAME_H_
#define _GAME_H_

#include"SDL.h"

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
private:
	//SDL���쐬����E�B���h�E
	SDL_Window* mWindow;
	bool mIsRunning;
};

#endif
