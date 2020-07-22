#include "ldpch.h"
#include "RendererAPI.h"

namespace Ladoo {

	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	void RendererAPI::SetClearColour(const glm::vec4& colour)
	{
	}

	void RendererAPI::Clear()
	{
	}

	void RendererAPI::DrawElements(const std::shared_ptr<VertexArray>& vertexArray)
	{
	}
}