#pragma once
#include "GL/glew.h"
#include "Shader.hpp"
#include "Quad.hpp"
#include "Shader.hpp"
class Framebuffer
{
private:
	unsigned int m_vbo, s_vao;
	void clear();
protected:
	bool s_created;
	int m_width, m_height;
	unsigned int m_ID, m_RBO, m_textureID;
public:
	const GLuint& getTexture() { return m_textureID; }
	Framebuffer();
	~Framebuffer();
	virtual void createFramebuffer();
	virtual void bindTexture();
	void bindFramebuffer(int type = GL_FRAMEBUFFER);
	void unbindFramebuffer(int type = GL_FRAMEBUFFER);
	void setSize(int _width, int _height);
};


