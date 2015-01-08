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

class Entity
{
public:
	//eventually make this a file path so can load model data via file.
	void Initialize(glm::vec4& a_position, glm::vec4& a_color)
	{

		position = a_position;
		color = a_color;

	}

	virtual void Draw() = 0;
	


protected:
	std::vector<glm::vec4> modelVertices;
	glm::vec4 position;
	glm::vec4 color;
	GLuint uiVBO;
	GLint verticeCount;
	Vertex* verticesBuffer;

	virtual void LoadModelVertices() = 0;

	void UpdateVertices()
	{
		for (int i = 0; i < verticeCount; i++)
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
	}
};

#endif