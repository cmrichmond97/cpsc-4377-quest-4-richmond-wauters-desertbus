#include<iostream> //ALWAYS PUT <> BEFORE ""
#include "Game.h"
#include "GraphicsDevice.h"
#include "../ThirdParty/SDL2-2.0.7/include/SDL.h"
#include "Definitions.h"
#include "Timer.h"
#include "InputDevice.h"
#include "View.h"
#include "AssetLibrary.h"
#include "Object.h"
#include "GameObjectFactory.h"
#include "PhysicsDevice.h"
#include "Blackboard.h"
#include "SoundDevice.h"






Game::Game()
{

}

Game::~Game()
{
	delete gDevice;
	delete timer;
	delete iDevice;
	delete view;
	delete assetLibrary;
	delete blackboard;

}


bool Game::initialize(std::string objectConfig)
{
	

	blackboard = new Blackboard;//create the blackboard
	blackboard->setLevel(1);
	inits.blackboard = blackboard;//add the blackboard to the initializers

	gDevice = new GraphicsDevice(SCREEN_WIDTH, SCREEN_HEIGHT);//create the graphics device
	if (!gDevice->Initialize(true))
	{
		printf("Graphics Device could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	inits.gDevice = gDevice;//add the graphics device to the initializers


	timer = new Timer;//create the timer
	if (!timer->Initialize())
	{
		printf("Timer could not initialize!");
		exit(1);
	}


	iDevice = new InputDevice;//create the input device
	if (!iDevice->initialize())
	{
		printf("Input Device could not initialize!");
		exit(1);
	}
	inits.iDevice = iDevice;//add the input device to the initializers

	pDevice = new PhysicsDevice;//create the Physics Device
	if (!pDevice->initialize(gDevice))
	{
		printf("Physics Device could not initialize!");
		exit(1);
	}
	inits.pDevice = pDevice;//add the Physics device to the initializers

	

	view = new View;// create the view
	if (!view->initialize(iDevice, 0, 0, blackboard))
	{
		printf("View could not initialize!");
		exit(1);
	}
	inits.view = view;//add the view to the initializers

	sDevice = new SoundDevice;//create the input device
	if (!sDevice->initialize())
	{
		printf("Sound Device could not initialize!");
		exit(1);
	}
	inits.sDevice = sDevice;//add the sound device to the initializers

	assetLibrary = new AssetLibrary;// create the asset library
	if (!assetLibrary->initialize(gDevice, objectConfig))
	{
		printf("Asset Library could not initialize!");
		exit(1);
	}
	inits.assetLibrary = assetLibrary;//add the asset library to the initializers
	sDevice->setLibrary(assetLibrary);

	sDevice->SetBackground("level1");

	objectFactory = new GameObjectFactory;

	inits.factory = objectFactory;


	/*all devices initialized.
	inits contains:
	pointer to gDevice
	pointer to iDevice
	pointer to pDevice
	pointer to view
	pointer to assetLibrary
	*/
	return(true);
}

void Game::Reset()
{
	for (int i = 0; i<objects.size(); i++)
	{
		delete objects[i];
	}

}

bool Game::LoadLevel(std::string levelConfig)
{




	if (levelConfig.c_str())//ensure that no NULL strings were passed in
	{
		TiXmlDocument levelFile(levelConfig.c_str());//create the document for the level file
		levelFile.LoadFile();//load the level file into the document
		TiXmlElement* levelRoot = levelFile.FirstChildElement(); //create a pointer to the begining of the level document
		TiXmlElement* levelElement = levelRoot->FirstChildElement();//create the pointer that will be used to
																	//loop through the level document
		while (levelElement)//while there are still objects left to create in the level document
		{
			std::string level = levelElement->Attribute("name");
			if (level != "Block")
			{
				levelElement->QueryFloatAttribute("xPosition", &inits.startPos.x);//query the starting x position of the next object
				levelElement->QueryFloatAttribute("yPosition", &inits.startPos.y);//query the starting y position of the next object
				if (level == "ShinyKey"||
					level == "JungleKey"||
					level == "IceKey")
				{
					inits.keyType = keyType_Convert(levelElement->Attribute("keyType"));
				}
				if (level == "ShinyChest" ||
					level == "JungleChest" ||
					level == "IceChest")
				{
					inits.keyType = keyType_Convert(levelElement->Attribute("keyType"));
					inits.heldLoot = gameLoot_Convert(levelElement->Attribute("heldLoot"));
				}
				if (level == "Bandit")
				{
					levelElement->QueryIntAttribute("speed", &inits.speed);
				}
				/*

				Call the factory's create method, then push the returned
				object pointer onto the Objects vector.
				create will return a pointer to the newly created object.

				inits contains all of the initializers that might be required by the object.
				*/

				inits.type = objectType_Convert(levelElement->Attribute("name"));

				objects.push_back(objectFactory->create(inits));
			}
			else
			{
				int xStart, xEnd, yStart, yEnd;
				levelElement->QueryIntAttribute("xStart", &xStart);
				levelElement->QueryIntAttribute("xEnd", &xEnd);
				levelElement->QueryIntAttribute("yStart", &yStart);
				levelElement->QueryIntAttribute("yEnd", &yEnd);
				inits.type = objectType_Convert(levelElement->Attribute("name"));
				if (xStart != xEnd)
				{
					for (int x = xStart; x <= xEnd; x += 28)
					{
						inits.startPos.x = x;
						inits.startPos.y = yStart;
						objects.push_back(objectFactory->create(inits));
					}
				}
				else
				{
					for (int y = yStart; y <= yEnd; y += 28)
					{
						inits.startPos.y = y;
						inits.startPos.x = xStart;
						objects.push_back(objectFactory->create(inits));
					}
				}
			}

			levelElement = levelElement->NextSiblingElement();//move to the next object in the level document
		}

		return(true);//loadlevel successful
	}
	else
	{
		return(false);//loadlevel failed
	}


}

bool Game::Run()
{
	timer->start();




	if (!iDevice->getEvent(GAME_QUIT))
	{
		bool gameOver;
		gameOver = Update();
		pDevice->update(1);
		gDevice->Begin();
		Draw();
		gDevice->Present();
		timer->fpsRegulate();
		return(gameOver);
	}
	else
		return(true);
}

bool Game::Update()
{
	bool gameOver = false;
	bool levelCleared = false;
	for (int i = 0; i<objects.size(); i++)
	{

		if (!gameOver)
		{


			Object* newObject = objects[i]->update(dt);
			if (objects[i]->getType() == PLAYER)
			{
				gameOver = objects[i]->getIsDead();
				

			}

			if (newObject)
			{
				objects.push_back(newObject);
			}
			if (objects[i]->getIsDead())
			{
				objects[i]->finish();
				delete objects[i];
				objects.erase(objects.begin() + i);
			}
		}
	}
	if (blackboard->getGameClear() == true)
	{
		
		if (blackboard->getLevel() == 1)
		{
			for (int j = 0; j < objects.size();)
			{

				objects[j]->finish();
				delete objects[j];
				objects.erase(objects.begin() + j);

			}
			LoadLevel("./Assets/Config/level2.xml");
			//sDevice->SetBackground("level2");
			blackboard->setLevel(2);
			blackboard->setGameClear(false);
		}
		else
		{
			gameOver = true;
		}
		
	}
	if (!gameOver)
	{
		view->update(blackboard->getLevel());
		iDevice->update();
	}
	return(gameOver);
}

bool Game::Draw()
{

	for (int i = 0; i<objects.size(); i++)
	{
		objects[i]->draw();
	}
	//Draw the Debug overlay
	//pDevice->world->DrawDebugData();
	return(true);
}