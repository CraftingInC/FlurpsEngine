
#include "ogl.h"
#include "logging.h"

unsigned int initMainShaders()
{
    // This shader is needed to cover the whole screen
    const char *vertexBackgroundShaderSource = "#version 450 core\n"
    "const vec2 quadVertices[4] = {\n"
    " vec2(-1.0, -1.0),\n"
    " vec2(1.0, -1.0),\n"
    " vec2(-1.0, 1.0),\n"
    " vec2(1.0, 1.0) };\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);\n"
    "}\n";

    // Eventually this shader will be a solid color for the background.
    // Using this also speeds up the frame rates since we are not using glClear.
    const char *fragmentBackgroundShaderSource = "#version 450 core\n"
    "#define fragCoord gl_FragCoord.xy\n"
    "out vec4 fragColor;\n"
    "uniform vec2 iResolution;\n"
    "uniform float iTime;\n"
    "uniform vec4 iMouse;\n"
    "void main()\n"
    "{\n"
    "    vec2 uv = fragCoord / iResolution.xy;\n"
    "    vec3 col = 0.5 + 0.5 * cos(iTime + uv.xyx + vec3(0, 2, 4));\n"
    "    fragColor = vec4(col,1.0);\n"
    "}\n";

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexBackgroundShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        logs("ERROR : SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
        return 0;
    } else {
        logs("INFO : VERTEX Shader created");
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentBackgroundShaderSource, NULL);
        glCompileShader(fragmentShader);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            logs("ERROR : SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
            return 0;
        } else {
            logs("INFO : FRAGMENT Shader created");
            unsigned int programID = glCreateProgram();
            glAttachShader(programID, vertexShader);
            glAttachShader(programID, fragmentShader);
            glLinkProgram(programID);
            checkCompileErrors(programID);
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            return programID;
        }
    }
}

void useShader(unsigned int programID)
{
    glUseProgram(programID);
}

int loadShaderFromFile(const char* fileName, int shaderType)
{
	FILE* shaderSource = fopen(fileName, "rb");
	if (shaderSource != NULL)
    {
        fseek(shaderSource, 0, SEEK_END);
        size_t TOTAL_SIZE = ftell(shaderSource);
        rewind(shaderSource);

        char* shader = (char*)malloc(TOTAL_SIZE + 1);
        if(fread(shader, 1, TOTAL_SIZE, shaderSource) <= 0)
        {
            logs("ERROR : Unable to fread shader");
        }
        shader[TOTAL_SIZE] = 0;
        fclose(shaderSource);

        GLuint shaderID = 0;
        shaderID = glCreateShader(shaderType);
        glShaderSource(shaderID, 1, (const char**)&shader, NULL);
        glCompileShader(shaderID);

        GLint fragment_compiled;
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &fragment_compiled);
        if (fragment_compiled != GL_TRUE)
        {
            GLsizei logLength;
            GLchar  log[1024];
            glGetShaderInfoLog(shaderID, sizeof(log), &logLength, log);
            logs("ERROR: %s -->   %s", fileName, log);

        } else {
            free(shader);
            return shaderID;
        }
	} else {
		logs("ERROR : Unable to open shader file : %s", fileName);
	}
    return -1;
}

void checkCompileErrors(unsigned int shader)
{
    int success;
    char infoLog[1024];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
        logs("ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n%s\n"
               " -- --------------------------------------------------- -- ", infoLog);
    }
}

void ShaderCleanUp(unsigned int programID)
{
    glDeleteProgram(programID);
}

