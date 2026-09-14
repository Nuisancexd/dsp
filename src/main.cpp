#include "iostream"

#include "plot.h"
#include "signal.h"
#include <vector>

#include "time_domain.h"

#include <cassert>
#include <math.h>


int main()
{
    size_t freq_hz_signal = 2;
    size_t sample_rate = 35;
    complex complex_rx(1, 0);
    //auto t = signal_generator::triangular_pulse(30, 10, 1, complex_rx);
    auto t = time_domain::sinusoid(40, freq_hz_signal, sample_rate, 1.f, 0.0f);

    //size_t N = time_domain::signal_period(freq_hz_signal, sample_rate);
    // if(time_domain::is_signal_periodic(t, N))
    //     printf("true\n");
    // else
    //     printf("false\n");

    //auto h = signal_generator::impulse(10, 0, sample_rate, complex(0.5f, 0.0f));
    auto h = time_domain::impulse(10, 9, sample_rate, complex(0.5f, 0.0f));
    auto h2 = time_domain::impulse(300, 10, sample_rate, complex(0.2f, 0.0f));
    auto hn = time_domain::cascade_impulse_parallel(h, h);
    auto tr = time_domain::cumulative_sum_impulse(30, 10, 1, complex_rx);
    signal out = time_domain::convolve(t, h2);

    plot_config::plot(out, "clown");
}