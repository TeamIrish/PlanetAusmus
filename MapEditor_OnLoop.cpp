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
	if(Camera::CameraControl.MovingLeft == true){
		Camera::CameraControl.OnMove(moveSize,0);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(-moveSize,0);
	}
	if(Camera::CameraControl.MovingRight == true){
		Camera::CameraControl.OnMove(-moveSize,0);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(moveSize,0);
	}
	if(Camera::CameraControl.MovingUp == true){
		Camera::CameraControl.OnMove(0,moveSize);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(0,-moveSize);
	}
	if(Camera::CameraControl.MovingDown == true){
		Camera::CameraControl.OnMove(0,-moveSize);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(0,moveSize);
	}

	// Check to make sure that the camera didn't move out of bounds - if so, change map view
	Camera::CameraControl.CheckBounds();

	// Change player character state
	Camera::CameraControl.AnimateCharacter();

	// Check for collision with enemies
	CheckEnemyCollisions();

	// Check to see if player is dead
	if(playerHealth < 1) Running = false;

	// Decide whether to spawn enemy
	if(numEnemies<6 && rand()%100<1) SpawnEnemy();

	// Move entities
	for(int i=0;i<EntityList.size();i++) EntityList[i]->OnLoop();

	// De-spawn enemies if too far from player
	DeSpawnEnemies();
		
}


//==============================================================================
//
bool MapEditor::CheckTileCollision(int centerX,int centerY,int width,int height){
  int tileX,tileY,ID;

  for(int i=0;i<4;i++){ // check all four corners of the sprite
	int mapID = 0;
	tileX = (centerX + pow(-1,i%2)*width*.3) / TILE_SIZE;
	tileY = (centerY + (i/2)*height*.3) / TILE_SIZE;  // only check bottom half of sprite, to give 3D effect

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
  int spawnX,spawnY;

  // generate random coordinates onscreen
  int X = -Camera::CameraControl.GetX()+WWIDTH/2+pow(-1,rand()%2)*(rand()%(WWIDTH/3));
  int Y = -Camera::CameraControl.GetY()+WHEIGHT/2+pow(-1,rand()%2)*(rand()%(WHEIGHT/3));

  // move coordinates to somewhere offscreen
  while(1){
    spawnX = X;
    spawnY = Y;
    int random=rand()%3;
    if(random>0) spawnX += pow(-1,rand()%2)*WWIDTH;
    if(random<2) spawnY += pow(-1,rand()%2)*WHEIGHT;

    // ensure that chosen tile is not nontraversable
    int pixelX = X - Camera::CameraControl.GetX();
    int pixelY = Y - Camera::CameraControl.GetY();
    if(!CheckTileCollision(pixelX,pixelY,32,32)) break;
  }

  // instantiate enemy and add to list
  Entity* tmp = new Enemy(typestring,32,32,spawnX,spawnY,2);
  tmp->setType(ENTITY_TYPE_ENEMY);
  EntityList.push_back(tmp);

  numEnemies++;
  if(debug) cout<<"Entity (Enemy) Spawned: "<<spawnX/TILE_SIZE<<","<<spawnY/TILE_SIZE<<endl;
}


//==============================================================================
//
bool MapEditor::CheckEnemyCollisions(){
  int charX = -Camera::CameraControl.GetX()+WWIDTH/2;
  int charY = -Camera::CameraControl.GetY()+WHEIGHT/2;

  for(int i=0;i<EntityList.size();i++){
		if(EntityList[i]->getType() == ENTITY_TYPE_ENEMY){
    	int Xdist = (CHARACTER_W*.9 + EntityList[i]->getW())/2;
    	int Ydist = (CHARACTER_H*.9 + EntityList[i]->getH())/2;
    	if(abs(charX-EntityList[i]->getX())<Xdist && abs(charY-EntityList[i]->getY())<Ydist){
				EntityList[i]->OnCleanup();
	  		delete EntityList[i];
				EntityList.erase(EntityList.begin() + i);
				playerHealth--;
				return true;
			}
		}  
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
      if(debug)	cout<<"Entity "<<i<<" despawned."<<endl;
      EntityList[i]->OnCleanup();
      EntityList.erase(EntityList.begin()+i);
      numEnemies--;
    }
  }
}

void MapEditor::AddBullet(){
  Bullet * tmp = new Bullet();
  EntityList.push_back(tmp);
}
