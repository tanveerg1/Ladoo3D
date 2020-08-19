#include <Ladoo.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public Ladoo::Layer 
{
public:
	ExampleLayer() 
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Ladoo::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
		};

		Ladoo::Ref<Ladoo::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Ladoo::VertexBuffer::Create(vertices, sizeof(vertices)));

		Ladoo::BufferLayout layout = {
		{ Ladoo::ShaderDataType::Float3, "a_Position"},
		{ Ladoo::ShaderDataType::Float4, "a_Colour"},
		};

		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Ladoo::Ref<Ladoo::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Ladoo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		sq_VertexArray.reset(Ladoo::VertexArray::Create());
		float sqVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};
		Ladoo::Ref<Ladoo::VertexBuffer> squareVB;
		squareVB.reset(Ladoo::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		squareVB->SetLayout({
			{ Ladoo::ShaderDataType::Float3, "a_Position"},
			{ Ladoo::ShaderDataType::Float2, "a_TextureCoord"},
			});
		sq_VertexArray->AddVertexBuffer(squareVB);

		uint32_t sq_Indices[6] = { 0, 1, 2, 2, 3, 0 };
		Ladoo::Ref<Ladoo::IndexBuffer> squareIB;
		squareIB.reset(Ladoo::IndexBuffer::Create(sq_Indices, sizeof(sq_Indices) / sizeof(uint32_t)));

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

		m_Texture = (Ladoo::Texture2D::Create("assets/textures/Checkerboard.png"));
		m_TestTexture = (Ladoo::Texture2D::Create("assets/textures/ChernoLogo.png"));

		std::dynamic_pointer_cast<Ladoo::OpenGLShader>(texture_Shader)->Bind();
		std::dynamic_pointer_cast<Ladoo::OpenGLShader>(texture_Shader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Ladoo::TimeStep timeStep) override
	{
		if (Ladoo::Input::IsKeyPressed(LD_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed * timeStep;
		}
		else if (Ladoo::Input::IsKeyPressed(LD_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed * timeStep;
		}

		if (Ladoo::Input::IsKeyPressed(LD_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed * timeStep;
		}
		else if (Ladoo::Input::IsKeyPressed(LD_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed * timeStep;
		}

		if (Ladoo::Input::IsKeyPressed(LD_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed * timeStep;
		}
		if (Ladoo::Input::IsKeyPressed(LD_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed * timeStep;
		}

		Ladoo::RendererCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Ladoo::RendererCommand::Clear();

		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Ladoo::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Ladoo::OpenGLShader>(flatColour_Shader)->Bind();
		std::dynamic_pointer_cast<Ladoo::OpenGLShader>(flatColour_Shader)->UploadUniformFloat3("u_Colour", m_SquareColour);

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

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		
		ImGui::ColorEdit3("Square Colour", glm::value_ptr(m_SquareColour));

		ImGui::End();
	}

	void OnEvent(Ladoo::Event& event) override
	{
	}

private:
	Ladoo::ShaderLibrary m_ShaderLibrary;
	Ladoo::Ref<Ladoo::Shader> m_Shader;
	Ladoo::Ref<Ladoo::VertexArray> m_VertexArray;

	Ladoo::Ref<Ladoo::Shader> flatColour_Shader;
	Ladoo::Ref<Ladoo::VertexArray> sq_VertexArray;

	Ladoo::Ref<Ladoo::Texture2D> m_Texture, m_TestTexture;

	Ladoo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;

	float m_CameraSpeed = 5.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_SquareColour = { 0.2f, 0.3f, 0.8f };
};


class Sandbox : public Ladoo::Application
{
public: 
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Ladoo::Application* Ladoo::CreateApplication()
{
	return new Sandbox();
}