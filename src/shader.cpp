#include "core/shader.h"
#include "core/renderer.h"

Core::Shader::Shader(const std::string& vertShaderPath, const std::string& fragShaderPath) 
    : mVertShaderPath(vertShaderPath), mFragShaderPath(fragShaderPath), mRendererID(0) 
{   
    Core::Path shaderSrc = ReadShader(vertShaderPath, fragShaderPath);
    mRendererID = CreateShader(shaderSrc.vertexShader, shaderSrc.fragmentShader);

    GLCall(glUseProgram(mRendererID));
}


Core::Shader::~Shader() {
    GLCall(glDeleteProgram(mRendererID));
}

void Core::Shader::Bind() const {
    GLCall(glUseProgram(mRendererID));
}

void Core::Shader::UnBind() const {
    GLCall(glUseProgram(0));
}



uint Core::Shader::CompileShader(const std::string& source, uint type) {
    uint id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
    
    int rlt; // result
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &rlt));

    if(!rlt) {
        int len;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len));

        std::vector<char> msg(len);
        GLCall(glGetShaderInfoLog(id, len, &len, msg.data()));
        fprintf(stderr, "Failed to compile the {} shader\n", (type == GL_VERTEX_SHADER) ? "vertex" : "fragment");
        fprintf(stderr, "{}\n", msg.data());
        GLCall(glDeleteShader(id));
        return 0;
    }
    return id;
}




uint Core::Shader::CreateShader(const std::string& vertShader, const std::string& fragShader) {
    uint program = glCreateProgram();
    uint vs = CompileShader(vertShader, GL_VERTEX_SHADER);
    uint fs = CompileShader(fragShader, GL_FRAGMENT_SHADER);
    if(!vs || !fs) {
        GLCall(glDeleteShader(program));
        return 0;
    }

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    
    return program;
}


Core::Path Core::Shader::ReadShader(const std::string& vertPath, const std::string& fragPath) {
    std::ifstream vFile(vertPath); // vertex shader
    std::ifstream fFile(fragPath); // fragment shader

    if(!vFile.is_open()) {
        fprintf(stderr, "Failed to open vertex shader file.\n\tGiven path: {}", vertPath);
         throw std::runtime_error("Vertex shader file not found");
    }

    if(!fFile.is_open()) {
        fprintf(stderr, "Failed to open fragment shader file.\n\tGiven path: {}", fragPath);
         throw std::runtime_error("Fragment shader file not found");
    }

    std::stringstream vBuffer, fBuffer;
    vBuffer << vFile.rdbuf();
    fBuffer << fFile.rdbuf();

    return Core::Path { vBuffer.str(), fBuffer.str() };
}



int Core::Shader::GetUniformLocation(const std::string& name) {
    if(mUniformLocationCache.find(name) != mUniformLocationCache.end()) {
        return mUniformLocationCache[name];
    }

    GLCall(int location = glGetUniformLocation(mRendererID, name.c_str()));

    if(location == -1) {
        fprintf(stderr, "Failed to get uniform location ({})\n", name.c_str());
        return -1;
    }

    mUniformLocationCache[name] = location;

    return location;
}


void Core::Shader::SetUniform1f(const std::string& name, glm::vec1 vec) {
    GLCall(glUniform1f(GetUniformLocation(name), vec.x));
}

void Core::Shader::SetUniform2f(const std::string& name, glm::vec2 vec) {
    GLCall(glUniform2f(GetUniformLocation(name), vec.x, vec.y));
}

void Core::Shader::SetUniform3f(const std::string& name, glm::vec3 vec) {
    GLCall(glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z));
}

void Core::Shader::SetUniform4f(const std::string& name, glm::vec4 vec) {
    GLCall(glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
}



void Core::Shader::SetUniform1i(const std::string& name, glm::vec1 vec) {
    GLCall(glUniform1i(GetUniformLocation(name), vec.x));
}

void Core::Shader::SetUniform2i(const std::string& name, glm::vec2 vec) {
    GLCall(glUniform2i(GetUniformLocation(name), vec.x, vec.y));
}

void Core::Shader::SetUniform3i(const std::string& name, glm::vec3 vec) {
    GLCall(glUniform3i(GetUniformLocation(name), vec.x, vec.y, vec.z));
}

void Core::Shader::SetUniform4i(const std::string& name, glm::vec4 vec) {
    GLCall(glUniform4i(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w));
}

