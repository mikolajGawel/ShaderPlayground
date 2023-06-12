#include "Buffer.hpp"
#include <GL/glew.h>
Buffer::Buffer(int type,bool dynamic)
{
	this->m_ID = 0;
	this->type = type;
	this->dynamic = dynamic;
}
Buffer::~Buffer()
{
	glDeleteBuffers(1, &m_ID);
}
void Buffer::storeData(void *data,size_t size)
{
	if (!s_created) { glGenBuffers(1, &m_ID); s_created = true; }
	bindBuffer();
	glBufferData(type, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(type, 0);
}
void Buffer::bindBuffer()
{
	glBindBuffer(type, m_ID);
}