#if defined(_MSC_VER)
#ifdef BUILDING_PXCORE
#define PX_API __declspec(dllexport)
#else
#define PX_API __declspec(dllimport)
#endif
#else
#define PX_API __attribute__((visibility("default")))
#endif
#define PX_C_API extern "C" PX_API
