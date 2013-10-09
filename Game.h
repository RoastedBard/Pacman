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
	InitDataFromClient   _initDataFromClient;	//Данные клиента для инициализации сервера
	InitDataFromServer   _initDataFromServer;	//Данные сервера для инициализации клиента
	CommonDataFromClient _commonDataFromClient; //Пакет данных от клиента, передающийся серверу каждую итерацию игрового цикла
	CommonDataFromServer _commonDataFromServer;	//Пакет данных от сервера, передающийся клиенту каждую итерацию игрового цикла

private:
	Server _server;
	Client _client;
};

#endif



