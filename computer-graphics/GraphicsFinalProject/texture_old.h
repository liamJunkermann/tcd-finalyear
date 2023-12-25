#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include"shaderClass.h"

class TextureOld {
public:
	GLuint ID;
	const char* type;
	TextureOld(const char* image, const char* texType, GLenum slot);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();
};

#endif // !TEXTURE_CLASS_H
