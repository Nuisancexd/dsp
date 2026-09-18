#include "plot.h"
#include "common.h"

#include <matplot/matplot.h>
using namespace matplot;


std::vector<double> plot_config::real_axis(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(s[i].i);
    return vec;
}

std::vector<double> plot_config::imag_axis(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(s[i].q);
    return vec;
}

std::vector<double> plot_config::ampl_axis(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(s[i].abs_amplitude());
    return vec;
}

std::vector<double> plot_config::index_axis(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(i);
    return vec;
}

std::vector<double> plot_config::time_axis(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(i / s.get_sample_rate());
    return vec;
}

std::vector<double> plot_config::freq_axis(const signal& s)
{
    float bin = s.get_sample_rate() / s.size();
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(i * bin);
    return vec;
}

void plot_config::plot(const signal& s, const char* title, int x_pos, int y_pos, AXIS ax, STYLE style)
{
    std::vector<double> x;
    switch (ax) 
    {
    case AXIS::REAL:
        x = real_axis(s);
        break;
    case AXIS::IMAG:
        x = imag_axis(s);
        break;
    case AXIS::INDEX:
        x = index_axis(s);
        break;
    case AXIS::TIME:
        x = time_axis(s);
        break;
    case AXIS::FREQ:
        x = freq_axis(s);
        break;
    };

    auto y = real_axis(s);
    auto fig = matplot::figure();
    /*need sudo permission for move win*/
    fig->x_position(x_pos);
    fig->y_position(y_pos);
    if(style == STYLE::LINE)
        matplot::plot(x, y);
    else if(style == STYLE::STEM)
        matplot::stem(x, y);
    matplot::xlabel("n");
    matplot::ylabel("x[n]");
    matplot::title(title);
    matplot::grid(true);
}