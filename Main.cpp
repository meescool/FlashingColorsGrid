#include <iostream>
#include <glad/glad.h>  // this needs to go before GLFW
#include <GLFW/glfw3.h>

#include"Shader.h"
#include"VAO.h"
#include"VBO.h"
#include"EBO.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// safer to use OPENGL version of floats
// give the coordinates of the vertices of a triangle
GLfloat vertices[] =
{ //			coordinates	   /				colors				//
	-1.0f,	 1.0f,		0.0f,	0.3f,	0.0f,	1.0f,	// lower left corner
	-0.33f,	 1.0f,		0.0f,	0.9f,	0.1f,	0.9f,	// lower right corner
	-1.0f,	 0.33f,		0.0f,	0.9f,	0.1f,	0.9f,	// upper corner
	-0.33f,  0.33f,		0.0f,	0.9f,	0.1f,	0.9f	// inner left
};

GLuint indices[] =
{
	0,1,2, // lower left triangle
	2,1,3, // lower right triangle

};

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(600, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // initializing glad
    //gladLoadGL();
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 600, 600);

    // for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // setting initial color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);




    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	const int ilen = 6;

	Shader shaderProgram("default.vert", "default.frag");

	// generates vertex array object and binds it
	VAO VAO1;
	VAO1.Bind();

	// generates vertex buffer object and links it to vertices
	VBO VBO1(vertices, sizeof(vertices));
	// generates element buffer object and links it to indices
	EBO EBO1(indices, sizeof(indices));

	// links vob to vao
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	// unbind all objects
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint mxID = glGetUniformLocation(shaderProgram.ID, "moveX");
	GLuint myID = glGetUniformLocation(shaderProgram.ID, "moveY");
	GLuint cID = glGetUniformLocation(shaderProgram.ID, "myColor");


	float m = 0;
	float x = 0;
	float y = 0;
	float c = 0;

    while (!glfwWindowShouldClose(window))
    {
		m+= 0.001;
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Start();
		// bind the vao so opengl knows to use it
		VAO1.Bind();
		// draw the triangle using the GL_TRIANGLES primitive
		x = 0.0f;
		y = 0.0f;
		glUniform1f(cID, 1);
		for (int i = 0; i <= 36 ; i++) {
			glUniform1f(cID, sin(c+i));
			glDrawElements(GL_TRIANGLES, ilen, GL_UNSIGNED_INT, 0);
			glUniform1f(mxID, x);
			glUniform1f(myID, y);
			x += 0.333f;
			if (i > 0) {
				if (i % 6 == 0) {
					x = 0.0f;
					y += 0.333f;
				}
			}
			c += 0.0001f;

		}

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // delete all the object we created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();

    glfwDestroyWindow(window);
    // need to always terminate
    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		std::cout << "F is being pressed" << std::endl;
}
