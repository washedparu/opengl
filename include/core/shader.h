#pragma once
#include <unordered_map>
#include <string>
#include <glm/glm.hpp>

namespace Core { 

    struct Path {
        std::string vertexShader;
        std::string fragmentShader;
    };

    class Shader {
    public:
        Shader(const std::string& vertShaderPath, const std::string& fragShaderPath);
        ~Shader();
        
        
        void Bind() const;
        void UnBind() const;
        
        void SetUniform1f(const std::string& name, const glm::vec1& vec);
        void SetUniform2f(const std::string& name, const glm::vec2& vec);
        void SetUniform3f(const std::string& name, const glm::vec3& vec);
        void SetUniform4f(const std::string& name, const glm::vec4& vec);
        
        void SetUniform1i(const std::string& name, const glm::vec1& vec);
        void SetUniform2i(const std::string& name, const glm::vec2& vec);
        void SetUniform3i(const std::string& name, const glm::vec3& vec);
        void SetUniform4i(const std::string& name, const glm::vec4& vec);

        void SetUniformMat4(const std::string& name, glm::mat4);

    private:
        uint mRendererID;
        std::string mFragShaderPath;
        std::string mVertShaderPath;

        int GetUniformLocation(const std::string& name);
        std::unordered_map<std::string, int> mUniformLocationCache;
        
        uint CreateShader(const std::string& vertShader, const std::string& fragShader);
        uint CompileShader(const std::string& source, uint type);
        Path ReadShader(const std::string& vertPath, const std::string& fragPath);
    };
    
}