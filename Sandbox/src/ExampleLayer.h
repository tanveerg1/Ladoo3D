#pragma once

#include <Ladoo.h>

class ExampleLayer : public Ladoo::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	void OnUpdate(Ladoo::TimeStep timeStep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ladoo::Event& event) override;

private:
	Ladoo::ShaderLibrary m_ShaderLibrary;
	Ladoo::Ref<Ladoo::Shader> m_Shader;
	Ladoo::Ref<Ladoo::VertexArray> m_VertexArray;

	Ladoo::Ref<Ladoo::Shader> flatColour_Shader;
	Ladoo::Ref<Ladoo::VertexArray> sq_VertexArray;

	Ladoo::Ref<Ladoo::Texture2D> m_Texture, m_TestTexture;

	Ladoo::OrthoCameraController m_CameraController;

	glm::vec3 m_SquareColour = { 0.2f, 0.3f, 0.8f };
};
