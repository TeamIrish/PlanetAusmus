#include "MapEditor.h"
 
void MapEditor::OnLoop() {
	// Move camera
	if(Camera::CameraControl.MovingLeft == true){
		Camera::CameraControl.OnMove(5,0);
		CheckCollision();
	}

	if(Camera::CameraControl.MovingRight == true){
		Camera::CameraControl.OnMove(-5,0);
		CheckCollision();
	}

	if(Camera::CameraControl.MovingUp == true){
		Camera::CameraControl.OnMove(0,5);
		CheckCollision();
	}

	if(Camera::CameraControl.MovingDown == true){
		Camera::CameraControl.OnMove(0,-5);
		CheckCollision();
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
  cout<<"Tile "<<X<<","<<Y<<": ";
  ID = Y*MAP_WIDTH + X;

  if(gameMap[0].TileList[ID].TypeID == TILE_TYPE_TRAVERSABLE) cout<<"Traversable"<<endl;
  else if(gameMap[0].TileList[ID].TypeID == TILE_TYPE_NON_TRAVERSABLE) cout<<"Non-traversable"<<endl;
  else cout<<"Other."<<endl;
  return true;
}
