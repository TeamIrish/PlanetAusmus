#ifndef _MAP_H_
	#define _MAP_H_

#include "SDL/SDL.h"
#include <vector>
#include <string>

#include "Tile.h"
#include "Surface.h"
using namespace std;

class Map {

	public:

		SDL_Surface* Surf_Tileset;

		std::vector<Tile> TileList;

	public:

		Map();

	public:

		bool OnLoad(char*,string,int,int);
		void ValueToTile(int,int&,int&,int&);
		void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);

};

#endif
