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

// Compiles shader  from source code and id
unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id=glCreateShader(type);
    const char * src=source.c_str();
    // Compile shader
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
    // Error catching in compiling shader
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
// Create shader function
unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    // Compiles the vertex and the fragment shader, also creates the program to be used
    unsigned int program=glCreateProgram();
    unsigned int vs=CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs=CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    // Prepare all programs and shaders
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    // Shaders are not needed
    glDeleteShader(vs);
    glDeleteShader(fs);
    // Returns the ID of the final program
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
    // Vertices for basic triangle
    float vertices[] = {
        -0.5f, -.5f, 0.0f, // left  
         1.0f,0.0f,0.0f,
         0.5f, -.5f, 0.0f, // right 
         0.0f,1.0f,0.0f,
         -0.5f,  0.5f, 0.0f,// top   
         0.0f,0.0f,1.0f,
         0.5f,  0.5f, 0.0f,// top   
         0.0f,0.0f,1.0f,
        
    };
    // Indices for shader
    unsigned int indicies[]={
        0,1,2,
        2,1,3
    };
    // Path to pawn when running from the build location
    std::string f="../../../../data/pawn.obj";
    // The object is instantiated
    Object ele=Object(f);
    // The initial vertices array and index array is created
    std::vector<float> vs=ele.getVBO();

    std::vector<unsigned int> is=ele.getIndices();
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vs.size()*sizeof(float), vs.data(), GL_STATIC_DRAW);
    // The following line was for sample triangle
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
    // GPU Sided
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(4*sizeof(float)));
    // GPU Sided
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7*sizeof(float)));
    // glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(7*sizeof(float)));
    glEnableVertexAttribArray(2);
    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    // The following line was for sample triangle
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, is.size()*sizeof(unsigned int), is.data(), GL_STATIC_DRAW);
    // note that this is allowed, the call to g0VertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
    // Shaders are parsed and created
    std::string sourceV=parseShaders("../../../../Shaders/vertex.shader");
    std::string sourceF=parseShaders("../../../../Shaders/fragment.shader");
    unsigned int shader=CreateShader(sourceV, sourceF);
    glUseProgram(shader);
    // GPU Sided
    ele.viewTrans=glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 10000.0f);
    unsigned int transLoc=glGetUniformLocation(shader, "trans");
    // uncomment this call to draw in wireframe polygons.
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    float theta=0.0f;
    std::vector<int> times;
    glEnable(GL_DEPTH_TEST);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        auto start=std::chrono::high_resolution_clock::now();
        // input
        // -----
        theta++;
        // Include this code below to allow user control
        processInput(window, &ele, theta);
        // ele.rotate(glm::vec3{0.0f, 0.0f, 1.0f});        // Default rotation
        std::vector<float> copy=vs;
        for(int i=0;i<vs.size();i+=10){
            glm::vec4 vert=glm::vec4{copy[i], copy[i+1], copy[i+2], copy[i+3]};
            vert=ele.trans*vert;
            // vert=ele.viewTrans*vert;
            copy[i]=vert.x;
            copy[i+1]=vert.y;
            copy[i+2]=vert.z;
            copy[i+3]=vert.w;
        }
        // GPU sided code below
        glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(ele.viewTrans));
        // render
        // ------
        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        // vs=ele.getVBO();
        // Redefine buffer data
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, copy.size()*sizeof(float), copy.data(), GL_STATIC_DRAW);
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
    // std::cout<<(total/times.size())<<std::endl; 
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