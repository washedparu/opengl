#pragma once

#include "core/renderer.h"
#include <vector>

struct vbe {
    uint type;
    uint count;
    unsigned char normalized;

    static uint getTypeSize(uint t) {
        switch (t) {
            case GL_FLOAT: return sizeof(GLfloat);
            case GL_UNSIGNED_INT: return sizeof(GLuint);
            case GL_UNSIGNED_BYTE: return sizeof(GLubyte);
        }
        ASSERT(false);
        return 0;
    }
};
namespace Core {
    
    class BufferLayout {
        public:
        BufferLayout() { this->mStride = 0; }
    
        template<typename T>
        void push(uint count);
        
        const std::vector<vbe>& GetElements() const { return mElements; }
        int GetStride() const { return mStride; }

        private:
            int mStride = 0;
            std::vector<vbe> mElements;
    };



    template<>
    inline void BufferLayout::push<float>(uint count) {
        mElements.push_back({GL_FLOAT, static_cast<unsigned int>(count), false});
        mStride += vbe::getTypeSize(GL_FLOAT) * count;
    }

    template<>
    inline void BufferLayout::push<unsigned int>(uint count) {
        mElements.push_back({GL_UNSIGNED_INT, static_cast<unsigned int>(count), GL_FALSE});
        mStride += vbe::getTypeSize(GL_UNSIGNED_INT) * count;
    }

    template<>
    inline void BufferLayout::push<unsigned char>(uint count) {
        mElements.push_back({GL_UNSIGNED_BYTE, static_cast<unsigned int>(count), GL_TRUE});
        mStride += vbe::getTypeSize(GL_UNSIGNED_BYTE) * count;
    }

}