#include "ShaderPlayground.hpp"
#include <memory>
int main(int* argc,char* argv[])
{
	std::unique_ptr<ShaderPlayground> shader_playground =
		std::make_unique<ShaderPlayground>(1280, 720);
	shader_playground->run();
}