#include "art.h"

#include <iostream>
using namespace std;

#include "core/Input.h"

#include "complex.h"
#include "transform.h"

namespace fft
{

art::art()
{
  uiRenderer = new Vision::ImGuiRenderer(m_DisplayWidth, m_DisplayHeight, m_DisplayScale);
  renderer = new Vision::Renderer2D(m_DisplayWidth, m_DisplayHeight, m_DisplayScale);
  camera = new Vision::OrthoCamera(m_DisplayWidth, m_DisplayHeight, 15.0f);
}

art::~art()
{
  delete uiRenderer;
  delete renderer;
  delete camera;
}

void art::OnUpdate(float timestep)
{
  glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // camera
  if (Vision::Input::KeyDown(SDL_SCANCODE_P))
    camera->Update(timestep);

  // render
  renderer->Begin(camera);

  // draw trace
  for (int i = 0; i < static_cast<int>(tracePoints.size()) - 1; i++)
  {
    renderer->DrawLine(tracePoints[i], tracePoints[(i + 1)], glm::vec4(0.5f, 0.5f, 0.5f, 1.0f), 0.1f);
  }
  if (tracePoints.size() > 0)
    renderer->DrawPoint(tracePoints.back(), glm::vec4(1.0f), 0.2f);

  // show our points
  for (int i = 0; i < positions.size(); i++)
  {
    renderer->DrawPoint(positions[i], glm::vec4(1.0f), 0.2f);
  }

  ShowFFT(freqs, SDL_GetTicks() * 2.0f * M_PI / 4000.0f, 0);
  renderer->End();

  // render ui
  uiRenderer->Begin();
  if (ImGui::Begin("Settings"))
  {
    if (ImGui::Button("Clear Points (c)") || Vision::Input::KeyPress(SDL_SCANCODE_C))
    {
      positions.clear();
      freqs.clear();
      tracePoints.clear();
    }

    if (ImGui::Button("Clear Trace (t)") || Vision::Input::KeyPress(SDL_SCANCODE_T))
    {
      tracePoints.clear();
    }

    if (ImGui::Button("Stop DFT (d)") || Vision::Input::KeyDown(SDL_SCANCODE_D))
    {
      freqs.clear();
    }

    if (ImGui::Button("Run DFT (space)") || Vision::Input::KeyPress(SDL_SCANCODE_SPACE))
    {
      tracePoints.clear();
      freqs = transform::dft(positions);
    }

    if (ImGui::DragInt("Max Circles", &maxCircles, 1.0, 1.0, 100.0))
    {
      tracePoints.clear();
    }
  }
  ImGui::End();
  uiRenderer->End();

  // add points
  if (Vision::Input::MousePress(SDL_BUTTON_LEFT) && !Vision::Input::KeyDown(SDL_SCANCODE_P))
    positions.push_back(camera->GetMouseInWorldSpace());
}

void art::OnResize()
{
  uiRenderer->Resize(m_DisplayWidth, m_DisplayHeight);
  renderer->Resize(m_DisplayWidth, m_DisplayHeight);
  camera->SetWindowSize(m_DisplayWidth, m_DisplayHeight);
}

void art::ShowFFT(std::vector<glm::vec2> &amps, float phase, std::size_t numberCircles)
{
  // 1) track our position in the complex plane as we add circles
  glm::vec2 position = {0.0f, 0.0f};

  // 2) determine how many circles to draw (if set 0, draw all)
  int numFreqs = static_cast<int>(numberCircles ? glm::min(numberCircles, amps.size()) : amps.size());

  // 3) iterate over all desired circles
  for (int circle = 0; circle < numFreqs; circle++)
  {
    // 4) for each freq, determine the effect it has on our position (freq * e^i*phase*k)
    int actualFreq = (circle % 2 == 0) ? circle / 2 : numFreqs - (circle+1) / 2;
    float displayFreq = (circle % 2 == 0) ? circle / 2 : - (circle + 1) / 2;

    glm::vec2 delta = complex::mult(amps[actualFreq], complex::exp(phase * displayFreq));
    
    // 5) calculate the new position
    glm::vec2 newPos = position + delta;

    // 6) draw a new circle using this information.
    if (circle != 0) // don't draw the first circle
    {
      float radius = glm::length(delta);
      renderer->DrawCircle(position, glm::vec4(1.0f), radius, 0.025f);
      renderer->DrawLine(position, newPos, glm::vec4(1.0f), 0.05f);
    }

    // 7) update the position
    position = newPos;
  }

  tracePoints.push_back(position);
}

}