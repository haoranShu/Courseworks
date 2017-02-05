/*********************************************************
FILE : submit.cpp (csci3260 2016-2017 Assignment 2)
*********************************************************/
/*********************************************************
Student Information
Student ID: 1155028934
Student Name: SHU Haoran
*********************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using glm::vec3;
using glm::mat4;

glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
glm::vec3 CameraPosition = glm::vec3(16, 12, 6);
glm::vec3 CameraPosition_jeep = glm::vec3(16, 12, 6);
glm::vec3 Origin_jeep = glm::vec3(0, 0, 0);
glm::mat4 ViewMatrix = glm::lookAt(
	CameraPosition,
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);
glm::mat4 ViewMatrix_jeep = glm::lookAt(
	CameraPosition_jeep,
	Origin_jeep, // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

void updateView() {
	ViewMatrix = glm::lookAt(
		CameraPosition,
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

void updateView_jeep() {
	ViewMatrix_jeep = glm::lookAt(
		CameraPosition_jeep,
		Origin_jeep, // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

glm::mat4 ModelMatrix = glm::mat4(1.0f);
glm::mat4 ModelMatrix_jeep = glm::mat4(1.0f);
glm::mat4 ModelMatrix_env = glm::mat4(1.0f);
glm::mat4 scale_env = glm::scale(glm::mat4(), glm::vec3(0.3f, 0.3f, 0.3f));

int xOrigin = -1;
int yOrigin = -1;
int xLast = xOrigin, yLast = yOrigin;
float mousespeed = 0.015f;

float LightPowerDiffuse = 100.0f;
float LightPowerSpecular = 100.0f;

glm::mat4 rotated = glm::mat4(1.0f);

glm::mat4 translationright = glm::translate(glm::mat4(), glm::vec3(rotated*glm::vec4(0, 0, -1, 1)));
glm::mat4 translationleft = glm::translate(glm::mat4(), glm::vec3(rotated*glm::vec4(0, 0, -1, 1)));
glm::mat4 translationback = glm::translate(glm::mat4(), glm::vec3(rotated*glm::vec4(1, 0, 0, 1)));
glm::mat4 translationfront = glm::translate(glm::mat4(), glm::vec3(rotated*glm::vec4(-1, 0, 0, 1)));

glm::mat4 rotatey = glm::rotate(glm::mat4(), -1.57f, glm::vec3(0, 1, 0));
glm::mat4 rotatesmall = glm::rotate(glm::mat4(), 0.001f, glm::vec3(0, 1, 0));

glm::vec3 LightPosition = glm::vec3(5.0,15.0,5.0);
glm::vec3 LightPosition_cameraspace;
void updateLightPosition_cameraspace() {
	glm::vec4 tmp = ViewMatrix*glm::vec4(LightPosition,1.0);
	LightPosition_cameraspace = glm::vec3(tmp.x,tmp.y,tmp.z);
}

std::vector<glm::vec3> vertices_plane, vertices_jeep, vertices_env;
std::vector<glm::vec2> uvs_plane, uvs_jeep, uvs_env;
std::vector<glm::vec3> normals_plane, normals_jeep, normals_env;

GLuint vaoID;

GLuint plane_texture, jeep_texture, env_texture;
GLuint plane_vertex_vbo, jeep_vertex_vbo, env_vertex_vbo;
GLuint plane_uv_vbo, jeep_uv_vbo, env_uv_vbo;
GLuint plane_normal_vbo, jeep_normal_vbo, env_normal_vbo;
GLsizei plane_drawsize, jeep_drawsize, env_drawsize;

GLint programID;
// Could define the Vao&Vbo and interaction parameter here

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
	string temp = readShaderCode("VertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
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

bool sOn = false;
void keyboard(unsigned char key, int x, int y)
{
	//TODO: Use keyboard to do interactive events and animation
	if (key == 's') {
		if (sOn) {
			sOn = false;
		}
		else {
			sOn = true;
		}
	}
	if (key == 'q') {
		LightPowerDiffuse *= 1.1f;
	}
	if (key == 'w') {
		LightPowerDiffuse *= 0.91f;
	}
	if (key == 'z') {
		LightPowerSpecular *= 1.1f;
	}
	if (key == 'x') {
		LightPowerSpecular *= 0.91f;
	}
}

int direction = 3;
int frontD = 3, backD = 1, leftD = 2, rightD = 0;

void specialKeys(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		int i = (direction - leftD + 4)%4;
		for (int k = 0; k < i; k++) {
			ModelMatrix_jeep = rotatey*ModelMatrix_jeep;
		}
		direction = leftD;
		CameraPosition_jeep += glm::vec3(rotated*glm::vec4(0, 0, -1, 1));
		Origin_jeep += glm::vec3(rotated*glm::vec4(0, 0, -1, 1));
	}
	if (key == GLUT_KEY_RIGHT) {
		int i = (direction - rightD + 4) % 4;
		for (int k = 0; k < i; k++) {
			ModelMatrix_jeep = rotatey*ModelMatrix_jeep;
		}
		direction = rightD;
		CameraPosition_jeep += glm::vec3(rotated*glm::vec4(0, 0, 1, 1));
		Origin_jeep += glm::vec3(rotated*glm::vec4(0, 0, 1, 1));
	}
	if (key == GLUT_KEY_UP) {
		int i = (direction - backD + 4) % 4;
		for (int k = 0; k < i; k++) {
			ModelMatrix_jeep = rotatey*ModelMatrix_jeep;
		}
		direction = backD;
		CameraPosition_jeep += glm::vec3(rotated*glm::vec4(1, 0, 0, 1));
		Origin_jeep += glm::vec3(rotated*glm::vec4(1, 0, 0, 1));
	}
	if (key == GLUT_KEY_DOWN) {
		int i = (direction - frontD + 4) % 4;
		for (int k = 0; k < i; k++) {
			ModelMatrix_jeep = rotatey*ModelMatrix_jeep;
		}
		direction = frontD;
		CameraPosition_jeep += glm::vec3(rotated*glm::vec4(-1, 0, 0, 1));
		Origin_jeep += glm::vec3(rotated*glm::vec4(-1, 0, 0, 1));
	}
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
	if (xOrigin >= 0) {
		CameraPosition.z += mousespeed*float(xLast - x);
		CameraPosition_jeep.z += mousespeed*float(xLast - x);
		xLast = x;
	}
	if (yOrigin >= 0) {
		CameraPosition.y += mousespeed*float(yLast - y);
		CameraPosition_jeep.y += mousespeed*float(yLast - y);
		yLast = y;
	}
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

	
	GLuint textureID;
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

void sendDataToOpenGL()
{
	//TODO:
	//Load objects and bind to VAO & VBO
	bool res1 = loadOBJ("plane.obj", vertices_plane, uvs_plane, normals_plane);
	bool res2 = loadOBJ("jeep.obj", vertices_jeep, uvs_jeep, normals_jeep);
	bool res3 = loadOBJ("stop_sign.obj", vertices_env, uvs_env, normals_env);

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	glGenBuffers(1, &plane_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_plane.size()*sizeof(glm::vec3), &vertices_plane[0], GL_STATIC_DRAW);

	glGenBuffers(1, &plane_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_plane.size()*sizeof(glm::vec2), &uvs_plane[0], GL_STATIC_DRAW);

	glGenBuffers(1, &plane_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, plane_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_plane.size()*sizeof(glm::vec3), &normals_plane[0], GL_STATIC_DRAW);

	glGenBuffers(1, &jeep_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, jeep_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_jeep.size()*sizeof(glm::vec3), &vertices_jeep[0], GL_STATIC_DRAW);

	glGenBuffers(1, &jeep_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, jeep_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_jeep.size()*sizeof(glm::vec2), &uvs_jeep[0], GL_STATIC_DRAW);

	glGenBuffers(1, &jeep_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, jeep_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_jeep.size()*sizeof(glm::vec3), &normals_jeep[0], GL_STATIC_DRAW);

	glGenBuffers(1, &env_vertex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env_vertex_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices_env.size()*sizeof(glm::vec3), &vertices_env[0], GL_STATIC_DRAW);

	glGenBuffers(1, &env_uv_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env_uv_vbo);
	glBufferData(GL_ARRAY_BUFFER, uvs_env.size()*sizeof(glm::vec2), &uvs_env[0], GL_STATIC_DRAW);

	glGenBuffers(1, &env_normal_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, env_normal_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals_env.size()*sizeof(glm::vec3), &normals_env[0], GL_STATIC_DRAW);

	//Load texture
	plane_texture = loadBMP_custom("plane_texture.bmp");
	jeep_texture = loadBMP_custom("jeep_texture.bmp");
	env_texture = loadBMP_custom("stop_texture.bmp");

	plane_drawsize = (GLsizei)vertices_plane.size();
	jeep_drawsize = (GLsizei)vertices_jeep.size();
	env_drawsize = (GLsizei)vertices_env.size();
}

void paintGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	//TODO:
	//Set lighting information, such as position and color of lighting source
	//Set transformation matrix
	//Bind different texture
	GLint ModelMatrixUniformLocation = glGetUniformLocation(programID, "ModelMatrix");
	GLint ViewMatrixUniformLocation = glGetUniformLocation(programID, "ViewMatrix");
	GLint ProjectionUniformLocation = glGetUniformLocation(programID, "Projection");
	GLint LightPositionUniformLocation = glGetUniformLocation(programID, "LightPosition_cameraspace");
	GLint LightPowerDiffuseUniformLocation = glGetUniformLocation(programID, "LightPower_Diffuse");
	GLint LightPowerSpecularUniformLocation = glGetUniformLocation(programID, "LightPower_Specular");
	
	updateLightPosition_cameraspace();
	glUniform1f(LightPowerDiffuseUniformLocation, LightPowerDiffuse);
	glUniform1f(LightPowerSpecularUniformLocation, LightPowerSpecular);
	glUniform3f(LightPositionUniformLocation, LightPosition_cameraspace.x, LightPosition_cameraspace.y, LightPosition_cameraspace.z);
	glUniformMatrix4fv(ProjectionUniformLocation, 1, GL_FALSE, &Projection[0][0]);

	//draw plane
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix[0][0]);
	updateView();
	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &ViewMatrix[0][0]);
	GLuint plane_textureID = glGetUniformLocation(programID, "myTextureSampler");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, plane_texture);
	glUniform1i(plane_textureID, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, plane_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, plane_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, plane_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
	glDrawArrays(GL_TRIANGLES, 0, plane_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//draw stop_sign
	glm::mat4 translationz = glm::translate(glm::mat4(), glm::vec3(3, 0, 4));
	ModelMatrix_env = translationz*rotatey*scale_env;
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_env[0][0]);
	GLuint env_textureID = glGetUniformLocation(programID, "myTextureSampler");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, env_texture);
	glUniform1i(env_textureID, 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, env_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, env_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, env_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, env_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	//draw car
	glUniformMatrix4fv(ModelMatrixUniformLocation, 1, GL_FALSE, &ModelMatrix_jeep[0][0]);
	if (sOn) {
		ModelMatrix_jeep = rotatesmall*ModelMatrix_jeep;
		rotated = rotatesmall*rotated;
	}
	updateView_jeep();
	glUniformMatrix4fv(ViewMatrixUniformLocation, 1, GL_FALSE, &ViewMatrix_jeep[0][0]);
	GLuint jeep_textureID = glGetUniformLocation(programID, "myTextureSampler");
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, jeep_texture);
	glUniform1i(jeep_textureID, 2);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, jeep_vertex_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, jeep_uv_vbo);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, jeep_normal_vbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glDrawArrays(GL_TRIANGLES, 0, jeep_drawsize);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	
	glFlush();
	glutPostRedisplay();
}

void initializedGL(void) 
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	installShaders();
	sendDataToOpenGL();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	//TODO:

	//Create a window with title specified
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("My Window");

	initializedGL();
	glutDisplayFunc(paintGL);
	glutPassiveMotionFunc(PassiveMouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutMouseFunc(mousePress);
	glutMotionFunc(PassiveMouse);

	glutMainLoop();

	return 0;
}