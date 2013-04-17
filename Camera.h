#ifndef _CAMERA_H_
    #define _CAMERA_H_
 
#include "SDL/SDL.h"
 
#include "Define.h"
 
enum {
    TARGET_MODE_NORMAL = 0,
    TARGET_MODE_CENTER
};
 
class Camera {
    public:
        static Camera CameraControl;
 
    private:
        int X;
        int Y;
 
        int* TargetX;
        int* TargetY;

	int currentMapX,currentMapY;
	int animTimerMax;
 
    public:
        int TargetMode;
	bool MovingRight;
	bool MovingLeft;
	bool MovingUp;
	bool MovingDown;
	int facingDir;  // -1=same as movement,0=down,1=up,2=left,3=right
	int numDirKeys; // number of directional keys currently pressed

	int playerStateX; // 0=down,1=up,2=left,3=right
	int playerStateY; // 0=still,1-2=moving
	int animationTimer;
	void AnimateCharacter();
 
    public:
        Camera();
 
    public:
        void OnMove(int MoveX, int MoveY);

	bool ChangeMapView();
	void GetCornerValues(int,int,int[]);
	int TileToValue(int,int);
 
    public:
        int GetX();
        int GetY();
 
    public:
        void SetPos(int X, int Y);
 
        void SetTarget(int* X, int* Y);

	void CheckBounds();
};
 
#endif
