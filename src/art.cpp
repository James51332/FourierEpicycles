#include "art.h"

#include <iostream>
using namespace std;

#include "core/Input.h"

#include "transform.h"

namespace fft
{

art::art()
{
  uiRenderer = new Vision::ImGuiRenderer(m_DisplayWidth, m_DisplayHeight, m_DisplayScale);
  renderer = new Vision::Renderer2D(m_DisplayWidth, m_DisplayHeight, m_DisplayScale);
  camera = new Vision::OrthoCamera(m_DisplayWidth, m_DisplayHeight, 5.0f);

  // ----- DFT and IDFT Test -----
  std::vector<glm::vec2> times = { {1.0f, 0.0f}, {2.0f, 0.0f}, {3.0f, 0.0f} };
  
  cout << "Performing the DFT on the following time domain values:" << endl;
  for (auto time : times)
  {
    cout << time.x << " + " << time.y << "i" << endl;
  }
  cout << "-------------------------" << endl;

  std::vector<glm::vec2> freqs = transform::dft(times);

  cout << "The resulting amplitudes in the frequency domain are:" << endl;
  for (auto freq : freqs)
  {
    cout << freq.x << " + " << freq.y << "i" << endl;
  }
  cout << "-------------------------" << endl;

  times = transform::idft(freqs);

  cout << "The time domain values from the IDFT are:" << endl;
  for (auto time : times)
  {
    cout << time.x << " + " << time.y << "i" << endl;
  }
  cout << "-------------------------" << endl;
}

art::~art()
{
  delete uiRenderer;
  delete renderer;
  delete camera;
}

void art::OnUpdate(float timestep)
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

  // render ui
  uiRenderer->Begin();
  if (ImGui::Begin("Settings"))
  {
    if (ImGui::Button("Clear Points (c)") || Vision::Input::KeyPress(SDL_SCANCODE_C))
      positions.clear();
  }
  ImGui::End();
  uiRenderer->End();

  // add points
  if (Vision::Input::MouseDown(SDL_BUTTON_LEFT))
  {
    positions.push_back(camera->GetMouseInWorldSpace());
  }
}

void art::OnResize()
{
  uiRenderer->Resize(m_DisplayWidth, m_DisplayHeight);
  renderer->Resize(m_DisplayWidth, m_DisplayHeight);
  camera->SetWindowSize(m_DisplayWidth, m_DisplayHeight);
}

}