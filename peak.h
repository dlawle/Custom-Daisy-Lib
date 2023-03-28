#pragma once
#ifndef PEAK_H
#define PEAK_H
#include <stdlib.h>

#include "daisysp.h"

namespace daisysp {
    class Peak
        {
        public:
            Peak() {}
            ~Peak() {}

            void Init(){
                peak_ = 0.5f;
            };


            // From @antisvin on discord:
            //
            // The code is incorrect as you're not progressing the value referenced by input data pointer.
            // It's supposed to be something like this (assuming that you're trying to detect values above the default peak once per block of audio):
            //
            //void ProcessBlock(float *in, size_t size, float pre_gain){
            //    float new_peak = 0;
            //    while(size--)
            //    {
            //        float peak = *in++ * pre_gain;
            //        new_peak = std::max(fabsf(peak), new_peak);
            //    }
            //    new_peak_ = new_peak;
            //};

            /** Processes a block of audio through the limiter.
            \param in - pointer to a block of audio samples to be processed. The buffer is operated on directly.
            \param size - size of the buffer "in"
            \param pre_gain - amount of pre_gain applied to the signal.
            */
            void ProcessBlock(float *in, size_t size, float pre_gain) {
                while(size--)
                {
                    float pre = *in * pre_gain;
                    //float peak = fabsf(pre);
                    new_peak_ = fabsf(pre);
                }
            };

            bool PeakTrig(){
                bool peaked;
                if(new_peak_ >= peak_){
                    peaked = true;
                } else {
                    peaked = false;
                };
                return peaked;
            };

            /** Set the initial Peak dector "limit" 
             \param base_peak - works best 0-1. Default is 0.5 
            */
            void SetPeak(float base_peak){
                peak_ = base_peak;
            };

            private:
                float peak_;
                float new_peak_;
        };
    }

#endif