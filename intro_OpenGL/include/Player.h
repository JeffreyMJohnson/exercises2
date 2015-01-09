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
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));

		glDrawElements(GL_TRIANGLES, modelVertices.size(), GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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