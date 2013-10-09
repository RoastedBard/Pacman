#ifndef CLIENT_H_
#define CLIENT_H_

#include <SFML\Graphics.hpp>
#include "DataFromServerAndClient.h"

class Client
{
public:
	void readData(InitDataFromServer data);
	void readData(CommonDataFromServer data);
	void sendData(InitDataFromClient &data);
	void sendData(CommonDataFromClient &data);

public:
	void	   initialize();
	void	   update(sf::Time deltaTime);
	void	   render();
	void	   processEvents();
	void	   input();
	bool	   isWindowOpen() const;
	sf::Time   getFps() const;
	sf::Sprite getPacmanSprite() const;

public:
	Client(void);
	~Client(void);

private:
	int							  _screenHeight;
	int							  _screenWidth;
	int							  _mazeSize;
	std::vector<std::vector<int>> _abstractMaze;
	int							  _pacmanStartPoint[2];
	int							  _cellToRedraw[3];
	float						  _pacmanMovingVector[2];
	int							  _keyPressed;
	int							  _cellPixelSize;
	int							  _pacmanPixelSize;
	int							  _pillPixelSize;

private:
	sf::Time		 _fps;
	sf::RenderWindow _window;

	sf::Sprite  _pacmanSprite;
	sf::Texture _pacmanTexture;

	sf::Texture _wallTexture;

	sf::Texture _pillTexture;

	sf::Texture _pillOnTheFloorTexture;

	sf::Texture _nothingTexture;

	std::vector<std::vector<sf::Sprite>> _levelSprites;
};

#endif


