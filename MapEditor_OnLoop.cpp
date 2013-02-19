#include "MapEditor.h"
 
void MapEditor::OnLoop() {
	// Check to make sure that the camera didn't move out of bounds - if so, fix
	Camera::CameraControl.CheckBounds();

	// Move camera
	if(Camera::CameraControl.MovingLeft == true){
		Camera::CameraControl.OnMove(5,0);
	}

	if(Camera::CameraControl.MovingRight == true){
		Camera::CameraControl.OnMove(-5,0);
	}

	if(Camera::CameraControl.MovingUp == true){
		Camera::CameraControl.OnMove(0,5);
	}

	if(Camera::CameraControl.MovingDown == true){
		Camera::CameraControl.OnMove(0,-5);
	}
}
