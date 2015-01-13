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
		LoadModelUVs();
		verticesBuffer = new Vertex[modelVertices.size()];
		textureWidth = 50;
		textureHeight = 50;
		textureBPP = 4;
		uiTextureID = loadTexture(".\\resources\\images\\lobo2.png", textureWidth, textureHeight, textureBPP);
	}
	~Asteroid()
	{
		delete verticesBuffer;
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
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 4));
		//now we have UVs to worry about, we need to send that info to the graphics card too
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 8));

		glDrawElements(GL_TRIANGLE_FAN, modelVertices.size(), GL_UNSIGNED_BYTE, NULL);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
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

	void LoadModelUVs()
	{
		modelUVs.push_back(glm::vec2(.7, 1));
		modelUVs.push_back(glm::vec2(1,.6));
		modelUVs.push_back(glm::vec2(.8,.2));
		modelUVs.push_back(glm::vec2(.5,0));
		modelUVs.push_back(glm::vec2(0,.2));
		modelUVs.push_back(glm::vec2(0, .6));
		modelUVs.push_back(glm::vec2(.2, 1));
	}
};
#endif