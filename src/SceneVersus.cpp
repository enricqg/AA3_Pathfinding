#include "SceneVersus.h"

using namespace std;

SceneVersus::SceneVersus()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	frameCounter = 0;

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent* agent = new Agent("../res/maze.csv", new AStar);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20, -20));
	agents.push_back(agent);

	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1, -1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(rand_cell));
	agents[0]->setCellPosition(rand_cell);

	Agent* agent2 = new Agent("../res/maze.csv", new AStar);
	agent2->loadSpriteTexture("../res/soldier.png", 4);
	agent2->setBehavior(new PathFollowing);
	agent2->setTarget(Vector2D(-20, -20));
	agents.push_back(agent2);

	// set agent position coords to the center of a random cell
	rand_cell = Vector2D(-1, -1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[1]->setPosition(maze->cell2pix(rand_cell));
	agents[1]->setCellPosition(rand_cell);

	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell) < 3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	coinPosition2 = Vector2D(-1, -1);
	while ((!maze->isValidCell(coinPosition2)) || (Vector2D::Distance(coinPosition2, rand_cell) < 3))
		coinPosition2 = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	agents[0]->CalculatePath(coinPosition, agents[1]->getCellPosition());
	agents[1]->CalculatePath(coinPosition2, agents[0]->getCellPosition());

}

SceneVersus::~SceneVersus()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneVersus::update(float dtime, SDL_Event* event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			/*Vector2D cell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(cell)) {
				agents[0]->addPathPoint(maze->cell2pix(cell));
			}*/

		}
		break;
	default:
		break;
	}

	

	agents[0]->update(dtime, event);

	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[0]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[0]->getPosition()) == coinPosition))
	{
		Vector2D lastCoinPos = coinPosition;

		agents[0]->setPosition(maze->cell2pix(coinPosition));
		agents[0]->setCellPosition(coinPosition);

		// set the coin in a random cell (but at least 3 cells far from the agent)
		coinPosition = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, lastCoinPos) < 3))
			coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

		agents[0]->CalculatePath(coinPosition, agents[1]->getCellPosition());

	}

	agents[1]->update(dtime, event);

	// if we have arrived to the coin, replace it in a random cell!
	if ((agents[1]->getCurrentTargetIndex() == -1) && (maze->pix2cell(agents[1]->getPosition()) == coinPosition2))
	{
		Vector2D lastCoinPos = coinPosition2;

		agents[1]->setPosition(maze->cell2pix(coinPosition2));
		agents[1]->setCellPosition(coinPosition2);

		// set the coin in a random cell (but at least 3 cells far from the agent)
		coinPosition2 = Vector2D(-1, -1);
		while ((!maze->isValidCell(coinPosition2)) || (Vector2D::Distance(coinPosition2, lastCoinPos) < 3))
			coinPosition2 = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

		agents[1]->CalculatePath(coinPosition2, agents[0]->getCellPosition());
	}

	frameCounter++;

	if (frameCounter==30) {
		frameCounter = 0;

		Vector2D agent0Pos = agents[0]->getPathPoint(agents[0]->getCurrentTargetIndex());
		Vector2D agent1Pos = agents[1]->getPathPoint(agents[1]->getCurrentTargetIndex());

		agents[0]->clearPath();
		agents[1]->clearPath();

		agents[0]->setCellPosition(maze->pix2cell(agent0Pos));
		agents[1]->setCellPosition(maze->pix2cell(agent1Pos));

		agents[0]->CalculatePath(coinPosition, agents[1]->getCellPosition());
		agents[1]->CalculatePath(coinPosition2, agents[0]->getCellPosition());
	}
}

void SceneVersus::draw()
{
	drawMaze();
	drawCoin(coinPosition);
	drawCoin(coinPosition2);

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw();
	agents[1]->draw();
}

const char* SceneVersus::getTitle()
{
	return "SDL Path Finding :: Pathfinfing Versus Demo";
}

void SceneVersus::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			if (!maze->isValidCell(Vector2D((float)i, (float)j)))
			{
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
				rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
				SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			}
			else {
				// Do not draw if it is not necessary (bg is already black)
			}


		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void SceneVersus::drawCoin(Vector2D _coinPosition)
{
	Vector2D coin_coords = maze->cell2pix(_coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = { (int)coin_coords.x - offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE };
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool SceneVersus::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface* image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

