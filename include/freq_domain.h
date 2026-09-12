#ifndef _FREQUENCY_DOMAIN_H_
#define _FREQUENCY_DOMAIN_H_

#include "signal.h"

namespace freq_domain
{
    signal mv_average_freq_impulse(size_t M1, size_t M2, size_t N);
    signal symmetric_fft(const signal& sign);
    signal anti_symmetric_fft(const signal& sign);
}

#endif