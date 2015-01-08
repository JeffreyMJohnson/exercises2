#ifndef _ASTEROID_H_
#define _ASTEROID_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include "glm\glm.hpp"

struct Vertex;

class Asteroid
{
public:
	const GLint mVerticeTotalCount = 7;
	glm::vec4 modelVertices[7];
	glm::vec4 position;
	glm::vec4 color;
	GLuint uiVBO;


	//size vertex buffer object needs to be
	const GLint mVertexBufferSize = sizeof(Vertex) * mVerticeTotalCount;
	Vertex vertices[7];


	Asteroid()
	{
		position = glm::vec4(1024 * .25f, 720 * .75f, 0, 0);
		modelVertices[0] = glm::vec4(6, 18, 0, 1);
		modelVertices[1] = glm::vec4(24, 6, 0, 1);
		modelVertices[2] = glm::vec4(18, -12, 0, 1);
		modelVertices[3] = glm::vec4(0, -18, 0, 1);
		modelVertices[4] = glm::vec4(-18, -12, 0, 1);
		modelVertices[5] = glm::vec4(-18, 6, 0, 1);
		modelVertices[6] = glm::vec4(-6, 18, 0, 1);
		color = glm::vec4(0, 1, 0, 1);


		//create id for a vertex buffer
		glGenBuffers(1, &uiVBO);

		UpdateVertecis();
	}

	void SetPosition(glm::vec4& a_position)
	{
		position = a_position;
		UpdateVertecis();
	}

	void Draw()
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));

		glDrawArrays(GL_LINE_LOOP, 0, mVerticeTotalCount);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:
	void UpdateVertecis()
	{
		for (int i = 0; i < mVerticeTotalCount; i++)
		{
			vertices[i].fPositions[0] = modelVertices[i].x + position.x;
			vertices[i].fPositions[1] = modelVertices[i].y + position.y;
			vertices[i].fPositions[2] = 0;
			vertices[i].fPositions[3] = 1;
			vertices[i].fColors[0] = color.r;
			vertices[i].fColors[1] = color.g;
			vertices[i].fColors[2] = color.b;
			vertices[i].fColors[3] = color.a;
		}
		UpdateVBO();
	}

	void UpdateVBO()
	{
		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		//size of buffer needs to be 3 vec4 for vertices and 3 vec4 for 
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVerticeTotalCount, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy data to graphics card
		memcpy(vBuffer, vertices, mVertexBufferSize);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};

#endif