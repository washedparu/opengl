#include "core/vertexarray.h"
#include "core/bufferlayout.h"
#include "core/renderer.h"



Core::VertexArray::VertexArray() {
    GLCall(glGenVertexArrays(1, &mRendererID));
}

Core::VertexArray::~VertexArray() {
    GLCall(glDeleteVertexArrays(1, &mRendererID));
}

void Core::VertexArray::Bind() const {
    GLCall(glBindVertexArray(mRendererID));
}


void Core::VertexArray::UnBind() const {
    GLCall(glBindVertexArray(0));
}



void Core::VertexArray::addBuffer(const VertexBuffer& vb, const BufferLayout& layout) {
    Bind();
    vb.Bind();
    const auto& elements = layout.GetElements();
    uintptr_t offset = 0;
    
    for(unsigned int v = 0; v < elements.size(); v++) {
        const auto& elm = elements[v];
        GLCall(glEnableVertexAttribArray(v));
        GLCall(glVertexAttribPointer(v, 
            elm.count,
            elm.type, 
            elm.normalized, 
            layout.GetStride(), 
            (const void*)offset));
            
        offset += elm.count * vbe::getTypeSize(elm.type);
    }
    
}