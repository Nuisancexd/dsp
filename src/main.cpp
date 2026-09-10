#include "iostream"

#include "signal.h"
#include <vector>

#include "time_domain.h"

#include <cassert>
#include <math.h>

int main()
{
    size_t freq_hz_signal = 2;
    size_t sample_rate = 10;
    complex complex_rx(1, 0);
    //auto t = signal_generator::triangular_pulse(30, 10, 1, complex_rx);
    auto t = time_domain::sinusoid(20, freq_hz_signal, sample_rate, 1.f, 0.0f);
    for(int i = 0; i < t.size(); ++i)
       //printf("%f  ", t[i].abs_amplitude());
       printf("%f  ", t[i].i);
    printf("\n");

    size_t N = time_domain::signal_period(freq_hz_signal, sample_rate);
    if(time_domain::is_signal_periodic(t, N))
        printf("true\n");
    else
        printf("false\n");

    //auto h = signal_generator::impulse(10, 0, sample_rate, complex(0.5f, 0.0f));
    auto h = time_domain::impulse(30, 4, sample_rate, complex(0.5f, 0.0f));
    auto h2 = time_domain::impulse(3, 0, sample_rate, complex(0.2f, 0.0f));
    auto hn = time_domain::cascade_impulse_parallel(h, h);
    signal out = time_domain::convolve(t, hn);

    for(int i = 0; i < out.size(); ++i)
       printf("%f  ", out[i].abs_amplitude());
    printf("\n");
    for(int i = 0; i < out.size(); ++i)
       printf("%f  ", out[i].i);
    printf("\n");
}