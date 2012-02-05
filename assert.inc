// This include provides the ASSERT macro.

#if !defined ASSERT_DEBUG_LEVEL
	// By default, generate assertions when either -d2 and -d3 switch used.
	#define ASSERT_DEBUG_LEVEL 1
#endif

// Setting ASSERT_DEBUG_LEVEL to 0 will make ASSERT() behave exactly as assert().

#if debug >= ASSERT_DEBUG_LEVEL
	#define ASSERT(%0) assert(%0)
#else
	#define ASSERT(%0);
#endif
