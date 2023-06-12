#pragma once
#include "GL/glew.h"
#include "Buffer.hpp"
class Quad
{
	static unsigned int s_vao;
	static Buffer s_VBO, s_IBO;
	static bool s_created;
public:
	static void Init();
	static void Render();
	static void Destroy();
};

