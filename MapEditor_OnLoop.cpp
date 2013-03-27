#include "MapEditor.h"
 
void MapEditor::OnLoop() {

	// Move camera
	int moveSize = 1;
	if(Camera::CameraControl.MovingLeft == true){
		Camera::CameraControl.OnMove(moveSize,0);
		if(!(CheckCollision())) Camera::CameraControl.OnMove(-moveSize,0);
	}

	if(Camera::CameraControl.MovingRight == true){
		Camera::CameraControl.OnMove(-moveSize,0);
		if(!(CheckCollision())) Camera::CameraControl.OnMove(moveSize,0);
	}

	if(Camera::CameraControl.MovingUp == true){
		Camera::CameraControl.OnMove(0,moveSize);
		if(!(CheckCollision())) Camera::CameraControl.OnMove(0,-moveSize);
	}

	if(Camera::CameraControl.MovingDown == true){
		Camera::CameraControl.OnMove(0,-moveSize);
		if(!(CheckCollision())) Camera::CameraControl.OnMove(0,moveSize);
	}

	// Check to make sure that the camera didn't move out of bounds - if so, change map view
	Camera::CameraControl.CheckBounds();

	// Change player character state
	Camera::CameraControl.AnimateCharacter();
}


bool MapEditor::CheckCollision(){
  int X,Y,ID;
  X = -(Camera::CameraControl.GetX() - WWIDTH/2) / TILE_SIZE;
  Y = -(Camera::CameraControl.GetY() - WHEIGHT/2) / TILE_SIZE;

	int mapID = 0;
	if(X > MAP_WIDTH){
		X = X - MAP_WIDTH;
		mapID += 1;
	}
	if(Y > MAP_HEIGHT){
		Y = Y - MAP_HEIGHT;
		mapID += 2;
	}

	//cout<<"Tile "<<X<<","<<Y<<": "<<"(mapID = "<<mapID<<"): ";
  ID = Y*MAP_WIDTH + X;

	if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_TRAVERSABLE){
		//cout<<"Traversable"<<endl;
		return true;
	}else if(gameMap[mapID].TileList[ID].TypeID == TILE_TYPE_NON_TRAVERSABLE){
		//cout<<"Non-traversable"<<endl;
		return false;
	}else{
		//cout<<"Other."<<endl;
		return true;
	}
}
