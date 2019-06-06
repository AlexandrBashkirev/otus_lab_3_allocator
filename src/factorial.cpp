#include "factorial.h"

namespace flaber
{
	unsigned int factorial(unsigned int t)
	{
		unsigned int result = 1;

		for (unsigned int i = 1; i <= t; ++i)
			result *= i;

		return result;
	}
}
