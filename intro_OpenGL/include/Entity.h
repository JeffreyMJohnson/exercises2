#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include "glm\glm.hpp"
#include <vector>

#include <iostream>

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
		glGenBuffers(1, &uiVBO);
		glGenBuffers(1, &uiIBO);
		UpdateVertices();
	}

	void SetPosition(glm::vec4& a_position)
	{
		position = a_position;
		UpdateVertices();
	}

	virtual void Draw() = 0;

	void CleanUp()
	{
		glDeleteBuffers(1, &uiIBO);
	}
	


protected:
	std::vector<glm::vec4> modelVertices;
	glm::vec4 position;
	glm::vec4 color;
	GLuint uiVBO;
	GLuint uiIBO;
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

	void UpdateIBO()
	{
		//bind IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		//allocate space for index info on  the graphics card
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelVertices.size() * sizeof(char), NULL, GL_STATIC_DRAW);
		//get pointer to newly allocated space on GPU
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		//specify order to draw vertices
		//in this case it's in sequential order
		for (int i = 0; i < modelVertices.size(); i++)
		{
			((char*)iBuffer)[i] = i;
		}
		//unmap and unbind 
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
		UpdateIBO();
	}

	//return the max distance from given point and all the points of this object
	float MaxDistance(glm::vec4& otherPoint)
	{
		float result = 0;
		for (glm::vec4 pos : modelVertices)
		{
			float d = sqrt(
				((pos.x - otherPoint.x) * (pos.x - otherPoint.x)) +
				((pos.y - otherPoint.y) * (pos.y - otherPoint.y)));
			if (d > result)
				result = d;
		}
		return result;
	}
};

#endif