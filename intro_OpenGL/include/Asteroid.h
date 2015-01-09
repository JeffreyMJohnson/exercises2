#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include "Entity.h"

class Asteroid :
	public Entity
{
public:
	Asteroid()
	{
		LoadModelVertices();
		verticesBuffer = new Vertex[modelVertices.size()];
	}
	~Asteroid()
	{
		delete verticesBuffer;
	}

	void Draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));

		glDrawElements(GL_LINE_LOOP, modelVertices.size(), GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
private:
	void LoadModelVertices()
	{
		modelVertices.push_back(glm::vec4(6, 18, 0, 1));
		modelVertices.push_back(glm::vec4(24, 6, 0, 1));
		modelVertices.push_back(glm::vec4(18, -12, 0, 1));
		modelVertices.push_back(glm::vec4(0, -18, 0, 1));
		modelVertices.push_back(glm::vec4(-18, -12, 0, 1));
		modelVertices.push_back(glm::vec4(-18, 6, 0, 1));
		modelVertices.push_back(glm::vec4(-6, 18, 0, 1));
	}
};
#endif