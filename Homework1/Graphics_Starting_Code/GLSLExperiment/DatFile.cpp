#include "DatFile.h"


void DatFile::GenerateGeometry()
{
	if (this->points.size() <= 0)
	{
		this->points = vector<point2>();
		ifstream inFile;
		string fileLocation = "..\\HomegrownFiles\\" + filename;

		inFile.open(fileLocation);

		if (!inFile)
		{
			printf("Failed to open File: %s\n", fileLocation);
			return;
		}

		string oneLine;
		bool startParse = false;

		int totalLines = 0;

		while (inFile)
		{
			//Take in and parse the line
			getline(inFile, oneLine, '\n');	
			istringstream iss(oneLine);
			vector<string> tokens{ istream_iterator<string>{iss},
				istream_iterator<string>{} };

			// Determine when to start parsing
			if (!startParse)
			{
				if (tokens.size() == 1 && tokens[0][0] == '*')
				{
					startParse = true;			
				}
				continue;
			}

			/*
				The structure of GRS files is:

				a number of comment lines, followed by a line starting with at least one asterisk: '*'. - ignore
				The "extent" of the figure: (left, top, right, bottom). - set to left top right bottom
				The number of polylines in the figure. - init pointsPerLine
				The list of polylines: each starts with the number of points in the polyline, followed by the (x, y) pairs for each point. - add first value to pointsPerLine, create point out of subsequent lines
		
			*/
			cout << "Parsing Tokens" << endl;
			int pplAttribute;
			float x;
			float y;
			int numberOfTokens = tokens.size();

			switch (numberOfTokens)
			{
			case 1:
				cout << "Adding a new line" << endl;
				pplAttribute = stoi(tokens[0]);

				if (!totalLines)
				{
					totalLines = pplAttribute;
					pointsPerLine = vector<int>();
				}
				else {
					pointsPerLine.push_back(pplAttribute);
				}
				break;
			case 2:
				cout << "X: " << tokens[0] << " Y: " << tokens[1] << endl;
				x = stof(tokens[0]);
				y = stof(tokens[1]);
				
				this->points.push_back(point2(x, y));
				break;
			case 4:
				this->left = stof(tokens[0]);
				this->top = stof(tokens[1]);
				this->right = stof(tokens[2]);
				this->bottom = stof(tokens[3]);

				cout << "Left: " << this->left << " Top: " << this->top << " Right: " << this->right << " Bottom: " << this->bottom << endl;
				break;
			default:
				cout << "ERROR!!!! Shouldn't get here" << endl;
				break;
			}
		}

		cout << "closing the file" << endl;
		inFile.close();
	}
}

void DatFile::SetupShader() 
{
	mat4 ortho = Ortho2D(this->left, this->right, this->bottom, this->top);
	GLuint ProjLoc = glGetUniformLocation(program, "Proj");
	glUniformMatrix4fv(ProjLoc, 1, GL_TRUE, ortho);

	// Initialize the vertex position attribute from the vertex shader
	GLuint loc = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(loc);
	glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}

void DatFile::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window

	int startPoint = 0;

	for (int index = 0; index < this->pointsPerLine.size(); index++)
	{
		glDrawArrays(GL_LINE_STRIP, startPoint, pointsPerLine[index]);    // draw the points
		startPoint = startPoint + pointsPerLine[index];
	}
	
	glFlush();
}