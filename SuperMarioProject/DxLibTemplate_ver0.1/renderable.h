#pragma once

#include"AnimationPlayer.h"
#include"Float2.h"
#include"Line.h"
#include"Rect.h"
#include"Circle.h"
#include"debug_color.h"
#include"DxLib.h"

// •`‰æ•¨‚ğ•\Œ»‚·‚éŠî’êƒNƒ‰ƒX
// 0.0 ~ 1.0‚Ì”ÍˆÍ‚Ì•`‰æ‡•Ï”‚ğ•Û‚µA
// ƒˆ‰¼‘zŠÖ”render()‚ğŒp³æ‚ÅƒI[ƒo[ƒ‰ƒCƒh‚³‚¹‚é‚±‚Æ‚Å•`‰æ‚ğˆêŠ‡ŠÇ—‚·‚é
class Renderable
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

protected :
	// •`‰æ—Dæ‡ˆÊ‚Ì”ÍˆÍ
	// 0.0f
	static const float PRIORITY_MIN;
	// 0.5f
	static const float PRIORITY_MAX;
	// 1.0f
	static const float PRIORITY_DEFAULT;

	// •`‰æ—Dæ‡ˆÊ•Ï”
	float priority;

	// •`‰æÀ•W
	RenderPosition position;

public :
	Renderable(float _priority = 0.0f);
	void setPriority(float newPriority);

	float getPriority();
	virtual void render() = 0;
};

// •`‰æ‚Å‚«‚éü
class RenderableLine : public Renderable
{
public:
	Line line;
	DebugColor color;
public:
	RenderableLine();
	RenderableLine(float _priority, Float2 _begin, Float2 _end);
	void set(Float2 _begin, Float2 _end);
	void setColor(int r, int g, int b, int a = 255);
	DebugColor& getColor();
	virtual void render() override;

};

// •`‰æ‚Å‚«‚élŠp
class RenderableRect : public Renderable
{
public:
	Rect rect;
	DebugColor color;
public:
	RenderableRect();
	RenderableRect(float _priority, Float2 _leftTop, Float2 _size);
	void set(Float2 _leftTop, Float2 _size);
	void setColor(int r, int g, int b, int a = 255);
	DebugColor& getColor();
	virtual void render() override;

};

// •`‰æ‚Å‚«‚é‰~
class RenderableCircle : public Renderable
{
public:
	Circle circle;
	DebugColor color;
public:
	RenderableCircle();
	RenderableCircle(float _priority, Float2 _pos, float _radius);
	void set(Float2 _pos, float _radius);
	void setColor(int r, int g, int b, int a = 255);
	DebugColor& getColor();
	virtual void render() override;

};


// •`‰æ‚Å‚«‚é‰æ‘œ
class RenderableImage : public Renderable
{
protected:
	int imageHandle;
	Float2 pos;
	float rotation;

public :
	RenderableImage(float _priority, int _imageHandle);
	void setPos(Float2 _pos);
	void setRot(float _rot);
	virtual void render() override;
};

// •`‰æ‚Å‚«‚éƒAƒjƒ[ƒVƒ‡ƒ“
class RenderableAnimation : public Renderable
{
protected:
	AnimationPlayer AP;
	Float2 pos;
	Float2 base;
public :
	RenderableAnimation(float _priority, AnimationDataSet* pAdc);
	void setBase(Float2 _base);
	void setPos(Float2 _pos);	
	AnimationPlayer& getAP();
	virtual void render() override;
};
