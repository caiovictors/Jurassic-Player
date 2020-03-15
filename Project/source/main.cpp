#include <glm/glm.hpp>
#include "functions.hpp"
using namespace std;

//ESSAS SAO AS CORES QUE CORRESPONDEM AOS VERTICES
float timeValue; 
float greenValue;
float redValue;
float blueValue;

//VERTICES UTILIZADOS
float vertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  greenValue, redValue, blueValue,  // bottom right
        -0.5f, -0.5f, 0.0f,  greenValue, redValue, blueValue,  // bottom left
         0.0f,  0.5f, 0.0f,  greenValue, redValue, blueValue   // top 

    };

int main()
{   
    // função pra instanciar a janela do GLFW
    glfwInit();
    glwindowhint();

    //objeto janela
    GLFWwindow* window = glfwCreateWindow(800, 600, "janelinha da alegria", NULL, NULL);
    
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // função glad para carregar a função do openGL

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }    
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  
    /* -------------------------------------------
        CLOUD NE */

    int vertexShader = glCreateShader(GL_VERTEX_SHADER); // criando um shader de vertice
    glVertexsourcecompile(vertexShader);

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // criando frag shader
    glFragmentsourcecompile(fragmentShader);

    int shaderProgram = glCreateProgram();//criando programa shader
    glattachlink(shaderProgram, vertexShader, fragmentShader);

    
    unsigned int VBO, VAO;  //criando objetos vertice
    glGenBindvertexarray(&VAO);
  //  glGenBindvertexbuffer(&VBO, vertices);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); //carregando vertices no buffer

    //setando atributos de vertices
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 


    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // loop de renderização
    while(!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);
        // comandos de renderização
        glUseProgram(shaderProgram);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // limpar o buffer com essa cor :)
        glClear(GL_COLOR_BUFFER_BIT);
        timeValue = glfwGetTime();
        greenValue = sin(timeValue);
        redValue = cos(timeValue);
        blueValue = (redValue + greenValue) / 2.0f;
        if(greenValue < 0) greenValue = greenValue*-1;
        if (redValue < 0) redValue = redValue*-1;
        if (blueValue < 0) blueValue = blueValue*-1;
        vertices[3] = greenValue;
        vertices[10] = redValue;
        vertices[17] = blueValue;
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW); //carregando vertices no buffer

    //    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
    //    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
        // draw our first triangle
        
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        
        glDrawArrays(GL_TRIANGLES, 0, 3); //desenhando

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    //limpar memoria
    glfwTerminate();
    return 0;
}