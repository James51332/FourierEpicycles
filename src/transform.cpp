#include "transform.h"
#include "complex.h"

namespace fft::transform
{

// ----- Discrete Fourier Transform -----

std::vector<glm::vec2> dft(std::vector<glm::vec2>& times)
{
  // 1) allocate our frequency array with same size as time domain.
  int numFreq = times.size(); 
  std::vector<glm::vec2> freqs(numFreq, glm::vec2(0.0f));

  // 2) cache the angle of the nth root of unity
  float basisAngle = -2.0f * M_PI / static_cast<float>(numFreq);

  // 3) cache the scaling factor
  float scalingFactor = 1.0f / numFreq;

  // 3) iterate over each frequency in the array
  for (int freq = 0; freq < numFreq; freq++)
  { 
    // 4) perform the dft for that frequncy using the formula
    // X_k = 1/N * (x_0 + x_1 * e^-(i*2pi/N)*k*1 + x_2 * e^-(i*2pi/N)*k*2 + ...)
    for (int time = 0; time < numFreq; time++)
    {
      freqs[freq] += complex::mult(times[time], complex::exp(basisAngle * freq * time));
    }

    // 5) finish the formula by applying the scaling factor
    freqs[freq] = complex::scale(freqs[freq], scalingFactor);
  }

  // 6) return the resulting array
  return std::move(freqs);
}

// ----- Inverse Discrete Fourier Transform -----

std::vector<glm::vec2> idft(std::vector<glm::vec2>& freqs)
{
  // 1) allocate our frequency array with same size as time domain.
  int numTimes = freqs.size();
  std::vector<glm::vec2> times(numTimes, glm::vec2(0.0f));

  // 2) cache the angle of the nth root of unity
  float basisAngle = 2.0f * M_PI / static_cast<float>(numTimes);

  // 3) iterate over each frequency in the array
  for (int time = 0; time < numTimes; time++)
  {
    // 4) perform the idft for that frequncy using the formula
    // x_n = X_0 + X_1 * e^(i*2pi/N)*1*n + X_2 * e^(i*2pi/N)*2*n + ...
    for (int freq = 0; freq < numTimes; freq++)
    {
      times[time] += complex::mult(freqs[freq], complex::exp(basisAngle * freq * time));
    }
  }

  // 5) return the resulting array
  return std::move(times);
}

}