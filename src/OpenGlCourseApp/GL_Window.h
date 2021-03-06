#pragma once

#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GL_Window
{
public:
	GLFWwindow *mainWindow;

	GL_Window();
	GL_Window(GLint windowWidth, GLint windowHeight);	
	GL_Window(GLint windowWidth, GLint windowHeight, GLfloat sensitivity);
	int Initialize();
	GLfloat getAspectRatio() const { return ( (GLfloat)bufferWidth / (GLfloat)bufferHeight ); }
	GLint getWindowWidth() const { return width; }
	GLint getWindowHeight() const { return height; }
	GLint getBufferWidth() const { return bufferWidth; }
	GLint getBufferHeight() const { return bufferHeight; }
	bool getShouldClose() const { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; };
	GLfloat getXChange() ;
	GLfloat getYChange()  ;
	GLfloat getSensitivity() ;

	void setSensitivity(float newSensitivity);

	void swapBuffers() { glfwSwapBuffers(mainWindow); }
	~GL_Window();

private:

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	bool keys[1024];

	// GLfloat sensitivity;
	// maybe add up down sensitivity

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat sensitivity;
	bool mouseFirstMoved;

	void createCallbacks();
	static void handleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow *window, double xPos, double yPos);
};

