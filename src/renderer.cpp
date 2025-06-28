#include "core/renderer.h"
#include "core/vertexarray.h"    
#include "core/indexbuffer.h"   
#include "core/shader.h"         

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): "
                  << function << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}



Core::Renderer::Renderer() : mRendererID(0) {}
Core::Renderer::~Renderer() = default;

void Core::Renderer::DrawElements(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
    va.Bind();
    ib.Bind();
    glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Core::Renderer::Clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.1f, 0.1f, 0.15f, 1.0f); // grey
}