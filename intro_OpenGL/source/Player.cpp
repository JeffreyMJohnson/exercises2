#include "player.h"

Player::Player()
{
	vertices[0] = Vector4(1024 * .5f);
	vertices[1] = Vector4(720 * .5f) + 10.0f;
	vertices[2] = Vector4(1024 * .5f) - 5.0f;
}