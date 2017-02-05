/*********************************************************
FILE : submit.cpp (csci3260 2016-2017 Assignment 1)
*********************************************************/
/*********************************************************
Student Information
Student ID: 1155028934
Student Name: Shu Haoran
*********************************************************/


#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
using namespace std;

GLint programID;
GLuint vaoID;
GLuint vboID[3];
GLuint indices[2];
GLuint colorbuffer[2];

int xOrigin = -1;
int yOrigin = -1;

glm::vec3 position = glm::vec3(0, -6, 3);
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
float FoV = 45.0f;

float speed = 1.0f;
float mousespeed = 0.005f;

glm::vec3 center;
glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
glm::mat4 Model = glm::mat4(1.0f);

glm::mat4 translationX = glm::translate(glm::mat4(), glm::vec3(1, 0, 0));
glm::mat4 translationY = glm::translate(glm::mat4(), glm::vec3(0, 1, 0));
glm::mat4 translationZ = glm::translate(glm::mat4(), glm::vec3(0, 0, 1));

glm::mat4 translationx = glm::translate(glm::mat4(), glm::vec3(-1, 0, 0));
glm::mat4 translationy = glm::translate(glm::mat4(), glm::vec3(0, -1, 0));
glm::mat4 translationz = glm::translate(glm::mat4(), glm::vec3(0, 0, -1));

glm::mat4 scaleL = glm::scale(glm::mat4(), glm::vec3(1.1f, 1.1f, 1.1f));
glm::mat4 scaleS = glm::scale(glm::mat4(), glm::vec3(0.91f, 0.91f, 0.91f));

glm::mat4 rotateX = glm::rotate(glm::mat4(), 0.523f,glm::vec3(1, 0, 0));
glm::mat4 rotateY = glm::rotate(glm::mat4(), 0.523f, glm::vec3(0, 1, 0));
glm::mat4 rotateZ = glm::rotate(glm::mat4(), 0.523f, glm::vec3(0, 0, 1));

void computeProj(){
	Projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
}

glm::mat4 View;

void computeViewMatrix() {
	center = glm::vec3(
		horizontalAngle,
		-verticalAngle,
		0
		);
	View = glm::lookAt(
		position,
		center,
		glm::vec3(0, 1, 0)
		);
}

bool fullScreen = false;

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
}

bool checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

string readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good())
	{
		cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}

void installShaders()
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	//adapter[0] = vertexShaderCode;
	string temp = readShaderCode("VertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("FragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
}

void mouseWheel(int button, int dir, int x, int y) {
	FoV += dir;
	computeProj();
}

void mousePress(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_UP) {
			xOrigin = -1;
			yOrigin = -1;
		}
		else {
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void mouseMotion(int x, int y) {
	if (xOrigin >= 0) {
		horizontalAngle = mousespeed*float(xOrigin - x);
	}
	if (yOrigin >=0) {
		verticalAngle = mousespeed*float(yOrigin - y);
	}
	computeViewMatrix();
}

void keyboard(unsigned char key, int x, int y)
{
	//TODO:
	if (key == 'f') {
		fullScreen = true;
		glutFullScreen();
	}
	if (key == 'c') {
		if (fullScreen == true) {
			glutReshapeWindow(640, 480);
			glutPositionWindow(100, 100);
		}
	}
	if (key == 'a') {
		Model = rotateX*Model;
	}
	if (key == 'b') {
		Model = rotateY*Model;
	}
	if (key == 'c') {
		Model = rotateZ*Model;
	}
	if (key == 'X') {
		Model = translationX*Model;
	}
	if (key == 'Y') {
		Model = translationY*Model;
	}
	if (key == 'Z') {
		Model = translationZ*Model;
	}
	if (key == 'x') {
		Model = translationx*Model;
	}
	if (key == 'y') {
		Model = translationy*Model;
	}
	if (key == 'z') {
		Model = translationz*Model;
	}
	if (key == 'l') {
		Model = scaleL*Model;
	}
	if (key == 's') {
		Model = scaleS*Model;
	}
}

void specialKeys(int key, int x, int y){
	if (key == GLUT_KEY_LEFT) {
		position.x += speed;
		computeViewMatrix();
	}
	if (key == GLUT_KEY_RIGHT) {
		position.x -= speed;
		computeViewMatrix();
	}
	if (key == GLUT_KEY_UP) {
		position.y += speed;
		computeViewMatrix();
	}
	if (key == GLUT_KEY_DOWN) {
		position.y -= speed;
		computeViewMatrix();
	}
}

void sendDataToOpenGL()
{
	//TODO:
	//create solid objects here and bind to VAO & VBO

	//Define vertices, indices and colors for each object
	const GLfloat square[] = {
		-1.0f, -1.0f, +0.0f, //vert
		+1.0f, +1.0f, +1.0f,
		+1.0f, -1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
		-1.0f, +1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,

		+1.0f, -1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
		+1.0f, +1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
		-1.0f, +1.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
	};
	
	const GLfloat obj1[] = {
		+0.0f, +0.0f, +0.1f,
		+0.0f, +0.33f, +0.1f,
		+0.33f, +0.33f, +0.1f,
		+0.33f, +0.0f, +0.1f,

		+0.0f, +0.0f, +1.0f,
		+0.0f, +0.33f, +1.0f,
		+0.33f, +0.33f, +1.0f,
		+0.33f, +0.0f, +1.0f,
	};

	const GLushort obj1Indices[] = {
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		1, 4, 5,
		0, 1, 4,
		2, 6, 7,
		2, 3, 7,
		1, 2, 5,
		2, 5, 6,
		0, 4, 7,
		0, 3, 7,
	};

	const GLfloat obj1Color[] = {
		+1.0f, +0.0f, +0.0f,
		+0.0f, +1.0f, +0.0f,
		+0.0f, +0.0f, +0.1f,
		+1.0f, +0.0f, +0.0f,

		+0.0f, +1.0f, +0.0f,
		+0.0f, +0.0f, +0.1f,
		+0.5f, +0.5f, +0.0f,
		+0.5f, +0.0f, +0.5f,
	};
	
	const GLfloat obj2[] = {
		-0.2f, -0.2f, +1.2f,
		-0.6f, -0.2f, +1.2f,
		-0.2f, -0.2f, +1.6f,
		-0.6f, -0.2f, +1.6f,

		-0.4f, -0.5f, +1.4f,
		-0.4f, +0.1f, +1.4f,
	};

	const GLushort obj2Indices[] = {
		0, 1, 4,
		0, 2, 4,
		1, 3, 4,
		2, 3, 4,
		0, 1, 5,
		0, 2, 5,
		1, 3, 5,
		2, 3, 5,
	};

	const GLfloat obj2Color[] = {
		+0.321f, +0.0f, +1.0f,
		+0.150f, +0.0f, +1.0f,
		+0.321f, +0.0f, +1.0f,
		+0.150f, +0.0f, +1.0f,

		+1.0f, +0.0f, +0.0f,
		+1.0f, +1.0f, +1.0f,
	};
	
	//Generate and bind first VAO
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	//Generate, bind and send data to three VBOs, each for one object
	glGenBuffers(3, &vboID[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(square), square, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj1), obj1, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj2), obj2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	//Generate, bind and send data to two indices objects, each for one object
	glGenBuffers(2, &indices[0]);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj1Indices), obj1Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(obj2Indices), obj2Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//Generate, bind and send data to two color buffers, each for one VBO-indexed object
	glGenBuffers(2, &colorbuffer[0]);
	
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj1Color), obj1Color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(obj2Color), obj2Color, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void paintGL(void)
{
	//TODO:
	//render your objects and control the transformation here
	computeViewMatrix();
	glm::mat4 MVP = Projection * View * Model;
	
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	
	GLint MVPUniformLocation = glGetUniformLocation(programID, "MVP");
	glUniformMatrix4fv(MVPUniformLocation, 1, GL_FALSE, &MVP[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, vboID[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (char*)(3 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[1]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[0]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vboID[2]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices[1]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[1]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawElements(GL_TRIANGLE_STRIP, 24, GL_UNSIGNED_SHORT, 0);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glFlush();
	glutPostRedisplay();
}

void initializedGL(void) //run only once
{
	glewInit();
	sendDataToOpenGL();
	installShaders();
}

int main(int argc, char *argv[])
{
	/*Initialization of GLUT library*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

	/*Create a window with title specified*/
	//TODO:
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My Window");

	initializedGL();

	/*Register different CALLBACK function for GLUT to response
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutDisplayFunc(paintGL);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mousePress);
	glutMotionFunc(mouseMotion);
	glutMouseWheelFunc(mouseWheel);

	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

	return 0;
}