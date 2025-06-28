#include "core/vertexbuffer.h"
#include "core/renderer.h"

Core::VertexBuffer::VertexBuffer(const void* data, unsigned int size) {
    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

Core::VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1,&mRendererID));
}

void Core::VertexBuffer::Bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, mRendererID));
}
void Core::VertexBuffer::UnBind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,0));
}