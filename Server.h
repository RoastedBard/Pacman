#ifndef SERVER_H_
#define SERVER_H_

#include "Core\Pacman.h"
#include "Core\Maze.h"
#include "Core\Logic.h"
#include "Core\Ghost.h"
#include "Core\Enums.h"
#include "DataFromServerAndClient.h"

class Server
{
public:
	void readData(InitDataFromClient data);
	void readData(CommonDataFromClient data);
	void sendData(InitDataFromServer &data);
	void sendData(CommonDataFromServer &data);

public:
	void   update(int &gameState);
	void   processInput();			
	void   loadLevel(const char *filename);
	void   reset();

public:
	Server(void);
	~Server(void);

private:
	int _keyPressed;

private:
	Pacman _pacman;
	Maze   _maze;
	std::vector<Ghost>  _ghosts;
};

#endif



