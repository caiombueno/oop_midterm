#include <vector>

class Chart
{
public:
    // Return a vector of values for the Y axis.
    static std::vector<double> generateYAxisValues(double maxValue, double minValue, int numberOfElements)
    {
        std::vector<double> result(numberOfElements);
        double step = (maxValue - minValue) / (numberOfElements - 1);

        for (int i = 0; i < numberOfElements; i++)
        {
            result[i] = maxValue - (i * step);
        }

        return result;
    }
};