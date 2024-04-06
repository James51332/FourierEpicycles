#pragma once
#include "core/App.h"

#include <vector>
#include <glm/glm.hpp>

#include "renderer/Renderer2D.h"

namespace fft
{

class art : public Vision::App
{
public:
  art();
  ~art();

  void OnUpdate(float timestep);
  void OnResize();

private:
  Vision::ImGuiRenderer* uiRenderer;
  Vision::Renderer2D* renderer;
  Vision::OrthoCamera* camera;

  std::vector<glm::vec2> positions;
};

}