#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Scene.h"
#include "Agent.h"
#include "Seek.h"
#include "PathFollowing.h"
#include "Grid.h"

class SceneVersus :
	public Scene
{
public:
	SceneVersus();
	~SceneVersus();
	void update(float dtime, SDL_Event* event);
	void draw();
	const char* getTitle();
private:
	std::vector<Agent*> agents;
	Vector2D coinPosition, coinPosition2;

	int frameCounter;

	Grid* maze;
	bool draw_grid;

	void drawMaze();
	void drawCoin(Vector2D _coinPosition);
	SDL_Texture* background_texture;
	SDL_Texture* coin_texture;
	bool loadTextures(char* filename_bg, char* filename_coin);

};
