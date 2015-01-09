#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include "glm\glm.hpp"
#include <vector>

//generic vertex for sending to GPU via Vertex Buffer Object
struct Vertex
{
	float fPositions[4];
	float fColors[4];
};

#define BUFFERSIZE sizeof(Vertex) * modelVertices.size()

class Entity
{
public:
	//eventually make this a file path so can load model data via file.
	void Initialize(glm::vec4& a_position, glm::vec4& a_color)
	{
		position = a_position;
		color = a_color;
		glGenBuffers(1, &uiVBO);
		UpdateVertices();

	}

	void SetPosition(glm::vec4& a_position)
	{
		position = a_position;
		UpdateVertices();
	}

	virtual void Draw() = 0;
	


protected:
	std::vector<glm::vec4> modelVertices;
	glm::vec4 position;
	glm::vec4 color;
	GLuint uiVBO;
	Vertex* verticesBuffer;

	virtual void LoadModelVertices() = 0;

	void UpdateVBO()
	{
		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		//size of buffer needs to be 3 vec4 for vertices and 3 vec4 for 
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * modelVertices.size(), NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy data to graphics card
		memcpy(vBuffer, verticesBuffer, sizeof(Vertex) * modelVertices.size());
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void UpdateVertices()
	{
		for (int i = 0; i < modelVertices.size(); i++)
		{
			verticesBuffer[i].fPositions[0] = modelVertices[i].x + position.x;
			verticesBuffer[i].fPositions[1] = modelVertices[i].y + position.y;
			verticesBuffer[i].fPositions[2] = 0;
			verticesBuffer[i].fPositions[3] = 1;
			verticesBuffer[i].fColors[0] = color.r;
			verticesBuffer[i].fColors[1] = color.g;
			verticesBuffer[i].fColors[2] = color.b;
			verticesBuffer[i].fColors[3] = color.a;
		}
		UpdateVBO();
	}
};

#endif