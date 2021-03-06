#include "ldpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ladoo {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateRef<OpenGLVertexArray>();
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}