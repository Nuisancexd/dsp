#include "iostream"

#include "plot.h"
#include "signal.h"
#include "freq_domain.h"
#include "time_domain.h"

#include <cassert>
#include <cmath>


int main()
{
    size_t freq_hz_signal = 1;
    size_t sample_rate = freq_hz_signal * 10;
    signal exp_signal(30, sample_rate);
    time_domain::exponential(exp_signal, freq_hz_signal, sample_rate, 0.8f, 0.0f);
    //time_domain::exponential(exp_signal, freq_hz_signal + 5, sample_rate, 0.5f, 0.5f);
    //time_domain::exponential(exp_signal, freq_hz_signal + 7, sample_rate, 0.3f, 1.5f);

    signal impulse(10);
    time_domain::impulse(impulse, 1, complex(0.8f, 0.0f));
    time_domain::impulse(impulse, 5, complex(0.4f * std::cos(0.7f), 0.4f * std::sin(0.7f)));
    time_domain::impulse(impulse, 9, complex(0.2f * std::cos(1.2f), -0.2f * std::sin(1.2f)));
    signal out = time_domain::convolve(exp_signal, impulse);
    signal spec = freq_domain::dft(out);
    signal iexp = freq_domain::idft(spec);
    
    plot_config::plot(iexp, "ispec", 600, 700, plot_config::AXIS::INDEX);
    plot_config::plot(spec, "spec", 100, 700, plot_config::AXIS::FREQ);
    plot_config::plot( exp_signal, "signal", 1200, 100, plot_config::AXIS::INDEX);
    plot_config::plot( out, "out", 100, 100, plot_config::AXIS::INDEX);
    plot_config::plot(impulse, "impulse", 650, 100, plot_config::AXIS::INDEX, plot_config::STYLE::STEM);

    getchar();
}