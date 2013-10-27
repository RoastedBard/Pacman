#ifndef CLIENT_H_
#define CLIENT_H_

#include <SFML\Graphics.hpp>
#include "DataFromServerAndClient.h"
#include "Core\Vector2.h"

class Client
{
public:
	void readData(InitDataFromServer data);
	void readData(CommonDataFromServer data);
	void sendData(InitDataFromClient &data);
	void sendData(CommonDataFromClient &data);

public:
	void	   initialize();
	void	   createWindow();
	void	   update(sf::Time deltaTime);
	void	   render();
	void	   processEvents(int &gameState);
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
	Vector2<int>				  _pacmanStartPoint;
	std::vector<Vector2<int>>	  _ghostsStartPoint;
	int							  _cellToRedraw[3];
	Vector2<float>				  _pacmanMovingVector;
	vector<Vector2<float>>		  _ghostsMovingVectors;
	int							  _keyPressed;
	int							  _cellPixelSize;
	int							  _pacmanPixelSize;
	int							  _pillPixelSize;

private:
	sf::Time		 _fps;
	sf::RenderWindow _window;

	sf::Sprite  _pacmanSprite;
	sf::Texture _pacmanTexture;

	sf::Texture _ghostTexture;

	sf::Texture _wallTexture;

	sf::Texture _pillTexture;

	sf::Texture _pillOnTheFloorTexture;

	sf::Texture _nothingTexture;

	std::vector<sf::Sprite> _ghostSprites;

	std::vector<std::vector<sf::Sprite>> _levelSprites;
};

#endif


