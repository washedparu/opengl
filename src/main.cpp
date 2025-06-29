#include "core/renderer.h"
#include "core/vertexarray.h"
#include "core/vertexbuffer.h"
#include "core/bufferlayout.h"
#include "core/indexbuffer.h"
#include "core/shader.h"
#include "core/texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*
    TODO: follow up with the cherno and how the FUCK he made that 'testing framework'
*/

int main() {
    using namespace Core;
    using namespace glm;

    GLFWwindow* window;
    const int windowWidth = 1000, windowHeight = 800;

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



    float vertices[16] = {
        // pos          // texcoord
        -0.5f, -0.5f,   0.0f, 0.0f,
         0.5f, -0.5f,   1.0f, 0.0f,
         0.5f,  0.5f,   1.0f, 1.0f,
        -0.5f,  0.5f,   0.0f, 1.0f
    };

    uint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    VertexArray va; 
    VertexBuffer vb(vertices, sizeof(vertices));

    BufferLayout layout;

    layout.push<float>(2);
    layout.push<float>(2);

    va.addBuffer(vb, layout);

    IndexBuffer ib(indices, sizeof(indices) / sizeof(uint));
    
    Shader shader(
        "../res/shaders/vert.glsl",
        "../res/shaders/frag.glsl"
    );
    shader.Bind();
    
    Texture texture("../res/textures/paru.png");
    
    texture.Bind(0); // sloth's 0
    shader.SetUniform1i("uTexture", vec1(0));
    shader.SetUniform2f("uOffset", vec2(0.0f, 0.0f));
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
