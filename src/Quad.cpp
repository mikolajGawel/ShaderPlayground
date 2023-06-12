#include "Quad.hpp"
unsigned int Quad::s_vao;
Buffer Quad::s_VBO = Buffer(GL_ARRAY_BUFFER, false), Quad::s_IBO = Buffer(GL_ELEMENT_ARRAY_BUFFER, false);
bool Quad::s_created = false;
void Quad::Init()
{
	if (s_created)return;
	glGenVertexArrays(1, &s_vao);
	glBindVertexArray(s_vao);
	
	float vertices[16] = 
	{ 
		-1,-1, 0,0,
		1,-1,  1,0,
		1,1,   1,1,
		-1,1,  0,1
	};
	s_VBO.storeData(vertices, sizeof(vertices));
	s_VBO.bindBuffer();
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float)*2));

	GLuint indices[6] =
	{
		0,1,2,
		3,2,0
	};
	s_IBO.storeData(indices,sizeof(indices));
	s_created = true;
}
void Quad::Render()
{
	if (!s_created)Init();
	glBindVertexArray(s_vao);
	s_IBO.bindBuffer();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
void Quad::Destroy()
{
	glDeleteVertexArrays(1, &s_vao);
}