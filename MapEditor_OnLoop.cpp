/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnLoop.cpp

This is the implementation file for the OnLoop() function of the MapEditor class. This function is called
every iteration through the game loop and makes appropriate changes to game data.
*/

#include "MapEditor.h"

//==============================================================================
//
void MapEditor::OnLoop() {
	
	// Move camera
	int moveSize = 5;
	if(Camera::CameraControl.MovingLeft == true){
		Camera::CameraControl.OnMove(moveSize,0);
		if(!debug && CheckCollision()) Camera::CameraControl.OnMove(-moveSize,0);
	}
	if(Camera::CameraControl.MovingRight == true){
		Camera::CameraControl.OnMove(-moveSize,0);
		if(!debug && CheckCollision()) Camera::CameraControl.OnMove(moveSize,0);
	}
	if(Camera::CameraControl.MovingUp == true){
		Camera::CameraControl.OnMove(0,moveSize);
		if(!debug && CheckCollision()) Camera::CameraControl.OnMove(0,-moveSize);
	}
	if(Camera::CameraControl.MovingDown == true){
		Camera::CameraControl.OnMove(0,-moveSize);
		if(!debug && CheckCollision()) Camera::CameraControl.OnMove(0,moveSize);
	}

	// Check to make sure that the camera didn't move out of bounds - if so, change map view
	Camera::CameraControl.CheckBounds();

	// Change player character state
	Camera::CameraControl.AnimateCharacter();

	// Check for collision with enemies
	if(!debug && CheckEnemyCollisions()) Running=false;

	// Decide whether to spawn enemy
	if(rand()%100<1 && EntityList.size()<6) SpawnEnemy();

	// De-spawn enemies if too far from player
	DeSpawnEnemies();
		
}


//==============================================================================
//
bool MapEditor::CheckCollision(){

  int centerX,centerY,tileX,tileY,ID;
  centerX = -(Camera::CameraControl.GetX() - WWIDTH/2);
  centerY = -(Camera::CameraControl.GetY() - WHEIGHT/2);

  for(int i=0;i<4;i++){ // check all four corners of the sprite
	int mapID = 0;
	tileX = (centerX + pow(-1,i%2)*CHARACTER_W*.4) / TILE_SIZE;
	tileY = (centerY + (i/2)*CHARACTER_H*.25) / TILE_SIZE;  // only check bottom half of sprite, to give 3D effect

	if(tileX >= MAP_WIDTH){
		tileX -= MAP_WIDTH;
		mapID += 1;
	}
	if(tileY >= MAP_HEIGHT){
		tileY -= MAP_HEIGHT;
		mapID += 2;
	}

	//cout<<"Tile "<<X<<","<<Y<<": "<<"(mapID = "<<mapID<<"): ";
	ID = tileY*MAP_WIDTH + tileX;

	if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_TRAVERSABLE){
		//cout<<"Traversable"<<endl;
		continue;
	}else if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_NON_TRAVERSABLE){
		//cout<<"Non-traversable"<<endl;
		return true;
	}else{
		//cout<<"Other."<<endl;
		continue;
	}
  }
  return false;
}


//==============================================================================
//
void MapEditor::SpawnEnemy(){
  string typestring = "golem.png";
  // generate random coordinates onscreen
  int spawnX = -Camera::CameraControl.GetX()+WWIDTH/2+pow(-1,rand()%2)*(rand()%(WWIDTH/3));
  int spawnY = -Camera::CameraControl.GetY()+WHEIGHT/2+pow(-1,rand()%2)*(rand()%(WHEIGHT/3));
  // move coordinates to somewhere offscreen
  int random=rand()%3;
  if(random>0) spawnX += pow(-1,rand()%2)*WWIDTH;
  if(random<2) spawnY += pow(-1,rand()%2)*WHEIGHT;

  // instantiate enemy and add to list
  Entity* tmp = new Entity(typestring,32,32,spawnX,spawnY);
  EntityList.push_back(tmp);
  cout<<"Entity (Enemy) Spawned: "<<spawnX/TILE_SIZE<<","<<spawnY/TILE_SIZE<<endl;
}


//==============================================================================
//
bool MapEditor::CheckEnemyCollisions(){
  int charX = -Camera::CameraControl.GetX()+WWIDTH/2;
  int charY = -Camera::CameraControl.GetY()+WHEIGHT/2;

  for(int i=0;i<EntityList.size();i++){
    int Xdist = (CHARACTER_W*.9 + EntityList[i]->getW())/2;
    int Ydist = (CHARACTER_H*.9 + EntityList[i]->getH())/2;
    if(abs(charX-EntityList[i]->getX())<Xdist && abs(charY-EntityList[i]->getY())<Ydist) return true;
  }
  return false;
}


//==============================================================================
//
void MapEditor::DeSpawnEnemies(){
  for(int i=0;i<EntityList.size();i++){
    int distX = EntityList[i]->getX() + Camera::CameraControl.GetX();
    int distY = EntityList[i]->getY() + Camera::CameraControl.GetY();
    double dist = sqrt(distX*distX+distY*distY);

    if(dist > 1280){
      EntityList[i]->OnCleanup();
      EntityList.erase(EntityList.begin()+i);
      if(debug) cout<<"Enemy "<<i<<" despawned."<<endl;
    }
  }
}
