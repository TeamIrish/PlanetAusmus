/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnLoop.cpp

This is the implementation file for the OnLoop() function of the MapEditor class. This function is called
every iteration through the game loop and makes appropriate changes to game data.
*/

#include "MapEditor.h"

//==============================================================================
//
void MapEditor::OnLoop()
{
	// Move camera
	if(Camera::CameraControl.MovingLeft == true){ // the camera is moving left
		Camera::CameraControl.OnMove(moveSize,0);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(-moveSize,0);
	}

	if(Camera::CameraControl.MovingRight == true){ // the camera is moving right
		Camera::CameraControl.OnMove(-moveSize,0);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(moveSize,0);
	}

	if(Camera::CameraControl.MovingUp == true){ // the camera is moving up
		Camera::CameraControl.OnMove(0,moveSize);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(0,-moveSize);
	}

	if(Camera::CameraControl.MovingDown == true){ // the camera is moving down
		Camera::CameraControl.OnMove(0,-moveSize);
		if(!debug && CheckTileCollision()) Camera::CameraControl.OnMove(0,moveSize);
	}

	// Check to make sure that the camera didn't move out of bounds - if so, change map view
	Camera::CameraControl.CheckBounds();

	// Change player character state
	Camera::CameraControl.AnimateCharacter();

	// Check for collision between player character and Entities
	CheckEntityCollisions();

	// Check for collision between bullets and enemies
	CheckBulletCollision();

	// Check to see if player is dead
	if(playerHealth < 1) Running = false;

	// Decide whether to spawn enemy
	if(numEnemies<6 && rand()%100<1){
	  SpawnEnemy();
	}

	// De-spawn entities if too far from player or marked for despawning
	DeSpawnEntities();

	// Move entities
	for(int i=0;i<EntityList.size();i++) EntityList[i]->OnLoop();
}


//==============================================================================
//
// arguments default to the center of the screen and the size of the player character
bool MapEditor::CheckTileCollision(int centerX, int centerY, int width, int height)
{  
  int tileX, tileY, ID;
	
	// check all four corners of the sprite
  for(int i = 0; i < 4; i++) { 
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
	
		if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_TRAVERSABLE) {
			//cout<<"Traversable"<<endl;
			continue;
		}
		else if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_NON_TRAVERSABLE) {
			//cout<<"Non-traversable"<<endl;
			return true;
		}
		else {
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
  int spawnX,spawnY,attempts=0;

  // generate random coordinates onscreen
  int X = -Camera::CameraControl.GetX()+WWIDTH/2+pow(-1,rand()%2)*(rand()%(WWIDTH/3));
  int Y = -Camera::CameraControl.GetY()+WHEIGHT/2+pow(-1,rand()%2)*(rand()%(WHEIGHT/3));

  // move coordinates to somewhere offscreen
  while(attempts<100){
    spawnX = X;
    spawnY = Y;
    int random=rand()%3;
    if(random>0) spawnX += pow(-1,rand()%2)*WWIDTH;
    if(random<2) spawnY += pow(-1,rand()%2)*WHEIGHT;

    // ensure that chosen tile is not nontraversable
    if(!CheckTileCollision(spawnX,spawnY,32,32)) break;
    attempts++;
  }

  if(attempts<100){
    // instantiate enemy and add to list
    Entity* tmp = new Enemy(typestring,32,32,spawnX,spawnY,2);
    tmp->setType(ENTITY_TYPE_ENEMY);
    EntityList.push_back(tmp);

    numEnemies++;
    if(debug) cout<<"Entity (Enemy) Spawned: "<<spawnX/TILE_SIZE<<","<<spawnY/TILE_SIZE<<endl;
  }
}


//==============================================================================
//  Checks collisions between enemies and hearts (can include all items in future)
//
bool MapEditor::CheckEntityCollisions(){
  int charX = -Camera::CameraControl.GetX()+WWIDTH/2;
  int charY = -Camera::CameraControl.GetY()+WHEIGHT/2;

  for(int i=0;i<EntityList.size();i++){
    int Xdist = (CHARACTER_W*.9 + EntityList[i]->getW())/2;
    int Ydist = (CHARACTER_H*.9 + EntityList[i]->getH())/2;
		if(EntityList[i]->getType() != ENTITY_TYPE_BULLET){
			if( abs(charX - EntityList[i]->getX()) < Xdist && abs(charY - EntityList[i]->getY()) < Ydist ){
				if(EntityList[i]->getType() == ENTITY_TYPE_ENEMY){
					playerHealth-=2;
					numEnemies--;
				}
				if(EntityList[i]->getType() == ENTITY_TYPE_HEART){
					if(playerHealth < 10) playerHealth+=2;
				}
				EntityList[i]->OnCleanup();
		 		delete EntityList[i];
				EntityList.erase(EntityList.begin() + i);
				return true;
			}
		}
	}
  return false;
}


//==============================================================================
//
void MapEditor::DeSpawnEntities(){
  for(int i=0;i<EntityList.size();i++){
    int distX = EntityList[i]->getX() + Camera::CameraControl.GetX();
    int distY = EntityList[i]->getY() + Camera::CameraControl.GetY();
    double dist = sqrt(distX*distX+distY*distY);

    if(EntityList[i]->isDestroyable() || dist > 1280){
      if(debug)	cout<<"Entity "<<i<<" despawned."<<endl;
      if(EntityList[i]->getType()==ENTITY_TYPE_ENEMY) numEnemies--;
      EntityList[i]->OnCleanup();
      EntityList.erase(EntityList.begin()+i);
    }
  }
}

//==============================================================================
//
void MapEditor::AddBullet(){
  Entity * tmp = new Bullet();
  tmp->setType(ENTITY_TYPE_BULLET);
  EntityList.push_back(tmp);
}

//==============================================================================
//
void MapEditor::CheckBulletCollision(){
	for(int i=0;i<EntityList.size();i++){
	  if(EntityList[i]->getType() == ENTITY_TYPE_BULLET){
	     int X1 = EntityList[i]->getX();
	     int Y1 = EntityList[i]->getY();
	     int W1 = EntityList[i]->getW();
	     int H1 = EntityList[i]->getH();
	     for(int j=0;j<EntityList.size();j++){
	       if(EntityList[j]->getType() == ENTITY_TYPE_ENEMY){
		 int X2 = EntityList[j]->getX();
		 int Y2 = EntityList[j]->getY();
		 int W2 = EntityList[j]->getW();
		 int H2 = EntityList[j]->getH();

		 if( (abs(X1-X2) < (W1+W2)/2) && (abs(Y1-Y2) < (H1+H2)/2) ) {
		   // delete both; using onHit allows death animations
		   EntityList[i]->onHit();
		   EntityList[j]->onHit();

		   // drop a heart (or any other item...)
		   if(rand()%2 ){
		     Entity * tmp = new Heart(X2,Y2);
		     tmp->setType(ENTITY_TYPE_HEART);
		     EntityList.push_back(tmp);
		   }

		   numEnemies--;

		   Mix_PlayChannel(-1, sfx1, 0); // Play a little noise for enemy destruction
		   //scoreNumber++; // Can increment score here if we want
		 }
	       }
	     }
	  }
	}
}
