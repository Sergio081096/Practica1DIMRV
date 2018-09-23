//Cano Olguin Luis Sergio
//Cruz Gomez Harold Antonio
//Hernandez Cuellar Jonathan
//DIMRV
//PRACTICA 1
//17/Septiembre/2018


#include <SDL_opengl.h>
#include <stdio.h>
#include <SDL.h>
#include <Main.h>


#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <sstream>
//Dimension de la Pantalla
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

float transX = 0.0;
float transZ = 0.0;
float angleX = 0.0;
float angleY = 0.0;

int a;

float c = 0;
float b = 1;

// La música que se reproducirá
Mix_Music *gMusic = NULL;

// Los efectos de sonido que se usarán
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;

//Bandera principal
bool quit = false;


//Iniciamos SDL, crea una ventana en OpenGL
bool init();

bool loadMedia();

//Matrices de colores
bool initGL();

//Controlador para el uso del teclado
void handleKeys(unsigned char key, int x, int y);

void prisma();

//Actualizacion de los cuadros
void update();

//Funcion para dibujar
void display();

//Liberamos lo que se utilize de SDL
void close();

//Renderizamos la ventana
SDL_Window* gWindow = NULL;

//Contexto de SDL
SDL_GLContext gContext;

bool init()
{
	bool success = true;

	//Inicializamos SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Para uso especifico de OpenGL 2.0
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		//Creamos la ventana
		gWindow = SDL_CreateWindow("Practica 1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{

			gContext = SDL_GL_CreateContext(gWindow);
			if (gContext == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Inicializamos OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
				

				//Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load prompt texture
	//if (!gPromptTexture.loadFromFile("21_sound_effects_and_music/prompt.png"))
	//{
		//printf("Failed to load prompt texture!\n");
		//success = false;
	//}
	
	//Load music
	gMusic = Mix_LoadMUS("beat.wav");
	if (gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	//Load sound effects
	gScratch = Mix_LoadWAV("scratch.wav");
	if (gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gHigh = Mix_LoadWAV("high.wav");
	if (gHigh == NULL)
	{
		printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gMedium = Mix_LoadWAV("medium.wav");
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	gLow = Mix_LoadWAV("low.wav");
	if (gLow == NULL)
	{
		printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}


void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista
	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 50.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
}

bool initGL()
{
	bool success = true;
	GLenum error = GL_NO_ERROR;

	//Proyecciones
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//Verificamos error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
	}

	//Matrz de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
	}

	//Color de la pantalla
	glClearColor(0.f, 0.f, 0.f, 1.f);

	//Check for error
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		success = false;
	}

	return success;
}

void handleKeys(unsigned char key, int x, int y)
{


	switch (key)
	{
	case 'Q':
	case 'q':
		quit = true;
		break;
	case 'w':
	case 'W':
		transX += .1f;
		break;
	case 's':
	case 'S':
		transX -= .1f;
		break;
	case 'a':
	case 'A':
		transZ -= .1f;
		break;
	case 'd':
	case 'D':
		transZ += .1f;
		break;
	}
}



void update()
{
	//No per frame update needed
}

void prisma()
{
	GLfloat vertice[8][3] = {
					{0.5 ,-0.5, 0.5},    //Coordenadas Vértice 0 V0
					{-0.5 ,-0.5, 0.5},    //Coordenadas Vértice 1 V1
					{-0.5 ,-0.5, -0.5},    //Coordenadas Vértice 2 V2
					{0.5 ,-0.5, -0.5},    //Coordenadas Vértice 3 V3
					{0.5 ,0.5, 0.5},    //Coordenadas Vértice 4 V4
					{0.5 ,0.5, -0.5},    //Coordenadas Vértice 5 V5
					{-0.5 ,0.5, -0.5},    //Coordenadas Vértice 6 V6
					{-0.5 ,0.5, 0.5},    //Coordenadas Vértice 7 V7
	};

	glBegin(GL_POLYGON);	//Front		
	glColor3f(c, b, 0);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[1]);
	glEnd();

	glBegin(GL_POLYGON);	//Right
	//glColor3f(0, 1, 0);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[4]);
	glEnd();

	glBegin(GL_POLYGON);	//Back
	//glColor3f(0, 0, 1);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[3]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Left
	//glColor3f(1, 1, 0);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[7]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[2]);
	glEnd();

	glBegin(GL_POLYGON);  //Bottom
	//glColor3f(1, 0, 1);
	glVertex3fv(vertice[0]);
	glVertex3fv(vertice[1]);
	glVertex3fv(vertice[2]);
	glVertex3fv(vertice[3]);
	glEnd();

	glBegin(GL_POLYGON);  //Top
	//glColor3f(0, 1, 1);
	glVertex3fv(vertice[4]);
	glVertex3fv(vertice[5]);
	glVertex3fv(vertice[6]);
	glVertex3fv(vertice[7]);
	glEnd();

}

void display()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);


	//Render quad

	glRotatef(0.2, 0.0f, 1.0f, 0.0f);    // Rotate The cube around the Y axis
	glRotatef(0.2f, 1.0f, 1.0f, 1.0f);

	//glColor3f(0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glTranslatef(transX, 0, transZ);
	prisma();
	glPopMatrix();
}

void close()
{
	//Free loaded images
	//gPromptTexture.free();

	//Free the sound effects
	Mix_FreeChunk(gScratch);
	Mix_FreeChunk(gHigh);
	Mix_FreeChunk(gMedium);
	Mix_FreeChunk(gLow);
	gScratch = NULL;
	gHigh = NULL;
	gMedium = NULL;
	gLow = NULL;

	//Free the music
	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	//Destruimos la ventana
	//SDL_DestroyRenderer(gRenderer);
	//gRenderer = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quitamos todos los subsistemas de SDL
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Iniciamos SDL y creamos ventana
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{

		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Controlador de eventos
			SDL_Event e;

			//Entrada de texto
			SDL_StartTextInput();

			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}
					//Handle keypress with current mouse position
					else if (e.type == SDL_TEXTINPUT)
					{
						int x = 0, y = 0;
						SDL_GetMouseState(&x, &y);
						handleKeys(e.text.text[0], x, y);
					}
					else if (e.type == SDL_KEYDOWN)
					{
						switch (e.key.keysym.sym)
						{
						case SDLK_F1:
							c = 1;
							b = 1;
							break;
						case SDLK_F2:
							c = .5;
							b = 0;
							break;
						case SDLK_F3:
							glColor3f(1, 0.5, 0);
							prisma(); //el color del cuadro es negro						
							break;
							//Play high sound effect
						case SDLK_1:
							Mix_PlayChannel(-1, gHigh, 0);
							break;

							//Play medium sound effect
						case SDLK_2:
							Mix_PlayChannel(-1, gMedium, 0);
							break;

							//Play low sound effect
						case SDLK_3:
							Mix_PlayChannel(-1, gLow, 0);
							break;

							//Play scratch sound effect
						case SDLK_4:
							Mix_PlayChannel(-1, gScratch, 0);
							break;

						case SDLK_9:
							//If there is no music playing
							if (Mix_PlayingMusic() == 0)
							{
								//Play the music
								Mix_PlayMusic(gMusic, -1);
							}
							//If music is being played
							else
							{
								//If the music is paused
								if (Mix_PausedMusic() == 1)
								{
									//Resume the music
									Mix_ResumeMusic();
								}
								//If the music is playing
								else
								{
									//Pause the music
									Mix_PauseMusic();
								}
							}
							break;

						case SDLK_0:
							//Stop the music
							Mix_HaltMusic();
							break;
						}
					}
					else if (e.type == SDL_QUIT)
					{
						float transX = 0.0;
						float transZ = 0.0;
						float angleX = 0.0;
						float angleY = 0.0;
					}

				}

				//Render quad
				display();

				//Update screen
				SDL_GL_SwapWindow(gWindow);
			}

			//Disable text input
			SDL_StopTextInput();
		}
		
		
	}

	//Free resources and close SDL
	close();

	return 0;
}