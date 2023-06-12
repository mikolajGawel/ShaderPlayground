#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include "Framebuffer.hpp"

class ShaderPlayground
{
	int m_width, m_height;
	GLFWwindow* m_window;
	Framebuffer m_framebuffer;
	Shader* m_currentShader = new Shader("","");
	float m_previewX = 0, m_previewY = 0;
	std::string m_shaderEditorCode;
	size_t m_codeSizeFactor = 1;
public:
	ShaderPlayground(int width, int height);
	~ShaderPlayground();
	void init();
	void run();

	void refresh();

	void pre_render();
	void renderPreview();
	void renderShaderEditor();
	void renderMenubar();
	void post_render();
	void update();
};