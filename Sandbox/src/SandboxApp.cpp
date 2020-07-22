#include <Ladoo.h>

#include <imgui/imgui.h>

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

		std::shared_ptr<Ladoo::VertexBuffer> m_VertexBuffer;
		m_VertexBuffer.reset(Ladoo::VertexBuffer::Create(vertices, sizeof(vertices)));

		Ladoo::BufferLayout layout = {
		{ Ladoo::ShaderDataType::Float3, "a_Position"},
		{ Ladoo::ShaderDataType::Float4, "a_Colour"},
		};

		m_VertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Ladoo::IndexBuffer> m_IndexBuffer;
		m_IndexBuffer.reset(Ladoo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddIndexBuffer(m_IndexBuffer);

		sq_VertexArray.reset(Ladoo::VertexArray::Create());
		float sqVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};
		std::shared_ptr<Ladoo::VertexBuffer> squareVB;
		squareVB.reset(Ladoo::VertexBuffer::Create(sqVertices, sizeof(sqVertices)));
		squareVB->SetLayout({
			{ Ladoo::ShaderDataType::Float3, "a_Position"},
			});
		sq_VertexArray->AddVertexBuffer(squareVB);

		uint32_t sq_Indices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Ladoo::IndexBuffer> squareIB;
		squareIB.reset(Ladoo::IndexBuffer::Create(sq_Indices, sizeof(sq_Indices) / sizeof(uint32_t)));

		sq_VertexArray->AddIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Colour;
			
			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Colour;			

			void main()
			{
				v_Position = a_Position;
				v_Colour = a_Colour;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(Ladoo::Shader::Create(vertexSrc, fragmentSrc));

		std::string blueVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;			

			out vec3 v_Position;		

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		
		)";

		std::string blueFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 f_Colour;

			in vec3 v_Position;

			void main()
			{
				f_Colour = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		blue_Shader.reset(Ladoo::Shader::Create(blueVertexSrc, blueFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Ladoo::Input::IsKeyPressed(LD_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraSpeed;
		}
		else if (Ladoo::Input::IsKeyPressed(LD_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraSpeed;
		}

		if (Ladoo::Input::IsKeyPressed(LD_KEY_UP))
		{
			m_CameraPosition.y += m_CameraSpeed;
		}
		else if (Ladoo::Input::IsKeyPressed(LD_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraSpeed;
		}

		if (Ladoo::Input::IsKeyPressed(LD_KEY_A))
		{
			m_CameraRotation += m_CameraRotationSpeed;
		}
		if (Ladoo::Input::IsKeyPressed(LD_KEY_D))
		{
			m_CameraRotation -= m_CameraRotationSpeed;
		}

		Ladoo::RendererCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
		Ladoo::RendererCommand::Clear();

		m_Camera.SetPostion(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Ladoo::Renderer::BeginScene(m_Camera);

		Ladoo::Renderer::Submit(blue_Shader, sq_VertexArray);
		Ladoo::Renderer::Submit(m_Shader, m_VertexArray);

		Ladoo::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}

	void OnEvent(Ladoo::Event& event) override
	{
	}

private:
	std::shared_ptr<Ladoo::Shader> m_Shader;
	std::shared_ptr<Ladoo::VertexArray> m_VertexArray;

	std::shared_ptr<Ladoo::Shader> blue_Shader;
	std::shared_ptr<Ladoo::VertexArray> sq_VertexArray;

	Ladoo::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraSpeed = 0.1f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
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