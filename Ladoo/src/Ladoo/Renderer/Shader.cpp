#include "ldpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Ladoo {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}