#include <glad/glad.h>
#include <GLFW/glfw3.h> 
#include <iostream>
//----------------------------------------------------------------------------------------
//FUNCOES REFERENTES A JANELAS

//redimenciona a janela para a viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

//entrada de controle 
void processInput(GLFWwindow *window)
{
    // função que recebe janela e tecla "esc" como entrada
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
        glfwSetWindowShouldClose(window, true);
}

void glwindowhint(){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
//--------------------------------------------------------------------------------------------

//FUNCOES REFERENTES A TRIANGULOS

//fonte dos shaders dos vertices
const char *vertexShaderSource = "#version 400 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
        "ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 400 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "uniform vec4 OurColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4 (ourColor, 1.0);\n"
    "}\n\0";

void glVertexsourcecompile(int vertexShader){
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//carregando fonte ao objeto shader

    glCompileShader(vertexShader);//compilando shader

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); // verificando se houve erro na compilacao
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void glFragmentsourcecompile(int fragmentShader){
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);//carregando fonte ao objeto

    glCompileShader(fragmentShader);// compilando frag shader

    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success); //verificando erro
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void glattachlink(int shaderProgram, int vertexShader, int fragmentShader){
    glAttachShader(shaderProgram, vertexShader);//aclopando shaders
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);// verificando erro
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader); //objetos deletados pois nao precisamos mais
    glDeleteShader(fragmentShader);
}

void glGenBindvertexarray(unsigned int *VAO){
    glGenVertexArrays(1, VAO);
    glBindVertexArray(*VAO);
}
/* NAO TO CONSEGUINDO FAZER ESSA FUNCAO FUNCIONAAAAAAAAAAAAAAAAR

void glGenBindvertexbuffer(unsigned int *VBO, float *vertices){
    glGenBuffers(1, VBO);
    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //carregando vertices no buffer

}
*/