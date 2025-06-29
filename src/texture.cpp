#include "core/texture.h"
#include "stb_image.h"

Core::Texture::Texture(const std::string& path) 
: mFilePath(path.c_str()), mRendererID(0), mBuffer(nullptr), mWidth(0), mHeight(0), mBPP(0)
{
    stbi_set_flip_vertically_on_load(true);
    mBuffer = stbi_load(path.c_str(), &mWidth, &mHeight, &mBPP, 4);

    if(!mBuffer) {
        fprintf(stderr, "Failed to load texture {}\n", path.c_str());
    }

    
    GLCall(glGenTextures(1, &mRendererID));
    glBindTexture(GL_TEXTURE_2D, mRendererID);
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mBuffer));

    GLCall(glGenerateMipmap(GL_TEXTURE_2D));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    GLCall(glBindTexture(GL_TEXTURE_2D, 0));


    stbi_image_free(mBuffer);

}


Core::Texture::~Texture() {
    GLCall(glDeleteTextures(1, &mRendererID));
}

void Core::Texture::Bind(uint slot) const {
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, mRendererID));
}

void Core::Texture::UnBind() const {
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}