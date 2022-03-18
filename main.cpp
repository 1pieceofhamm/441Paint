#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

int size = 1;
float frameBuffer[WINDOW_HEIGHT][WINDOW_WIDTH][3];
bool mask[WINDOW_HEIGHT][WINDOW_WIDTH];
GLFWwindow *window;


// Color structure. Can be used to define the brush and background color.
struct color { float r, g, b; };
color white = { 1,1,1 };
color black = { 0,0,0 };
color blue = { 0,0,1 };
color green = { 0,1,0 };
color cyan = { 0,1,1 };
color red = { 1,0,0 };
color magenta = { 1,0,1 };
color yellow = { 1,1,0 };
color choice = white;
color background = black;

// A function clamping the input values to the lower and higher bounds
#define CLAMP(in, low, high) ((in) < (low) ? (low) : ((in) > (high) ? (high) : in))

// Set a particular pixel of the frameBuffer to the provided color
void SetFrameBufferPixel(int x, int y, struct color lc)
{
	// Origin is upper left corner. 
	// Changes the origin from the lower-left corner to the upper-left corner
	y = WINDOW_HEIGHT - 1 - y;

	x = CLAMP(x, 0, WINDOW_WIDTH - 1);
	y = CLAMP(y, 0, WINDOW_HEIGHT - 1);

	frameBuffer[y][x][0] = lc.r;
	frameBuffer[y][x][1] = lc.g;
	frameBuffer[y][x][2] = lc.b;

}

void ClearFrameBuffer()
{
	background = black;
	for (int i = 0; i < WINDOW_WIDTH; i++) {
		for (int j = 0; j < WINDOW_HEIGHT; j++) {
			mask[j][i] = false;
			SetFrameBufferPixel(i, j, background);
			//mask[j][i]=false;
		}
	}
	memset(frameBuffer, 0.0f, sizeof(float) * WINDOW_WIDTH * WINDOW_HEIGHT * 3);
	
	
}

// Display frameBuffer on screen
void Display()
{	
	glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, frameBuffer);
}

// Mouse position callback function
void CursorPositionCallback(GLFWwindow* lWindow, double xpos, double ypos)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS)
	{
		//mark pixels true for background
		//for loops for square
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				SetFrameBufferPixel(xpos + i, ypos + j, choice);
				mask[(int)(xpos + i)][(int)(ypos + j)] = true;
				SetFrameBufferPixel(xpos - i, ypos - j, choice);
				mask[(int)(xpos - i)][(int)(ypos - j)] = true;
				SetFrameBufferPixel(xpos + i, ypos - j, choice);
				mask[(int)(xpos + i)][(int)(ypos - j)] = true;
				SetFrameBufferPixel(xpos - i, ypos + j, choice);
				mask[(int)(xpos - i)][(int)(ypos + j)] = true;
			}

		}

		std::cout << "Mouse position is: x - " << xpos << ", y - " << ypos << std::endl;
	}
}

// Mouse callback function
void MouseCallback(GLFWwindow* lWindow, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
	{
		std::cout << "Mouse left button is pressed." << std::endl;
	}
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
	{
		ClearFrameBuffer();
		std::cout << "Mouse right button is pressed." << std::endl;
	}

}

// You can use "switch" or "if" to compare key to a specific character.
// for example,
// if (key == '0')
//     DO SOMETHING

// Keyboard callback function
void CharacterCallback(GLFWwindow* lWindow, unsigned int key)
{
	std::cout << "Key " << (char)key << " is pressed." << std::endl;
	if (key == '0') {
		//change color to black 000
		choice = black;
	}
	if (key == '1') {
		//change color to blue 001
		choice = blue;
	}
	if (key == '2') {
		//change color to green 010
		choice = green;
	}
	if (key == '3') {
		//change color to cyan 011
		choice = cyan;
	}
	if (key == '4') {
		//change color to red 100
		choice = red;
	}
	if (key == '5') {
		//change color to magenta 101
		choice = magenta;
	}
	if (key == '6') {
		//change color to yellow 110
		choice = yellow;
	}
	if (key == '7') {
		//change color to white 111
		choice = white;
	}
	if (key == '+') {
		//change size by a factor of 2
		if (size < 128 && size>0) {
			size *= 2;
		}
		if (size > 128) {
			size = 128;
		}
	}
	if (key == '-') {
		//change size by a factor of 1/2
		if (size < 128 && size>0) {
			size /= 2;
		}
		if (size < 1) {
			size = 1;
		}
	}
	if (key == ')') {
		//change backgroud to black 000
		background = black;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, black);
				}
			}
		}
	}
	if (key == '!') {
		//change backgroud to blue 001
		background = blue;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, blue);
				}
			}
		}
	}
	if (key == '@') {
		//change backgroud to green 010
		background = green;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, green);
				}
			}
		}
	}
	if (key == '#') {
		//change backgroud to cyan 011
		background = cyan;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, cyan);
				}
			}
		}
	}
	if (key == '$') {
		//change backgroud to red 100
		background = red;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, red);
				}
			}
		}
	}
	if (key == '%') {
		//change backgroud to magenta 101
		background = magenta;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, magenta);
				}
			}
		}
	}
	if (key == '^') {
		//change backgroud to yellow 110
		background = yellow;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, yellow);
				}
			}
		}
	}
	if (key == '&') {
		//change backgroud to white 111
		background = white;
		for (int i = 0; i < WINDOW_WIDTH; i++) {
			for (int j = 0; j < WINDOW_HEIGHT; j++) {
				if (mask[i][j] == false) {
					SetFrameBufferPixel(i, j, white);
				}
			}
		}
	}
}

void Init()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Assignment 1 - <Caleb Hammack>", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetMouseButtonCallback(window, MouseCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
	glfwSetCharCallback(window, CharacterCallback);
	glewExperimental = GL_TRUE;
	glewInit();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	ClearFrameBuffer();
}


int main()
{	
	Init();
	while (glfwWindowShouldClose(window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		Display();
		glFlush();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}