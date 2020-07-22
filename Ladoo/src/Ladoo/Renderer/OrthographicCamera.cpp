#include "ldpch.h"
#include "OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ladoo {

    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : c_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), c_ViewMatrix(1.0f)
    {
        c_ViewProjectionMatrix = c_ProjectionMatrix * c_ViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), c_Position) * 
            glm::rotate(glm::mat4(1.0f), glm::radians(c_Rotation), glm::vec3(0, 0, 1));

        c_ViewMatrix = glm::inverse(transform);
        c_ViewProjectionMatrix = c_ProjectionMatrix * c_ViewMatrix;
    }
}