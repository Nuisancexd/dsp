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


signal freq_domain::symmetric_fft(const signal& sign)
{
    size_t N = sign.size();
    signal xe(N);
    xe[0].i = sign[0].i;
    xe[0].q = 0.0f;

    for(size_t i = 1; i < N; ++i)
    {
        size_t mirror_indx = N - i;
        complex mrr_conj = sign[mirror_indx].conj();

        xe[i] = sign[i] + mrr_conj;
        xe[i] *= 0.5f;
    }

    return xe;
}

signal freq_domain::anti_symmetric_fft(const signal& sign)
{
    size_t N = sign.size();
    signal xo(N);
    xo[0].i = 0.0f;
    xo[0].q = sign[0].i;

    for(size_t i = 1; i < N; ++i)
    {
        size_t mrr_indx = N - i;
        complex mrr_conj = sign[mrr_indx].conj();

        xo[i] = sign[i] - mrr_conj;
        xo[i] *= 0.5f;
    }

    return xo;
}