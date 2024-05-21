#pragma once

#include <UIEngine.h>

namespace UIEngine
{
    class Transform : public UIWidget
    {
    };

    class ViewportWidget : public UIWidget
    {
      public:
        ViewportWidget(std::string);
        void Render() override;
    };

    class WSettings : public UIWidget
    {
      public:
        WSettings(std::string);
        void Render() override;
    };

    class WInfo : public UIWidget
    {
      public:
        WInfo(std::string);
        void Render() override;
    };
} // namespace UIEngine
