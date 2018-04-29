#pragma once

#include"Definitions.h"

#include"../ThirdParty/Box2D_new/Box2D/Box2D.h"


class b2World;
class b2Body;
class b2Vec2;
class GraphicsDevice;

class PhysicsDevice
{
public:
	PhysicsDevice();
	~PhysicsDevice();
	PhysicsDevice(GAME_VEC gravity);
	bool initialize(GraphicsDevice* gDevice);
	bool update(float dt);
	bool createFixture(Object* object,GAME_PHYSICS, GAME_OBJECTFACTORY_INITIALIZERS presets);

	bool setTransform(Object* object, GAME_VEC position, GAME_FLT angle);
	bool setLinearVelocity(Object* object, GAME_VEC linearVelociy);
	bool setAngularVelocity(Object* object, GAME_FLT angularVelocity);
	bool setTorque(Object* object, GAME_FLT torque);
	bool setLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter);
	bool setStatic(Object* object);
	bool setStopPhysics(Object* object);
	bool setAngle(Object* object, GAME_FLT angle);


	GAME_FLT getAngularVelocity(Object* object);
	GAME_VEC* getPosition(Object* object);
	GAME_FLT getAngle(Object* object);
	GAME_VEC getVelocity(Object* object);
	GAME_VEC getLinearVelocity(Object* object);
	b2World* getWorld() { return world; }

	bool createRevolvingJoint(Object* object1, Object* object2, GAME_VEC anchor1, GAME_VEC anchor2);
	bool destroyJoint(Object* object);

	//helper methods
	b2Body* findBody(Object* Object);
	b2Vec2 GV2PV(GAME_VEC gameVec);
	GAME_VEC PV2GV(b2Vec2 physicsVec);
	bool removeObject(Object* object);

	b2World* world;

	//helper methods
	inline float PW2RW(GAME_FLT x) { return x*fPRV; }
	inline float RW2PW(GAME_FLT x) { return x / fPRV; }
	inline float RW2PW(GAME_INT x) { return (float)x / fPRV; }
	inline float RW2PWAngle(GAME_FLT x) { return((float)x*(2.0f*3.14159f) / 360.0f); }
	inline float PW2RWAngle(GAME_FLT x) { return((float)x*360.0f / (2.0f*3.14159f)); }

	bool destroyJoint(b2Body* body);
	const b2Vec2 gravity;   
	GAME_VEC* alignCenters(Object* object); //adjusts position to centers from top-left

private:

};

