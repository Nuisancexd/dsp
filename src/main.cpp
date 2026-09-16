#include "iostream"

#include "plot.h"
#include "signal.h"
#include <vector>

#include "time_domain.h"

#include <cassert>
#include <math.h>


int main()
{
    size_t freq_hz_signal = 1;
    size_t sample_rate = freq_hz_signal * 10;
    auto t = time_domain::exponential(100, freq_hz_signal, sample_rate, 1.f, 0.0f);
    auto h = time_domain::impulse(10, 0, sample_rate, complex(0.8f, 0.0f));
    time_domain::add_impulse(h, 5, complex(0.4f, 0.0f));
    time_domain::add_impulse(h, 9, complex(0.2f, 0.0f));    
    signal out = time_domain::convolve(t, h);

    plot_config::plot(t, "signal", 1200, 100);
    plot_config::plot(out, "out", 100, 100);
    plot_config::plot_stem(h, "h", 650, 100);
    getchar();
}