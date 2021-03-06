#include "Map.h"
#include "MapEditor.h"

Map::Map() {
	Surf_Tileset = NULL;
}

bool Map::OnLoad(char* File, string filenameLoad) {
	TileList.clear();

	  FILE* FileHandle = fopen(filenameLoad.c_str(),"r");

		if(FileHandle == NULL) {
		  cout<<"Error opening file."<<endl;
			return false;
		}

		Tile tempTile;
		int tempTileValue;
		for(int Y=0;Y<MAP_HEIGHT;Y++) {
			for(int X=0;X<MAP_WIDTH;X++) {
				fscanf(FileHandle,"%d ",&tempTileValue);
				ValueToTile(tempTileValue,tempTile.TileXID,tempTile.TileYID,tempTile.TypeID);
				TileList.push_back(tempTile);
			}
			fscanf(FileHandle, " \n");
		}

		fclose(FileHandle);

	return true;
}

void Map::ValueToTile(int value,int &tileX,int &tileY,int &type){
  if(value>95) value=95;
  if(value<0) value=0;
  tileX = MapEditor::tileX[value/6];
  tileY = MapEditor::tileY[value/6];
  type = MapEditor::tileTypes[value/6]; // assigns tile type non-traversable or traversable
}

void Map::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if(Surf_Tileset == NULL){
		return;
	}

	int ID = 0;

	for(int Y=0;Y<MAP_HEIGHT;Y++) {
		for(int X=0;X<MAP_WIDTH;X++) {

			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);

			int TilesetX = (TileList[ID].TileXID) * TILE_SIZE;
			int TilesetY = (TileList[ID].TileYID) * TILE_SIZE;

			// This is placing each tile on the display, 
			Surface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			
			ID++;
		}
	}
}


