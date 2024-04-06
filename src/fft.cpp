#include "fft.h"

#include "core/Input.h"

namespace fft
{

fft::fft()
{
  uiRenderer = new Vision::ImGuiRenderer(m_DisplayWidth, m_DisplayHeight, m_DisplayScale);
  renderer = new Vision::Renderer2D(m_DisplayWidth, m_DisplayHeight, m_DisplayScale);
  camera = new Vision::OrthoCamera(m_DisplayWidth, m_DisplayHeight, 5.0f);
}

fft::~fft()
{
  delete uiRenderer;
  delete renderer;
  delete camera;
}

void fft::OnUpdate(float timestep)
{
  glClearColor(0.1f, 0.8f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // render lines
  renderer->Begin(camera);
  for (int i = 0; i < positions.size(); i++)
  {
    renderer->DrawLine(positions[i], positions[(i + 1) % positions.size()], glm::vec4(1.0f), 0.5f);
  }
  renderer->End();

  // add points
  if (Vision::Input::MouseDown(SDL_BUTTON_LEFT))
  {
    positions.push_back(camera->GetMouseInWorldSpace());
  }
}

void fft::OnResize()
{
  uiRenderer->Resize(m_DisplayWidth, m_DisplayHeight);
  renderer->Resize(m_DisplayWidth, m_DisplayHeight);
  camera->SetWindowSize(m_DisplayWidth, m_DisplayHeight);
}

}