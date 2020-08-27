#include "ldpch.h"
#include "RendererContext.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Ladoo {
	Scope<RendererContext> RendererContext::Create(void* window)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}