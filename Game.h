#ifndef GAME_H_
#define GAME_H_

#include "Client.h"
#include "Server.h"
#include "DataFromServerAndClient.h"
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game(void);
	~Game(void);

public:
	void run();

private:
	InitDataFromClient   _initDataFromClient;	//������ ������� ��� ������������� �������
	InitDataFromServer   _initDataFromServer;	//������ ������� ��� ������������� �������
	CommonDataFromClient _commonDataFromClient; //����� ������ �� �������, ������������ ������� ������ �������� �������� �����
	CommonDataFromServer _commonDataFromServer;	//����� ������ �� �������, ������������ ������� ������ �������� �������� �����

private:
	Server _server;
	Client _client;

private:
	struct GameState
	{
		int currentGameState;
		int previousGameState;
	};

	GameState _gameState;
};

#endif



