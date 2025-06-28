#include "core/indexbuffer.h"
#include "core/renderer.h"

Core::IndexBuffer::IndexBuffer(const void* data, u_int count) : mCount(count) {
    ASSERT(sizeof(u_int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &mRendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW);
}

Core::IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &mRendererID));
}

void Core::IndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
}


void Core::IndexBuffer::UnBind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

u_int Core::IndexBuffer::GetCount() const {
    return mCount;
}