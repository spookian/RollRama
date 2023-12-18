#define MAX_CLONES 20

namespace hel::math
{
	struct Vector3
	{
		float x, y, z;
	}; // include functions later
}

namespace mem
{
	class IAllocator // welcome to the dark side of c++ reverse engineering, finding a fucking allocator.
	{
		
	};

	class Memory
	{
		IAllocator& sceneHeap();
	};
} // normally these class declarations would be problematic because who the fuck wants an empty class? but these are just here to act as convoluted void pointers

namespace g3d
{
	
	class RootContext
	{
		RootContext(mem::IAllocator& heap, unsigned long unk0, unsigned long unk1, unsigned long unk2, unsigned long unk3);
	};

	class Root
	{
		Root(const RootContext& context);
	};

	class Model
	{
		Model(); // wip definition

		void RegisterToRoot(const Root& root);
	};
}

namespace scn
{
	// haven't decomped yet
	class DrawReqInfo
	{
	};

	// interface
	class IScene
	{
		public:
		~IScene();
		virtual void updateMain();
		virtual void updateUseGPU();
		virtual void updateDebug();
		virtual void draw(const scn::DrawReqInfo& info);
		virtual void isSceneEnd() const;
	};
}
// move these eyesores to a different header file, please

namespace rscn
{
	struct EntityList
	{
		unsigned long num;
		IEntity *list[MAX_CLONES];

		void clear(); 
	}; // entitylist should act a lot like a queue, except if anything in the middle is taken out, the last item will fill in the vacant space
	// prevent shit from getting wonky

	class SceneTilt : public scn::IScene
	{
		public:
		Vector3 cam_pos;
		Vector3 cam_rot; // radians

		IEntity *player;
		EntityList clone_list;
		EntityList enemy_list;
	};
}

/*
	A word of advice to Kirby GCN fans,

	Don't try remaking Kirby GCN in Return to Dream Land. BAD IDEA. Very bad. I'm not saying this to be an asshole, I'm saying this as
	a warning.
	
	Kirby GCN was very obviously made with Air Ride and Melee's engine, meaning it used collision with polygons instead of RtDL's tile-based collision.
	Collision is a HEADACHE. I spent approximately a year or two learning two types of polygon collision 
	(side note, you should have a solid linear algebra base when working with 3d)
	and reverse-engineering/hacking is another headache. One I also spent a whole ass year on. I lost 3-4 years of my life on Kirby GCN,
	and this is the culmination of those efforts. A shitty tech demo made for April Fools.

	Please just make a standalone Kirby GCN recreation. Either one on Gamecube or one on Unity if you're a cheap bastard.
	Also? STOP PUTTING ANIME OR ORIGINAL ELEMENTS INTO YOUR GAME. I wanna see exactly what I saw in the trailers, nothing more, nothing less! Take some inspiration
	from The Preservation Project and just do what you've seen. 
*/