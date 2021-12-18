
#include "Clock.h"

Clock::Clock()
{
	Clock::deltaTime();
}

GLfloat Clock::deltaTime()
{
	now = glfwGetTime();
	delta_time = now - last_time;
	last_time = now;

	return delta_time;
}

GLfloat Clock::getDeltaTime()
{
	return delta_time;
}