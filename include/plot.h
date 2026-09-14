#ifndef _PLOT_H_
#define _PLOT_H_

#include "signal.h"

class plot_config
{
    float line_width = 1.5f;
    int width = 800;
    int height = 600;
    bool grid = true;

public:
    plot_config();

    plot_config& set_line_width(float width);
    plot_config& set_figure_size(int width, int height);
    void plot_obj(const signal& s, const char* title);

    static std::vector<double> get_real(const signal& s);
    static std::vector<double> get_imag(const signal& s);
    static std::vector<double> get_ampl(const signal& s);
    static std::vector<double> index_axis(const signal& s);
    static std::vector<double> time_axis(const signal& s);
    static std::vector<double> freq_axis(const signal& s);

    static void plot(const signal& s, const char* title);
    static void plot_complex(const signal& s, const char* title);
    static void plot_amplitude(const signal& s, const char* title);
    static void plot_spec(const signal& s, const char* title);
};

#endif