#include "ldpch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ladoo {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	Scope<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateScope<OpenGLRendererAPI>();
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

}