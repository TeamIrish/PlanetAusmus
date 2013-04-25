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

	// De-spawn entities if too far from player or marked for despawning
	DeSpawnEntities();

	// Move entities and animate
	for(unsigned int i = 0; i < EntityList.size(); ++i) EntityList[i]->OnLoop();

	// Check for collision between player character and Entities
	CheckEntityCollisions();

	// Check for collision between bullets and enemies
	CheckBulletCollision();

	// Check to see if player is dead
	if(playerHealth < 1) Running = false;

	// Decide whether to spawn enemy
	if(numEnemies<20 && rand()%50<1) SpawnEnemy();

}


//==============================================================================
//
// arguments default to the center of the screen and the size of the player character
int MapEditor::CheckTileCollision(int centerX, int centerY, int width, int height)
{  // returns 0 for traversable, 1 for shootable, 2 for neither
  // check chests
  for(unsigned int i=0;i<EntityList.size();i++){
    if(EntityList[i]->getType()==ENTITY_TYPE_CHEST){
      if(abs(centerX-EntityList[i]->getX())<(width+EntityList[i]->getW())/3
	 && abs(centerY+height/4-EntityList[i]->getY())<(height/2+EntityList[i]->getH())/2){
	return 2;
      }
    }
  }

  // check tiles
  int tileX, tileY, ID, returnvalue=0;
  for(int i = 0; i < 4; i++) {   // check all four corners of the sprite
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

		if(mapID<4 && ID>=0 && ID<MAP_HEIGHT*MAP_WIDTH){
		  int tiletype = gameMap[mapID].TileList[ID].TypeID;
		  if(tiletype == TILE_TYPE_TRAVERSABLE) {
		    //cout<<"Traversable"<<endl;
		    continue;
		  }
		  else if(tiletype == TILE_TYPE_NON_TRAVERSABLE) {
		    //cout<<"Non-traversable"<<endl;
		    return TILE_TYPE_NON_TRAVERSABLE; // 3
		  }
		  else if(tiletype == TILE_TYPE_SHOOTABLE){
		    //cout<<"Shootable."<<endl;
		    returnvalue = 1;
		    continue;
		  }
		  else {
		    //cout<<"Other."<<endl;
		    returnvalue = 1;
		    continue;
		  }
		}
		else{
		  if(debug) cout<<"Entity out of tile collision checking range."<<endl;
		  return TILE_TYPE_NON_TRAVERSABLE;
		}
  }
  return returnvalue;
}


//==============================================================================
//
void MapEditor::SpawnEnemy(){ string typestring; int spawnX,spawnY,attempts=0,enemyW,enemyH;

  // generate random coordinates onscreen
  int X = -Camera::CameraControl.GetX()+WWIDTH/2+pow(-1,rand()%2)*(rand()%(WWIDTH/3));
  int Y = -Camera::CameraControl.GetY()+WHEIGHT/2+pow(-1,rand()%2)*(rand()%(WHEIGHT/3));

  // set enemy parameters
  int choose = rand()%10; // decides which type of enemy
  int speed,hitpoints;
  if(choose<2){ // golem
    typestring = "golem.png";
    enemyW = enemyH = 64;
    speed = 3;
    hitpoints = 5;
  }
  else if(choose<6){ // skeleton
    typestring = "skeleton.png";
    enemyW = 26;
    enemyH = 34;
    speed = 6;
    hitpoints = 3;
  }
  else{ // skull
    typestring = "skull.png";
    enemyW = 16;
    enemyH = 22;
    speed = 9;
    hitpoints = 1;
  }

  // move coordinates to somewhere offscreen
  while(attempts<100){
    spawnX = X;
    spawnY = Y;
    int random=rand()%3;
    if(random>0) spawnX += pow(-1,rand()%2)*WWIDTH*1.5;
    if(random<2) spawnY += pow(-1,rand()%2)*WHEIGHT*1.5;

    // ensure that chosen tile is not nontraversable
    if(!CheckTileCollision(spawnX,spawnY,enemyW,enemyH)) break;
    attempts++;
  }

  if(attempts<100){
    // instantiate enemy and add to list
    Entity * tmp = new Enemy(typestring,enemyW,enemyH,spawnX,spawnY,speed,hitpoints);
    tmp->setType(ENTITY_TYPE_ENEMY);
    EntityList.push_back(tmp);

    numEnemies++;
    if(debug) cout<<"Entity (Enemy) Spawned: "<<spawnX/TILE_SIZE<<","<<spawnY/TILE_SIZE<<endl;
  }
}


//==============================================================================
//  Checks collisions between player and entities
bool MapEditor::CheckEntityCollisions()
{
	// character coordinates
  int charX = -Camera::CameraControl.GetX() + WWIDTH/2;
  int charY = -Camera::CameraControl.GetY() + WHEIGHT/2;

	// for all entities
  for(unsigned int i = 0; i < EntityList.size(); ++i) {
		// get the distance values
    int Xdist = ( CHARACTER_W*0.9 + EntityList[i]->getW() ) / 2;
    int Ydist = ( CHARACTER_H*0.9 + EntityList[i]->getH() ) / 2;
		
		// for all entities except bullets
		if(EntityList[i]->getType() != ENTITY_TYPE_BULLET) { 
			// if there is a collision
			if( abs(charX - EntityList[i]->getX()) < Xdist && abs(charY - EntityList[i]->getY()) < Ydist ){
				int type = EntityList[i]->getType(); // entity type

				// for an enemy
				if(type == ENTITY_TYPE_ENEMY){
					// hurt the player
					playerHealth-=2;
					Camera::CameraControl.playerStateY=4;

					// decrement numEnemies because it dies
					numEnemies--;
				}

				// for a heart
				else if(type == ENTITY_TYPE_HEART) {
					// increment player health and play sound
					Mix_PlayChannel(-1, healSound, 0);
					if(playerHealth < 10) playerHealth+=2;
				}

				// for a chest
				else if(type == ENTITY_TYPE_CHEST) dynamic_cast<Chest*>(EntityList[i])->OpenChest();

				// remove anything other than a chest that the player touches
				if(type != ENTITY_TYPE_CHEST){
				  EntityList[i]->OnCleanup(); // clean up surface
				  delete EntityList[i]; // deallocate memory
				  EntityList.erase(EntityList.begin() + i); // erase the pointer from EntityList vector
				  return true; // collision detected
				}
			}
		}
	}
  return false; // no collision detected
}


//==============================================================================
//
void MapEditor::DeSpawnEntities()
{
	for(unsigned int i = 0; i < EntityList.size(); ++i) {
		// for all non-chest entities
		if(EntityList[i]->getType() != ENTITY_TYPE_CHEST){
			// get distance from player
			int distX = EntityList[i]->getX() + Camera::CameraControl.GetX();
			int distY = EntityList[i]->getY() + Camera::CameraControl.GetY();
			double dist = sqrt(distX*distX+distY*distY);

			// if the entity is marked for destroying or the distance > 1280
			if(EntityList[i]->isDestroyable() || dist > 1280) {
				// decrement numEnemies if the entity is an enemy
				if( EntityList[i]->getType() == ENTITY_TYPE_ENEMY ) numEnemies--;

				// despawn the enemy
				EntityList[i]->OnCleanup();
				EntityList.erase( EntityList.begin() + i );

				if(debug) cout << "Entity " << i << " despawned." << endl; // debug message
			}
		}
	}
}

//==============================================================================
//
void MapEditor::AddBullet()
{
  Entity * tmp = new Bullet();
  tmp->setType(ENTITY_TYPE_BULLET);
  EntityList.push_back(tmp);
}

//==============================================================================
//
void MapEditor::CheckBulletCollision(){
	// cycle through entities looking for bullets
	for(unsigned int i = 0; i < EntityList.size(); ++i) {
		if(EntityList[i]->getType() == ENTITY_TYPE_BULLET){
			// record bullet coordinates and size
			int X1 = EntityList[i]->getX();
			int Y1 = EntityList[i]->getY();
			int W1 = EntityList[i]->getW();
			int H1 = EntityList[i]->getH();
			
			// cycle through entities looking for enemies and chests
			for(unsigned int j = 0; j < EntityList.size(); ++j) {
				int tmptype = EntityList[j]->getType(); // temporary variable for entity type
				
				if(tmptype == ENTITY_TYPE_ENEMY || tmptype == ENTITY_TYPE_CHEST) {
					int X2 = EntityList[j]->getX();
					int Y2 = EntityList[j]->getY();
					int W2 = EntityList[j]->getW();
					int H2 = EntityList[j]->getH();

					if( (abs(X1-X2) < (W1+W2)/2) && (abs(Y1-Y2) < (H1+H2)/2) ) {
						// delete both; using onHit allows health and death animation
						EntityList[i]->onHit();
						EntityList[j]->onHit();
						
						//scoreNumber++; // Can increment score here if we want
					}
				}
			}
	  }
	}
}
