#ifndef UTILITY_H
#define UTILITY_H

class Utility {
public :
    static float clamp(float x, float min, float max)
    {
        if(x<min)
            return min;
        else if (x>max)
            return max;
        else
            return x;
    }
};
#endif // UTILITY_H
