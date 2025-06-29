#pragma once

#include "core/renderer.h"


namespace Core {
    class Texture {
    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind(uint slot) const;
        void UnBind() const;


        inline const char* GetFilePath() const { return mFilePath; }
        inline int GetWidth() const { return mWidth; }
        inline int GetHeight() const { return mHeight; }
        inline uint GetRendererID() const { return mRendererID; }
        inline unsigned char* GetBuffer() const { return mBuffer; }


    private:
        uint mRendererID;
        const char* mFilePath;
        unsigned char* mBuffer;
        int mWidth, mHeight, mBPP;
    };
}