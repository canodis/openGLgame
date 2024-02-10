#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram()
{
    programId = glCreateProgram();
    attachShader("./shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
    attachShader("./shaders/VertexShader.glsl", GL_VERTEX_SHADER);
    link();
    use();
}

ShaderProgram::ShaderProgram(const char *vertexShader, const char *fragmentShader)
{
    programId = glCreateProgram();
    attachShader(vertexShader, GL_VERTEX_SHADER);
    attachShader(fragmentShader, GL_FRAGMENT_SHADER);
    link();
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(programId);
}

void ShaderProgram::link()
{
    glLinkProgram(programId);
    int status;
    glGetProgramiv(programId, GL_LINK_STATUS, &status);
    if (!status)
    {
        char log[512];
        glGetProgramInfoLog(programId, 512, 0, log);
        std::cout << "Link Error !\n"
                  << log << std::endl;
    }
}

void ShaderProgram::use()
{
    glUseProgram(programId);
}

void ShaderProgram::attachShader(const char *fileName, unsigned int shaderType)
{
    unsigned int shaderId = glCreateShader(shaderType);

    std::string sourceCode = getShaderFromFile(fileName);
    const char *pointerSourceCode = &sourceCode[0];
    glShaderSource(shaderId, 1, &pointerSourceCode, 0);
    glCompileShader(shaderId);
    int status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        char log[512];
        glGetShaderInfoLog(shaderId, 512, 0, log);
        std::cout << "Shader Error !\n"
                  << log << std::endl;
        exit(1);
    }

    glAttachShader(programId, shaderId);
    glDeleteShader(shaderId);
}

std::string ShaderProgram::getShaderFromFile(const char *fileName)
{
    std::ifstream file(fileName);
    std::string data;

    if (file.is_open())
    {
        char readed;

        while ((readed = file.get()) != EOF)
            data += readed;
        file.close();
    }

    return (data);
}

void ShaderProgram::setMat3(const std::string &name, const glm::mat3 *value)
{
    glUniformMatrix3fv(m_UniformVars[name], 1, false, (GLfloat *)value);
}

void ShaderProgram::setVec3(const std::string &name, const glm::vec3 &value)
{
    glUniform3f(m_UniformVars[name], value.x, value.y, value.z);
}

void ShaderProgram::setVec4(const std::string &name, const glm::vec4 &value)
{
    glUniform4f(m_UniformVars[name], value.x, value.y, value.z, value.w);
}

void ShaderProgram::addUniform(const std::string &name)
{
    m_UniformVars[name] = glGetUniformLocation(programId, name.c_str());
}

void ShaderProgram::setMat4(const std::string &name, const glm::mat4 *value)
{
    glUniformMatrix4fv(m_UniformVars[name], 1, false, (GLfloat *)value);
}

void ShaderProgram::setFloat(const std::string &name, const float &value)
{
    glUniform1f(m_UniformVars[name], value);
}

void ShaderProgram::setInt(const std::string &name, const int &value)
{
    glUniform1i(m_UniformVars[name], value);
}

unsigned int ShaderProgram::getProgramId() const
{
    return (programId);
}
