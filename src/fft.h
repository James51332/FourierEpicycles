#pragma once
#include "core/App.h"

#include <vector>
#include <glm/glm.hpp>

#include "renderer/Renderer2D.h"

namespace fft
{

class fft : public Vision::App
{
public:
  fft();
  ~fft();

  void OnUpdate(float timestep);
  void OnResize();

private:
  Vision::ImGuiRenderer* uiRenderer;
  Vision::Renderer2D* renderer;
  Vision::OrthoCamera* camera;

  std::vector<glm::vec2> positions;
};

}