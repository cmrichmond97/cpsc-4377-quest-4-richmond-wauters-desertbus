
//only include this header 1 time per compile
#pragma once
//so no include guards are needed

#include <Box2D\Box2D.h>
#include "Definitions.h"
#include "GraphicsDevice.h"

class Box2DDebugDraw : public b2Draw {

public:
	Box2DDebugDraw();
	~Box2DDebugDraw();
	bool Initialize(GraphicsDevice* gDevice);

	void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
	void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color);
	void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color);
	void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color);
	void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color);
	void DrawTransform(const b2Transform &xf);

	inline float PW2RW(GAME_FLT x) { return x * fPRV; };
	inline float RW2PW(GAME_FLT x) { return x / fPRV; };
	inline float RW2PW(GAME_INT x) { return (float)x / fPRV; };
	inline float RW2PWAngle(GAME_FLT x) { return((float)x*(2.0f*3.14159f) / 360.0f); };
	inline float PW2RWAngle(GAME_FLT x) { return((float)x*360.0f / (2.0f*3.14159f)); };

private:

	GraphicsDevice * gDevice;
	int circleAccuracy;

};