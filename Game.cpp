#include "Game.h"

#include <SFML\System.hpp>

Game::Game(void)
{	
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

			//Обработка пользовательского ввода
			_client.input();

			//Обработка пользовательского ввода
			_client.processEvents();

			//Отправка данных от клиента к серверу
			_client.sendData(_commonDataFromClient);
			_server.readData(_commonDataFromClient);

			_server.update();

			//Отправка данных от сервера к клиенту
			_server.sendData(_commonDataFromServer);
			_client.readData(_commonDataFromServer);
		
			//Обновление полей клиента
			_client.update(_client.getFps());
		}

		//Вывод изображения
		_client.render();
	}
}