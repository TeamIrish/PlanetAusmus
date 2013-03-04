#include "MapEditor.h"
 
void MapEditor::OnLoop() {
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

	// Check to make sure that the camera didn't move out of bounds - if so, change map view
	Camera::CameraControl.CheckBounds();
}
