#ifndef _CONVOLUTION_H_
#define _CONVOLUTION_H_

#include "signal.h"

namespace conv
{
    signal convolve(const signal& x, const signal& h);
}

#endif