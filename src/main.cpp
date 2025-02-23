#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void setRandomColor();

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* orangeFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";
const char* yellowFragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\n\0";

int main()
{

    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SHU", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load all OpenGL function pointers with GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    



    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }



    unsigned int orangeFragmentShader, yellowFragmentShader;
    orangeFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(orangeFragmentShader, 1, &orangeFragmentShaderSource, NULL);
    glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, NULL);
    glCompileShader(orangeFragmentShader);
    glCompileShader(yellowFragmentShader);

    glGetShaderiv(orangeFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(orangeFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(yellowFragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    unsigned int yellowShaderProgram, orangeShaderProgram;
    yellowShaderProgram = glCreateProgram();
    orangeShaderProgram = glCreateProgram();

    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(orangeShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowFragmentShader);
    glAttachShader(orangeShaderProgram, orangeFragmentShader);
    glLinkProgram(orangeShaderProgram);
    glLinkProgram(yellowShaderProgram);



    glGetProgramiv(orangeShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(orangeShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(yellowShaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(orangeFragmentShader);
    glDeleteShader(yellowFragmentShader);

    float vertices1[] = {
        -0.9f, -0.5f, 0.0f,  // left 
        0.0f, -0.5f, 0.0f,  // right
        -0.45f, 0.5f, 0.0f,  // top 
    };
    float vertices2[] = {
        0.0f, -0.5f, 0.0f,  // left
        0.9f, -0.5f, 0.0f,  // right
        0.45f, 0.5f, 0.0f   // top 
    };


    //setup buffer objects
    unsigned int VBO[2], VAO[2];
    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);


    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    

    //set background color
    setRandomColor();

    //set to wireframe mode
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // rendering commands
        glClear(GL_COLOR_BUFFER_BIT);

        
        
        // draw first triangle using the data from the first VAO
        glUseProgram(orangeShaderProgram);
        glBindVertexArray(VAO[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // then we draw the second triangle using the data from the second VAO
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAO[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        // check and call events and swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();


    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteProgram(yellowShaderProgram);
    glDeleteProgram(orangeShaderProgram);

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
    {
        glfwSetWindowShouldClose(window, true);
    }

    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
		setRandomColor();
    }

}

void setRandomColor() {
    float r = (float)rand() / RAND_MAX;
    float g = (float)rand() / RAND_MAX;
    float b = (float)rand() / RAND_MAX;
    glClearColor(r, g, b, 1.0f);
}