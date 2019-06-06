#include "factorial.h"

namespace flaber
{
	size_t factorial(size_t t)
	{
		size_t result = 1;

		for (int i = 1; i <= t; ++i)
			result *= i;

		return result;
	}
}
