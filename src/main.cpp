#include "iostream"

#include "signal.h"
#include <vector>

#include "signal_generator.h"

#include <cassert>
#include <math.h>
int main()
{
    complex complex_rx(1, 0);
    //auto t = signal_generator::triangular_pulse(30, 10, 1, complex_rx);
    auto t = signal_generator::sinc_pulse(100, 5, 1.0f, complex_rx);
    for(int i = 0; i < t.size(); ++i)
        printf("%f  ", t[i].amplitude());

}