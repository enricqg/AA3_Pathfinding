#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "SDL_SimpleApp.h"
#include "ScenePathFindingMouse.h"
#include "SceneBFS.h"
#include "SceneDijkstra.h"
#include "SceneGreedyBFS.h"
#include "SceneAStar.h"
#include "SceneVersus.h"


using namespace std;

int main(int argc, char ** argv)
{
	bool quit = false;
	SDL_Event event;
	
	SDL_SimpleApp *app = SDL_SimpleApp::Instance();

	Scene *curr_scene = new SceneBFS;
	app->setWindowTitle(curr_scene->getTitle());

	
	if (argc > 1) {
		cout << argv[1] << endl; 
		exit(0);
	}

	while (!quit)
	{
		// run app frame by frame
		event = app->run(curr_scene);

		/* Keyboard events */
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_1)
			{
				delete(curr_scene);
				curr_scene = new ScenePathFindingMouse;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_2)
			{
				delete(curr_scene);
				curr_scene = new SceneBFS;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_3)
			{
				delete(curr_scene);
				curr_scene = new SceneDijkstra;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_4)
			{
				delete(curr_scene);
				curr_scene = new SceneGreedyBFS;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_5)
			{
				delete(curr_scene);
				curr_scene = new SceneAStar;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_6)
			{
				delete(curr_scene);
				curr_scene = new SceneVersus;
				app->setWindowTitle(curr_scene->getTitle());
			}
			if ((event.key.keysym.scancode == SDL_SCANCODE_Q) || (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				quit = true;
			}
			if (event.key.keysym.scancode == SDL_SCANCODE_F)
			{
				app->setFullScreen();
			}
			break;
		case SDL_QUIT:
			quit = true;
			break;
		}

	}

	return 0;
}