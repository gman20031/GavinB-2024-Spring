#pragma once

#include <iostream>

#ifdef NO_VERBOUS_LOG

	#define VERBOSE_LOG(message) (void(0))

#else // VERBOUS_LOG enabled

	#define VERBOSE_LOG(message)                   \
		std::cout << __FILE__ << ", "              \
				  << __func__ << ", "              \
				  << "line:"  << __LINE__ << ", "  \
				  << message  << '\n'

#endif // NO_VERBOUS_LOG



