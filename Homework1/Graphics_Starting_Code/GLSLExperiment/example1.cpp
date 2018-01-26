// Starter program for HW 1. 
// Program draws a triangle. Study the program first
// The function generateGeometry can be modified to draw many 2D drawings (e.g. 2D Sierpinski Gasket)
// Generated using randomly selected vertices and bisection

#include "Angel.h"  // Angel.h is homegrown include file, which also includes glew and freeglut

// Number of points in polyline
int NumPoints = 0;

// Function to draw
void(*drawImage)(void);

// remember to prototype
void generateGeometry( void );
void GenerateSeirpinski(void);
void GenerateDatFile(void);
void initGPUBuffers( void );
void shaderSetup( void );
void display( void );
void keyboard( unsigned char key, int x, int y );

typedef vec2 point2;

using namespace std;

// Array for polyline
point2 points[10000];
GLuint program;

// Mode for drawing
GLenum mode = GL_LINE_LOOP;
/* -------------------------------------------------------------- */


/* Geometry Generation Section */
void generateGeometry( void )
{
	// Specifiy the vertices for a triangle
	NumPoints = 3;

	points[0] = point2( -0.5, -0.5 );
	points[1] = point2( 0.0, 0.5 );
	points[2] = point2( 0.5, -0.5 );
}

void GenerateSeirpinski(void)
{
	/*
	Author's Notes:
		- Requires GL_POINTS to correctly draw
		- Drew 5000 iterations (NumPoints = 5000)
		- Re-read chapter 2
	*/

	mat4 ortho = Ortho2D(-2.0, 2.0, -2.0, 2.0);
	GLuint ProjLoc = glGetUniformLocation(program, "Proj");
	glUniformMatrix4fv(ProjLoc, 1, GL_TRUE, ortho);

	mode = GL_POINTS;

	NumPoints = 10000;
	point2 vertices[3];
	vertices[0] = point2(-1.0, -1.0);
	vertices[1] = point2(0.0, 1.0);
	vertices[2] = point2(1.0, -1.0);

	points[0] = point2(.25, .5);

	for (int index = 1; index < NumPoints; index++)
	{
		int determineVertex = rand() % 3;
		points[index] = (points[index - 1] + vertices[determineVertex]) / 2.0;
	}
}

/*
Author-s Notes:
	- Adding Proj * vPosition causes other drawings to break; why?; Default Proj needed
	- 
*/

void GenerateDatFile(void)
{
	//mat4 ortho = Ortho2D(left, right, bottom, top);
	GLuint ProjLoc = glGetUniformLocation(program, "Proj");
	//glUniformMatrix4fv(ProjLoc, 1, GL_TRUE, ortho);
}

/* ------------------------------------------------------------- */

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


void shaderSetup( void )
{
	// Load shaders and use the resulting shader program
    program = InitShader( "vshader1.glsl", "fshader1.glsl" );
    glUseProgram( program );

    // Initialize the vertex position attribute from the vertex shader
    GLuint loc = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( loc );
    glVertexAttribPointer( loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	mat4 ortho = Ortho2D(-1.0, 1.0, -1.0, 1.0);
	GLuint ProjLoc = glGetUniformLocation(program, "Proj");
	glUniformMatrix4fv(ProjLoc, 1, GL_TRUE, ortho);

    glClearColor( 1.0, 1.0, 1.0, 1.0 );        // sets white as color used to clear screen
}


void display( void )
{
	// All drawing happens in display function
    glClear( GL_COLOR_BUFFER_BIT );                // clear window
    glDrawArrays( mode, 0, NumPoints );    // draw the points
    glFlush();										// force output to graphics hardware
}


void keyboard( unsigned char key, int x, int y )
{
	// keyboard handler

    switch ( key ) {
	case 's':
		GenerateSeirpinski();
		display();
		break;
    case 033:			// 033 is Escape key octal value
        exit(1);		// quit program
        break;
    }
}


int main( int argc, char **argv )
{
	// main function: program starts here

    glutInit( &argc, argv );                       // intialize GLUT  
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB ); // single framebuffer, colors in RGB
    glutInitWindowSize( 640, 480 );                // Window size: 640 wide X 480 high
	glutInitWindowPosition(100,150);               // Top left corner at (100, 150)
    glutCreateWindow( "Starting App" );            // Create Window

    glewInit();										// init glew

	GenerateDatFile();
    //generateGeometry( );                           // Call function that generates points to draw
	GenerateSeirpinski();
	initGPUBuffers( );							   // Create GPU buffers
    shaderSetup( );                                // Connect this .cpp file to shader file

    glutDisplayFunc( display );                    // Register display callback function
    glutKeyboardFunc( keyboard );                  // Register keyboard callback function

	// Can add minimalist menus here
	// add mouse handler
	// add resize window functionality (should probably try to preserve aspect ratio)

	// enter the drawing loop
    glutMainLoop();
    return 0;
}
