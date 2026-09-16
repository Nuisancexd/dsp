#include "plot.h"
#include "common.h"

#include <matplot/matplot.h>
using namespace matplot;


std::vector<double> plot_config::get_real(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(s[i].i);
    return vec;
}

std::vector<double> plot_config::get_imag(const signal& s)
{
    std::vector<double> vec(s.size());
    for(size_t i = 0; i < s.size(); ++i)
        vec[i] = TO_DOUBLE(s[i].q);
    return vec;
}

std::vector<double> plot_config::get_ampl(const signal& s)
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

std::vector<double> freq_axis(const signal& s);

void plot_config::plot(const signal& s, const char* title, int x_pos, int y_pos)
{
    auto x = index_axis(s);
    auto y = get_real(s);
    auto fig = matplot::figure();
    /*need sudo permission for move win*/
    fig->x_position(x_pos);
    fig->y_position(y_pos);
    matplot::plot(x, y);
    matplot::xlabel("n");
    matplot::ylabel("x[n]");
    matplot::title(title);
    matplot::grid(true);
}

void plot_config::plot_amplitude(const signal &s, const char *title, int x_pos, int y_pos)
{
    auto x = index_axis(s);
    auto y = get_ampl(s);
    auto fig = matplot::figure();
    /*need sudo permission for move win*/
    fig->x_position(x_pos);
    fig->y_position(y_pos);
    matplot::plot(x, y);
    matplot::xlabel("n");
    matplot::ylabel("x[n]");
    matplot::title(title);
    matplot::grid(true);
}

void plot_config::plot_stem(const signal& s, const char* title, int x_pos, int y_pos)
{
    auto x = index_axis(s);
    auto y = get_real(s);
    auto fig = matplot::figure();
    /*need sudo permission for move win*/
    fig->x_position(x_pos);
    fig->y_position(y_pos);
    matplot::stem(x, y)->marker_size(10);
    matplot::xlabel("n");
    matplot::ylabel("x[n]");
    matplot::title(title);
    matplot::grid(true);
}