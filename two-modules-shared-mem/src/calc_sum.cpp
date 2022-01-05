extern "C"
{
    int calc_sum(int *array, int size);
}
#include <emscripten.h>
int calc_sum(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; ++i)
    {
        sum += arr[i];
        EM_ASM(
            {console.log("in function calc_sum, sum is " + $0, "")}, sum);
    }

    return sum;
}