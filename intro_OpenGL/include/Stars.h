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
		//no texture
		textureWidth = 0;
		textureHeight = 0;
		textureBPP = 0;
		uiTextureID = 0;
	}

	~Stars()
	{
		delete verticesBuffer;
	}

	void Draw(GLuint uniformLocationID, float* orthoProjection)
	{
		glUseProgram(programShader);

		//send ortho projection info to shader
		glUniformMatrix4fv(uniformLocationID, 1, GL_FALSE, orthoProjection);

		//enable vertex array state
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));

		glDrawElements(GL_POINTS, modelVertices.size(), GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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