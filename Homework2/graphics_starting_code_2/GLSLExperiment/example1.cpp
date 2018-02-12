// Draws colored cube  

#ifndef __DATATYPES__
#define __DATATYPES__

#include "PlyManager.h"

#endif

// Program Variables----------------------------------------------------------

// GLUT Window Width
int width = 512;

// GLUT Window Height
int height = 512;

// Toggle for random colors
bool colorToggle = false;

// Index for Vertex Buffer
int pointColorIndex = 0;

// Polygon Manager
PlyManager *plyManager;

// Current Polygon to be drawn
Ply currentPolygon;

// handle to shader program
GLuint program;

// Number of vertices to be rendered; recalculated after swapping into buffer
int NumVertices = 0;

// vertices buffer
point4 points[MAXPOINTS];

// color buffer
color4 colors[MAXCOLOR];

// Function Prototypes -------------------------------------------------------

// Draw Polygon Prototypes ---------------------------------------------------

/*
* Helper function for adding to framebuffer
*/
void AddVertexAndColor(Vertex vertex);

/*
* Populate both buffers
*/
void copyPolygonToFrameBuffer(void);

/*
* Creates VBO; Stores vertex data into VBO; sends VBO to the shader
*/
void sendToShader();

/*
* Sets the current Projection Matrix
*/
void setProjectionMatrix(void);

/*
* Sets the current Model Matrix
* See Ch 3 Section 11
* CTM = Projection View Matrix * Model View Matrix * Vertex Position
*/
void setModelMatrix(void);

/*
* Draws the current polygon
*/
void drawPolygon(void);

/*
* Wraps all method calls needed to render a polygon
*/
void renderPolygon(void);

// Callback Prototypes -------------------------------------------------------

/*
* Display callback

// SOME RANDOM TIPS
//========================================================================
// remember to enable depth buffering when drawing in 3d

// avoid using glTranslatex, glRotatex, push and pop
// pass your own view matrix to the shader directly
// refer to the latest OpenGL documentation for implementation details

// Do not set the near and far plane too far appart!
// depth buffers do not have unlimited resolution
// surfaces will start to fight as they come nearer to each other
// if the planes are too far appart (quantization errors :(   )

*/
void display(void);

/*
* keyboard callback
*/
void keyboard(unsigned char key, int x, int y);

/*
* idle callback
*/
void idle();

/*
* reshape callback
*/
void reshape(int width, int height);

// Init Helper ProtoTypes -----------------------------------------------------

/*
* Clears program state in between renderings of different polygons
*/
void clearPriorPolygonState(void);

/*
* Initializes GLUT window
*/
void initWindow(int argc, char **argv);

/*
* Initializes polygon manager and loads ply files
*/
void initPolygons();

/*
* Maps callbacks to glut functions
*/
void initCallbacks();

/*
* Creates the vPosition array
*/
void setVertexArray();

/*
* Creates and marks the position of the color attribute
*/
void setColorArray();

// Draw Helper Prototypes ----------------------------------------------------

/*
* Creates the VAO and VBO
*/
void createVertexBufferObject();

/*
* Sends the points array to the shader
*/
void setVertexArray();

/*
* Sends the Colors array to the shader
*/
void setColorArray();

// Draw Polygon Definitions --------------------------------------------------

void AddVertexAndColor(Vertex vertex)
{
	if (pointColorIndex > MAXPOINTS || pointColorIndex > MAXCOLOR) return;

	points[pointColorIndex] = vertex.GetPosition();
	colors[pointColorIndex] = vertex.GetColor();
	pointColorIndex++;
}

void copyPolygonToFrameBuffer()
{
	// Load Geometry
	pointColorIndex = 0;
	vector<Face> faces = currentPolygon.getFaces();
	vector<Vertex> vertices = currentPolygon.getVertices();

	// Add vertices and colors from the faces
	for (int index = 0; index < faces.size(); index++)
	{
		Face currentFace = faces[index];
		AddVertexAndColor(vertices[currentFace.v1]);
		AddVertexAndColor(vertices[currentFace.v2]);
		AddVertexAndColor(vertices[currentFace.v3]);
	}

	NumVertices = pointColorIndex - 1;
}

void setProjectionMatrix()
{
	// Section for Projection Matrix
	Angel::mat4 perspectiveMat = Angel::Perspective((GLfloat)45.0, (GLfloat)width / (GLfloat)height, (GLfloat)0.1, (GLfloat) 100.0);

	float viewMatrixf[16];
	viewMatrixf[0] = perspectiveMat[0][0]; viewMatrixf[4] = perspectiveMat[0][1];
	viewMatrixf[1] = perspectiveMat[1][0]; viewMatrixf[5] = perspectiveMat[1][1];
	viewMatrixf[2] = perspectiveMat[2][0]; viewMatrixf[6] = perspectiveMat[2][1];
	viewMatrixf[3] = perspectiveMat[3][0]; viewMatrixf[7] = perspectiveMat[3][1];

	viewMatrixf[8] = perspectiveMat[0][2]; viewMatrixf[12] = perspectiveMat[0][3];
	viewMatrixf[9] = perspectiveMat[1][2]; viewMatrixf[13] = perspectiveMat[1][3];
	viewMatrixf[10] = perspectiveMat[2][2]; viewMatrixf[14] = perspectiveMat[2][3];
	viewMatrixf[11] = perspectiveMat[3][2]; viewMatrixf[15] = perspectiveMat[3][3];

	GLuint viewMatrix = glGetUniformLocationARB(program, "projection_matrix");
	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, viewMatrixf);
}

void setModelMatrix()
{
	// Section for Model Matrix
	Angel::mat4 modelMat = Angel::identity();
	modelMat = modelMat * Angel::Translate(0.0, 0.0, -2.0f) * Angel::RotateY(45.0f) * Angel::RotateX(35.0f); // Remember to post multiply

	float modelMatrixf[16];
	modelMatrixf[0] = modelMat[0][0]; modelMatrixf[4] = modelMat[0][1];
	modelMatrixf[1] = modelMat[1][0]; modelMatrixf[5] = modelMat[1][1];
	modelMatrixf[2] = modelMat[2][0]; modelMatrixf[6] = modelMat[2][1];
	modelMatrixf[3] = modelMat[3][0]; modelMatrixf[7] = modelMat[3][1];

	modelMatrixf[8] = modelMat[0][2]; modelMatrixf[12] = modelMat[0][3];
	modelMatrixf[9] = modelMat[1][2]; modelMatrixf[13] = modelMat[1][3];
	modelMatrixf[10] = modelMat[2][2]; modelMatrixf[14] = modelMat[2][3];
	modelMatrixf[11] = modelMat[3][2]; modelMatrixf[15] = modelMat[3][3];

	// set up projection matricies
	GLuint modelMatrix = glGetUniformLocationARB(program, "model_matrix");
	glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, modelMatrixf);
}

void drawPolygon()
{
	// change to GL_FILL
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	// draw functions should enable then disable the features 
	// that are specifit the themselves
	// the depth is disabled after the draw 
	// in case you need to draw overlays
	glEnable( GL_DEPTH_TEST );
    glDrawArrays( GL_TRIANGLES, 0, NumVertices );
	glDisable( GL_DEPTH_TEST ); 
}

void sendToShader()
{
	createVertexBufferObject();
	setVertexArray();
	setColorArray();

	// sets the default color to clear screen
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background
}

void renderPolygon()
{
	copyPolygonToFrameBuffer();
	sendToShader();
	setProjectionMatrix();
	setModelMatrix();
	drawPolygon();
}

//Callback Definitions -------------------------------------------------------

void display( void )
{
	// clear the window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );     

	// prepare polygon information for framebuffer
	renderPolygon();

	// force output to graphics hardware
    glFlush(); 

	// use this call to double buffer
	glutSwapBuffers();
}

void keyboard( unsigned char key, int x, int y )
{
    switch ( key ) 
	{
	case 'W':
		// TODO: (Draw your wireframe) at a suitable initial position from the viewer. 
		// Question: Does this mean a reset to color and CTM?
		// TODO: Currently working but need to set start position and bounding box
		// After changing x, y or z location, or rotating the wireframe (R key), W resets position and rotation by drawing the wireframe at origin and with no rotation applied. 
		// W does NOT reset shear and twist effects.
		currentPolygon = plyManager->GetCurrentPly();
		clearPriorPolygonState();
		break;

	case 'N':
		// TODO: (Draw next wireframe) Organize the PLY files in a list going from 1-43. 
		// Hitting N should load and draw the next wireframe model to the current one in your list of PLY files. 
		// You can hardcode filenames if you want. The PLY files may not all be of the same size. 
		// So to properly set up the viewing position using LookAt, you may have to calculate the bounding box of the mesh and then set your view distance to a suitable multiple of the bounding box
		// TODO: Currently working but need to set start position and bounding box
		currentPolygon = plyManager->GetNextPly();
		clearPriorPolygonState();
		break;

	case 'P':
		// TODO: (Draw previous wireframe) Organize the PLY files in a list going from 1-43. 
		// Hitting P should load and draw the previous wireframe model to the current one in your list of PLY files. 
		// TODO: Currently working but need to set start position and bounding box
		currentPolygon = plyManager->GetPreviousPly();	
		clearPriorPolygonState();
		break;

	case 'X':
		// TODO: (Translate your wireframe in the +ve X direction) Continously move your wireframe some small units along the +ve X axis and redraw it. 
		// Use the idle function to animate this. The ply file should continue to slide along the +ve X axis till the user hits 'X' again. 
		// Essentially, the 'X' key acts as a toggle key. If the ply file is stationary and the user hits the 'X' key, the ply file should continue to slide along the +ve X axis until the user hits 'X' again. 
		// Camera position remains fixed for this translation and all other translations below. 
		// The exact amount to move the ply file before redrawing will affect how much and how much your translation is apparent depends on how far you positioned your wireframe from the viewer. 
		// So, it's left to you as a design choice to pick an appropriate distance to translate the wireframe along the +ve X axis each time the user hits 'X'. 

		// Pressing 'X' and then 'x' moves the PLY file along +x then -x. Translations are generally concatenated. 
		// Hitting 'X' and then 'Y' moves the PLY file along the +x direction and then WITHOUT RETURNING TO ORIGIN, moves the PLY file along +y direction.
		break;

	case 'x':
		// TODO: (Translate your wireframe in the -ve X direction) Use the idle function to continuously move your wireframe some units along the -ve X axis. 
		// The number of units to translate your wireframe each time the user hits 'x' is left to you as a design choice. 
		break;

	case 'Y':
		// TODO: (Translate your wireframe in the +ve Y direction) Use the idle function to continuously move your wireframe some units along the +ve Y axis. 
		// The number of units to translate your wireframe each time the user hits 'Y' is left to you as a design choice. 
		break;

	case 'y':
		// TODO: (Translate your wireframe in the -ve y direction) Use the idle function to continuously move your wireframe some units along the -ve Y axis. 
		// The number of units to translate your wireframe each time the user hits 'y' is left to you as a design choice. 
		break;

	case 'Z':
		// TODO: (Translate your wireframe in the +ve Z direction) Use the idle function to continuously move your wireframe some units along the +ve Z axis. 
		// The number of units to translate your wireframe each time the user hits 'Z' is left to you as a design choice.
		break;

	case 'z':
		// TODO: (Translate your wireframe in the -ve Z direction) Use the idle function to continuously move your wireframe some units along the -ve Z axis. 
		// The number of units to translate your wireframe each time the user hits 'z' is left to you as a design choice.
		break;

	case 'R':
		// TODO: (Rotate your wireframe about it's CURRENT position) Just like in a showroom where the wireframe is on a swivel, rotate your wireframe smoothly 360 degrees at a moderate speed about its CURRENT position (not about the center of the scene) 
		// This rotation is NOT the same as moving the wireframe in a wide arc. The rotation should be about the Y axis and the wireframe should not translate while rotating. 
		// After each 360 degree rotation of the "current" PLY file, load and display the "next" (of the 43 PLY) files. 
		// In this way, after 43 cycles, all polyline files should have been drawn one by one. On the 44th cycle, go back and display the first PLY file that was drawn. 
		// Finally, alternate between rotating PLY files clockwise and counter-clockwise. For instance, PLY file 1 should rotate 360 degrees clockwise before loading PLY file 2 which rotates counterclockwise before loading PLY file 3 which rotates clockwise, and so on.
		// Hint: Use double buffering (glutSwapBuffers( )) to make the rotation smooth. You can continously update the new wireframe positions and redisplay the meshes in the glutIdleFunc function. 
		//
		// If the PLY file is translating when the 'R' key is hit, just stop the translation and rotate the PLY file about the Y axis AT THE CURRENT LOCATION.
		// Do NOT reset the PLY file to origin before applying the rotation.
		//
		// The 'R' key is hit once and then the current PLY file is rotated clockwise 360 degrees.After this 360 degree rotation, this current PLY file is erased and the next PLY file is drawn at the same position and then rotated ANTI - CLOCKWISE 360 degrees.
		// This file is then erased and the next PLY file is drawn and rotated CLOCKWISE 360 degrees, and so on.Essentially, PLY file 1 is rotated clockwise, PLY file 2 is rotated anti - clockwise, PLY file 3 is rotated clockwise, etc.
		// If the user hits 'R' once and just watches, PLY files 1 - 43 will eventually be displayed one by one WITHOUT ANY ADDITIONAL keys being pressed.
		break;

	case 'c':
		// Toggle defaulted to off on start
		// Toggle resets between renderings
		colorToggle = !colorToggle;
		currentPolygon.UpdateColor(colorToggle);	
		break;

	case 'h':
		// TODO: Increment the amount of shearing of the wireframe along the X axis by a small amount. 
		// Repeatedly hitting the 'h' key should shear the wireframe by a bit more and more. 
		// Note that after you shear the mesh, performing a transform (e.g. rotation, scale or translate) should transform the sheared mesh. 
		//
		// If shearing is applied and you decrease shearing (H key), the shearing should be reduced till a value of 0 (no shearing). 
		// Trying to reduce shearing further beyond 0 should have no effect. 
		// The same goes for twist. 
		// Trying to reduce twist beyond 0 should have no effect.
		break;

	case 'H':
		// TODO: Decrease the amount of shearing of the wireframe along the X axis by a small amount. 
		// Repeatedly hitting the 'H' key should shear the wireframe by a bit less and less. 
		// Note that after you shear the mesh, performing a transform (e.g. rotation, scale or translate) should transform the sheared mesh.
		break;

	case 't':
		// TODO:  Increment the amount of twisting of the wireframe around the Y axis by a small amount. 
		// Repeatedly hitting the 't' key should twist the wireframe by a bit more and more. 
		// Note that after you twist the mesh, performing a transform (e.g. rotation, scale or translate) should transform the twisted mesh.
		break;

	case 'T':
		//TODO: Decrease the amount of twisting of the wireframe around the Y axis by a small amount. 
		// Repeatedly hitting the 'T' key should twist the wireframe by a bit less and less. 
		// Note that after you twist the mesh, performing a transform (e.g. rotation, scale or translate) should transform the twisted mesh.
		break;

    case 033:
        exit( EXIT_SUCCESS );
        break;
    }

	display();
}

void idle() 
{

}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
}

// Draw Helper Definitions ---------------------------------------------------

void createVertexBufferObject()
{
	// Create a vertex array object
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create and initialize a buffer object
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points) + sizeof(colors),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors);
}

void setVertexArray()
{
	// set up vertex arrays
	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(0));
}

void setColorArray()
{
	GLuint vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(sizeof(points)));
}

// Helper Definitions --------------------------------------------------------

void clearPriorPolygonState()
{
	colorToggle = false;
}

void initWindow(int argc, char **argv)
{
	// init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);

	// create window opengl can be incorperated into other packages like wxwidgets, fltoolkit, etc.
	glutCreateWindow("CS543 Computer Graphics Homework 2");

	// init glew
	glewInit();
}

void initPolygons()
{
	
	plyManager = new PlyManager(program);
	plyManager->LoadPlyFiles();
	currentPolygon = plyManager->GetCurrentPly();
	copyPolygonToFrameBuffer();
}

void initCallbacks()
{
	// assign callback handlers
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
}

void initShaders()
{
	// Load shaders and use the resulting shader program
	program = InitShader("vshader1.glsl", "fshader1.glsl");
	glUseProgram(program);
}

//entry point ----------------------------------------------------------------
int main( int argc, char **argv )
{
	// initialize GLUT window and polygon manager
	initWindow(argc, argv);
	initPolygons();
	initCallbacks();
	createVertexBufferObject();
	initShaders();

	// Added so white background doesn't flicker on start
	// prepareVertexBufferObject();
	glClearColor(1.0, 1.0, 1.0, 1.0); // white background

	// enter the drawing loop
    glutMainLoop();
    return 0;
}
