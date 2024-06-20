#include <Renderer.h>

namespace GLRenderer
{
    void RenderQueue::Submit(GLRenderer::RenderCommand *command)
    {
        commandQueue.push_back(command);
    }

    void Renderer::Draw()
    {
        
    }

    void Renderer::PrepareShader()
    {
      
    }

    void Renderer::Init()
    {
    }

} // namespace GLRenderer
