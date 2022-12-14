
#include "ogl.h"
#include "logging.h"

unsigned int shaderTextureProgramID;
unsigned int shaderMainProgramID;
unsigned int shaderNodeProgramID;

unsigned int getTextureShaderProgramID()
{
    return shaderTextureProgramID;
}

unsigned int getMainShaderProgramID()
{
    return shaderMainProgramID;
}

unsigned int getNodeShaderProgramID()
{
    return shaderNodeProgramID;
}

void installShaders()
{
    // This shader is needed to cover the whole screen
    const char *vertexMainShaderSource = "#version 450 core\n"
    "const vec2 quadVertices[4] = {\n"
    "   vec2(-1.0, -1.0),\n"
    "   vec2(1.0, -1.0),\n"
    "   vec2(-1.0, 1.0),\n"
    "   vec2(1.0, 1.0) };\n"
    "const vec2 textureCoords[4] = {\n"
    "   vec2(0.0, 0.0),\n"
    "   vec2(1.0, 0.0),\n"
    "   vec2(0.0, 1.0),\n"
    "   vec2(1.0, 1.0) };\n"
    "out vec2 texCoords;\n"
    "void main()\n"
    "{\n"
    "    int ID = gl_VertexID;\n"
    "    texCoords = textureCoords[ID];\n"
    "    gl_Position = vec4(quadVertices[ID], 0.0, 1.0);\n"
    "}\n";

    const char *fragmentMainShaderSource = "#version 450 core\n"
    "in vec2 texCoords;\n"
    "out vec4 fragColor;\n"
    "uniform vec4 Color;\n"
    "uniform sampler2D mainTexture;\n"
    "void main()\n"
    "{\n"
    "    fragColor = texture(mainTexture, texCoords) * Color;\n"
    "}\n";

    const char *vertexTextureShaderSource = "#version 450 core\n"
    "const vec2 quadVertices[4] = {\n"
    "   vec2(-1.0, -1.0),\n"
    "   vec2(1.0, -1.0),\n"
    "   vec2(-1.0, 1.0),\n"
    "   vec2(1.0, 1.0) };\n"
    "const vec2 textureCoords[4] = {\n"
    "   vec2(0.0, 0.0),\n"
    "   vec2(1.0, 0.0),\n"
    "   vec2(0.0, 1.0),\n"
    "   vec2(1.0, 1.0) };\n"
    "out vec2 texCoords;\n"
    "void main()\n"
    "{\n"
    "    int ID = gl_VertexID;\n"
    "    texCoords = textureCoords[ID];\n"
    "    gl_Position = vec4(quadVertices[ID], 0.0, 1.0);\n"
    "}\n";

    const char *fragmentTextureShaderSource = "#version 450 core\n"
    "in vec2 texCoords;\n"
    "out vec4 fragColor;\n"
    "uniform vec4 texColor;\n"
    "uniform sampler2D texTexture;\n"
    "void main()\n"
    "{\n"
    "    fragColor = texture(texTexture, texCoords) * texColor;\n"
    "}\n";

    const char *vertexNodeShaderSource = "#version 450 core\n"
    "const vec2 quadVertices[4] = {\n"
    "   vec2(-0.5, -0.5),\n"
    "   vec2(0.5, -0.5),\n"
    "   vec2(-0.5, 0.5),\n"
    "   vec2(0.5, 0.5) };\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);\n"
    "}\n";

    const char *fragmentNodeShaderSource = "#version 450 core\n"
    "#define fragCoord gl_FragCoord.xy\n"
    "out vec4 fragColor;\n"
    "uniform vec4 iNodeRect;\n"
    "float roundedBoxSDF(vec2 CenterPosition, vec2 Size, vec4 Radius) {\n"
    "    Radius.xy = (CenterPosition.x > 0.0) ? Radius.xy : Radius.zw;\n"
    "    Radius.x  = (CenterPosition.y > 0.0) ? Radius.x  : Radius.y;\n"
    "    vec2 q = abs(CenterPosition) - Size + Radius.x;\n"
    "    return min(max(q.x, q.y), 0.0) + length(max(q, 0.0)) - Radius.x;\n"
    "}\n"
    "void main()\n"
    "{\n"
    "    vec2 location = iNodeRect.xy;\n"
    "    vec2 wh = iNodeRect.zw;\n"
    "    float edgeSoftness  = 2.0f;\n"
    "    vec4 radius = vec4(10.0f, 0.0f, 10.0f, 0.0f);\n"
    "    float distance = roundedBoxSDF(fragCoord.xy - location, wh, radius);\n"
    "    float smoothedAlpha =  1.0f - smoothstep(0.0f, edgeSoftness,distance);\n"
    "    // Border.\n"
    "    float borderThickness = 0.9f;\n"
    "    float borderSoftness  = 1.0f;\n"
    "    float borderAlpha     = 1.0f - smoothstep(borderThickness - borderSoftness, borderThickness, abs(distance));\n"
    "    // Colors\n"
    "    vec4 rectColor = vec4(0.2f, 0.2f, 0.2f, 1.0f);\n"
    "    vec4 borderColor = vec4(0.8f, 0.6f, 0.1f, 1.0f);\n"
    "    vec4 bgColor = vec4(0.1f, 0.1f, 0.1f, 0.0f);\n"
    "    fragColor = mix(bgColor, mix(rectColor, borderColor, borderAlpha), smoothedAlpha);\n"
    "}\n";

    shaderMainProgramID    = initShaders(vertexMainShaderSource, fragmentMainShaderSource);
    shaderTextureProgramID = initShaders(vertexTextureShaderSource, fragmentTextureShaderSource);
    shaderNodeProgramID = initShaders(vertexNodeShaderSource, fragmentNodeShaderSource);
}

unsigned int initShaders(const char* vert, const char* frag)
{
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vert, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        logging("ERROR : SHADER::VERTEX::COMPILATION_FAILED\n%s\n", infoLog);
        return 0;
    } else {
        logging("INFO : VERTEX Shader created");
        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &frag, NULL);
        glCompileShader(fragmentShader);
        if (!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            logging("ERROR : SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n", infoLog);
            return 0;
        } else {
            logging("INFO : FRAGMENT Shader created");
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

void useTextureShader()
{
    glUseProgram(shaderTextureProgramID);
}

void useMainShader()
{
    glUseProgram(shaderMainProgramID);
}

void useNodeShader()
{
    glUseProgram(shaderNodeProgramID);
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
            logging("ERROR : Unable to fread shader");
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
            logging("ERROR: %s -->   %s", fileName, log);

        } else {
            free(shader);
            return shaderID;
        }
	} else {
		logging("ERROR : Unable to open shader file : %s", fileName);
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
        logging("ERROR::PROGRAM_LINKING_ERROR of type: PROGRAM\n%s\n"
               " -- --------------------------------------------------- -- ", infoLog);
    }
}

void shaderCleanUp()
{
    if(shaderTextureProgramID){glDeleteProgram(shaderTextureProgramID); logging("INFO : Texture Shader cleaned up successfully.");}
    if(shaderMainProgramID){glDeleteProgram(shaderMainProgramID); logging("INFO : Main Shader cleaned up successfully.");}
    if(shaderNodeProgramID){glDeleteProgram(shaderNodeProgramID); logging("INFO : Node Shader cleaned up successfully.");}
}

