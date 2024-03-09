// template based on material from learnopengl.com
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include "Shaders.h"
#include "ParseElements.h"
#include "Object.h"
#include "Inputs.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <chrono>
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 800;




unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id=glCreateShader(type);
    const char * src=source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message=(char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout<<"Failed to compile shader"<<(type==GL_VERTEX_SHADER?"vertex":"fragment")<<std::endl;
        std::cout<<message<<std::endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program=glCreateProgram();
    unsigned int vs=CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs=CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "viewGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // glew: load all OpenGL function pointers
    glewInit();




    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    // float vertices[] = {
    //     -0.5f, -.5f, 0.0f, 1.0f, 0.0f,0.0f, // left  
    //      0.5f, -.5f, 0.0f, 0.0f, 1.0f, 0.0f,// right 
    //      0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f// top   
    // };
    // // unsigned int numVertices = sizeof(vertices)/3;
    float vertices[] = {
        -0.5f, -.5f, 0.0f, // left  
         1.0f,0.0f,0.0f,
         0.5f, -.5f, 0.0f, // right 
         0.0f,1.0f,0.0f,
        //  0.5f,0.5f, 0.0f,
         -0.5f,  0.5f, 0.0f,// top   
         0.0f,0.0f,1.0f,
         0.5f,  0.5f, 0.0f,// top   
         0.0f,0.0f,1.0f,
        
    };
    unsigned int indicies[]={
        0,1,2,
        2,1,3
    };
    std::string f="../../../../data/pawn.obj";
    Object ele=Object(f);
    std::vector<float> vs=ele.getVBO();
    std::vector<unsigned int> is=ele.getIndices();
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vs.size()*sizeof(float), vs.data(), GL_STATIC_DRAW);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, is.size()*sizeof(unsigned int), is.data(), GL_STATIC_DRAW);
    // note that this is allowed, the call to g0VertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    std::string sourceV=parseShaders("../../../../Shaders/vertex.shader");
    std::string sourceF=parseShaders("../../../../Shaders/fragment.shader");
    unsigned int shader=CreateShader(sourceV, sourceF);
    glUseProgram(shader);
    unsigned int transLoc=glGetUniformLocation(shader, "trans");
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float theta=0.0f;
    std::vector<int> times;
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        auto start=std::chrono::high_resolution_clock::now();
        // input
        // -----
        theta++;
        // processInput(window, &ele, theta);
        ele.rotate(glm::vec3{0.0f, 0.0f, 1.0f});
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(ele.trans));
        // render
        // ------
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        // vs=ele.getVBO();
        // glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // glBufferData(GL_ARRAY_BUFFER, vs.size()*sizeof(float), vs.data(), GL_STATIC_DRAW);
        // glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawElements(GL_TRIANGLES, is.size(), GL_UNSIGNED_INT, nullptr);
        // glDrawArrays(GL_TRIANGLES, 0, 6);
        // glBindVertexArray(0); // unbind our VA no need to unbind it every time 
 
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        auto stop=std::chrono::high_resolution_clock::now();
        std::chrono::microseconds duration=std::chrono::duration_cast<std::chrono::microseconds>(stop-start);
        times.push_back(duration.count());
    }
    int total=0;
    for(auto currTime:times){
        total+=currTime;
    }
    std::cout<<(total/times.size())<<std::endl; 
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}