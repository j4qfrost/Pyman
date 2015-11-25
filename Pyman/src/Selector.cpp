/*
 * Selector.cpp
 *
 *  Created on: Apr 29, 2014
 *      Author: frosty
 */

#include "Selector.h"

Package::Package()
{
	objects = NULL;
	int count = 0;
}

Package::~Package()
{
	for (; count > 1; count--)
	{
		delete objects[count - 1];
	}
	delete[] objects;
	objects = NULL;
}

Selector::Selector() {
	blocks = NULL;
	colors = NULL;
	index = 0;
}

Selector::Selector(const char* fileName)
{
	generateLevel(fileName);
}

void Selector::generateLevel(const char* fileName)
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName);

	if (result)
	{
		printf("Loading xml resources SUCCESS!");

		pugi::xml_node node = doc.child("blocks");
		index = node.attribute("count").as_uint();

		blocks = new SDL_Rect[index];
		colors = new Uint32[index];

		int i = 0;
		for(pugi::xml_node_iterator it = node.begin(); it != node.end(); it++)
		{
			blocks[i].x = it->attribute("x").as_int();
			blocks[i].y = it->attribute("y").as_int();
			blocks[i].w = it->attribute("w").as_int();
			blocks[i].h = it->attribute("h").as_int();
			colors[i] = it->attribute("color").as_uint();
			i++;
		}
	}
	else
		printf("Loading xml resources FAILED!");
}

void Selector::regenerateLevel(const char* fileName)
{
	delete [] blocks;
	delete [] colors;

	generateLevel(fileName);
}

Package* Selector::sendPackage() const
{
	Package* package = new Package();
	package->objects = new BaseObject*[index];

	for (int i = 0; i < index - 1; i++)
	{
		package->objects[i] = new BaseObject;
		package->objects[i]->setPos(&blocks[i]);
	}

	PyInterface* inter = PyInterface::Instance();

	PyObject* pyTest = inter->getModule("platform");
	PyObject* test = inter->getAttr(pyTest, "movePlatform");

	package->objects[index - 1] = new Platform;

	package->objects[index - 1]->setCallable(test);
	package->objects[index - 1]->setPos(&blocks[index - 2]);

	package->count = index;
	return package;
}

Selector::~Selector() {
	delete [] blocks;
	delete [] colors;
	blocks = NULL, colors = NULL;
}

