#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace fft::transform
{

// ----- DFT and IDFT -----

// convert from the time domain to the freq domain (assumes period is 0 to 2pi)
std::vector<glm::vec2> dft(std::vector<glm::vec2>& timeDomain);

// convert from the freq. domain to the time domain (freq increases by 2pi rad/s)
std::vector<glm::vec2> idft(std::vector<glm::vec2>& freqDomain);

}