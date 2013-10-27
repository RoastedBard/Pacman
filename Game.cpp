#include "Game.h"

#include <SFML\System.hpp>

Game::Game(void)
{	
	_gameState.currentGameState = GameStates::GAME_RUNNING;
}

Game::~Game(void)
{
}

void Game::run()
{
	//Отправка инициализационных данных от сервера к клиенту
	_server.sendData(_initDataFromServer);
	_client.readData(_initDataFromServer);

	//Инициализация полей клиента
	_client.createWindow();
	_client.initialize();

	//Отправка инициализационных данных от клиента к серверу
	_client.sendData(_initDataFromClient);
	_server.readData(_initDataFromClient);

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while(_client.isWindowOpen())
	{
		timeSinceLastUpdate += clock.restart();
	
		while(timeSinceLastUpdate > _client.getFps())
		{
			timeSinceLastUpdate -= _client.getFps();

			_gameState.previousGameState = _gameState.currentGameState;

			//Обработка пользовательского ввода
			_client.processEvents(_gameState.currentGameState);
			
			if(_gameState.previousGameState == GameStates::GAME_PAUSED && _gameState.currentGameState == GameStates::GAME_RUNNING)
			{
				_server.reset();
				_server.update(_gameState.currentGameState);

				//Отправка данных от сервера к клиенту
				_server.sendData(_initDataFromServer);
				_client.readData(_initDataFromServer);
				
				_client.initialize();
				_gameState.previousGameState = GameStates::GAME_RUNNING;
			}

			switch(_gameState.currentGameState)
			{
				case GameStates::GAME_RUNNING:
					//Обработка пользовательского ввода
					_client.input();

					//Отправка данных от клиента к серверу
					_client.sendData(_commonDataFromClient);
					_server.readData(_commonDataFromClient);

					_server.update(_gameState.currentGameState);

					//Отправка данных от сервера к клиенту
					_server.sendData(_commonDataFromServer);
					_client.readData(_commonDataFromServer);
		
					//Обновление полей клиента
					_client.update(_client.getFps());
				break;
			}
		}

		//Вывод изображения
		_client.render();
	}
}