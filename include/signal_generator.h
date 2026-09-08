#ifndef _SIGNAL_GENERATOR_H
#define _SIGNAL_GENERATOR_H

#include "signal.h"

namespace signal_generator
{
    signal impulse(size_t size, size_t position, size_t sample_rate = 1.0f, complex sample_sig = {1.0f, 0.0f});
    signal sum_shifted_impulse(size_t size, size_t position, size_t sample_rate = 1.0f, complex sample_sig = {1.0f, 0.0f});
    signal cumulative_sum_impulse(size_t size, size_t position, size_t sample_rate = 1.0f, complex sample_sig = {1.0f, 0.0f});
    signal triangular_pulse(size_t size, size_t N, size_t sample_rate, complex sample_sig);
    signal rectangular_pulse(size_t size, size_t N, size_t sample_rate, complex sample_sig);
    signal sinc_pulse(size_t size, size_t N, size_t sample_rate, complex amplitude);
    signal sinusoid(size_t size, size_t freq_hz, size_t sample_rate, float amplitude = 1.0f, float phase_rad = 0.0f);
    signal exponential(size_t size, size_t freq_hz, size_t sample_rate, float amplitude, float phase_rad);
    size_t signal_period(size_t freq_hz, size_t sample_rate);
    bool is_signal_periodic(const signal& signal, size_t N);
    signal white_noise();
}


#endif