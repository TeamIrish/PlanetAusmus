// Benjamin Laws, Matt Rundle, Matt Mahan, Paul Kennedy
// CSE 20212 Final Project

#include "MapEditor.h"
#include <cstdlib>

using namespace std;

// macros for entityStateX (direction)
const int ENEMY_DOWN = 0;
const int ENEMY_UP = 1;
const int ENEMY_RIGHT = 2;
const int ENEMY_LEFT = 3;

// number of frames in the enemy's animation cycle
const int NUM_FRAMES = 4;

Enemy::Enemy( string file, int w, int h, int x, int y, int s, int hits )
	: Entity( file, w, h, x, y, s ){
  health = 2 * hits; // each bullet decreases health by 2
}

// randomly select enemy's next move, biased towards current direction
void Enemy::OnLoop()
{
	// move depending on current state
	switch( entityStateX )
	{
		case ENEMY_DOWN:
			Y += speed; // move
			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) Y -= speed; // undo the move
			break;
		case ENEMY_RIGHT:
			X += speed; // move
			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) X -= speed; // undo the move
			break;
		case ENEMY_UP:
			Y -= speed; // move
			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) Y += speed; // undo the move
			break;
		case ENEMY_LEFT:
			X -= speed; // move
			// check for non-traversable tile collisions
			if(MapEditor::CheckTileCollision(X, Y, width, height)) X += speed; // undo the move
	}

	// determine relative position of enemy and player
	int directionToPlayerX,directionToPlayerY;
	if(X > WWIDTH/2-Camera::CameraControl.GetX()) directionToPlayerX = ENEMY_LEFT;
	else directionToPlayerX = ENEMY_RIGHT;
	if(Y > WHEIGHT/2-Camera::CameraControl.GetY()) directionToPlayerY = ENEMY_UP;
	else directionToPlayerY = ENEMY_DOWN;
	// (advanced tracking)
	if(abs(X-WWIDTH/2-Camera::CameraControl.GetX()) < width+CHARACTER_W) directionToPlayerX = directionToPlayerY;
	if(abs(Y-WHEIGHT/2-Camera::CameraControl.GetY()) < height+CHARACTER_H) directionToPlayerY = directionToPlayerX;

	// random number to determine enemy's direction
	int randNum = rand() % 40;
	// set next state pseudo-randomly
	if( randNum == 39 ) entityStateX = ENEMY_LEFT;
	else if( randNum == 38 ) entityStateX = ENEMY_UP;
	else if( randNum == 37 ) entityStateX = ENEMY_RIGHT;
	else if( randNum == 36 ) entityStateX = ENEMY_RIGHT;
	else if( randNum>28 ) entityStateX = directionToPlayerY;
	else if( randNum>21 ) entityStateX = directionToPlayerX;
	// else continue in same direction as currently

	// make sure the enemy is in bounds
	if( X < width/2 ) { // too far left
		X = width/2;
	}
	if( (X + width/2) > (2 * MAP_WIDTH * TILE_SIZE) ) { // too far right
		X = 2 * MAP_WIDTH * TILE_SIZE - width/2;
	}
	if( Y < height/2 ) { // too far up
		Y = height/2;
	}
	if( (Y + height) > (2 * MAP_HEIGHT * TILE_SIZE) ) { // too far down
		Y = 2* MAP_HEIGHT * TILE_SIZE - height;
	}

	// shift animation frame
	entityStateY = ++entityStateY%NUM_FRAMES;
}

void Enemy::onHit(){
  entityStateY = 4;

  health--;  // each bullet actually decreases health by 2, because of the two frames that it stays in contact with the enemy
  if(health <= 0){
    destroy = true;
    // drop a heart (or any other item...)
    if(rand()%4==3){
      Entity * tmp = new Heart(X,Y);
      tmp->setType(ENTITY_TYPE_HEART);
      MapEditor::EntityList.push_back(tmp);
    }

    MapEditor::numEnemies--;
  }
}

void Enemy::OnSave(ofstream & savefile){
  savefile<<spritefilename<<endl;
  savefile<<width<<endl;
  savefile<<height<<endl;
  savefile<<X<<endl<<Y<<endl;
  savefile<<speed<<endl;
  savefile<<type<<endl;
  savefile<<entityStateX<<endl<<entityStateY<<endl;
  savefile<<health<<endl;
}
