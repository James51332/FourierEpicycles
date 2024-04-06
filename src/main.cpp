#include "art.h"

int main()
{
  fft::art* app = new fft::art();
  app->Run();
  delete app;
}