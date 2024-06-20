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
    using namespace GLEngine;
//    enum RenderCommand
//    {
//        DRAW_ELEMENTS,
//        DRAW_INDICES,
//        CLEAR,
//    };

    class RenderCommand
    {
    public:
        virtual void execute() = 0;
    };

    class RenderQueue
    {
      public:
        void Submit(RenderCommand *command);
        void Clear();

      private:
        std::vector<RenderCommand *> commandQueue;
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
