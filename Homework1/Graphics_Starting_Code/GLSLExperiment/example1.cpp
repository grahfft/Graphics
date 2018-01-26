// Starter program for HW 1. 
// Program draws a triangle. Study the program first
// The function generateGeometry can be modified to draw many 2D drawings (e.g. 2D Sierpinski Gasket)
// Generated using randomly selected vertices and bisection

#ifndef __IMAGES__
#define __IMAGES__

#include "Triangle.h"
#include "Sierpinski.h"

#endif // !__DATA__


// Number of points in polyline
int NumPoints = 0;

// General Functions
void initGPUBuffers( void );
void CopyGeometryToBuffer(Data *data);
void GenerateImage(Data *data);

// Initialization prototypes
void InitWindow(int argc, char **argv);
void InitCallbacks(void);
void InitShader(void);

// Callbacks
void display( void );
void keyboard( unsigned char key, int x, int y );

using namespace std;

// Array for polyline
point2 points[10000];
GLuint program;

// Images
Triangle *triangle;
Sierpinski *gasket;
/* -------------------------------------------------------------- */

void GenerateImage(Data *data) 
{
	CopyGeometryToBuffer(data);
	initGPUBuffers();
	data->SetupShader();
	data->DrawImage();
}

void CopyGeometryToBuffer(Data *data)
{
	data->GenerateGeometry();
	NumPoints = data->points.size();

	for (int index = 0; index < NumPoints; index++)
	{
		points[index] = data->points[index];
	}
}

void initGPUBuffers( void )
{
	// Create a vertex array object
	GLuint vao;
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW );
}

void display( void )
{
	// All drawing happens in display function
    glClear( GL_COLOR_BUFFER_BIT );                // clear window
    glDrawArrays( GL_LINE_LOOP, 0, NumPoints );    // draw the points
    glFlush();										// force output to graphics hardware
}

void keyboard( unsigned char key, int x, int y )
{
	// keyboard handler
	Data *data;

    switch ( key ) {
	case 's':
		/*
		Author's Notes:
		- Requires GL_POINTS to correctly draw
		- Drew 5000 iterations (NumPoints = 5000)
		- Re-read chapter 2
		- swap bug caused by not passing points into framebuffer; LINE_LOOP Test
		- default loc and proj are needed; best represented by a section each per
		*/
		if (!gasket)
		{
			gasket = new Sierpinski(program);

		}

		GenerateImage(gasket);
		break;
	case 't':
		if (!triangle)
		{
			triangle = new Triangle(program);
		}
		
		GenerateImage(triangle);
		break;
	case 'u':
		//TODO Generate USA file
		break;
	case 'd':
		//TODO Generate dragon file
		break;
	case 'v':
		//TODO Generate Vinci file
		break;
    case 033:			// 033 is Escape key octal value
        exit(1);		// quit program
        break;
    }
}

void InitWindow(int argc, char **argv)
{
	glutInit(&argc, argv);                       // intialize GLUT  
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // single framebuffer, colors in RGB
	glutInitWindowSize(640, 480);                // Window size: 640 wide X 480 high
	glutInitWindowPosition(100, 150);               // Top left corner at (100, 150)
	glutCreateWindow("Starting App");            // Create Window

	glewInit();										// init glew
}

void InitShader(void)
{
	// Load shaders and use the resulting shader program
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);

	glClearColor(1.0, 1.0, 1.0, 1.0);        // sets white as color used to clear screen
}

void InitCallbacks(void)
{
	glutDisplayFunc(display);                    // Register display callback function
	glutKeyboardFunc(keyboard);                  // Register keyboard callback function
}

int main( int argc, char **argv )
{
	// main function: program starts here
	InitWindow(argc, argv);
	InitShader();
	InitCallbacks();

	if (!triangle)
	{
		triangle = new Triangle(program);
	}
	GenerateImage(triangle);

	// Can add minimalist menus here
	// add mouse handler
	// add resize window functionality (should probably try to preserve aspect ratio)

	// enter the drawing loop
    glutMainLoop();
    return 0;
}
