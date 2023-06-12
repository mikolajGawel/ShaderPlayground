#include "ShaderPlayground.hpp"
#include "Quad.hpp"
#include <iostream>

#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>


ShaderPlayground::ShaderPlayground(int width,int height):
	m_width(width),m_height(height)
{m_window = NULL;}
void ShaderPlayground::init()
{
	if (!glfwInit()) { std::cout << "GLFW can't be initialized\n"; return; }
	m_window = glfwCreateWindow(m_width, m_height, "Shader Playground", NULL, NULL);
	if (!glfwInit()) { std::cout << "Window can't be created\n"; return; }

	glfwSwapInterval(1);
	glfwMakeContextCurrent(m_window);
	if(glewInit() != GLEW_OK)
	{
		std::cout << "OpenGL can't be initialied\n";
	}

	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	m_framebuffer.createFramebuffer();

	const std::string test_vertex =
		"#version 330 core						  \n"
		"layout(location = 0) in vec2 aPos;		  \n"
		"layout(location = 1) in vec2 aTex;		  \n"
		"out vec2 UV;					  \n"
		"void main()							  \n"
		"{										  \n"
		"	UV = aTex;					  \n"
		"	gl_Position = vec4(aPos.xy, 0.0, 1.0);\n"
		"}										  ";
	const std::string test_fragment =
		"#version 330 core\n"
		"out vec4 FragOut;\n"
		"in vec2 UV;\n"
		"void main()\n"
		"{\n"
		"	FragOut = vec4(1.0,1.0,1.0,1.0);\n"
		"}\n";


	
	m_currentShader = new Shader(test_vertex, test_fragment);
	m_currentShader->createShader();
	m_shaderEditorCode = test_fragment;
	m_shaderEditorCode.reserve(1024*8);
	Quad::Init();

}
ShaderPlayground::~ShaderPlayground()
{
	Quad::Destroy();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
void ShaderPlayground::run()
{
	init();
	while(!glfwWindowShouldClose(m_window))
	{
		glfwPollEvents();
		update();

		pre_render();

		renderShaderEditor();
		renderPreview();
		renderMenubar();

		post_render();
	}
}
void ShaderPlayground::refresh()
{
	std::cout << "Refresh\n";
	m_currentShader->~Shader();
	delete(m_currentShader);
	const std::string test_vertex =
		"#version 330 core						  \n"
		"layout(location = 0) in vec2 aPos;		  \n"
		"layout(location = 1) in vec2 aTex;		  \n"
		"out vec2 UV;					  \n"
		"void main()							  \n"
		"{										  \n"
		"	UV = aTex;					  \n"
		"	gl_Position = vec4(aPos.xy, 0.0, 1.0);\n"
		"}";
	m_currentShader = new Shader(test_vertex, m_shaderEditorCode);
	m_currentShader->createShader();
}
/*p_refreshedBefore is created to prevent multiple refreshes when refresh key is pressed once */
static bool p_refreshedBefore = false;
void ShaderPlayground::update()
{
	if (glfwGetKey(m_window, GLFW_KEY_F5) && !p_refreshedBefore)
	{
		refresh();
		p_refreshedBefore = true;
	}
	else if(!glfwGetKey(m_window, GLFW_KEY_F5))p_refreshedBefore = false;
}
void ShaderPlayground::pre_render()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
}

void ShaderPlayground::renderShaderEditor()
{
	ImGui::Begin("Shader Editor");
	ImVec2 size =
	{ ImGui::GetWindowContentRegionMax().x - ImGui::GetWindowContentRegionMin().x,
	  ImGui::GetWindowContentRegionMax().y - ImGui::GetWindowContentRegionMin().y };
	ImGui::SetWindowFontScale(1.0);
	char* shc = (char*)m_shaderEditorCode.c_str();
	
	ImGui::InputTextMultiline("Code Editor", shc, m_shaderEditorCode.capacity() + 1, size);
	m_shaderEditorCode = shc;
	ImGui::End();
	
}
void ShaderPlayground::renderPreview()
{
	m_framebuffer.bindFramebuffer(GL_FRAMEBUFFER);
	glClear(GL_COLOR_BUFFER_BIT);
	m_currentShader->bind();
	glViewport(0, 0, m_previewX, m_previewY);
	Quad::Render();
	m_currentShader->unbind();
	m_framebuffer.unbindFramebuffer();
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui::Begin("Preview");
	{
		ImGui::BeginChild("Renderer");
		ImVec2 wsize = ImGui::GetWindowSize();
		if((wsize.x != m_previewX || wsize.y != m_previewY )&&  !ImGui::IsMouseDown(0))
		{	
			m_framebuffer.setSize(wsize.x, wsize.y);
			m_previewX = wsize.x;
			m_previewY = wsize.y;
		}

		ImGui::Image((ImTextureID)m_framebuffer.getTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
		ImGui::End();
	}
}
void ShaderPlayground::renderMenubar()
{
	ImGui::BeginMainMenuBar();
	if (ImGui::MenuItem("Refresh[F5]")) { refresh(); }
	ImGui::EndMainMenuBar();
}
void ShaderPlayground::post_render()
{ 
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_window);
}