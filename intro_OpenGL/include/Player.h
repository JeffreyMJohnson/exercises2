#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "glm\glm.hpp"


class Player
{
public:
	Player();
	void Update();

	glm::vec4 modelVertices[3];
	glm::vec4 position;
	glm::vec4 color;

};
#endif

//Vertex* myShape = new Vertex[3];
//myShape[0].fPositions[0] = 1024 / 2.0;
//myShape[0].fPositions[1] = 720 / 2.0 + 10.0f;
//myShape[1].fPositions[0] = 1024 / 2.0 - 5.0f;
//myShape[1].fPositions[1] = 720 / 2.0f - 10.0f;
//myShape[2].fPositions[0] = 1024 / 2.0f + 5.0f;
//myShape[2].fPositions[1] = 720 / 2.0f - 10.0f;
//for (int i = 0; i < 3; i++)
//{
//	myShape[i].fPositions[2] = 0.0f;
//	myShape[i].fPositions[3] = 1.0f;
//	myShape[i].fColors[0] = 0.0f;
//	myShape[i].fColors[1] = 0.0f;
//	myShape[i].fColors[2] = 1.0f;
//	myShape[i].fColors[3] = 1.0f;
//}