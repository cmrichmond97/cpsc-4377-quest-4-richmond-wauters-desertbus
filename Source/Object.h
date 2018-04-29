#ifndef OBJECT_H
#define OBJECT_H

#include<vector>
#include<map>
#include "Definitions.h"
#include"tinyxml\tinystr.h"
#include"tinyxml\tinyxml.h"
#include "../ThirdParty/SDL2-2.0.7/include/SDL.h"




class Component;
class BodyComponent;
class SpriteComponent;

class Object
{
public:
	Object();
	~Object();

	void addComponent(Component* component);
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	Blackboard* getBlackboard() { return(blackboard); }
	void kill(){ isDead = true; }
	void draw();
	bool finish();

	//getters
	bool getIsDead() { return isDead; };
	bool getLevelClear() { return levelClear; };
	OBJECT_TYPE getType();


	template<class T>
	T* getComponent()
	{
		for (auto comp : components)
		{
			T* target = nullptr;
			if (target = dynamic_cast<T*>(comp))
			{
				return(target);
			}
		}
		return(nullptr);
	}


protected:
	std::vector<Component*> components;
	OBJECT_TYPE type;
	Blackboard* blackboard;
	bool isDead = false;
	bool levelClear = false;
};



#endif