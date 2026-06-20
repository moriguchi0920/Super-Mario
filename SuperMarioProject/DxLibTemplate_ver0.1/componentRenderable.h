#pragma once

#include"AnimationPlayer.h"
#include"Float2.h"
#include"Line.h"
#include"Rect.h"
#include"Circle.h"
#include"debug_color.h"
#include"componentBase.h"
#include"DxLib.h"

class ComponentTransform;

// •`‰æ•¨‚ğ•\Œ»‚·‚éŠî’êƒNƒ‰ƒX
// 0.0 ~ 1.0‚Ì”ÍˆÍ‚Ì•`‰æ‡•Ï”‚ğ•Û‚µA
// ƒˆ‰¼‘zŠÖ”render()‚ğŒp³æ‚ÅƒI[ƒo[ƒ‰ƒCƒh‚³‚¹‚é‚±‚Æ‚Å•`‰æ‚ğˆêŠ‡ŠÇ—‚·‚é
class ComponentRenderable : public Component
{
public:
	// •`‰æÀ•W•\Œ»—p‚Ì\‘¢‘Ì
	struct Pos
	{
		float x;
		float y;
	};
	union RenderPosition
	{
		Pos leftTop;
		Pos center;
	};

	// •`‰æ—Dæ‡ˆÊ‚Ì”ÍˆÍ
	// 0.0f
	static constexpr float PRIORITY_MIN = 0.0f;
	// 0.5f
	static constexpr float PRIORITY_DEFAULT = 0.5f;
	// 1.0f
	static constexpr float PRIORITY_MAX = 1.0f;

protected:


	// •`‰æ—Dæ‡ˆÊ•Ï”
	float priority;

	// •`‰æÀ•W
	RenderPosition position;

	std::weak_ptr<ComponentTransform> transformRef;

public:
	ComponentRenderable(int objectId, float _priority = 0.0f);
	virtual ~ComponentRenderable();
	void setPriority(float newPriority);

	float getPriority();
	virtual void render() = 0;

	void bindToTransform(std::weak_ptr<ComponentTransform> wpTransform);

	virtual void syncFromTransform();

};

// •`‰æ‚Å‚«‚éü
class ComponentRenderableLine : public ComponentRenderable
{
public:
	Line line;
	DebugColor color;
public:
	ComponentRenderableLine(int objectId);
	ComponentRenderableLine(int objectId, float _priority, Float2 _begin, Float2 _end);
	void set(Float2 _begin, Float2 _end);
	void setColor(int r, int g, int b, int a = 255);
	DebugColor& getColor();
	virtual void render() override;
	void syncFromTransform() override;
};

// •`‰æ‚Å‚«‚élŠp
class ComponentRenderableRect : public ComponentRenderable
{
public:
	Rect rect;
	DebugColor color;
public:
	ComponentRenderableRect(int objectId);
	ComponentRenderableRect(int objectId, float _priority, Float2 _leftTop, Float2 _size);
	ComponentRenderableRect(int objectId, float _priority, Rect _rect);
	void set(Float2 _leftTop, Float2 _size);
	void setColor(int r, int g, int b, int a = 255);
	DebugColor& getColor();
	virtual void render() override;
	void syncFromTransform()override;
};

// •`‰æ‚Å‚«‚é‰~
class ComponentRenderableCircle : public ComponentRenderable
{
public:
	Circle circle;
	DebugColor color;
public:
	ComponentRenderableCircle(int objectId);
	ComponentRenderableCircle(int objectId, float _priority, Float2 _pos, float _radius);
	ComponentRenderableCircle(int objectId, float _priority, Circle _cir);
	void set(Float2 _pos, float _radius);
	void setColor(int r, int g, int b, int a = 255);
	DebugColor& getColor();
	virtual void render() override;
	void syncFromTransform()override;
};


// •`‰æ‚Å‚«‚é‰æ‘œ
class ComponentRenderableImage : public ComponentRenderable
{
protected:
	int imageHandle;
	Float2 pos;
	float rotation;
	bool isTurn = false;

public:
	ComponentRenderableImage(int objectId, float _priority, int _imageHandle);
	void setPos(Float2 _pos);
	void setRot(float _rot);
	void setImage(int handle);

	void setTurn(bool _isTurn) { isTurn = _isTurn; }

	virtual void render() override;
	void syncFromTransform()override;
};

// •`‰æ‚Å‚«‚éƒAƒjƒ[ƒVƒ‡ƒ“
class ComponentRenderableAnimation : public ComponentRenderable
{
protected:
	AnimationPlayer AP;
	Float2 pos;
	Float2 base;
public:
	ComponentRenderableAnimation(int objectId, float _priority, AnimationDataSet* pAdc);
	void setBase(Float2 _base);
	void setPos(Float2 _pos);
	AnimationPlayer& getAP();
	virtual void render() override;
	void syncFromTransform()override;
};
