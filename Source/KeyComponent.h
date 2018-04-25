#pragma once
#include "Component.h"


class KeyComponent :
	public Component
{
public:
	KeyComponent();
	~KeyComponent();
	KEY_TYPE getKeyType() { return (keyType); };
	void finish();
private:
	KEY_TYPE keyType;
};

