#include "stdafx.h"

#include "Window.h"
#include <SDL.h>

namespace
{

const glm::ivec2 WINDOW_SIZE = { 1280, 960 };
const char WINDOW_TITLE[] = "The Cubes";
const char ERROR_TITLE[] = "Fatal Error";

}

int main(int, char * [])
{
	try
	{
		CWindow window;
		window.Show(WINDOW_TITLE, WINDOW_SIZE);
		CWindowClient client(window);
		window.DoMainLoop();
	}
	catch (const std::exception & ex)
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, ERROR_TITLE, ex.what(), nullptr);
	}
	return 0;
}
