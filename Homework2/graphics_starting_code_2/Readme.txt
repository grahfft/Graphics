Please read:

opengl-quick-reference-card.pdf
glsl_quickref.pdf
The OpenGL Shading Language.pdf

before starting.


OGL manpages:
http://www.opengl.org/sdk/docs/manglsl/

Homework2 Write up

Known issues:

- Using the showcase has a memory bug that needed major overhaul to fix. Wasn't able to finish in time
	- potential solutions are moving color out and removing Vertex class wrapper
	- clean up my pointers
- I didn't understand the LookAt function and went to look in the class notes for help. We hadn't studied this in class yet.

Structure:

Vertex
	- This class is a data container class for point4s and color4s
	- Used to map Color to Vertex

Face
	- This class is a data container class for vertices
	- Used for the vertex list

Ply
	- class contains all data from a Ply File
	- Manipulated by all transformer classes

PlyBuilder
	- Loads a file and builds the mesh from the data provided
	- Should be set up to dynamically load

PlyManager
	- Manages the current, previous and next mesh to load
	- loads up all ply files

Translator
	- Manages all translation matrices
	- create the concatentated matrix of all translations

Shearer
	- Shear the mesh
	- goes from 0 - 180

Showcase
	- this class is responsible for the R rotation
	- Provides a matrix for rotating

Twister
	- this class is responsible for twisting the image
	- creates the matrix for twisting transformation

ColorRandomizer
	- Randomizes the colors of a vertex if toggled on

Bounding Box
	- Data class for calculating the bounding box of a mesh
