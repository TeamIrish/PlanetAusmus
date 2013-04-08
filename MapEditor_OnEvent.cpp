#include "MapEditor.h"
 
//==============================================================================
void MapEditor::OnEvent(SDL_Event* Event) {
	Event::OnEvent(Event);
}

//==============================================================================
void MapEditor::OnLButtonDown(int MouseXPos, int MouseYPos) {
	// On left mouse button click
}

//==============================================================================
void MapEditor::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
       	switch(sym) {

	  /*case SDLK_LEFT: {

		}

		case SDLK_RIGHT: {

		}

		case SDLK_UP: {
			
		}*/

		// Left
		case SDLK_a: {
		        if(Running) Camera::CameraControl.MovingLeft = true;
			break;
		}

		// Right
		case SDLK_d: {
			if(Running) Camera::CameraControl.MovingRight = true;	
			break;
		}

		// Up
		case SDLK_w: {
			if(Running) Camera::CameraControl.MovingUp = true;
			break;
		}

		// Down
		case SDLK_s: {
			if(Running) Camera::CameraControl.MovingDown = true;
			break;
		}

		// menu (toggles on and off)
		case SDLK_m: {
			dispMenu = !(dispMenu);
			break;
		}

    case SDLK_ESCAPE: {  
                if(Running) OnStop();
		else OnExit();
   		break;
    }

		default: {
		}
	}
}

//------------------------------------------------------------------------------
void MapEditor::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_a: {
			Camera::CameraControl.MovingLeft = false;
			break;
		}

		case SDLK_d: {
			Camera::CameraControl.MovingRight = false;
			break;
		}

		case SDLK_w: {
			Camera::CameraControl.MovingUp = false;
			break;
		}

		case SDLK_s: {
			Camera::CameraControl.MovingDown = false;
			break;
		}

		default: {
		}
	}
}


//------------------------------------------------------------------------------
void MapEditor::OnStop(){
  Running = false;
}

void MapEditor::OnExit(){
  Quit = true;
}
