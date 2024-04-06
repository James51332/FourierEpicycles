#include "fft.h"

int main()
{
  fft::fft* app = new fft::fft();
  app->Run();
  delete app;
}