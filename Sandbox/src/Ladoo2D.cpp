#include "Ladoo2D.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Ladoo2D::Ladoo2D()
	: Layer("Ladoo2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Ladoo2D::OnAttach()
{
	m_Texture = Ladoo::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Ladoo2D::OnDetach()
{
}

void Ladoo2D::OnUpdate(Ladoo::TimeStep timeStep)
{
	// Update
	m_CameraController.OnUpdate(timeStep);

	// Render
	Ladoo::RendererCommand::SetClearColour({ 0.1f, 0.1f, 0.1f, 1 });
	Ladoo::RendererCommand::Clear();

	Ladoo::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Ladoo::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Ladoo::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColour);
	Ladoo::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_Texture);

	Ladoo::Renderer2D::EndScene();

}

void Ladoo2D::OnImGuiRender()
{
	ImGui::Begin("Settings");

	ImGui::ColorEdit4("Square Colour", glm::value_ptr(m_SquareColour));

	ImGui::End();
}

void Ladoo2D::OnEvent(Ladoo::Event& event)
{
	m_CameraController.OnEvent(event);
}
