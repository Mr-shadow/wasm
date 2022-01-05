#include <emscripten.h>
extern "C"
{
    int *fill_array(int n)
    {
        int *arr = new int[n];
        for (int i = 0; i < n; ++i)
        {
            arr[i] = i;
            EM_ASM(
                {console.log("in function fill_array, arr[i] is " + $0)}, arr[i]);
        }

        return arr;
    }
}
