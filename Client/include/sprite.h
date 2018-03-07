#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED

typedef enum View_Orientation
{
	UP = 0,
	UP_RIGHT = 1,
	RIGHT = 2,
	DOWN_RIGHT = 3,
	DOWN = 4,
	DOWN_LEFT = 5,
	LEFT = 6,
	UP_LEFT = 7,
} View_Orientation;

typedef	struct  s_struct
{
	int a;
}				t_struct;

typedef enum Player_State
{
	IDLE = 0,
	WALK = 1,
	FIRE = 2,
	HIT = 3,
	DEAD = 4
} Player_State;
#endif // SPRITE_H_INCLUDED