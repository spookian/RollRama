#define MAX_CLONES 20

typedef struct Vector3_s
{
	float x, y, z;
} Vector3;


typedef struct
{
	unsigned long num;
	IEntity *list[MAX_CLONES];
} EntityList; // order will not and shall not matter.

typedef struct SceneTilt_s
{
	void *vtable; // see my documentation on the scn::IScene class

	Vector3 cam_pos;
	Vector3 cam_rot; // radians

	IEntity *player;
	EntityList clone_list;
	EntityList enemy_list;
} SceneTilt;


/*
	A word of advice to Kirby GCN fans,

	Don't try remaking Kirby GCN in Return to Dream Land. BAD IDEA. Very bad. I'm not saying this to be an asshole, I'm saying this as
	a warning.
	
	Kirby GCN was very obviously made with Air Ride and Melee's engine, meaning it used collision with polygons instead of RtDL's tile-based collision.
	Collision is a HEADACHE. I spent approximately a year or two learning two types of polygon collision (side note, you should have a solid linear algebra base when working with 3d),
	and reverse-engineering/hacking is another headache.

	I'm warning you right now, DON'T DO THIS. I'm doing it because I'm a masochist and I love experimenting with stuff like this, but you're gonna have to deal with two completely different
	forms of bullshit all at once.

	Make a standalone Kirby GCN recreation, please. You have two different decompilations to choose from. Don't do it.
*/