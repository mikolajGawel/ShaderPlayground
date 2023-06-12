#include "Framebuffer.hpp"

Framebuffer::Framebuffer(){
	//m_shader(std::make_shared<Shader>(framebuffer_vertex,framebuffer_fragment)){
	clear();
}
void Framebuffer::clear()
{
	m_ID = 0;
	m_RBO = 0;
	m_width = 0;
	m_height = 0;
	m_textureID = 0;
	s_created = false;
}
Framebuffer::~Framebuffer()
{
	glDeleteTextures(1, &m_textureID);
	glDeleteRenderbuffers(1, &m_RBO);
	glDeleteFramebuffers(1, &m_ID);
}
void Framebuffer::createFramebuffer()
{
	glDeleteFramebuffers(1, &m_ID);
	glDeleteRenderbuffers(1, &m_RBO);
	glDeleteTextures(1, &m_textureID);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glGenFramebuffers(1, &m_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);

	glGenRenderbuffers(1, &m_RBO);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

	s_created = true;
}
void Framebuffer::bindFramebuffer(int type)
{
	if (!s_created)createFramebuffer();
	glBindFramebuffer(type, m_ID);
}
void Framebuffer::unbindFramebuffer(int type)
{
	glBindFramebuffer(type, 0);
}
void Framebuffer::bindTexture()
{
	if (!s_created)createFramebuffer();
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
void Framebuffer::setSize(int _width, int _height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

	m_width = _width;
	m_height = _height;

	createFramebuffer();
}