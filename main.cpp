#pragma once
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <string>

void render_loop();

GLFWwindow* window;
int ScrnWidth = 800;
int ScrnHeight = 600;
float scale = 500;
float ratioW = scale / ScrnWidth;
float ratioH = scale / ScrnHeight;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdShow,
	_In_ int nCmdShow)
{
	int VPWidth, VPHeight;



	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	if (!glfwInit())
		return -1;

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* screen = glfwGetVideoMode(monitor);
	if(!monitor || !screen)
	{
		glfwTerminate();
		return -1;
	}

	// Windowed mode
	window = glfwCreateWindow(ScrnWidth, ScrnHeight, "OpenGL Screen Saver", NULL, NULL);
	
	/* Fullscreen mode
	int ScrnWidth = screen->width;
	int ScrnHeight = screen->height;
	window = glfwCreateWindow(ScrnWidth, ScrnHeight, "OpenGL Screen Saver", monitor, NULL);
	*/
	//glfwSetWindowMonitor(window, monitor, 0, 0, screen->width, screen->height, screen->refreshRate);
	//glfwSetWindowPos(window, 0, 0);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwGetWindowSize(window, &VPWidth, &VPHeight);
	glViewport(0, 0, VPWidth, VPHeight);
	glfwMakeContextCurrent(window);
	glClearColor(0.1, .2, .3, 1);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	render_loop();

	glFlush();
	glfwTerminate();
	return 0;
}

void render_loop()
{
	double time;
	double frametime = 0;
	double newframetime = 0;
	double deltatime = 0;
	float i = 0.1 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.4f);
	float j = 0.1 + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.4f);
	float posx = 0;
	float posy = 0;
	int fpsupdate = 0;
	
	time = glfwGetTime();
	while (!glfwWindowShouldClose(window))
	{	
		//Render Loop Here
		newframetime = glfwGetTime();
		deltatime = newframetime - frametime;
		fpsupdate++;
		if (fpsupdate >= 20)
		{
			int fps = 1 / deltatime;
			char titletext[10];
			snprintf(titletext, 64, "Fps: %d", fps);
			glfwSetWindowTitle(window, titletext);
			fpsupdate = 0;
		}

		//new frame time stored as old frame time
		frametime = newframetime;
		glClear(GL_COLOR_BUFFER_BIT);

		if (posx > 49 || posx < -49)
		{
			j = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.5f);
			i = i * -1;
		}
		else if (posy > 49 || posy < -49)
		{
			i = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 0.5f);
			j = j * -1;

		}
		posx += i;
		posy += j;

		glTranslatef(i * deltatime, j * deltatime, 0);
		glRotatef(.2, i * deltatime, j * deltatime, 0);
		glBegin(GL_POLYGON);
		glColor3f(0, 1, 0);
		glVertex3f(-0.2 * ratioW, 0.2 * ratioH,0);
		glVertex3f(-0.2 * ratioW, -0.2 * ratioH,0);
		glColor3f(2, 0.2f, .3f);
		glVertex3f(0.2 * ratioW, -0.2 * ratioH,0);
		glVertex3f(0.2 * ratioW, 0.2 * ratioH,0);
		glEnd();
		glBegin(GL_POLYGON);
		glColor3f(1, 0, 0);
		glVertex3f(-0.2 * ratioW, 0.2 * ratioH, .3);
		glVertex3f(-0.2 * ratioW, -0.2 * ratioH, .3);
		glColor3f(2, 0.2f, .3f);
		glVertex3f(0.2 * ratioW, -0.2 * ratioH, .3);
		glVertex3f(0.2 * ratioW, 0.2 * ratioH, .3);
		glEnd();

		//Swap the back frame buffer to the front (display it on screen)
		glfwSwapBuffers(window);
		//Handle windows events
		glfwPollEvents();

	}
}
