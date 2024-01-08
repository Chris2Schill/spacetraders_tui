#pragma once

namespace ncfw {

class RingIndex {
public:
    RingIndex() : RingIndex(0,0) {}

    RingIndex(int min, int max) 
        : min(min)
        , max(max)
        , value(0)
    {}

    void next() {
        value++;
        if (value > max) {
            value = min;
        }
    }
    void prev() {
        value--;
        if (value < min) {
            value = max;
        }
    }

    int get_min() const { return min; }
    void set_min(int m) { min = m; }

    int get_max() const { return max; }
    void set_max(int m) {  max = m; }

    int get_value() const { return value; }
    bool set_value(int v) { 
        if (min <= value && value <= max) {
            value = v;
            return true;
        }
        return false;
    }

private:
    int min;
    int max;
    int value;
};

}
