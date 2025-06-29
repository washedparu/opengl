#pragma once

#include "core/vertexbuffer.h"
#include "core/bufferlayout.h"

namespace Core {
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        void Bind() const;
        void UnBind() const;
        
        void addBuffer(const VertexBuffer& vb, const BufferLayout& layout);

    private:
        uint mRendererID;
    };
}