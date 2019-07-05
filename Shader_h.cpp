#include "Shader_h.h"

Shader::Shader(const char * vShaderCode, const char* fShaderCode) {
	//
	/*std::string vertexCode;
	std::string fragmenrCode;
	std::ifstream vShadeFile;
	std::ifstream fShadeFile;
	vShadeFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	fShadeFile.exceptions(std::ifstream::badbit | std::ifstream::failbit);
	try
	{
		vShadeFile.open(vertexFilePath);
		fShadeFile.open(fragmentFilePath);
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShadeFile.rdbuf;
		fShaderStream << fShadeFile.rdbuf;
		vShadeFile.close;
		fShadeFile.close;
		vertexCode = vShaderStream.str;
		fragmenrCode = fShaderStream.str;
	}
	catch(std::ifstream::failure e)
{
		std::cout << "ERROR:SHADER :: FILE_NOT_SUCCESSFULLY_LOAD" << std::endl;
}
	const char* vShadercode = vertexCode.c_str();
	const char* fShadercode = fragmenrCode.c_str();*/

	unsigned int vertexShader, fragShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glShaderSource(fragShader, 1, &fShaderCode, NULL);
	glCompileShader(fragShader);
	checkCompileError(fragShader, "Fragment");
	glCompileShader(vertexShader);
	checkCompileError(vertexShader, "Vertex");

	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	glLinkProgram(ID);
	checkCompileError(ID, "Program");
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader :: setBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader :: setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader :: setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}


void Shader :: checkCompileError(unsigned int shaderId, std::string type) {
	int success;
	char infolog[512];
	if (type == "Program")
	{
		glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderId, 512, NULL, infolog);
			std::cout << "ERROR :: PROGRAM_LINKING_ERROR OF TYPE: " << type << infolog
				<< "\n--------" << std::endl;
		}
	}
	else
	{
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shaderId, 512, NULL, infolog);
			std::cout << "ERROR:: COMPILATION_ERROR OF TYPE:" << type << infolog <<
				"\n-------------" << std::endl;
		}
	}
}