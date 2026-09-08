#include "complex.h"

#include <math.h>

complex& complex::operator+=(complex& sample)
{
    i += sample.i;
    q += sample.q;
    return *this;
}

complex& complex::operator-=(const complex& sample)
{
    i -= sample.i;
    q -= sample.q;
    return *this;
}

complex& complex::operator*=(const complex& sample)
{
    //  (z1.i + z1.q) * (z2.i + z2.q)
    float i_src = i;
    i = i * sample.i - q * sample.q;
    q = i_src * sample.q + q * sample.i;
    return *this;
}

complex operator*(complex l_sample, const complex& r_sample)
{
    l_sample *= r_sample;
    return l_sample;
}

complex& complex::operator/=(complex& sample)
{
    // z1/z2 = (z1 * z2_*) / (z2 * z1_*) = (z1.i * z2.i + z1.q * z2.q) + i(z1.q * z2.i - z1.i * z2.q) / z2^2
    float denom = (sample.i * sample.i + sample.q * sample.q);
    float i_src = i;
    i = (i * sample.i + q * sample.q) / denom;
    q = (q * sample.i - i_src * sample.q) / denom;
    return *this;
}

complex& complex::operator*=(float scalar)
{
    i *= scalar;
    q *= scalar;
    return *this;
}

complex& complex::operator_add(float sample_i, float sample_q)
{
    i += sample_i;
    q += sample_q;
    return *this;
}

complex& complex::operator_dec(float sample_i, float sample_q)
{
    i -= sample_i;
    q -= sample_q;
    return *this;
}

complex& complex::operator_mul(float sample_i, float sample_q)
{
    i = i * sample_i - q * sample_q;
    q = i * sample_q + q * sample_i;
    return *this;
}

complex& complex::operator_div(float sample_i, float sample_q)
{
    i = (i * sample_i + q * sample_q) / sample_i * sample_i + sample_q * sample_q;
    q = (q * sample_i + i * sample_q) / sample_i * sample_i + sample_q * sample_q;
    return *this;
}

float complex::abs_amplitude() const
{
    return sqrt(i * i + q * q);
}

float complex::signal_amplitude(complex& signal) const
{
    return sqrt(signal.i * signal.i + signal.q * signal.q);
}

float complex::power() const
{
    return i * i + q * q;
}

float complex::signal_power(complex& signal) const
{
    return signal.i * signal.i + signal.q + signal.q;
}

float complex::phase_rad()
{
    return atan2f(q, i);
}

float complex::phase_rad(complex& signal) const
{
    return atan2f(signal.q, signal.i);
}

float complex::phase_deg()
{
    return 180.0f * phase_rad() / static_cast<float>(M_PI);
}

float complex::phase_deg(complex& signal)
{
    return 180.0f * phase_rad(signal) / static_cast<float>(M_PI);
}