#include "MapEditor.h"
 
void MapEditor::OnRender() {

  // render maps
  for(int i=0;i<4;i++){
    gameMap[i].OnRender(Surf_Display, Camera::CameraControl.GetX()+MAP_WIDTH*TILE_SIZE*(i%2), Camera::CameraControl.GetY()+MAP_HEIGHT*TILE_SIZE*(i/2));
  }

  // render player character
  Surface::OnDraw(Surf_Display,Player_Character,WWIDTH/2,WHEIGHT/2,Camera::CameraControl.playerStateX*CHARACTER_W,Camera::CameraControl.playerStateY*CHARACTER_H,CHARACTER_W,CHARACTER_H);

  /*Map Editing Tile Selector
    Surface::OnDraw(Control_Display, Tileset, 16, 0, 0, currentTileYID * TILE_SIZE,9 * TILE_SIZE,TILE_SIZE);
    Surface::OnDraw(Control_Display, Selector, 16 + (currentTileXID * TILE_SIZE), 0);
    Surface::OnDraw(Surf_Display, Control_Display, WWIDTH - CBAR_WIDTH, 0);*/


  // Refresh the buffer and display Surf_Display to screen
  SDL_Flip(Surf_Display);
}
