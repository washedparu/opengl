<<<<<<< HEAD
// TODO: 
/*
a different shader class
and keep learning fuckhead.
*/
=======
#include "core/renderer.h"
#include "core/vertexarray.h"
#include "core/vertexbuffer.h"
#include "core/bufferlayout.h"
#include "core/indexbuffer.h"
#include "core/shader.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
>>>>>>> dd92d0c (i foking did it)

int main() {
    using namespace Core;

    GLFWwindow* window;
    int windowWidth = 1000, windowHeight = 800;

    if(!glfwInit()) {
        fprintf(stderr, "Failed to intialize glfw\n");
        return 0;
    }
    printf("Initialized glfw!\n");

    window = glfwCreateWindow(windowWidth, windowHeight, "OpenGL", nullptr, nullptr);

    if(!window) {
        fprintf(stderr, "Failedt to create the window\n");
        return 0;
    }
    printf("Created the window!\n");


    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to intialize glew\n");
        return 0;
    }
    printf("Initialized glew!\n");



    float vertices[8] = {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    uint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexArray va; 
    VertexBuffer vb(vertices, sizeof(vertices));

    BufferLayout layout;

    layout.push<float>(2);

    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(uint));
    
    Shader shader(
        "../res/shaders/vert.glsl",
        "../res/shaders/frag.glsl"
    );

    shader.Bind();
    shader.SetUniform4f("uColor", glm::vec4(1.0f, 0.5f, 0.2f, 1.0f));


    Renderer renderer;

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    while (!glfwWindowShouldClose(window)) {
        renderer.Clear();

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }
        renderer.DrawElements(va, ib, shader);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
