#include "ldpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Ladoo {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetCurrentAPI())
		{
		case RendererAPI::API::None:
			LD_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL:

			return std::make_shared<OpenGLTexture2D>(path);
		}

		LD_CORE_ASSERT(false, "Unknown RendererAPI");
		return nullptr;
		//return Ref<Texture2D>();
	}
}