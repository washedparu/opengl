#pragma once

#include <iostream>

namespace Core {
    class IndexBuffer {
    public:
        IndexBuffer(const void* data, uint count);
        ~IndexBuffer();

        void Bind() const;
        void UnBind() const;
        uint GetCount() const;

    private:
        uint mRendererID;
        uint mCount;
    };
}