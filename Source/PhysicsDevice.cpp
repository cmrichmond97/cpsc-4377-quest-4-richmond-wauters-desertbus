
#include "PhysicsDevice.h"
#include "Object.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "ContactListener.h"
#include "GraphicsDevice.h"
#include "Box2DDebugDraw.h"



PhysicsDevice::PhysicsDevice()
{

}

PhysicsDevice::~PhysicsDevice()
{
	
}

PhysicsDevice::PhysicsDevice(GAME_VEC gravity):gravity(RW2PW(gravity.x),RW2PW(gravity.y))
{
}

bool PhysicsDevice::initialize(GraphicsDevice* gDevice)
{
	world = new b2World(gravity);
	if (world == NULL) return false;
	ContactListener* c1 = new ContactListener();
	world->SetContactListener(c1);

	Box2DDebugDraw* debugDraw = new Box2DDebugDraw();
	debugDraw->Initialize(gDevice);
	debugDraw->SetFlags(b2Draw::e_shapeBit | b2Draw::e_aabbBit);  //Turn on shape (red color) and aabb (green) 

																  //Add the Debug Draw to the world
	if (debugDraw != NULL)
	{
		world->SetDebugDraw(debugDraw);
	}
	return true;

}

bool PhysicsDevice::update(float dt)
{

	world->Step(dt, 8, 3);
	return true;
}

bool PhysicsDevice::createFixture(Object * object, GAME_PHYSICS physics, GAME_OBJECTFACTORY_INITIALIZERS presets)
{
	//new body definition
	b2BodyDef* bd = new b2BodyDef;
	//made need one or the other, depending on what was passed.
	b2PolygonShape pShape;
	b2CircleShape cShape;

	//Fixture definition
	b2FixtureDef shapefd;

	//Set userData field with passed in object pointer.
	bd->userData = object;


	//set body type
	switch (physics.bodyType)
	{
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody;
		break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody;
		break;
	case GAME_STATIC:
		bd->type = b2_staticBody;
		break;
	}

	shapefd.filter.groupIndex = physics.collisionClass;



	//subtract off half the width.
	presets.startPos.x += (physics.dimensions.x / 2);
	//subtract off half the height
	presets.startPos.y += (physics.dimensions.y / 2);
	//**********************************************************************************

	// set starting position & angle
	bd->position.Set(RW2PW(presets.startPos.x), RW2PW(presets.startPos.y));
	bd->angle = RW2PWAngle(presets.angle);


	b2Body* body = world->CreateBody(bd);

	//Set damping values on the body
	body->SetAngularDamping(physics.angularDamping);
	body->SetLinearDamping(physics.linearDamping);

	//Set fixture's shape

	//rectangle's dimensions
	pShape.SetAsBox(RW2PW(physics.dimensions.x / 2.0f), RW2PW(physics.dimensions.y / 2.0f));
	shapefd.shape = &pShape;
	
	

	//set fixture values based on passed in values.
	shapefd.density = physics.density;
	shapefd.friction = physics.friction;
	shapefd.restitution = physics.restitution;

	//create the fixture on the body.
	body->CreateFixture(&shapefd);
	body->SetActive(physics.physicsOn);


	return false;
}

//**************************************
//Moves body to a set location & angle
bool PhysicsDevice::setTransform(Object* object, GAME_VEC position, GAME_FLT angle)
//**************************************
{
	//finds which body this object is attached to.
	//based on value set in UserData field of body
	b2Body* body = findBody(object);

	//Applies' Box2D transform.
	body->SetTransform
	(
		GV2PV(position),
		RW2PWAngle(angle)
	);
	return true;

}
bool PhysicsDevice::setAngle(Object* object, GAME_FLT angle)
{
	b2Body* body = findBody(object);
	body->SetTransform(body->GetPosition(), RW2PWAngle(angle));
	return true;
}

//**************************************
//Sets linear velocity
bool PhysicsDevice::setLinearVelocity(Object* object, GAME_VEC linearVelociy)
//**************************************
{
	b2Body* body = findBody(object);
	b2Vec2 b2LVelocity;
	b2LVelocity.x = RW2PW(linearVelociy.x);
	b2LVelocity.y = RW2PW(linearVelociy.y);
	body->SetLinearVelocity(b2LVelocity);
	return true;
}

//**************************************
//Sets angular velocity
bool PhysicsDevice::setAngularVelocity(Object* object, GAME_FLT angularVelocity)
//**************************************
{
	b2Body* body = findBody(object);
	body->SetAngularVelocity(RW2PW(angularVelocity));
	return true;

}

//**************************************
//Sets torque on body based on passed values
bool PhysicsDevice::setTorque(Object* object, GAME_FLT torque)
//**************************************
{
	b2Body* body = findBody(object);
	body->ApplyTorque(RW2PW(torque), true);
	return true;
}

//**************************************
//Sets a linear impulse based on passed force vector and center vector
bool PhysicsDevice::setLinearImpulse(Object* object, GAME_VEC forceVec, GAME_VEC forceCenter)
//**************************************
{
	b2Body* body = findBody(object);
	body->ApplyLinearImpulse
	(
		GV2PV(forceVec),
		body->GetWorldPoint(GV2PV(forceCenter)),
		true
	);
	return true;
}

bool PhysicsDevice::setStatic(Object* object)
{
	b2Body* body = findBody(object);
	body->SetType(b2_staticBody);
	return true;
}

bool PhysicsDevice::setStopPhysics(Object* object)
{
	b2Body* body = findBody(object);
	body->SetActive(false);
	return true;
}

//**************************************
//Gets Angular velocity of body
GAME_FLT PhysicsDevice::getAngularVelocity(Object* object)
//**************************************
{
	b2Body* body = findBody(object);
	return (PW2RWAngle(body->GetAngularVelocity()));
}

//**************************************
//Gets bodies' position
GAME_VEC* PhysicsDevice::getPosition(Object* object)
//**************************************
{

	return (alignCenters(object));
}

//**************************************
//Gets bodies' angle
GAME_FLT PhysicsDevice::getAngle(Object* object)
//**************************************
{
	b2Body* body = findBody(object);
	return (PW2RWAngle(body->GetAngle()));
}

GAME_VEC PhysicsDevice::getVelocity(Object* object)
{
	b2Body* body = findBody(object);
	return (PV2GV(body->GetLinearVelocity()));
}

GAME_VEC PhysicsDevice::getLinearVelocity(Object* object)
{
	b2Body* body = findBody(object);
	return(PV2GV(body->GetLinearVelocity()));
}

//**************************************
//Creates a revolute joint using the passed objects and anchor points
bool PhysicsDevice::createRevolvingJoint(Object* object1, Object* object2, GAME_VEC anchor1, GAME_VEC anchor2)
//**************************************
{
	//find corresponding bodies for objects
	b2Body* bodyA = findBody(object1);
	b2Body* bodyB = findBody(object2);
	if (bodyA == NULL || bodyB == NULL)
	{
		return false;
	}

	//joint definition
	b2RevoluteJointDef revoluteJointDef;

	//assign bodies to definition
	revoluteJointDef.bodyA = bodyA;
	revoluteJointDef.bodyB = bodyB;

	//They cannot collide
	revoluteJointDef.collideConnected = false;

	//set anchor points
	revoluteJointDef.localAnchorA.Set(RW2PW(anchor1.x), RW2PW(anchor1.y));
	revoluteJointDef.localAnchorB.Set(RW2PW(anchor2.x), RW2PW(anchor2.y));

	//Joint starts at angle zero
	revoluteJointDef.referenceAngle = 0;

	//Add the joint to the world. If successful will return True, othewise false.
	return (b2RevoluteJoint*)world->CreateJoint(&revoluteJointDef);

}


//**************************************
//Destroys a  physics joint from outside the physics device
bool PhysicsDevice::destroyJoint(Object* object)
//**************************************
{
	b2Body* body = findBody(object);

	//destroy joints associated with body.
	return destroyJoint(body);
}

//**************************************
//Uses the user data field in the body and compares the memory location
//to the memory location of the passed object pointer.
//Returns the body that has the same memory location in the user data field
b2Body* PhysicsDevice::findBody(Object* object)
//**************************************
{
	//loop through the bodies
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		//when we have a match, return it.
		if (object == body->GetUserData())
		{
			return body;
		}
	}
	//if there was no match, return NULL
	return NULL;
}

//**************************************
//Converts passed GAME_VEC to b2Vec2
b2Vec2 PhysicsDevice::GV2PV(GAME_VEC gameVec)
//**************************************
{
	return b2Vec2(RW2PW(gameVec.x), RW2PW(gameVec.y));
}

//**************************************
//converts passed b2Vec2 to GAME_VEC
GAME_VEC PhysicsDevice::PV2GV(b2Vec2 physicsVec)
//**************************************
{
	GAME_VEC temp;
	temp.x = PW2RW(physicsVec.x);
	temp.y = PW2RW(physicsVec.y);
	return temp;
}

//**************************************
//Removes an object from the World
bool PhysicsDevice::removeObject(Object* object)
//**************************************
{
	//Find the body based on the passed object
	b2Body* body = findBody(object);
	destroyJoint(body);

	//check to see if we have a body.
	if (body == NULL)
	{
		return false;
	}
	else
	{
		//delete the body from the world
		world->DestroyBody(body);
		return true;
	}

}


//**************************************
//Destroys the joint from within the device
bool PhysicsDevice::destroyJoint(b2Body* body)
//**************************************
{
	bool jointFound = false;
	//destroy joints associated with body.
	for (b2JointEdge* j = body->GetJointList(); j != NULL; j = j->next)
	{
		world->DestroyJoint(j->joint);
		jointFound = true;
	}
	return jointFound;
}

//**************************************
//adjusts postion based on the fact that SDL is top left and Box2d uses the center of an object for position.
GAME_VEC* PhysicsDevice::alignCenters(Object* object)
//**************************************
{
	b2Body* body = findBody(object);
	b2Vec2 physPosition = body->GetPosition();
	GAME_VEC position;
	Texture* texture = object->getComponent<SpriteComponent>()->getTexture();

	//subtract off half the width.
	position.x = PW2RW(physPosition.x) - (object->getComponent<BodyComponent>()->getDimensions().x / 2);
	//subtract off half the height
	position.y = PW2RW(physPosition.y) - (object->getComponent<BodyComponent>()->getDimensions().y / 2);


	return (&position);
}
