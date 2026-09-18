#include "signal.h"

complex signal::sum()
{
    complex sum;
    for(auto& sample : samples)
        sum += sample;
    return sum;
}

float signal::absolute_sum()
{
    float sum;
    for(auto& sample : samples)
        sum += sample.abs_amplitude();
    return sum;
}

signal signal::cumulative_sum()
{
    std::vector<complex> running_sum;
    running_sum.reserve(samples.size());
    complex run_sum;
    
    for(auto& sample : samples)
    {
        run_sum += sample;
        running_sum.push_back(run_sum);
    }

    return signal(std::move(running_sum), sample_rate);
}

float signal::energy()
{
    float en = 0.0f;
    for(auto& sample : samples)
        en += sample.power();
    return en;
}

float signal::average_power()
{
    if(samples.empty())
        return 0.0f;
    return energy() / static_cast<float>(samples.size());
}

signal& signal::operator*=(const signal& sig)
{
    size_t sz = size();
    if(sz > sig.size())
        sz = sig.size();

    for(int i = 0; i < sz; ++i)
        samples[i] *= sig[i];

    return *this;
}

signal signal::mult_signals(const signal& lsig, const signal& rsig)
{
    size_t sz = lsig.size();
    if(sz > rsig.size())
        sz = rsig.size();

    signal sret(lsig.size(), lsig.sample_rate);
    for(int i = 0; i < sz; ++i)
        sret[i] = lsig[i] * rsig[i];

    return sret;
}

signal& signal::operator+=(signal& s)
{
    for(size_t i = 0; i < samples.size(); ++i)
        samples[i] += s[i];
    return *this;
}

void signal::zero_samples()
{
    size_t bytes = samples.size() * sizeof(complex);
    if(bytes == 0)
        return;
    volatile char* p = (volatile char*)samples.data();
#if defined(__GNUC__)
    //void* ptr = samples.data();    
    asm volatile ("" : : "r"(p) : "memory");
#endif
    while (bytes--) *p++ = 0;
}