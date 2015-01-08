#include <GL\glew.h>
#include <GL\wglew.h>

//GLEW includes must b e first!
#include <GLFW\glfw3.h>

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include "Player.h"
#include "Asteroid.h"

#define GLEW_STATIC

using namespace std;

GLuint CreateShader(GLenum a_ShaderType, const char* a_strShaderFile);

GLuint CreateProgram(const char* a_vertex, const char* a_frag);

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar);

//struct Vertex
//{
//	float fPositions[4];
//	float fColors[4];
//};

int main()
{
	srand(time(nullptr));

	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window;
	window = glfwCreateWindow(1024, 720, "Hello World", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	//make window's context current 
	glfwMakeContextCurrent(window);

	//start GLEW
	if (glewInit() != GLEW_OK)
	{
		//openGL didn't start shutdown GLFW and return error code
		glfwTerminate();
		return -1;
	}

	printf("Version: %s\n", glGetString(GL_VERSION));

	Vertex* stars = new Vertex[100];

	for (int i = 0; i < 100; i++)
	{
		stars[i].fPositions[0] = rand() % 1024;
		stars[i].fPositions[1] = rand() % 720;
		stars[i].fPositions[2] = 0.0f;
		stars[i].fPositions[3] = 1.0f;
		stars[i].fColors[0] = 1.0f;
		stars[i].fColors[1] = 1.0f;
		stars[i].fColors[2] = 1.0f;
		stars[i].fColors[3] = 1.0f;
	}

	Player myShape;
	myShape.Initialize(glm::vec4(1024 / 2.0, 720 / 2.0, 0, 0), glm::vec4(0, 0, 1, 1));
	Asteroid myAsteroid;
	myAsteroid.Initialize(glm::vec4(1024 * .25f, 720 * .75f, 0, 0), glm::vec4(0, 1, 0, 1));
	Asteroid anotherAsteroid;
	anotherAsteroid.Initialize(glm::vec4(1024 * .75f, 720 * .25f, 0, 0), glm::vec4(0, 1, 0, 1));

	//create ID for a vertex buffer object
	GLuint uiVBO;
	glGenBuffers(1, &uiVBO);

	//GLuint uiVBO2;
	//glGenBuffers(1, &uiVBO2);

	if (uiVBO != 0)
	{
		//bind vbo
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
		//allocate space for vertices on the graphics card
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* 100, NULL, GL_STATIC_DRAW);
		//get pointer to allocated space on the graphics card
		GLvoid* vBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		//copy data to graphics card
		memcpy(vBuffer, stars, sizeof(Vertex)* 100);
		//unmap and unbind buffer
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	//create shader program
	GLuint programFlat = CreateProgram(".\\source\\VertexShader.glsl", ".\\source\\FlatFragmentShader.glsl");

	//find the position of the matrix variable int the shader program
	GLuint IDFlat = glGetUniformLocation(programFlat, "MVP");

	//set up mapping to the screen to pixel coordinates
	float* orthographicProjection = getOrtho(0, 1024, 0, 720, 0, 100);
	//Matrix4::GetOrthographicProjection(0, 1024, 0, 720, 0, 100).Get(orthographicProjection);

	glPointSize(2);


	//loop until user closes the window
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//enable shaders
		glUseProgram(programFlat);

		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		//send ortho projection info to shader
		glUniformMatrix4fv(IDFlat, 1, GL_FALSE, orthographicProjection);

		//enable vertex array state
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		/*Since the data is in the same array, we need to specify the gap between vertices (a whole Vertex structure instance) and the offset
		of the data from the beginning of the structure instance.  The positions are at the start, so their offset is o. but the colors are after the positions
		so they are offset by the size of the position data.*/
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)* 4));

		//specify where vertex array is
		//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, vertexPositions);
		//glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, vertexColors);


		//draw code here
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glDrawArrays(GL_POINTS, 0, 100);

		myShape.Draw();
		myAsteroid.Draw();
		anotherAsteroid.Draw();

		//swap front and back buffers
		glfwSwapBuffers(window);

		//poll for and process events
		glfwPollEvents();
	}

	glfwTerminate();

	//delete myShape;
	delete stars;
	return 0;
}

GLuint CreateShader(GLenum a_ShaderType, const char* a_ShaderFile)
{
	std::string shaderCode;
	//open shader file
	std::ifstream shaderStream(a_ShaderFile);
	//if that worked ok, load file line by line
	if (shaderStream.is_open())
	{
		std::string line = "";
		while (std::getline(shaderStream, line))
		{
			shaderCode += "\n" + line;
		}
		shaderStream.close();
	}

	//convert to cstring
	char const* shaderSourcePointer = shaderCode.c_str();

	//create shader ID
	GLuint shader = glCreateShader(a_ShaderType);
	//load source code
	glShaderSource(shader, 1, &shaderSourcePointer, NULL);

	//compile shader
	glCompileShader(shader);

	//check for errors
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, infoLog);

		const char* shaderType = NULL;
		switch (a_ShaderType)
		{
		case GL_VERTEX_SHADER:
			shaderType = "vertex";
			break;
		case GL_FRAGMENT_SHADER:
			shaderType = "fragment";
			break;
		}

		fprintf(stderr, "Compile failure in %s shader:\n%s\n", shaderType, infoLog);
		delete[] infoLog;
	}

	return shader;

}

GLuint CreateProgram(const char* a_vertex, const char* a_frag)
{
	//ofstream file;
	//file.open(a_vertex, ios::in);
	//cout << file.is_open() << endl;

	std::vector<GLuint> shaderList;

	shaderList.push_back(CreateShader(GL_VERTEX_SHADER, a_vertex));
	shaderList.push_back(CreateShader(GL_FRAGMENT_SHADER, a_frag));

	//create shader program ID
	GLuint program = glCreateProgram();

	//attach shaders
	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glAttachShader(program, *shader);
	}

	//link program
	glLinkProgram(program);

	//check for link errors and output them
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, NULL, infoLog);

		fprintf(stderr, "Linker failure: %s\n", infoLog);
		delete[] infoLog;
	}

	for (auto shader = shaderList.begin(); shader != shaderList.end(); shader++)
	{
		glDetachShader(program, *shader);
		glDeleteShader(*shader);
	}
	return program;
}

float* getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar)
{
	//to correspond with mat4 in the shader
	//ideally this function would be part of your matrix class
	//however I wasn't willing to write your matrix class for you just to show you this
	//so here we are in array format!
	//add this to your matrix class as a challenge if you like!
	float* toReturn = new float[12];
	toReturn[0] = 2.0 / (right - left);;
	toReturn[1] = toReturn[2] = toReturn[3] = toReturn[4] = 0;
	toReturn[5] = 2.0 / (top - bottom);
	toReturn[6] = toReturn[7] = toReturn[8] = toReturn[9] = 0;
	toReturn[10] = 2.0 / (a_fFar - a_fNear);
	toReturn[11] = 0;
	toReturn[12] = -1 * ((right + left) / (right - left));
	toReturn[13] = -1 * ((top + bottom) / (top - bottom));
	toReturn[14] = -1 * ((a_fFar + a_fNear) / (a_fFar - a_fNear));
	toReturn[15] = 1;
	return toReturn;
}