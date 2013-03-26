// This class is going to define a single tile on the map

#ifndef _TILE_H_
	#define _TILE_H_

#include "Define.h"

enum {
	TILE_TYPE_NONE = 0,

	TILE_TYPE_TRAVERSABLE,
	TILE_TYPE_NON_TRAVERSABLE
};

class Tile {

	public:

		int TileXID;
		int TileYID;
		int TypeID;

		Tile();

};

#endif
