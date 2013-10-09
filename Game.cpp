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
	//�������� ����������������� ������ �� ������� � �������
	_server.sendData(_initDataFromServer);
	_client.readData(_initDataFromServer);

	//������������� ����� �������
	_client.initialize();

	//�������� ����������������� ������ �� ������� � �������
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

			//��������� ����������������� �����
			_client.input();

			//��������� ����������������� �����
			_client.processEvents();

			//�������� ������ �� ������� � �������
			_client.sendData(_commonDataFromClient);
			_server.readData(_commonDataFromClient);

			_server.update();

			//�������� ������ �� ������� � �������
			_server.sendData(_commonDataFromServer);
			_client.readData(_commonDataFromServer);
		
			//���������� ����� �������
			_client.update(_client.getFps());
		}

		//����� �����������
		_client.render();
	}
}