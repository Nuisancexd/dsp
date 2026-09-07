#include "signal_generator.h"

#include <complex.h>
#include <math.h>
#include <stdexcept>
#include <vector>


#define TO_FLOAT(x) static_cast<float>(x)
#define TO_INT(x) static_cast<int>(x)

signal signal_generator::impulse(size_t size, size_t position, float sample_rate, complex amplitude)
{
    std::vector<complex> samples(size);
    if(size > position)
        samples[position] = amplitude;
    return signal(std::move(samples), sample_rate);
}

signal signal_generator::sum_shifted_impulse(size_t size, size_t position, float sample_rate, complex amplitude)
{
    std::vector<complex> samples(size);
    for(size_t i = position; i < size; ++i)
        samples[i] = amplitude;
    
    return signal(std::move(samples), sample_rate);
}

signal signal_generator::cumulative_sum_impulse(size_t size, size_t position, float sample_rate, complex amplitude)
{
    std::vector<complex> samples;
    samples.reserve(size);
    complex runsum;
    for(size_t i = position; i < size; ++i)
    {
        runsum += amplitude;
        samples.push_back(runsum);
    }

    return signal(std::move(samples), sample_rate);
}

signal signal_generator::rectangular_pulse(size_t size, size_t N, float sample_rate, complex amplitude)
{
    if(2 * N + 1 > size)
        throw std::invalid_argument(" ");

    std::vector<complex> samples(size);
    for(size_t i = 0; i < N + 1; ++i)
        samples[i] = amplitude;
    for(size_t i = size - N; i < size; ++i)
        samples[i] = amplitude;
    return signal(std::move(samples), sample_rate);
}

signal signal_generator::triangular_pulse(size_t size, size_t N, float sample_rate, complex amplitude)
{
    if(2 * N + 1 > size || N == 0)
        throw std::invalid_argument(" ");

    std::vector<complex> samples(size);
    float n;
    for(size_t i = 0; i < N + 1; ++i)
    {
        n = static_cast<float>(i);
        samples[i] = amplitude;
        samples[i] *= 1.0f - fabs(static_cast<float>(n) / static_cast<float>(N));
    }
    for(size_t i = size - N; i < size; ++i)
    {
        n = static_cast<float>(i) - static_cast<float>(size);
        samples[i] = amplitude;
        samples[i] *= 1.0f - fabs(n) / static_cast<float>(N);
    }

    return signal(std::move(samples), sample_rate);
}

signal signal_generator::sinc_pulse(size_t size, size_t N, float sample_rate, complex amplitude)
{
    if(N == 0)
        throw std::invalid_argument(" ");

    std::vector<complex> samples(size);

    int n;
    float val, x;
    for(size_t i = 0; i < size; ++i)
    {
        n = (i <= size / 2) ? TO_INT(i) : TO_INT(i) - TO_INT(size);
        if(n != 0)
        {
            x = TO_FLOAT(n) * TO_FLOAT(M_PI) / TO_FLOAT(N);
            val = sin(x) / x;
        }
        else
            val = 1.0f;
        samples[i] = amplitude;
        samples[i] *= val;
    }

    return signal(std::move(samples), sample_rate);
}

signal signal_generator::sinusoid(size_t size, int freq_hz, int sample_rate, float amplitude, float phase_rad)
{
    std::vector<complex> samples(size);
    const float omega = 2.0f * static_cast<float>(M_PI) * freq_hz * sample_rate;
    float phase;
    for(int n = 0; n < size; ++n)
    {
        phase = omega * n + phase_rad;
        samples[n] = complex(amplitude * cos(phase), amplitude * sin(phase));
    }

    return signal(std::move(samples), sample_rate);
}