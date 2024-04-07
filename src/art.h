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

  // display the amplitudes of circles from the origin that draw a point in the complex plane
  void ShowFFT(std::vector<glm::vec2>& amps, float phase, std::size_t numberCircles = 0);

private:
  Vision::ImGuiRenderer* uiRenderer;
  Vision::Renderer2D* renderer;
  Vision::OrthoCamera* camera;

  std::vector<glm::vec2> positions;
  std::vector<glm::vec2> freqs;
  std::vector<glm::vec2> tracePoints;
};

}