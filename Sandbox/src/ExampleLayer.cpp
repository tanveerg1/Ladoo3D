#include "ExampleLayer.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>

ExampleLayer::ExampleLayer() 
	: Layer("Example"), m_CameraController(1280.0f / 720.0f)
{
	m_VertexArray = Ladoo::VertexArray::Create();

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	Ladoo::Ref<Ladoo::VertexBuffer> m_VertexBuffer;
	m_VertexBuffer = Ladoo::VertexBuffer::Create(vertices, sizeof(vertices));

	Ladoo::BufferLayout layout = {
	{ Ladoo::ShaderDataType::Float3, "a_Position"},
	{ Ladoo::ShaderDataType::Float4, "a_Colour"},
	};

	m_VertexBuffer->SetLayout(layout);

	m_VertexArray->AddVertexBuffer(m_VertexBuffer);

	uint32_t indices[3] = { 0, 1, 2 };
	Ladoo::Ref<Ladoo::IndexBuffer> m_IndexBuffer;
	m_IndexBuffer = Ladoo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));

	m_VertexArray->AddIndexBuffer(m_IndexBuffer);

	sq_VertexArray = Ladoo::VertexArray::Create();
	float sqVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
	};
	Ladoo::Ref<Ladoo::VertexBuffer> squareVB;
	squareVB = Ladoo::VertexBuffer::Create(sqVertices, sizeof(sqVertices));
	squareVB->SetLayout({
		{ Ladoo::ShaderDataType::Float3, "a_Position"},
		{ Ladoo::ShaderDataType::Float2, "a_TextureCoord"},
		});
	sq_VertexArray->AddVertexBuffer(squareVB);

	uint32_t sq_Indices[6] = { 0, 1, 2, 2, 3, 0 };
	Ladoo::Ref<Ladoo::IndexBuffer> squareIB;
	squareIB = Ladoo::IndexBuffer::Create(sq_Indices, sizeof(sq_Indices) / sizeof(uint32_t));

	sq_VertexArray->AddIndexBuffer(squareIB);

	std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;
			
			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Colour;			

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";

	std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 f_Colour;

			in vec3 v_Position;
			in vec4 v_Colour;

			void main()
			{
				f_Colour = vec4(v_Position * 0.5 + 0.5, 1.0);
				f_Colour = v_Colour;
			}
		)";

	m_Shader = (Ladoo::Shader::Create("VertexColourTriangle", vertexSrc, fragmentSrc));

	std::string flatColourVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;			
			uniform mat4 u_Transform;			

			out vec3 v_Position;		

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		
		)";

	std::string flatColourFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 f_Colour;

			in vec3 v_Position;

			uniform vec3 u_Colour;

			void main()
			{
				f_Colour = vec4(u_Colour, 1.0);
			}
		)";

	flatColour_Shader = (Ladoo::Shader::Create("FlatColourShader", flatColourVertexSrc, flatColourFragmentSrc));

	auto texture_Shader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

	m_Texture = Ladoo::Texture2D::Create("assets/textures/Checkerboard.png");
	m_TestTexture = Ladoo::Texture2D::Create("assets/textures/ChernoLogo.png");

	texture_Shader->Bind();
	texture_Shader->SetInt("u_Texture", 0);
}

void ExampleLayer::OnUpdate(Ladoo::TimeStep timeStep)
{
	// Update
	m_CameraController.OnUpdate(timeStep);

	// Render
	Ladoo::RendererCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
	Ladoo::RendererCommand::Clear();

	Ladoo::Renderer::BeginScene(m_CameraController.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	flatColour_Shader->Bind();
	flatColour_Shader->SetFloat3("u_Colour", m_SquareColour);

	// old code deleted the others kept this as a sample
	//std::dynamic_pointer_cast<Ladoo::OpenGLShader>(flatColour_Shader)->UploadUniformFloat3("u_Colour", m_SquareColour);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			Ladoo::Renderer::Submit(flatColour_Shader, sq_VertexArray, transform);
		}
	}
	auto texture_Shader = m_ShaderLibrary.Get("Texture");

	m_Texture->Bind();
	Ladoo::Renderer::Submit(texture_Shader, sq_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	m_TestTexture->Bind();
	Ladoo::Renderer::Submit(texture_Shader, sq_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	//Triangle
	//Ladoo::Renderer::Submit(m_Shader, m_VertexArray);

	Ladoo::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColour));

	ImGui::End();
}

void ExampleLayer::OnEvent(Ladoo::Event& event)
{
	m_CameraController.OnEvent(event);
}


