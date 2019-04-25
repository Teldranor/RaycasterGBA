#include "screen.h"
#include "input.h"
#include <math.h>

#define mapWidth 24
#define mapHeight 24

void render() {

	int worldMap[mapWidth][mapHeight]= {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,1,1,1,1,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	double posX = 3, posY = 3;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	unsigned short* currentScreen = Screen;
	//double time = 0; //time of current frame
	//double oldTime = 0; //time of previous frame

	while(1) {
		for(int x = 0; x < WIN_WIDTH; x++) {
			//calculate ray position and direction
			double cameraX = 2 * x / (double)(WIN_WIDTH) - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)(posX);
			int mapY = (int)(posY);

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if (rayDirX < 0) {
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else {
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0) {
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else {
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			//perform DDA
			while (hit == 0) {
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY) {
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else           perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
			if(drawStart < 0)drawStart = 0;
			int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
			if(drawEnd >= WIN_HEIGHT)drawEnd = WIN_HEIGHT - 1;

			//choose wall color
			int color = 0xff;

			//give x and y sides different brightness
			if (side == 1) {color = color - 0xbb;}

			//draw the pixels of the stripe as a vertical line
			for (int index = 0; index < drawStart; index++) {
				currentScreen[x+WIN_WIDTH*(index)] = 0xbf;
			}
			for (int index = 0; index < lineHeight; index++) {
				currentScreen[x+WIN_WIDTH*(index+drawStart)] = color;
			}
			for (int index = drawEnd; index < WIN_HEIGHT ; index++) {
				currentScreen[x+WIN_WIDTH*(index)] = 0xfb;
			}
		}
		/*if (currentScreen == Screen) currentScreen = ScreenBack;
		else currentScreen = Screen;
		*(unsigned long*)0x4000000 ^= 0x0010;*/
		/*//timing for input and FPS counter
		oldTime = time;
		time = getTicks();
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / frameTime); //FPS counter

		*///speed modifiers
		//double moveSpeed = /*frameTime **/ 0.34; //the constant value is in squares/second
		double rotSpeed = /*frameTime **/ 0.2; //the constant value is in radians/second
		/*readKeys();
		//move forward if no wall in front of you
		key_poll();
		if (wasKeyPressed(KEY_SELECT) || wasKeyPressed(KEY_START) || wasKeyPressed(KEY_UP)) {
		  if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == 0) posX += dirX * moveSpeed;
		  if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == 0) posY += dirY * moveSpeed;
		}
		//move backwards if no wall behind you
		if (keyDown(SDLK_DOWN))
		{
		  if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
		  if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
		}*/
		//rotate to the right
		key_poll();
		if (key_is_down(KEY_UP))
		{
		  //both camera direction and camera plane must be rotated
		  double oldDirX = dirX;
		  dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		  dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		  double oldPlaneX = planeX;
		  planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		  planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		}
	/*//rotate to the left
	if (keyDown(SDLK_LEFT))
	{
	//both camera direction and camera plane must be rotated
	double oldDirX = dirX;
	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
	double oldPlaneX = planeX;
	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}*/
	}
}
