#include "Bullet.h"

bool Bullet::OnLoad() {

	Type = ENTITY_TYPE_BULLET;

	if((Surf_Entity = CSurface::OnLoad("./gfx/bullet.png")) == NULL) {
		return false;
	}

	CSurface::Transparent(Surf_Entity, 255, 0, 255);

	this->Width = 10;
	this->Height = 5;

	this->xVel = .3;

	Anim_Control.MaxFrames = 1;

	return true;
}
