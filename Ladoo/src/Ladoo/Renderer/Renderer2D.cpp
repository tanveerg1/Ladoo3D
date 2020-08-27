#include "ldpch.h"
#include "Renderer2D.h"

#include "VertexArray.h"
#include "Shader.h"
#include "RendererCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ladoo {

	struct Render2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Render2DData* data;

	void Renderer2D::Init()
	{
		data = new Render2DData();

		data->QuadVertexArray = VertexArray::Create();

		float sqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};
		Ref<VertexBuffer> squareVB = VertexBuffer::Create(sqVertices, sizeof(sqVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float2, "a_TextureCoord"}
			});
		data->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t sq_Indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB = IndexBuffer::Create(sq_Indices, sizeof(sq_Indices) / sizeof(uint32_t));

		data->QuadVertexArray->AddIndexBuffer(squareIB);

		data->WhiteTexture = Texture2D::Create(1,1);
		uint32_t white_texture_data = 0xffffffff;
		data->WhiteTexture->SetData(&white_texture_data, sizeof(uint32_t));

		data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		data->TextureShader->Bind();
		data->TextureShader->SetInt("u_texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete data;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		data->TextureShader->Bind();
		data->TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& colour)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, colour);
		//std::dynamic_pointer_cast<OpenGLShader>(data->FlatColourShader)->Bind();
		//std::dynamic_pointer_cast<OpenGLShader>(data->FlatColourShader)->UploadUniformFloat4("u_Colour", colour);

		//data->QuadVertexArray->Bind();
		//RendererCommand::DrawElements(data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& colour)
	{
		data->TextureShader->SetFloat4("u_Colour", colour);
		data->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * /*glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(0, 0, 1)) **/ glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data->TextureShader->SetMat4("u_Transform", transform);

		data->QuadVertexArray->Bind();
		RendererCommand::DrawElements(data->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		data->TextureShader->SetFloat4("u_Colour", glm::vec4(1.0f)); // For tinting add { 0.2f, 0.3f, 0.8f, 0.5f } and remove glm::vec4(1.0f)
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data->TextureShader->SetMat4("u_Transform", transform);

		data->QuadVertexArray->Bind();
		RendererCommand::DrawElements(data->QuadVertexArray);
	}
}