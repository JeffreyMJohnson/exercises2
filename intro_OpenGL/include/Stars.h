#ifndef _STARS_H_
#define _STARS_H_

#include "Entity.h"
#include "Globals.h"
#include <time.h>

class Stars :
	public Entity
{
public:
	Stars()
	{
		LoadModelVertices();
		verticesBuffer = new Vertex[modelVertices.size()];
		glPointSize(2);
	}

	~Stars()
	{
		delete verticesBuffer;
	}

	void Draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));

		glDrawArrays(GL_POINTS, 0, modelVertices.size());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	const int NUMBER_OF_STARS = 100;
	void LoadModelVertices()
	{
		for (int i = 0; i < NUMBER_OF_STARS; i++)
		{
			int posX = rand() % Globals::SCREEN_WIDTH;
			int posY = rand() % Globals::SCREEN_HEIGHT;
			modelVertices.push_back(glm::vec4(posX, posY, 0, 1));
		}
	}
};
#endif