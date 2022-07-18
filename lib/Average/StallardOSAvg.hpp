#pragma once

template <typename valueTemplate>
class StallardOSAvg{
    private:
        const uint8_t size;
        uint8_t idx;
        volatile valueTemplate avg;
        volatile valueTemplate *history;

    public:
        StallardOSAvg(volatile valueTemplate *history_array, const uint8_t count, valueTemplate init=0): size(count), idx(0){
            history = history_array;
            for(int i=0; i<size; i++){
                history[i] = init;
            }
            avg = init;
        }

        void add_sample(valueTemplate sample){

            history[idx] = sample;
            if(idx >= size){
                idx = 0;
            }

            avg = 0;
            for(int i=0; i<size; i++){
                avg += history[i];
            }
            avg /= size;
        }

        volatile valueTemplate get_avg(){
            return avg;
        }

};