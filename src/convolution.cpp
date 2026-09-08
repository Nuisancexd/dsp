#include "convolution.h"

signal conv::convolve(const signal& x, const signal& h)
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