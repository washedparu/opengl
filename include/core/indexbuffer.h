#pragma once

#include <iostream>

namespace Core {
    class IndexBuffer {
    public:
        IndexBuffer(const void* data, u_int count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;
        u_int GetCount() const;

    private:
        u_int mRendererID;
        u_int mCount;
    };
}