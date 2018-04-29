#include "AssetLibrary.h"
#include"Texture.h"
#include "GraphicsDevice.h"
#include "Component.h"
#include "BanditComponent.h"
#include "BlockComponent.h"
#include "BodyComponent.h"
#include "ChestComponent.h"
#include "DoorComponent.h"
#include "InputComponent.h"
#include "InventoryComponent.h"
#include "KeyComponent.h"
#include "MimicComponent.h"
#include "OrcComponent.h"
#include "SpriteComponent.h"

AssetLibrary::AssetLibrary()
{
}

AssetLibrary::~AssetLibrary()
{
}

bool AssetLibrary::initialize(GraphicsDevice* gDevice, std::string objectConfig) 
{

	TiXmlDocument objectFile(objectConfig.c_str());
	objectFile.LoadFile();
	TiXmlElement* root = objectFile.FirstChildElement();
	TiXmlElement* element = root->FirstChildElement();

	while (element)//for each object in the file
	{
	
		OBJECT_TYPE objectTypeEnum;

		std::string objectTypeString = element->Attribute("type");
		objectTypeEnum = objectType_Convert(objectTypeString);
		
		TiXmlElement* initElement;
		initElement = element->FirstChildElement("Animations"); //set the animation root to the initializers level
		if(initElement)
		{ //Initialize Animations
			std::map<ANIM_STATE, std::vector<SPRITE_CLIP*>*>* animationsMap = new std::map<ANIM_STATE, std::vector<SPRITE_CLIP*>*>;
			ANIM_STATE animState;
			int width, height, x, y; //value to store width & height of sprite, in pixels

			
			TiXmlElement* animElement = initElement->FirstChildElement("Sequence");//set element to the first sprite sequence




			animElement->QueryIntAttribute("width", &width); //grab the width of the player sprites from the xml file
			animElement->QueryIntAttribute("height", &height); //grab the height of the player sprites from the xml file



			while (animElement)
			{
				int sequence;
				animElement->QueryIntAttribute("name", &sequence); //grab the name for the sequence
				switch (sequence)
				{
				case -1:
					animState = NA;
					break;
				case 0:
					animState = UP;
					break;

				case 180:
					animState = DOWN;
					break;

				case 270:
					animState = LEFT;
					break;

				case 90:
					animState = RIGHT;
					break;

				case 1:
					animState = CLOSED;
					break;

				case 2:
					animState = OPEN;
					break;
				}
				TiXmlElement* spriteElement = animElement->FirstChildElement("Sprite");
				std::vector<SPRITE_CLIP*>* animation = new std::vector<SPRITE_CLIP*>;
				while (spriteElement)
				{
					SPRITE_CLIP* clip = new SPRITE_CLIP;
					spriteElement->QueryIntAttribute("yPosition", &y);
					spriteElement->QueryIntAttribute("xPosition", &x);
					clip->x = x;
					clip->y = y;
					clip->h = height;
					clip->w = width;

					animation->push_back(clip);
					spriteElement = spriteElement->NextSiblingElement("Sprite");
				}
				animationsMap->insert(std::pair<ANIM_STATE, std::vector<SPRITE_CLIP*>*>(animState, animation));
				animElement = animElement->NextSiblingElement("Sequence");
			}
			animations[objectTypeEnum] = animationsMap;
		}//Initialize Animations

		initElement = element->FirstChildElement("StartUp");
		if (initElement)
		{// Initialize Texture
			COLOR_KEY key;
			Texture* newTexture = new Texture;
			std::string path;
			initElement->QueryIntAttribute("red", &key.r);
			initElement->QueryIntAttribute("green", &key.g);
			initElement->QueryIntAttribute("blue", &key.b);
			initElement->QueryIntAttribute("alpha", &key.a);
			path = initElement->Attribute("path");
			if (!newTexture->load(gDevice->getRenderer(), path, key))
			{
				return(false);//if load failed
			}
			paths[objectTypeEnum] = newTexture;
		}//Initialize Texture
		
		initElement = element->FirstChildElement("Physics");
		if(initElement)
		{//Initialize Physics
			GAME_PHYSICS newPhysics;
			std::string bodyType, bodyShape;

			bodyType = initElement->Attribute("bodyType");
			bodyShape = initElement->Attribute("bodyShape");
			
			if (bodyType == "GAME_DYNAMIC") { newPhysics.bodyType = GAME_DYNAMIC; }
			else { if (bodyType == "GAME_STATIC") { newPhysics.bodyType = GAME_STATIC; } }

			if (bodyShape == "GAME_RECTANGLE") { newPhysics.objectShape = GAME_RECTANGLE; }
			else { if (bodyShape == "GAME_CIRCLE") { newPhysics.objectShape = GAME_CIRCLE; } }

			initElement->QueryFloatAttribute("density", &newPhysics.density);
			initElement->QueryFloatAttribute("restitution", &newPhysics.restitution);
			initElement->QueryFloatAttribute("aDamping", &newPhysics.angularDamping);
			initElement->QueryFloatAttribute("lDamping", &newPhysics.linearDamping);
			initElement->QueryBoolAttribute("physicsOn", &newPhysics.physicsOn);
			initElement->QueryFloatAttribute("height", &newPhysics.dimensions.y);
			initElement->QueryFloatAttribute("width", &newPhysics.dimensions.x);

			objectPhysics[objectTypeEnum] = newPhysics;

		}//Initialize Physics

		initElement = element->FirstChildElement("Components");
		if (initElement)
		{//Initialize Components
			std::vector<GAME_COMPONENTS_LIST> components;
			TiXmlElement* compElement = initElement->FirstChildElement("component");
			while (compElement)
			{
				std::string component = compElement->Attribute("name");

				if (component == "Bandit")
				{
					components.push_back(BANDIT_COMPONENT);
				}
				if (component == "Block")
				{
					components.push_back(BLOCK_COMPONENT);
				}
				if (component == "Body")
				{
					components.push_back(BODY_COMPONENT);
				}
				if (component == "Chest")
				{
					components.push_back(CHEST_COMPONENT);
				}
				if (component == "Door")
				{
					components.push_back(DOOR_COMPONENT);
				}
				if (component == "Input")
				{
					components.push_back(INPUT_COMPONENT);
				}
				if (component == "Inventory")
				{
					components.push_back(INVENTORY_COMPONENT);
				}
				if (component == "Key")
				{
					components.push_back(KEY_COMPONENT);
				}
				if (component == "Mimic")
				{
					components.push_back(MIMIC_COMPONENT);
				}
				if (component == "Orc")
				{
					components.push_back(ORC_COMPONENT);
				}
				if (component == "Sprite")
				{
					components.push_back(SPRITE_COMPONENT);
				}

				compElement = compElement->NextSiblingElement("component");
			}
			componentLists[objectTypeEnum] = components;
		}//Initialize Components

		printf("Object type %s initialized successfully!\n", objectTypeString.c_str());
		element = element->NextSiblingElement();
	}




	return(true);//Initialize successful
}

Texture* AssetLibrary::getTexture(OBJECT_TYPE type)
{
	return(paths[type]);
}

std::map<ANIM_STATE, std::vector<SPRITE_CLIP*>*>* AssetLibrary::getAnimMap(OBJECT_TYPE objectType)
{
	return (animations[objectType]);
}

std::vector<Component*> AssetLibrary::getComponentList(OBJECT_TYPE type)
{
	std::vector<Component*> componentPtrList;
	std::vector<GAME_COMPONENTS_LIST> componentList = componentLists[type];
	for (auto comp : componentList)
	{
		switch (comp)
		{
		case BANDIT_COMPONENT:
			componentPtrList.push_back(new BanditComponent);
			break;
		case BLOCK_COMPONENT:
			componentPtrList.push_back(new BlockComponent);
			break;
		case BODY_COMPONENT:
			componentPtrList.push_back(new BodyComponent);
			break;
		case CHEST_COMPONENT:
			componentPtrList.push_back(new ChestComponent);
			break;
		case DOOR_COMPONENT:
			componentPtrList.push_back(new DoorComponent);
			break;
		case INPUT_COMPONENT:
			componentPtrList.push_back(new InputComponent);
			break;
		case INVENTORY_COMPONENT:
			componentPtrList.push_back(new InventoryComponent);
			break;
		case KEY_COMPONENT:
			componentPtrList.push_back(new KeyComponent);
			break;
		case MIMIC_COMPONENT:
			componentPtrList.push_back(new MimicComponent);
			break;
		case ORC_COMPONENT:
			componentPtrList.push_back(new OrcComponent);
			break;
		case SPRITE_COMPONENT:
			componentPtrList.push_back(new SpriteComponent);
			break;
		default:
			break;
		}
	}
	return (componentPtrList);
}

GAME_PHYSICS AssetLibrary::getObjectPhysics(OBJECT_TYPE type)
{
	return (objectPhysics[type]);
}
