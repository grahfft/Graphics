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
			int pplAttribute;
			float x;
			float y;
			int numberOfTokens = tokens.size();

			switch (numberOfTokens)
			{
			case 1:
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
				x = stof(tokens[0]);
				y = stof(tokens[1]);
				
				this->points.push_back(point2(x, y));
				break;
			case 4:
				this->left = stof(tokens[0]);
				this->top = stof(tokens[1]);
				this->right = stof(tokens[2]);
				this->bottom = stof(tokens[3]);

				break;
			default:
				cout << "ERROR!!!! Shouldn't get here, token size: " << tokens.size() << endl;
				break;
			}
		}

		inFile.close();
	}
}

void DatFile::DrawImage()
{
	glClear(GL_COLOR_BUFFER_BIT);                // clear window

	float w, h;
	w = this->width / 4;
	h = this->height / 4;
	for (int k = 0; k<4; k++) {
		for (int m = 0; m<4; m++) {
			glViewport(k * w, m * h, w, h);
			int startPoint = 0;

			for (int index = 0; index < this->pointsPerLine.size(); index++)
			{
				glDrawArrays(GL_LINE_STRIP, startPoint, pointsPerLine[index]);    // draw the points
				startPoint = startPoint + pointsPerLine[index];
			}
		}
	}
	
	glFlush();
}