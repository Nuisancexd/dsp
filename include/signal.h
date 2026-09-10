#ifndef _DSP_H_
#define _DSP_H_

#include <cstddef> 
#include <vector>
#include "complex.h"

class signal
{
private:
    std::vector<complex> samples;
    float sample_rate = 1.0f;
public:

    signal() {}
    explicit signal(std::vector<complex> samples_) : samples(std::move(samples_)) {}
    explicit signal(std::vector<complex> samples_, float sample_rate_) : samples(std::move(samples_)), sample_rate(sample_rate_) {}

    size_t size() { return samples.size(); }
    size_t size() const { return samples.size(); }
    bool empty() { return samples.empty(); }
    bool empty() const { return samples.empty(); }
    float get_sample_rate() { return sample_rate; }
    float get_sample_rate() const { return sample_rate; }

    complex& operator[](size_t i) { return samples[i]; }
    const complex& operator[](size_t i) const { return samples[i]; }
    
    complex sum();
    float absolute_sum();
    complex average_sum();
    float energy();
    float average_power();
    signal cumulative_sum();

    signal& operator*=(const signal& sig);
    signal mult_signals(const signal& lsig, const signal& rsig);
};



#endif