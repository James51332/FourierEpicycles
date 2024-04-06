#pragma once
#include "core/App.h"

namespace fft
{

class fft : public Vision::App
{
public:
  fft();
  ~fft();

  void OnUpdate(float timestep);
  void OnResize();
};

}