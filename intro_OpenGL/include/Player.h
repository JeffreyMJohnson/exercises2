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
		LoadModelUVs();
		verticesBuffer = new Vertex[modelVertices.size()];
		textureWidth = 50;
		textureHeight = 50;
		textureBPP = 4;
		uiTextureID = loadTexture(".\\resources\\images\\lobo.png", textureWidth, textureHeight, textureBPP);

	}

	~Player()
	{
		delete verticesBuffer;
	}

	void Update(GLFWwindow* windowHandle)
	{
		if (glfwGetKey(windowHandle, GLFW_KEY_W) == GLFW_PRESS)
		{
			//move forward 
			//std::cout << "move forward" << std::endl;
			for (int i = 0; i < 3; i++)
			{
				modelVertices[i].y += .01f;
			}
			UpdateVertices();
		}

		if (glfwGetKey(windowHandle, GLFW_KEY_S))
		{
			//move backwards
			for (int i = 0; i < modelVertices.size(); i++)
			{
				modelVertices[i].y -= .01f;
			}
			UpdateVertices();
		}

		if (glfwGetKey(windowHandle, GLFW_KEY_A))
		{
			//move backwards
			for (int i = 0; i < modelVertices.size(); i++)
			{
				modelVertices[i].x -= .01f;
			}
			UpdateVertices();
		}
		if (glfwGetKey(windowHandle, GLFW_KEY_D))
		{
			//move backwards
			for (int i = 0; i < modelVertices.size(); i++)
			{
				modelVertices[i].x += .01f;
			}
			UpdateVertices();
		}
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

		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));
		//now we have UVs to worry about, we need to send that info to the graphics card too
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));

		glDrawElements(GL_TRIANGLES, modelVertices.size(), GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

private:
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
};
#endif