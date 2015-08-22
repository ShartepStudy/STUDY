
#ifdef __MYDLL__
#define SIMPLE_EXAMPLE extern "C" __declspec(dllexport)
#else
#define SIMPLE_EXAMPLE extern "C" __declspec(dllimport)
#endif

SIMPLE_EXAMPLE void MessageInfo(char* str);
SIMPLE_EXAMPLE void Ref(int& ref);
SIMPLE_EXAMPLE int counter;
