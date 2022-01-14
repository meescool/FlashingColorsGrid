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
	-0.5f,	-0.5f,		0.0f,	0.8f,	0.3f,	0.02f,	// lower left corner
	-0.5f,	 0.5f,		0.0f,	0.8f,	0.3f,	0.02f,	// lower right corner
	 0.5f,	 0.5f,		0.0f,	1.0f,	0.6f,	0.32f,	// upper corner
	 0.5f,  -0.5f,		0.0f,	0.9f,	0.45f,	0.17f	// inner left
};

GLuint indices[] =
{
	0,2,1, // lower left triangle
	0,3,2, // lower right triangle

};


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
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

    glViewport(0, 0, 800, 600);

    // for resizing the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



    // setting initial color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);




    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

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

	//GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");



    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Start();
		//glUniform1f(uniID, 0.5);
		// bind the vao so opengl knows to use it
		VAO1.Bind();
		// draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
}
