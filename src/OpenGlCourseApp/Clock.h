#include <glad/glad.h>
#include <GLFW/glfw3.h>
class Clock
{
public:
	Clock();
	GLfloat deltaTime();
	GLfloat getDeltaTime();

private:
	GLfloat delta_time;
	GLfloat last_time;
	GLfloat now;
};
