/*********************************************************
FILE : submit.cpp (csci3260 2016-2017 Final Project)
*********************************************************/
/*********************************************************
Student Information
(0) Group Number:?0
(1) Student ID:1155029188
(1) Student Name:Wang Keluo
(2) Student ID:1155028934
(2) Student Name:Shu Haoran
*********************************************************/

#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "camera.h"
using namespace std;
using glm::vec3;
using glm::mat4;

//Camera
Camera camera;
glm::mat4 view = camera.GetViewMatrix();
int viewPoint = 0;

//Viewport Sizes
int WIDTH = 700;
int HEIGHT = 500;

//Vehicle Viewpoint
bool sOn = false;

//Vehicle Movement
bool vehicleRot = true;
bool vehicleTrans = false;
bool movTime = true;
GLfloat speed = 0.00083f;
glm::mat4 MovE = glm::translate(glm::mat4(), glm::vec3(glm::vec4(2.0f*speed, 0, -speed, 1)));
int swing = 0;
bool action = false;

//Matrices
glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 4.0f / 3.0f, 0.1f, 100.0f);
float FoV = 60.0f;
void computeProj() {
	Projection = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
}
glm::vec3 CameraPosition = glm::vec3(0, 0, 16);
glm::mat4 ViewMatrix = glm::lookAt(
	CameraPosition,
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
glm::vec3 lookto = glm::vec3(0, 0, 0);
void updateViewMat() {
	ViewMatrix = glm::lookAt(
		CameraPosition,
		lookto, // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
}
glm::mat4* astModelMatrices;
GLuint amount = 200;

glm::mat4 ModelMatrix = glm::mat4(1.0f);
glm::mat4 Skb_ModelMatrix = glm::mat4(1.0f);
glm::mat4 scale_B = glm::scale(glm::mat4(), glm::vec3(0.8f, 0.8f, 0.8f));
glm::mat4 scale_C = glm::scale(glm::mat4(), glm::vec3(0.3f, 0.3f, 0.3f));
glm::mat4 scale_E = glm::scale(glm::mat4(), glm::vec3(0.2f, 0.2f, 0.2f));
glm::mat4 scale_ast = glm::scale(glm::mat4(), glm::vec3(0.2f, 0.2f, 0.2f));
glm::mat4 tiltA = glm::rotate(glm::mat4(), 0.3f, glm::vec3(-0.5, 1, 0));
glm::mat4 ModelMatrix_A = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, -16, 1)))*tiltA;
glm::mat4 ModelMatrix_B = glm::translate(glm::mat4(), glm::vec3(glm::vec4(5, 0, -21, 1)))*scale_B;
glm::mat4 ModelMatrix_C = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, -11, 1)))*scale_C;
glm::mat4 ModelMatrix_E = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, -19.5, 1)))*scale_E;
glm::mat4 ModelMatrix_ast = glm::translate(glm::mat4(), glm::vec3(glm::vec3(2, 0, -21)))*scale_ast;
glm::mat4 translationC1 = glm::translate(glm::mat4(), glm::vec3(glm::vec4(5, 0, 16, 1)));
glm::mat4 rotationC2 = glm::rotate(glm::mat4(), 0.002f, glm::vec3(-0.5, 1, 0));
glm::mat4 translationC3 = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, -16, 1)));
glm::mat4 translationE1 = glm::translate(glm::mat4(), glm::vec3(glm::vec4(5, 0, 16, 1)));
glm::mat4 rotationE2 = glm::rotate(glm::mat4(), -0.005f, glm::vec3(0, 1, 0));
glm::mat4 translationE3 = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, -16, 1)));
glm::mat4 translationE4 = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, 21, 1)));
glm::mat4 rotationE5 = glm::rotate(glm::mat4(), 0.003f, glm::vec3(0, 1, 0));
glm::mat4 translationE6 = glm::translate(glm::mat4(), glm::vec3(glm::vec4(5, 0, -21, 1)));

glm::mat4 translationast1 = glm::translate(glm::mat4(), glm::vec3(glm::vec3(-5, 0, 21)));
glm::mat4 rotationast2 = glm::rotate(glm::mat4(), 0.002f, glm::vec3(0, 1, 0.2));
glm::mat4 translationast3 = glm::translate(glm::mat4(), glm::vec3(glm::vec3(5, 0, -21)));

glm::mat4 rotatedA = glm::mat4(1.0f);
glm::mat4 rotatedB = glm::mat4(1.0f);
glm::mat4 rotatedC = glm::mat4(1.0f);
glm::mat4 rotatedE = glm::mat4(1.0f);
float va = 0.8f;
float vb = 1.0f;
float vc = 1.0f;
glm::mat4 rotateA = glm::rotate(glm::mat4(), 0.0005f*va, glm::vec3(0, 1, 0));
glm::mat4 rotateB = glm::rotate(glm::mat4(), 0.0005f*vb, glm::vec3(0, 1, 0));
glm::mat4 rotateC = glm::rotate(glm::mat4(), 0.005f*vc, glm::vec3(0, 1, 0));

//mouse
int xOrigin = -1;
int yOrigin = -1;
int xLast = xOrigin, yLast = yOrigin;
float mousespeed = 0.015f;

// We have different programID for different object, the purpose is to bind different shader with different object.
GLint skybox_programID;
// VAO & VBA & Interaction parameter
GLuint skyboxVAO;
GLuint skyboxVBO;
GLuint skybox_textureID;

GLint objects_programID;
GLuint planetVAO;
GLuint vehicleVAO;

GLint lb_programID;
GLuint lightVAO;
GLuint lightVBO, indicesD, colorVBO;

GLuint A_texture[2], B_texture[2], C_texture, E_texture, ast_texture;
GLuint A_vertex_vbo, B_vertex_vbo, C_vertex_vbo, E_vertex_vbo, ast_vertex_vbo;
GLuint A_uv_vbo, B_uv_vbo, C_uv_vbo, E_uv_vbo, ast_uv_vbo;
GLuint A_normal_vbo, B_normal_vbo, C_normal_vbo, E_normal_vbo, ast_normal_vbo;
GLsizei A_drawsize, B_drawsize, C_drawsize, E_drawsize, ast_drawsize;


//Information to be loaded from .OBJs
std::vector<glm::vec3> vertices_A, vertices_B, vertices_C, vertices_E, vertices_ast;
std::vector<glm::vec2> uvs_A, uvs_B, uvs_C, uvs_E, uvs_ast;
std::vector<glm::vec3> normals_A, normals_B, normals_C, normals_E, normals_ast;


//Lights
glm::vec3 LightPosition = glm::vec3(0.0, 0.0, 0.0);
glm::vec3 addLightPosition = glm::vec3(0.0, 12.0, -16.0);
int x = 0;
int time = 0;
int timeInt = 240; 
glm::vec3 LightPosition_cameraspace;
glm::vec4 addtmp = view*glm::vec4(addLightPosition, 1.0);
glm::vec3 addLightPosition_cameraspace = glm::vec3(addtmp.x, addtmp.y, addtmp.z);
void updateLightPosition() {
	if (time % 10 == 0) {
		LightPosition.z = 0.1f*(float(abs((x + 1) % (2*timeInt+1)-timeInt))-120.0f)-16.0f;
		x += 1;
	}
	glm::vec4 tmp = view*glm::vec4(LightPosition, 1.0);
	LightPosition_cameraspace = glm::vec3(tmp.x, tmp.y, tmp.z);
	time++;
}
float LightPowerDiffuse = 100.0f;
float LightPowerSpecular = 100.0f;
float addLightPowerDiffuse = 150.0f;
float addLightPowerSpecular = 150.0f;

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

GLint installShaders(const char* vertexShader, const char* fragmentShader) {
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temp = readShaderCode(vertexShader);
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode(fragmentShader);
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID))
		return 0;

	GLint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return 0;

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	glUseProgram(programID);
	return programID;
}

void keyboard(unsigned char key, int x, int y)
{
	//TODO: Use keyboard to do interactive events and animation
	if (key == 'a') {
		Skb_ModelMatrix = glm::translate(glm::mat4(), glm::vec3(glm::vec4(0, 16, -16, 1)));
		CameraPosition = glm::vec3(0, 16, -16);
		glm::vec3 newUp = glm::vec3(0, 0, -1);
		glm::vec3 newFront = glm::vec3(0, -1, 0);
		camera.setViewMatrix(CameraPosition, newUp, newFront, -90.0f, -90.0f);
	}
	if (key == 's') {
		Skb_ModelMatrix = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-16, 0, -16, 1)));
		CameraPosition = glm::vec3(-16, 0, -16);
		glm::vec3 newUp = glm::vec3(0, 1, 0);
		glm::vec3 newFront = glm::vec3(1, 0, 0);
		camera.setViewMatrix(CameraPosition, newUp, newFront, 0.0f, 0.0f);
	}
	if (key == 'd') {
		Skb_ModelMatrix = glm::translate(glm::mat4(), glm::vec3(glm::vec4(16, 16, -16, 1)));
		CameraPosition = glm::vec3(16, 16, -16);
		glm::vec3 newUp = glm::vec3(-1, 1, 0);
		glm::vec3 newFront = glm::vec3(-0.7f, -0.7f, 0);
		camera.setViewMatrix(CameraPosition, newUp, newFront, -180.0f, -45.0f);
	}
	if (key == 'q') {
		Skb_ModelMatrix = glm::translate(glm::mat4(), glm::vec3(glm::vec4(0, 0, 0, 1)));
		CameraPosition = glm::vec3(0, 0, 0);
		glm::vec3 newUp = glm::vec3(0, 1, 0);
		glm::vec3 newFront = glm::vec3(0, 0, -1);
		camera.setViewMatrix(CameraPosition, newUp, newFront, -90.0f, 0.0f);
	}
	if (key == 'v') {
		if (sOn == true) {
			sOn = false;
			Skb_ModelMatrix = glm::translate(glm::mat4(), glm::vec3(glm::vec4(16, 16, -16, 1)));
			CameraPosition = glm::vec3(16, 16, -16);
			glm::vec3 newUp = glm::vec3(-1, 1, 0);
			glm::vec3 newFront = glm::vec3(-0.7f, -0.7f, 0);
			camera.setViewMatrix(CameraPosition, newUp, newFront, -180.0f, -45.0f);
		}
		else {
			sOn = true;
		}
	}
	if (key == 'T') {
		if (action == false) {
			vehicleRot = false;
			vehicleTrans = true;
			action = true;
			ModelMatrix_E = glm::translate(glm::mat4(), glm::vec3(glm::vec4(-5, 0, -12.5, 1)))*scale_E*glm::rotate(glm::mat4(), 0.5f, glm::vec3(0, 1, 0));
		}
	}
	if (key == 27) {
		exit(0);
	}
}

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		speed = float(sqrt(speed*0.01));
		MovE = glm::translate(glm::mat4(), glm::vec3(glm::vec4(2.0f*speed, 0,-speed, 1)));
		std::cout << speed << std::endl;
	}
	if (key == GLUT_KEY_DOWN) {
		speed = std::max(float(99*speed*speed), 0.0001f);
		MovE = glm::translate(glm::mat4(), glm::vec3(glm::vec4(2.0f*speed, 0, -speed, 1)));
		std::cout << speed << std::endl;
	}
}

void mouseWheel(int button, int dir, int x, int y) {
	FoV -= dir;
	computeProj();
	camera.ProcessMouseScroll(float(dir));
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
			xLast = xOrigin;
			yLast = yOrigin;
		}
	}
}

void PassiveMouse(int x, int y)
{
	//TODO: Use Mouse to do interactive events and animation
	GLfloat xoffset = float(x - xLast);
	GLfloat yoffset = float(yLast - y);  // Reversed since y-coordinates go from bottom to left
	xLast = x;
	yLast = y;
	camera.ProcessMouseMovement(xoffset, yoffset);
	/*if (xOrigin >= 0) {
		CameraPosition.z += mousespeed*float(x - xLast);
		xLast = x;
	}
	if (yOrigin >= 0) {
		CameraPosition.y += mousespeed*float(yLast - y);
		yLast = y;
	}
	updateViewMat();*/
}


bool loadOBJ(
	const char * path,
	std::vector<glm::vec3> & out_vertices,
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
) {
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else {
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}

	return true;
}

GLuint loadBMP_custom(const char * imagepath) {

	printf("Reading image %s\n", imagepath);

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;
	unsigned int width, height;
	unsigned char * data;

	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); return 0; }

	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
		return 0;
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n");    return 0; }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n");    return 0; }

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)    imageSize = width*height * 3; 
	if (dataPos == 0)      dataPos = 54; 

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	
	GLuint textureID = NULL;
	//TODO: Create one OpenGL texture and set the texture parameter 
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	return textureID;
}
void loadBMP_data(const char * imagepath, unsigned char * &data, unsigned int &width, unsigned int &height) {

	printf("Reading image %s\n", imagepath);

	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	FILE * file = fopen(imagepath, "rb");
	if (!file) { printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar(); }

	if (fread(header, 1, 54, file) != 54) {
		printf("Not a correct BMP file\n");
	}
	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
	}
	if (*(int*)&(header[0x1E]) != 0) { printf("Not a correct BMP file\n"); }
	if (*(int*)&(header[0x1C]) != 24) { printf("Not a correct BMP file\n"); }

	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);
	if (imageSize == 0)    imageSize = width*height * 3;
	if (dataPos == 0)      dataPos = 54;

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);
}
GLuint loadCubemap(vector<const GLchar*> faces) {
	unsigned int width, height;
	unsigned char* data;
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		loadBMP_data(faces[i], data, width, height);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return textureID;
}

void sendSkyBoxDataToOpenGL() {
	//Load objects and bind to VAO & VBO

	//skybox
	GLfloat skyboxVertices[] = {
		//right
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		//left
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		//top
		-1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		//bottom
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		// back
		-1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,
		//front
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f
	};
	//GLfloat skyboxVertices[] = {
	//	right
	//	50.0f, -50.0f, -50.0f,
	//	50.0f, -50.0f, 50.0f,
	//	50.0f, 50.0f, 50.0f,
	//	50.0f, 50.0f, 50.0f,
	//	50.0f, 50.0f, -50.0f,
	//	50.0f, -50.0f, -50.0f,
	//	left
	//	-50.0f, -50.0f, 50.0f,
	//	-50.0f, -50.0f, -50.0f,
	//	-50.0f, 50.0f, -50.0f,
	//	-50.0f, 50.0f, -50.0f,
	//	-50.0f, 50.0f, 50.0f,
	//	-50.0f, -50.0f, 50.0f,
	//	top
	//	-50.0f, 50.0f, -50.0f,
	//	50.0f, 50.0f, -50.0f,
	//	50.0f, 50.0f, 50.0f,
	//	50.0f, 50.0f, 50.0f,
	//	-50.0f, 50.0f, 50.0f,
	//	-50.0f, 50.0f, -50.0f,
	//	bottom
	//	-50.0f, -50.0f, -50.0f,
	//	-50.0f, -50.0f, 50.0f,
	//	50.0f, -50.0f, -50.0f,
	//	50.0f, -50.0f, -50.0f,
	//	-50.0f, -50.0f, 50.0f,
	//	50.0f, -50.0f, 50.0f,
	//	 back
	//	-50.0f, 50.0f, -50.0f,
	//	-50.0f, -50.0f, -50.0f,
	//	50.0f, -50.0f, -50.0f,
	//	50.0f, -50.0f, -50.0f,
	//	50.0f, 50.0f, -50.0f,
	//	-50.0f, 50.0f, -50.0f,
	//	front
	//	-50.0f, -50.0f, 50.0f,
	//	-50.0f, 50.0f, 50.0f,
	//	50.0f, 50.0f, 50.0f,
	//	50.0f, 50.0f, 50.0f,
	//	50.0f, -50.0f, 50.0f,
	//	-50.0f, -50.0f, 50.0f
	//};
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
	// Load texture
	vector<const GLchar*> earth_faces;
	earth_faces.push_back("skybox/space/right.bmp");
	earth_faces.push_back("skybox/space/left.bmp");
	earth_faces.push_back("skybox/space/bottom.bmp");
	earth_faces.push_back("skybox/space/top.bmp");
	earth_faces.push_back("skybox/space/back.bmp");
	earth_faces.push_back("skybox/space/front.bmp");
	skybox_textureID = loadCubemap(earth_faces);
}

void sendObjectsDataToOpenGL() {

	//planets and space vehicle
	bool res1 = loadOBJ("obj/planet.obj", vertices_A, uvs_A, normals_A);
	bool res2 = loadOBJ("obj/planet.obj", vertices_B, uvs_B, normals_B);
	bool res3 = loadOBJ("obj/planet.obj", vertices_C, uvs_C, normals_C);
	bool res4 = loadOBJ("obj/jeep.obj", vertices_E, uvs_E, normals_E);
	bool res5 = loadOBJ("obj/rock.obj", vertices_ast, uvs_ast, normals_ast);

	glGenVertexArrays(1, &planetVAO);
	glBindVertexArray(planetVAO);

	//planet A
	glGenBuffers(1, &A_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, A_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_A.size() * sizeof(glm::vec3), &vertices_A[0], GL_STATIC_DRAW);

	glGenBuffers(1, &A_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, A_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_A.size() * sizeof(glm::vec2), &uvs_A[0], GL_STATIC_DRAW);

	glGenBuffers(1, &A_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, A_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_A.size() * sizeof(glm::vec3), &normals_A[0], GL_STATIC_DRAW);

	//planet B
	glGenBuffers(1, &B_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, B_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_B.size() * sizeof(glm::vec3), &vertices_B[0], GL_STATIC_DRAW);

	glGenBuffers(1, &B_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, B_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_B.size() * sizeof(glm::vec2), &uvs_B[0], GL_STATIC_DRAW);

	glGenBuffers(1, &B_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, B_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_B.size() * sizeof(glm::vec3), &normals_B[0], GL_STATIC_DRAW);

	//planet C
	glGenBuffers(1, &C_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, C_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_C.size() * sizeof(glm::vec3), &vertices_C[0], GL_STATIC_DRAW);

	glGenBuffers(1, &C_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, C_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_C.size() * sizeof(glm::vec2), &uvs_C[0], GL_STATIC_DRAW);

	glGenBuffers(1, &C_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, C_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_C.size() * sizeof(glm::vec3), &normals_C[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &vehicleVAO);
	glBindVertexArray(vehicleVAO);

	//asteroid
	glGenBuffers(1, &ast_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ast_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_ast.size() * sizeof(glm::vec3), &vertices_ast[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ast_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ast_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_ast.size() * sizeof(glm::vec2), &uvs_ast[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ast_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, ast_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_ast.size() * sizeof(glm::vec3), &normals_ast[0], GL_STATIC_DRAW);

	//vehicle E
	glGenBuffers(1, &E_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, E_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_E.size() * sizeof(glm::vec3), &vertices_E[0], GL_STATIC_DRAW);

	glGenBuffers(1, &E_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, E_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_E.size() * sizeof(glm::vec2), &uvs_E[0], GL_STATIC_DRAW);

	glGenBuffers(1, &E_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, E_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_E.size() * sizeof(glm::vec3), &normals_E[0], GL_STATIC_DRAW);

	//textures
	A_texture[0] = loadBMP_custom("texture/earth.bmp");
	A_texture[1] = loadBMP_custom("normal_map/earth_normal.bmp");
	B_texture[0] = loadBMP_custom("texture/earth.bmp");
	B_texture[1] = loadBMP_custom("texture/grass.bmp");
	C_texture = loadBMP_custom("texture/stone.bmp");
	E_texture = loadBMP_custom("texture/brickwall.bmp");
	ast_texture = loadBMP_custom("texture/ast.bmp");

	//drawsizes
	A_drawsize = (GLsizei)vertices_A.size();
	B_drawsize = (GLsizei)vertices_B.size();
	C_drawsize = (GLsizei)vertices_C.size();
	E_drawsize = (GLsizei)vertices_E.size();
	ast_drawsize = (GLsizei)vertices_ast.size();
}

void sendLbDataToOpenGL() {
	//light box
	const GLfloat lb_vertices[] =
	{
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO); //forth VAO sun
	glGenBuffers(1, &lightVBO);
	//vertex
	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(lb_vertices), lb_vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void createAsteroidModel() {
	astModelMatrices = new glm::mat4[amount];
	GLfloat radius = 5.0f;
	GLfloat offset = 1.2f;
	for (GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y = displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));
		// 2. Scale: Scale between 0.05 and 0.25f
		GLfloat scale = float((rand() % 20) / 500.0f + 0.05);
		model = glm::scale(model, glm::vec3(scale));
		// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
		GLfloat rotAngle = float((rand() % 360));
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
		// 4. Now add to list of matrices
		astModelMatrices[i] = model;
	}
}

void paintGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	updateLightPosition();
	if (sOn == true) {
		Skb_ModelMatrix = glm::translate(glm::mat4(), glm::vec3(ModelMatrix_E*glm::vec4(0, 0, 0, 1)))*glm::translate(glm::mat4(), glm::vec3(glm::vec4(0, 2, 0, 1)));
		CameraPosition = glm::vec3(Skb_ModelMatrix*glm::vec4(0,0,0,1));
		glm::vec3 newUp = glm::vec3(0, 1, 0);
		glm::vec3 newFront = glm::vec3(ModelMatrix_E*glm::vec4(1,0,0,0));
		camera.setViewMatrix(CameraPosition, newUp, newFront, -90.0f, -0.0f);
	}
	view = camera.GetViewMatrix();

	//TODO:
	//Set lighting information, such as position and color of lighting source
	//Set transformation matrix
	//Bind different texture
	GLint ModelMatrixUniformLocation = glGetUniformLocation(objects_programID, "ModelMatrix");
	GLint ViewMatrixUniformLocation = glGetUniformLocation(objects_programID, "ViewMatrix");
	GLint ProjectionUniformLocation = glGetUniformLocation(objects_programID, "Projection");
	GLint LightPositionUniformLocation = glGetUniformLocation(objects_programID, "LightPosition_cameraspace");
	GLint addLightPositionUniformLocation = glGetUniformLocation(objects_programID, "addLightPosition_cameraspace");
	GLint LightPowerDiffuseUniformLocation = glGetUniformLocation(objects_programID, "LightPower_Diffuse");
	GLint LightPowerSpecularUniformLocation = glGetUniformLocation(objects_programID, "LightPower_Specular");
	GLint addLightPowerDiffuseUniformLocation = glGetUniformLocation(objects_programID, "addLightPower_Diffuse");
	GLint addLightPowerSpecularUniformLocation = glGetUniformLocation(objects_programID, "addLightPower_Specular");
	GLint normalMapping_flagUniformLocation = glGetUniformLocation(objects_programID, "normalMapping_flag");
	GLint multipleMapping_flagUniformLocation = glGetUniformLocation(objects_programID, "multipleMapping_flag");
	GLint lambdaUniformLocation = glGetUniformLocation(objects_programID, "lambda");
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)7.0f / (float)5.0f, 0.1f, 100.0f);

	glUniform1f(lambdaUniformLocation, 0.5f);
	glUniform1f(LightPowerDiffuseUniformLocation, LightPowerDiffuse);
	glUniform1f(LightPowerSpecularUniformLocation, LightPowerSpecular);
	glUniform1f(addLightPowerDiffuseUniformLocation, addLightPowerDiffuse);
	glUniform1f(addLightPowerSpecularUniformLocation, addLightPowerSpecular);
	glUniform3f(LightPositionUniformLocation, LightPosition_cameraspace.x, LightPosition_cameraspace.y, LightPosition_cameraspace.z);
	glUniform3f(addLightPositionUniformLocation, addLightPosition_cameraspace.x, addLightPosition_cameraspace.y, addLightPosition_cameraspace.z);
	glUniformMatrix4fv(ProjectionUniformLocation, 1, GL_FALSE, &projection[0][0]);

	//+++++Skybox++++++//
	glDepthMask(GL_FALSE);
	glUseProgram(skybox_programID);
	glUniformMatrix4fv(glGetUniformLocation(skybox_programID, "M"), 1, GL_FALSE, &Skb_ModelMatrix[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(skybox_programID, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(skybox_programID, "projection"), 1, GL_FALSE, &projection[0][0]);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skybox_programID, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
	//+++++Skybox++++++//

	//+++++Lightbox+++++//
	glUseProgram(lb_programID);
	glm::mat4 MVP = glm::mat4(1.0f);
	GLuint MatrixID = glGetUniformLocation(lb_programID, "MVP");
	glm::mat4 lb_translate = glm::translate(glm::mat4(), LightPosition);
	//Model matrix : translation
	glm::mat4 model = glm::mat4(1.0f);
	glBindVertexArray(lightVAO);
	MVP = projection * view * lb_translate * model * scale_ast;
	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//+++++Lightbox+++++//

	//+++++Objects+++++//
	glUseProgram(objects_programID);
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skybox_programID, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_textureID);
	glBindVertexArray(0);
	//draw planet A
	ModelMatrix_A = ModelMatrix_A*rotateA;
	rotatedA = rotateA*rotatedA;
	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_A[0][0]);
	glBindVertexArray(planetVAO);
	GLuint A_textureID_0 = glGetUniformLocation(objects_programID, "myTextureSampler");
	GLuint A_textureID_1 = glGetUniformLocation(objects_programID, "myTextureSampler2");
	glUniform1i(normalMapping_flagUniformLocation, 1);
	glUniform1i(multipleMapping_flagUniformLocation, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, A_texture[0]);
	glUniform1i(A_textureID_0, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, A_texture[1]);
	glUniform1i(A_textureID_1, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, A_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, A_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, A_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, A_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//draw planet B
	if (vehicleTrans == true) {
		if (movTime == false) {
			glUniform1f(lambdaUniformLocation, float(sin(swing/100.0f) + 1.0f) / 2.0f);
		}
	}
	ModelMatrix_B = ModelMatrix_B*rotateB;
	rotatedB = rotateB*rotatedB;
	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_B[0][0]);
	glBindVertexArray(planetVAO);
	GLuint B_textureID_0 = glGetUniformLocation(objects_programID, "myTextureSampler");
	GLuint B_textureID_1 = glGetUniformLocation(objects_programID, "myTextureSampler2");
	glUniform1i(normalMapping_flagUniformLocation, 0);
	glUniform1i(multipleMapping_flagUniformLocation, 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, B_texture[0]);
	glUniform1i(B_textureID_0, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, B_texture[1]);
	glUniform1i(B_textureID_1, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, B_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, B_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, B_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, B_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//draw planet C
	ModelMatrix_C = translationC3*rotationC2*translationC1*ModelMatrix_C*rotateC;
	rotatedC = rotateC*rotatedC;
	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_C[0][0]);
	glBindVertexArray(planetVAO);
	GLuint C_textureID = glGetUniformLocation(objects_programID, "myTextureSampler");
	glUniform1i(normalMapping_flagUniformLocation, 0);
	glUniform1i(multipleMapping_flagUniformLocation, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, C_texture);
	glUniform1i(C_textureID, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, C_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, C_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, C_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, C_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	#pragma region Asteroid normal method
	glm::mat4 asteroidOrbit = glm::translate(glm::mat4(), glm::vec3(glm::vec3(5, 0, -21)));
	glm::mat4 asteroidOrbit_Back = glm::translate(glm::mat4(), glm::vec3(glm::vec3(-5, 0, 21)));
	glm::mat4 asteroidRotate = glm::rotate(asteroidOrbit, 0.001f, glm::vec3(0, 1, -0.5));
	for (GLuint i = 0; i < amount; i++)
	{
		ModelMatrix_ast = asteroidOrbit*rotationast2*astModelMatrices[i];
		astModelMatrices[i] = asteroidOrbit_Back * ModelMatrix_ast;
		glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &view[0][0]);
		glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_ast[0][0]);
		glBindVertexArray(planetVAO);
		GLuint ast_textureID = glGetUniformLocation(objects_programID, "myTextureSampler");
		glUniform1i(normalMapping_flagUniformLocation, 0);
		glUniform1i(multipleMapping_flagUniformLocation, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, ast_texture);
		glUniform1i(ast_textureID, 1);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, ast_vertex_vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, ast_uv_vbo);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, ast_normal_vbo);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, ast_drawsize);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	}
	#pragma endregion

	//draw vehicle E
	if (vehicleRot == true) {
		ModelMatrix_E = translationE3*rotationE2*translationE1*ModelMatrix_E;
	}
	if (vehicleTrans == true) {
		if ((ModelMatrix_E*glm::vec4(0,0,0,1.0)).z > -18.2 && (ModelMatrix_E*glm::vec4(0, 0, 0, 1.0)).x < 6.4 && movTime == true) {
			ModelMatrix_E = MovE*ModelMatrix_E;
		}
		else {
			movTime = false;
			rotationE5 = glm::rotate(glm::mat4(), speed, glm::vec3(0, 1, 0));
			swing++;
			ModelMatrix_E = translationE6*rotationE5*translationE4*ModelMatrix_E;
		}
	}
	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_E[0][0]);
	glBindVertexArray(vehicleVAO);
	GLuint E_textureID = glGetUniformLocation(objects_programID, "myTextureSampler");
	glUniform1i(normalMapping_flagUniformLocation, 0);
	glUniform1i(multipleMapping_flagUniformLocation, 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, E_texture);
	glUniform1i(E_textureID, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, E_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, E_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, E_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, E_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	//+++++Objects+++++//

	glFlush();
	glutPostRedisplay();
}

void initializedGL(void) 
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	// set skybox_programID & bind its shader & send skybox geometry data to opengl
	skybox_programID = installShaders("skb_VertexShader.glsl", "skb_FragmentShader.glsl");
	sendSkyBoxDataToOpenGL();
	// objects
	objects_programID = installShaders("obj_VertexShader.glsl", "obj_FragmentShader.glsl");
	sendObjectsDataToOpenGL();
	// light box
	lb_programID = installShaders("lb_VertexShader.glsl", "lb_FragmentShader.glsl");
	sendLbDataToOpenGL();
	// asteroid
	createAsteroidModel();
}

// reshape function, call with glutReshapeFunc(reshape) in yout main function
void reshape(int width, int height) {
	const float ar_origin = (float)WIDTH / (float)HEIGHT;
	const float ar_new = (float)width / (float)height;

	float scale_w = (float)width / (float)WIDTH;
	float scale_h = (float)height / (float)HEIGHT;
	if (ar_new > ar_origin) {
		scale_w = scale_h;
	}
	else {
		scale_h = scale_w;
	}

	float margin_x = (width - WIDTH * scale_w) / 2;
	float margin_y = (height - HEIGHT * scale_h) / 2;

	glViewport(GLint(margin_x), GLint(margin_y), GLsizei(WIDTH * scale_w), GLsizei(HEIGHT * scale_h));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, WIDTH / ar_origin, 0, HEIGHT / ar_origin, 0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("CSCI3260 Final Project");
	initializedGL();
	glutDisplayFunc(paintGL);
	glutReshapeFunc(reshape);
	glutMouseFunc(mousePress);
	glutMotionFunc(PassiveMouse);
	glutMouseWheelFunc(mouseWheel);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);

	glutMainLoop();

	return 0;
}