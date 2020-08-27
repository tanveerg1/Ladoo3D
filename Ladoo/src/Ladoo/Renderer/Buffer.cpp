#include "ldpch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Ladoo {

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size) 
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
	}
}