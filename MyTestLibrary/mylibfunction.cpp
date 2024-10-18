/*
* Simple library that needs to be set up as dynamic linked library (.dll).
* In this library there is only one simple function my_sqrt, which
* calculates square root of the number with Heron's iterative formula.
*/

#define TEN(n) 1e##n
#define ACC TEN(-6)

#ifdef __cplusplus
extern "C"
{
#endif

__declspec(dllexport) double __cdecl my_sqrt(double value)
{
	if (value < 0) return -1;
	if (value == 0 || value == 1) return value;

	double result = value / 2;
	while (result - value / result > ACC || result - value / result < -ACC)
	{
		result = 0.5 * (result + value / result);
	}

	return result;
}

#ifdef __cplusplus
}
#endif