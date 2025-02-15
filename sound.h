#pragma once
#include <vector>
#include <fftw3.h>
#include <portaudio.h>

#define SAMPLE_RATE (48000)

using namespace std;


// Saving audio data
struct Data
{
    double value;
};


// Callback function
static int audio_callback(const void* input_buffer,
    void* output_buffer,
    unsigned long frames,
    const PaStreamCallbackTimeInfo* time,
    PaStreamCallbackFlags status,
    void* user_data)
{
    const float* input = (const float*)input_buffer;
    vector<double> audio_data(frames);

    Data* data = static_cast<Data*>(user_data);

    // FFT
    fftw_complex* in, * out;
    fftw_plan plan;

    in = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * frames);
    out = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * frames);
    plan = fftw_plan_dft_1d(frames, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    // Data from a buffer transferred to a vector for processing
    for (unsigned int i = 0; i < frames; ++i) {
        audio_data[i] = input[i];
    }

    // Filling the input array for FFT
    for (unsigned int i = 0; i < frames; ++i)
    {
        in[i][0] = audio_data[i];
        in[i][1] = 0.0; // Imaginary part, if any
    }

    fftw_execute(plan); // Performing FFT

    // Obtaining the amplitude spectrum
    vector<double> amplitude_spectrum(frames);
    for (unsigned int amplitude = 0; amplitude < frames; ++amplitude)
    {
        double real = out[amplitude][0];
        double imag = out[amplitude][1];
        amplitude_spectrum[amplitude] = sqrt(real * real + imag * imag);
    }

    // Outputting sound characteristics to the console
    for (unsigned int amplitude = 0; amplitude < amplitude_spectrum.size(); ++amplitude)
    {
        double frequency = (amplitude * SAMPLE_RATE / frames);

        if ((amplitude_spectrum[amplitude] > 20.0)
            && (frequency > 55.0)
            && (frequency < 380.0))
        {
            data->value = frequency;
            cout << "Frequency: "
                << frequency
                << " Hz, Amplitude: "
                << amplitude_spectrum[amplitude] << endl;
        }
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);

    // Continuing Audio Capture
    return paContinue;
}
