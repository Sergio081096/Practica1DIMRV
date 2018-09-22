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

//Bandera principal
bool quit = false;


//Iniciamos SDL, crea una ventana en OpenGL
bool init();

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
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
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
			}
		}
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
	//Destruimos la ventana
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quitamos todos los subsistemas de SDL
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
					switch (e.key.keysym.sym) {
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

	//Free resources and close SDL
	close();

	return 0;
}