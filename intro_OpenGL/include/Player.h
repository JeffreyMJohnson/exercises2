#ifndef _PLAYER_H_
#define _PLAYER_H_

//#include "Entity.h"

//class Player : public Entity
//{
//public:
//
//	Player()
//	{
//
//		LoadModelVertices();
//		verticeCount = modelVertices.size();
//		verticesBuffer = new Vertex[verticeCount];
//		UpdateVertices();
//	}
//
//	~Player()
//	{
//		delete verticesBuffer;
//	}
//
//	void Draw()
//	{
//		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
//
//		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
//		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
//
//		glDrawArrays(GL_TRIANGLES, 0, verticeCount);
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}
//
//
//	void LoadModelVertices()
//	{
//		modelVertices.push_back(glm::vec4(0, 10.0f, 0, 1));
//		modelVertices.push_back(glm::vec4(-5.0f, -10.0f, 0, 1));
//		modelVertices.push_back(glm::vec4(5.0f, -10.0f, 0, 1));
//	}
//};



#include <GL\glew.h>
#include <GL\wglew.h>
#include "glm\glm.hpp"

struct Vertex
{
	float fPositions[4];
	float fColors[4];
};

class Player
{
public:
	Player();
	void Draw();
	void SetPosition(glm::vec4& a_position);

	glm::vec4 modelVertices[3];
	glm::vec4 position;
	glm::vec4 color;
	GLuint uiVBO;

	const GLint mVerticeTotalCount = 3;
	//size vertex buffer object needs to be
	const GLint mVertexBufferSize = sizeof(Vertex) * mVerticeTotalCount;
	Vertex vertices[3];
private:
	//vec4 = f floats, 2 vec4's ( a position and color), 3 vertices in model
	//GLfloat VBOData[((sizeof(GLfloat) * 4) * 2) * 3];

	void UpdateVertecis();
	void UpdateVBO();

};
#endif