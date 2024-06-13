#include <GLCamera.h>

namespace GLEngine
{

    Camera::Camera(glm::mat4 view)
    {
        m_view = view;
        // set a 16:9 aspect ration 45 degree FOV camera;
        m_projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);
    }

    Camera::Camera(glm::mat4 projection, glm::mat4 view)
    {
        m_projection = projection;
        m_view = view;
    }

    const glm::mat4 &Camera::getProjection()
    {
        return m_projection;
    }

    const glm::mat4 &Camera::getView()
    {
        return m_view;
    }

    void Camera::setView(glm::mat4 &view)
    {
        m_view = view;
    }

    void Camera::setProjection(glm::mat4 &projection)
    {
        m_projection = projection;
    }

} // namespace GLEngine
