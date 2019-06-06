#include "factorial.h"

namespace flaber
{
	unsigned int factorial(unsigned int t)
	{
		unsigned int result = 1;

		for (int i = 1; i <= t; ++i)
			result *= i;

		return result;
	}
}
