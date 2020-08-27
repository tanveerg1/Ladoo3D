#pragma once

#include "Ladoo.h"

class Ladoo2D : public Ladoo::Layer
{
public:
	Ladoo2D();
	virtual ~Ladoo2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Ladoo::TimeStep timeStep) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Ladoo::Event& event) override;
private:
	Ladoo::OrthoCameraController m_CameraController;

	//Temp code
	Ladoo::Ref<Ladoo::Shader> flatColour_Shader;
	Ladoo::Ref<Ladoo::VertexArray> sq_VertexArray;

	Ladoo::Ref<Ladoo::Texture2D> m_Texture;

	glm::vec4 m_SquareColour = { 0.2f, 0.3f, 0.8f, 1.0f };
};