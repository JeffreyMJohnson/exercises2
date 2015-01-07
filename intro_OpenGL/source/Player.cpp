#include "player.h"

Player::Player()
{
	position = glm::vec4(1024 * .5f, 720 * .5f, 0,1);
	modelVertices[0] = glm::vec4(0, 10.0f,0,1);
	modelVertices[1] = glm::vec4(-5.0f, -10.0f,0,1);
	modelVertices[2] = glm::vec4(5.0f, -10.0f,0,1);
	color = glm::vec4(0, 0, 1, 1);

}