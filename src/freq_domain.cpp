#include "freq_domain.h"

#include <cmath>
#include <vector>

#define TO_FLOAT(x) static_cast<float>(x)
#define TO_INT(x) static_cast<int>(x)


signal freq_domain::mv_average_freq_impulse(size_t M1, size_t M2, size_t N)
{
    size_t M_samples = M1 + M2 + 1;
    std::vector<complex> samples(N);
    float norm = 1.0f / TO_FLOAT(M_samples);
    float denom = M_samples / 2.0f;

    for(size_t i = 0; i < M_samples; ++i)
    {
        float omega = 2.0f * TO_FLOAT(M_PI) * i / M_samples;
        float fn;
        if(i == 0)
            fn = norm * TO_FLOAT(M_samples);
        else
            fn = norm * (std::sin(omega * M_samples / 2.0f)) / std::sin(omega / 2.0f);
        float phase = -omega * TO_FLOAT(TO_INT(M2) - TO_INT(M1)) / 2.0f;
        complex sample(std::cos(phase), std::sin(phase));
        sample *= fn;
        samples[i] = sample;
    }

    return signal(std::move(samples));
}