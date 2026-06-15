#pragma once

class ICollisionTag
{
public:
	static enum TAG
	{
		DEFAULT = -1,
		FLOOR,
		MARIO,
		FIREBALL,
		SHELL,
		ENEMY,
		BLOCK,
		ITEM,
		RENGA,
		NUM
	};
	int tag;

public:
	inline ICollisionTag()
	{
		tag = DEFAULT;
	}
	virtual bool canCollide(int othertag) = 0;
};
class CollisionTagFloor : public ICollisionTag
{
public:
	inline CollisionTagFloor()
	{
		tag = TAG::FLOOR;
	}
	inline bool canCollide(int othertag)
	{
		bool ret = false;
		switch (othertag)
		{
		case FLOOR:
			ret = false;
			break;
		case MARIO:
			ret = true;
			break;
		case FIREBALL:
			ret = true;
			break;
		case ENEMY:
			ret = true;
			break;
		case SHELL:
			ret = true;
			break;
		case BLOCK:
			ret = false;
			break;
		case RENGA:
			ret = false;
			break;
		}

		return ret;
	}
};

class CollisionTagMario : public ICollisionTag
{
public:
	inline CollisionTagMario()
	{
		tag = TAG::MARIO;
	}
	inline bool canCollide(int othertag)
	{
		bool ret = false;
		switch (othertag)
		{
		case FLOOR:
			ret = true;
			break;
		case MARIO:
			ret = false;
			break;
		case FIREBALL:
			ret = false;
			break;
		case ENEMY:
			ret = true;
			break;
		case SHELL:
			ret = true;
			break;
		case BLOCK:
			ret = true;
			break;
		case RENGA:
			ret = true;
			break;
		}

		return ret;
	}
};
class CollisionTagFireBall : public ICollisionTag
{
public:
	inline CollisionTagFireBall()
	{
		tag = TAG::FIREBALL;
	}

	inline bool canCollide(int othertag)
	{
		bool ret = false;
		switch (othertag)
		{
		case FLOOR:
			ret = true;
			break;

		case MARIO:
			ret = false;
			break;
		case FIREBALL:
			ret = false;
			break;
		case ENEMY:
			ret = true;
			break;
		case SHELL:
			ret = true;
			break;
		case BLOCK:
			ret = true;
			break;
		}
		return ret;
	}
};
class CollisionTagShell : public ICollisionTag
{
public:
	inline CollisionTagShell()
	{
		tag = TAG::SHELL;
	}

	inline bool canCollide(int othertag)
	{
		bool ret = false;
		switch (othertag)
		{
		case FLOOR:
			ret = true;
			break;

		case MARIO:
			ret = true;
			break;
		case FIREBALL:
			ret = true;
			break;
		case ENEMY:
			ret = true;
			break;
		case SHELL:
			ret = true;
			break;
		case BLOCK:
			ret = true;
			break;
		}
		return ret;
	}
};
class CollisionTagEnemy : public ICollisionTag
{
public:
	inline CollisionTagEnemy()
	{
		tag = TAG::ENEMY;
	}

	inline bool canCollide(int othertag)
	{
		bool ret = false;
		switch (othertag)
		{
		case FLOOR:
			ret = true;
			break;

		case MARIO:
			ret = true;
			break;
		case FIREBALL:
			ret = true;
			break;
		case ENEMY:
			ret = false;
			break;
		case SHELL:
			ret = true;
			break;
		case BLOCK:
			ret = true;
			break;
		}
		return ret;
	}
};
class CollisionTagBlock : public ICollisionTag
{
public:
	inline CollisionTagBlock()
	{
		tag = TAG::BLOCK;
	}

	inline bool canCollide(int othertag)
	{
		bool ret = false;
		switch (othertag)
		{
		case FLOOR:
			ret = false;
			break;

		case MARIO:
			ret = true;
			break;
		case FIREBALL:
			ret = true;
			break;
		case ENEMY:
			ret = true;
			break;
		case SHELL:
			ret = true;
			break;
		case BLOCK:
			ret = false;
			break;

		case RENGA:
			ret = false;
			break;

		}
		return ret;
	}
};

class CollisionTagRenga : public ICollisionTag
{
public:
	inline CollisionTagRenga()
	{
		tag = TAG::RENGA;
	}

	inline bool canCollide(int othertag)
	{
		bool ret = false;

		switch (othertag)
		{
		case FLOOR:
			ret = false;
			break;

		case MARIO:
			ret = true;
			break;

		case FIREBALL:
			ret = true;
			break;

		case ENEMY:
			ret = true;
			break;

		case SHELL:
			ret = true;
			break;

		case BLOCK:
			ret = false;
			break;

		case RENGA:
			ret = false;
			break;
		}

		return ret;
	}
}; 