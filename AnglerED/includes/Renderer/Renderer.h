#pragma once

#include <pch.h>

#include <GLEngine.h>
#include <Shader.h>
#include <GLModel.h>

/*
Render command - [KEY, VALUE]
Render queue - A queue of render commands.
Renderer - Sort & execute the render commands.
*/

namespace GLRenderer
{
    enum RenderCommand
    {
        DRAW_ELEMENTS,
        DRAW_INDICES,
        CLEAR,
    };

    class RenderQueue
    {
      public:
        void Submit(RenderCommand &);

      private:
    };

    class Renderer
    {
      public:
        void Draw();
        void PrepareShader();
        void Init();

      private:
        RenderQueue queue;
    };
} // namespace GLRenderer
