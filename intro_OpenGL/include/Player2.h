#ifndef _PLAYER_2_H_
#define _PLAYER_2_H_

#include <GL\glew.h>
#include <GL\wglew.h>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "SOIL\SOIL.h"
#include <vector>

#include <iostream>

struct Vertex2
{
	float fPositions[4];
	float fColors[4];
	float fUVs[2];
};

class Player2
{
public:
	Player2()
	{
		LoadModelVertices();
		LoadModelUVs();
		verticesBuffer = new Vertex2[modelVertices.size()];
		textureWidth = 50;
		textureHeight = 50;
		textureBPP = 4;
		uiTextureID = loadTexture(".\\resources\\images\\lobo.png", textureWidth, textureHeight, textureBPP);
		scale = glm::vec4(5, 5, 0, 1);
	}

	~Player2()
	{
		delete verticesBuffer;
	}

	void Initialize(glm::vec4& a_position, glm::vec4& a_color, GLuint a_ShaderProgram)
	{
		position = a_position;
		color = a_color;
		glGenBuffers(1, &uiVBO);
		glGenBuffers(1, &uiIBO);
		programShader = a_ShaderProgram;
		UpdateVertices();
	}

	void Draw(GLuint uniformLocationID, float* orthoProjection)
	{
		glUseProgram(programShader);

		//send ortho projection info to shader
		glUniformMatrix4fv(uniformLocationID, 1, GL_FALSE, orthoProjection);

		//enable vertex array state
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glBindTexture(GL_TEXTURE_2D, uiTextureID);
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex2), (void*)(sizeof(float)* 4));
		//now we have UVs to worry about, we need to send that info to the graphics card too
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2), (void*)(sizeof(float)* 8));

		glDrawElements(GL_TRIANGLES, modelVertices.size(), GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void CleanUp()
	{
		glDeleteBuffers(1, &uiIBO);
	}

private:
	std::vector<glm::vec4> modelVertices;
	std::vector<glm::vec2> modelUVs;
	glm::mat4 transformMatrix;
	glm::vec4 scale;
	glm::vec4 position;
	glm::vec4 color;
	GLuint uiVBO;
	GLuint uiIBO;
	GLuint uiTextureID;
	GLuint programShader;
	int textureWidth;
	int textureHeight;
	int textureBPP;
	Vertex2* verticesBuffer;

	void LoadModelVertices()
	{
		modelVertices.push_back(glm::vec4(0, 10.0f, 0, 1));
		modelVertices.push_back(glm::vec4(-5.0f, -10.0f, 0, 1));
		modelVertices.push_back(glm::vec4(5.0f, -10.0f, 0, 1));
	}

	void LoadModelUVs()
	{
		modelUVs.push_back(glm::vec2(.5, 1));
		modelUVs.push_back(glm::vec2(0, 0));
		modelUVs.push_back(glm::vec2(1, 0));
	}

	void UpdateVBO()
	{
		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		//size of buffer needs to be 3 vec4 for vertices and 3 vec4 for 
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex2)* modelVertices.size(), NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		//copy data to graphics card
		memcpy(vBuffer, verticesBuffer, sizeof(Vertex2)* modelVertices.size());
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
			verticesBuffer[i].fUVs[0] = modelUVs[i].x;
			verticesBuffer[i].fUVs[1] = modelUVs[i].y;
		}
		UpdateVBO();
		UpdateIBO();
	}

	unsigned int loadTexture(const char* a_pFilename, int & a_iWidth, int & a_iHeight, int & a_iBPP)
	{
		unsigned int uiTextureID = 0;
		//check file exists
		if (a_pFilename != nullptr)
		{
			//read in image data from file
			unsigned char* pImageData = SOIL_load_image(a_pFilename, &a_iWidth, &a_iHeight, &a_iBPP, SOIL_LOAD_AUTO);

			//check for successful read
			if (pImageData)
			{
				//create opengl texture handle
				uiTextureID = SOIL_create_OGL_texture(pImageData, a_iWidth, a_iHeight, a_iBPP,
					SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
				//clear what was read in from file now that it is stored in the handle
				SOIL_free_image_data(pImageData);
			}

			//check for errors
			if (uiTextureID == 0)
			{
				std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
			}
			return uiTextureID;
		}
	}
};
#endif