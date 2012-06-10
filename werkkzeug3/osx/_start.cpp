#include <stdio.h>
#include <SDL/SDL.h>

static void initAttributes ()
{
	// Setup attributes we want for the OpenGL context

	int value;

	// Don't set color bit sizes (SDL_GL_RED_SIZE, etc)
	//    Mac OS X will always use 8-8-8-8 ARGB for 32-bit screens and
	//    5-5-5 RGB for 16-bit screens

	// Request a 16-bit depth buffer (without this, there is no depth buffer)
	// is there any speed benefit to using a lower precision depth buffer?
	value = 32;
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE, value);


	// Request double-buffered OpenGL
	//     The fact that windows are double-buffered on Mac OS X has no effect
	//     on OpenGL double buffering.
	value = 1;
	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER, value);
}

static void createSurface (int fullscreen)
{
	int flags = 0;

	flags = SDL_OPENGL;
	if (fullscreen)
		flags |= SDL_FULLSCREEN;

	// Create window
	SDL_Surface *surface = SDL_SetVideoMode (640, 480, 0, flags);
	if (surface == NULL) {

		fprintf (stderr, "Couldn't set 640x480 OpenGL video mode: %s\n",
			SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	SDL_WM_SetCaption("Blobs",NULL);
}

static void printAttributes ()
{
	// Print out attributes of the context we created
	int nAttr;
	int i;

	SDL_GLattr  attr[] = { SDL_GL_RED_SIZE, SDL_GL_BLUE_SIZE, SDL_GL_GREEN_SIZE,
		SDL_GL_ALPHA_SIZE, SDL_GL_BUFFER_SIZE, SDL_GL_DEPTH_SIZE };

	const char *desc[] = { "Red size: %d bits\n", "Blue size: %d bits\n", "Green size: %d bits\n",
		"Alpha size: %d bits\n", "Color buffer size: %d bits\n", 
		"Depth bufer size: %d bits\n" };

	nAttr = sizeof(attr) / sizeof(int);

	for (i = 0; i < nAttr; i++) {

		int value;
		SDL_GL_GetAttribute (attr[i], &value);
		printf (desc[i], value);
	} 
}

int main(int argc, char *argv[])
{
	// Init SDL video subsystem
	if ( SDL_Init (SDL_INIT_VIDEO) < 0 )
	{
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
			SDL_GetError());
		exit(1);
	}

	// Set GL context attributes
	initAttributes ();

	// Create GL context
	createSurface (0);

	// Get GL context attributes
	printAttributes ();

	// TODO app init
	// TODO app mainloop
	// TODO app shutdown
	//

	SDL_Quit();

	return 0;
}
