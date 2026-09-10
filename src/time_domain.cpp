#include "time_domain.h"

#include <complex.h>
#include <math.h>
#include <stdexcept>
#include <vector>


#define TO_FLOAT(x) static_cast<float>(x)
#define TO_INT(x) static_cast<int>(x)

signal time_domain::impulse(size_t size, size_t position, size_t sample_rate, complex amplitude)
{
    std::vector<complex> samples(size);
    if(size > position)
        samples[position] = amplitude;
    return signal(std::move(samples), sample_rate);
}

signal time_domain::sum_shifted_impulse(size_t size, size_t position, size_t sample_rate, complex amplitude)
{
    std::vector<complex> samples(size);
    for(size_t i = position; i < size; ++i)
        samples[i] = amplitude;
    
    return signal(std::move(samples), sample_rate);
}

signal time_domain::cumulative_sum_impulse(size_t size, size_t position, size_t sample_rate, complex amplitude)
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

signal time_domain::rectangular_pulse(size_t size, size_t N, size_t sample_rate, complex amplitude)
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

signal time_domain::triangular_pulse(size_t size, size_t N, size_t sample_rate, complex amplitude)
{
    if(2 * N + 1 > size || N == 0)
        throw std::invalid_argument(" ");

    std::vector<complex> samples(size);
    float n;
    for(size_t i = 0; i < N + 1; ++i)
    {
        n = static_cast<float>(i);
        samples[i] = amplitude;
        samples[i] *= 1.0f - fabs(TO_FLOAT(n) / TO_FLOAT(N));
    }
    for(size_t i = size - N; i < size; ++i)
    {
        n = TO_FLOAT(i) - TO_FLOAT(size);
        samples[i] = amplitude;
        samples[i] *= 1.0f - fabs(n) / TO_FLOAT(N);
    }

    return signal(std::move(samples), sample_rate);
}

signal time_domain::sinc_pulse(size_t size, size_t N, size_t sample_rate, complex amplitude)
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

signal time_domain::exponential(size_t size, size_t freq_hz, size_t sample_rate, float amplitude, float phase_rad)
{
    std::vector<complex> samples(size);
    const float omega = 2.0f * TO_FLOAT(M_PI) * TO_FLOAT(freq_hz) / TO_FLOAT(sample_rate);
    float phase;
    for(size_t n = 0; n < size; ++n)
    {
        phase = omega * n + phase_rad;
        samples[n] = complex(amplitude * cos(phase), amplitude * sin(phase));
    }

    return signal(std::move(samples), sample_rate);
}

signal time_domain::sinusoid(size_t size, size_t freq_hz, size_t sample_rate, float amplitude, float phase_rad)
{
    std::vector<complex> samples(size);
    const float omega = 2.0f * TO_FLOAT(M_PI) * TO_FLOAT(freq_hz) / TO_FLOAT(sample_rate);
    float phase;
    for(size_t n = 0; n < size; ++n)
    {
        phase = omega * n + phase_rad;
        samples[n] = complex(amplitude * cos(phase), 0.0f);
    }

    return signal(std::move(samples), sample_rate);
}

size_t time_domain::signal_period(size_t freq_hz, size_t sample_rate)
{
    if(freq_hz == 0)
        return 1;

    size_t tmp, a = freq_hz, b = sample_rate;
    while(b != 0)
    {
        tmp = b;
        b = a % b;
        a = tmp;
    }

    return sample_rate / a;
}

bool time_domain::is_signal_periodic(const signal& signal, size_t N)
{
    if(N == 0 || N >= signal.size())
        return false;

    for(size_t i = 0; i + N < signal.size(); ++i)
    {
        complex diff = signal[i];
        diff -= signal[i + N];
        if(diff.abs_amplitude() > 1e-4f)
            return false;
    }
    return true;
}

signal time_domain::convolve(const signal& x, const signal& h)
{
    if(x.empty() || h.empty())
        return signal();

    size_t size_x = x.size();
    size_t size_h = h.size();
    size_t size_y = x.size() + h.size() - 1;
    std::vector<complex> y(size_y);

    for(size_t n = 0; n < size_y; ++n)
    {
        complex sum;
        size_t k_min = (n >= size_h - 1) ? (n - (size_h - 1)) : 0;
        size_t k_max = std::min(n, size_x - 1);
        
        for(; k_min <= k_max; ++k_min)
        {
            //x[k_min] * h[n - k_min];
            complex tmp = x[k_min];
            tmp *= h[n - k_min];
            sum += tmp;
        }
        y[n] = sum;
    }

    return signal(std::move(y), x.get_sample_rate());
}

signal time_domain::cascade_impulse_series(const signal& h1, const signal& h2)
{
    std::vector<complex> h(h1.size());
    for(size_t i = 0; i < h1.size(); ++i)
        h[i] = h1[i] * h2[i];

    return signal(std::move(h), h1.get_sample_rate());
}

signal time_domain::cascade_impulse_parallel(const signal& h1, const signal& h2)
{
    std::vector<complex> h(h1.size());
    for(size_t i = 0; i < h1.size(); ++i)
        h[i] = h1[i] + h2[i];

    return signal(std::move(h), h1.get_sample_rate());
}