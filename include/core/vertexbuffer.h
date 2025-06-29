#pragma once

#include <iostream>

namespace Core {
    class VertexBuffer {
    public:
        VertexBuffer(const void* data, u_int size);
        ~VertexBuffer();

        void Bind() const;
        void UnBind() const;
    private:
        uint mRendererID;
    };
}