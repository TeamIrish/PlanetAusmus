/*
Team: Matt Rundle, Benjamin Laws, Matt Mahan, Paul Kennedy
File: MapEditor_OnRender.cpp

This is the implementation file for the OnEvent() function of the MapEditor class, which inherits from
the Event class. This takes in user input and handles it by applying changes to game data.
*/

#include "MapEditor.h"
 
//==============================================================================
void MapEditor::OnEvent(SDL_Event* Event) {
	Event::OnEvent(Event);
}

//==============================================================================
void MapEditor::OnLButtonDown(int MouseXPos, int MouseYPos) {
	// On left mouse button click
	//cout << "X: " << MouseXPos << "\nY: " << MouseYPos << "\n" << endl;
	if(dispTitle && !(dispTitleMenu)){
		// clicked "Start" button
		if(((MouseXPos > 359) && (MouseXPos < 432)) && ((MouseYPos > 298) && (MouseYPos < 323))){
			dispTitle = false;
		}
		if(((MouseXPos > 359) && (MouseXPos < 432)) && ((MouseYPos > 343) && (MouseYPos < 363))){
			dispTitleMenu = true;
		}
	}
	if(dispTitleMenu){
		if(((MouseXPos > 601) && (MouseXPos < 630)) && ((MouseYPos > 159) && (MouseYPos < 181))){
			dispTitleMenu = false;
		}
	}
}

//==============================================================================
void MapEditor::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
       	switch(sym) {

	        case SDLK_LEFT:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 2;
		  break;

		case SDLK_RIGHT:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 3;
		  break;

		case SDLK_UP:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 1;
		  break;

        	case SDLK_DOWN:
		  Camera::CameraControl.numDirKeys++;
		  Camera::CameraControl.facingDir = 0;
		  break;

		// Left
		case SDLK_a:
		  if(Running){
		    Camera::CameraControl.MovingLeft = true;
		    Camera::CameraControl.MovingRight = false;
		  }
		  break;

		// Right
		case SDLK_d:
		  if(Running){
		    Camera::CameraControl.MovingRight = true;	
		    Camera::CameraControl.MovingLeft = false;	
		  }
		  break;

		// Up
		case SDLK_w:
		  if(Running){
		    Camera::CameraControl.MovingUp = true;
		    Camera::CameraControl.MovingDown = false;
		  }
		  break;

		// Down
		case SDLK_s:
		  if(Running){
		    Camera::CameraControl.MovingDown = true;
		    Camera::CameraControl.MovingUp = false;
		  }
		  break;

		// menu (toggles on and off)
		case SDLK_m:
		  dispMenu = !(dispMenu);
		  break;

		case SDLK_p:
			dispTitle = false;
			break;

		case SDLK_ESCAPE:
		            if(Running) OnStop();
			else OnExit();
	   		break;

		// Objective (toggle on and off)
		case SDLK_o:
			dispObjective = !(dispObjective);
			break;

		// shoot
	        case SDLK_SPACE:
			Mix_PlayChannel(-1, sfx2, 0); // laser noise, yo
		  AddBullet();
		  break;

		default:
	  		break;
	}
}

//------------------------------------------------------------------------------
void MapEditor::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
         	case SDLK_LEFT:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

         	case SDLK_RIGHT:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

         	case SDLK_UP:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

         	case SDLK_DOWN:
		  if((--Camera::CameraControl.numDirKeys) == 0)
		    Camera::CameraControl.facingDir = -1;
		  break;

		case SDLK_a:
			Camera::CameraControl.MovingLeft = false;
			break;

		case SDLK_d:
			Camera::CameraControl.MovingRight = false;
			break;

		case SDLK_w:
			Camera::CameraControl.MovingUp = false;
			break;

		case SDLK_s:
			Camera::CameraControl.MovingDown = false;
			break;

		default:
		  break;
	}
}


//------------------------------------------------------------------------------
void MapEditor::OnStop(){
  Running = false;
}

void MapEditor::OnExit(){
  Quit = true;
}
