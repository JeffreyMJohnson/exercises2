#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Entity.h"

class Player : 
	public Entity
{
public:
	Player()
	{
		LoadModelVertices();
		verticesBuffer = new Vertex[modelVertices.size()];
	}

	~Player()
	{
		delete verticesBuffer;
	}

	void Draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));

		glDrawArrays(GL_TRIANGLES, 0, modelVertices.size());

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:

	void LoadModelVertices()
	{
		modelVertices.push_back(glm::vec4(0, 10.0f, 0, 1));
		modelVertices.push_back(glm::vec4(-5.0f, -10.0f, 0, 1));
		modelVertices.push_back(glm::vec4(5.0f, -10.0f, 0, 1));
	}
};
#endif