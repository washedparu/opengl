#pragma once

// includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>

#include "core/macros.h"


namespace Core { 
    class VertexArray;
    class IndexBuffer;
    class Shader;

    class Renderer
    {
    public:
        Renderer(); 
        ~Renderer();
        
        void DrawElements(const Core::VertexArray& va, const Core::IndexBuffer& ib, const Core::Shader& shader) const;
        void Clear() const;
    private:
        uint mRendererID;
    };

}