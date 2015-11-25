/* 
 * File:   Console.cpp
 * Author: frosty
 * 
 * Created on February 28, 2014, 2:18 AM
 */

#include "Console.h"

Console::Console()
{
	if(!TTF_WasInit())
		if (TTF_Init() == -1)
		    	exit(0);

	fontName = "res/FreeMonoBold.ttf";
	fontSize = 10;

	font = TTF_OpenFont(fontName.c_str(),fontSize);
	color.r = 255;
	color.b = 255;
	color.g = 255;
	frame = new Surface(300,300,32);
	sandBox = new SDL_Rect;
	textBox = new SDL_Rect;
	errBox = new SDL_Rect;

	slate = new Slate("scripts/platform.py",fontSize);
	slate->shiftToEnd();

	closeButton = new Button();

	sandBox->x = 50;
	sandBox->y = 50;

	textBox->x = 70;
	textBox->y = 80; //setCanvas
	textBox->w = frame->getSurface()->w + sandBox->x - 2 * textBox->x;
	textBox->h = frame->getSurface()->h + sandBox->y - 2 * textBox->y;
	slate->setCanvas(textBox);

	closeButton->setParams(sandBox->x,sandBox->y,20,20,Manage::editing,"res/closeButton.png");

	draw();
}

void Console::handleEvent()
{
	Tracker* tracker = new Tracker;
	int multiple = 0;

	switch(e.type) {
	case SDL_MOUSEBUTTONDOWN:
		slate->returnCursor();
		tracker->handle();
		break;
	case SDL_TEXTINPUT:
		slate->insert(e.text.text);
		slate->shiftCursor(1);
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym) {
		case SDLK_DELETE:
			slate->shiftCursor(1);
		case SDLK_BACKSPACE:
			multiple = slate->back();
			break;
		case SDLK_RETURN:
			slate->newLine();
			multiple = 2;
			break;
		case SDLK_UP:
			slate->shiftCursor(2);
			break;
		case SDLK_DOWN:
			slate->shiftCursor(3);
			break;
		case SDLK_LEFT:
			slate->shiftCursor(0);
			break;
		case SDLK_RIGHT:
			slate->shiftCursor(1);
			break;
		case SDLK_F5:
			//PyInterface::run(slate->getRunnable());
			//tau->functionCallback("bar", 0, NULL);
			//Check for errors
			Manage::scriptReload = true;
			//slate->setScript(slate->getScript());
			PyInterface::Instance()->reload(slate->getScript(false));
			break;
		case SDLK_F7:
			slate->save();
			break;
		}
		break;
	case SDL_TEXTEDITING:
		break;
	}

	closeButton->handle();
	redraw(multiple);

	if (!Manage::editing)
	{
		Uint32* pixels = (Uint32*) surface->getSurface()->pixels;
		SDL_FillRect(surface->getSurface(),sandBox,pixels[0]);
	}

	closeButton->show();
}

void Console::renderLines()
{
	unsigned int length = slate->getLines().size();
	for(unsigned int i = 0; i < length; i++)
		renderLine(i);
}

void Console::renderLine(unsigned int activeLine)
{
	SDL_Surface* process = NULL;
	process = TTF_RenderText_Solid(font,slate->getLines()[activeLine].c_str(),color);
	int diffX = textBox->x - sandBox->x;
	int diffY = textBox->y - sandBox->y;

	frame->applySurface(diffX,diffY + activeLine * fontSize,process,NULL);
}

SDL_Rect* Console::getAbsCursorPos() const
{
	SDL_Rect* cur = new SDL_Rect;
	cur->w = 1;
	cur->h = fontSize;
	cur->x = slate->getCursor().pos * (fontSize - 4) + textBox->x - 1;
	cur->y = slate->getCursor().li * fontSize + textBox->y;


	return cur;
}

void Console::draw()
{
	SDL_FillRect(frame->getSurface(),&(frame->getSurface()->clip_rect),0);
	renderLines();
	surface->applySurface(sandBox,frame);
}

void Console::redraw(int multiple)
{
	int diffX = textBox->x - sandBox->x;
	int diffY = textBox->y - sandBox->y;
	SDL_Rect filler;
	filler.x = diffX;

	filler.w = textBox->w;
	filler.h = fontSize;

	if (multiple == 0)
	{
		filler.y = diffY + slate->getCursor().li * fontSize;
		SDL_FillRect(frame->getSurface(),&filler,0);
		renderLine(slate->getCursor().li);
	}
	else if (multiple == 1)
	{
		filler.y = diffY + (slate->getCursor().li - 1) * fontSize;
		unsigned int active = slate->getCursor().li;
		unsigned int len = slate->getLines().size() + 1;

		while(active < len)
		{
			filler.y += filler.h;
			SDL_FillRect(frame->getSurface(),&filler,0);
			renderLine(active);

			active++;
		}
		SDL_FillRect(frame->getSurface(),&filler,0);
	}
	else if (multiple == 2)
	{
		filler.y = diffY + (slate->getCursor().li - 1) * fontSize;
		unsigned int active = slate->getCursor().li - 1;
		unsigned int len = slate->getLines().size();

		while(active < len)
		{
			SDL_FillRect(frame->getSurface(),&filler,0);

			renderLine(active);
			filler.y += filler.h;
			active++;
		}
		SDL_FillRect(frame->getSurface(),&filler,0);
	}

	surface->applySurface(sandBox,frame);
}

void Console::idling()
{
	SDL_FillRect(surface->getSurface(),getAbsCursorPos(),0);
}

bool Console::inBounds() const
{
	int cursorX = slate->getCursor().pos * (fontSize - 4);
	int cursorY = slate->getCursor().li * fontSize;
	return (cursorX >= 0 && cursorX < textBox->w)
			&& (cursorY >= 0 && cursorY < textBox->h - int(fontSize));
}

void Console::setFont(const char* newFont)
{
	fontName = newFont;
}

Console::~Console()
{
	delete frame;
	delete sandBox;
	delete textBox;
	delete errBox;

	frame = NULL, sandBox = NULL,
			textBox = NULL, errBox = NULL;
	TTF_Quit();
}
