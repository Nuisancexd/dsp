#ifndef _COMPLEX_H_
#define _COMPLEX_H_

class complex
{
public:
    float i;
    float q;

    complex() : i(0.0f), q(0.0f) {}
    complex(float i_, float q_) : i(i_), q(q_) {}

    complex& operator+=(complex& sample);
    complex& operator-=(const complex& sample);
    complex& operator*=(const complex& sample);
    complex& operator/=(complex& sample);
    complex& operator*=(float scalar);

    complex& operator_add(float sample_i, float sample_q);
    complex& operator_dec(float sample_i, float sample_q);
    complex& operator_mul(float sample_i, float sample_q);
    complex& operator_div(float sample_i, float sample_q);

    void zero_sample() { i = 0.0f; q = 0.0f; };

    float abs_amplitude() const;
    float signal_amplitude(complex& signal) const;
    float power() const;
    float signal_power(complex& signal) const;
    float phase_rad();
    float phase_rad(complex& signal) const;
    float phase_deg();
    float phase_deg(complex& signal);    

};

complex operator*(complex l_sample, const complex& r_sample);


#endif