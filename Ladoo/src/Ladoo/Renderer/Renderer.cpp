#include "ldpch.h"
#include "Renderer.h"

namespace Ladoo {

	Renderer::SceneData* Renderer::c_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		c_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", c_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RendererCommand::DrawElements(vertexArray);
	}
}