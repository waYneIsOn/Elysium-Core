#include "Elysium_Core.h"

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "Elysium_Core", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "Elysium_Core", __VA_ARGS__))

extern "C" {
	/* Diese triviale Funktion gibt den Plattform-ABI zurück, für die diese native dynamische Bibliothek kompiliert wurde.*/
	const char * Elysium_Core::getPlatformABI()
	{
	#if defined(__arm__)
	#if defined(__ARM_ARCH_7A__)
	#if defined(__ARM_NEON__)
		#define ABI "armeabi-v7a/NEON"
	#else
		#define ABI "armeabi-v7a"
	#endif
	#else
		#define ABI "armeabi"
	#endif
	#elif defined(__i386__)
		#define ABI "x86"
	#else
		#define ABI "unknown"
	#endif
		LOGI("This dynamic shared library is compiled with ABI: %s", ABI);
		return "This native library is compiled with ABI: %s" ABI ".";
	}

	void Elysium_Core()
	{
	}

	Elysium_Core::Elysium_Core()
	{
	}

	Elysium_Core::~Elysium_Core()
	{
	}
}
