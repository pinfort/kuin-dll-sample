#include <Windows.h>
 
BOOL WINAPI DllMain(HINSTANCE, DWORD, LPVOID)
{
  return TRUE;
}
 
// typedef unsigned char U8;
extern "C" _declspec(dllexport) unsigned char echoChar(unsigned char x)
{
	return x;
}

extern "C" _declspec(dllexport) unsigned char* echoStr(unsigned char* x)
{
  return x;
}

// typedef signed long long S64;
extern "C" _declspec(dllexport) signed long long echoInt(signed long long x)
{
	return x;
}

extern "C" _declspec(dllexport) double echoFloat(double x)
{
	return x;
}

// typedef unsigned char Bool;
extern "C" _declspec(dllexport) unsigned char echoBool(unsigned char x)
{
	return x;
}

// typedef unsigned char U8;
extern "C" _declspec(dllexport) unsigned char echoBit8(unsigned char x)
{
	return x;
}

// typedef unsigned short U16;
extern "C" _declspec(dllexport) unsigned short echoBit16(unsigned short x)
{
	return x;
}

// typedef unsigned int U32;
extern "C" _declspec(dllexport) unsigned int echoBit32(unsigned int x)
{
	return x;
}

// typedef unsigned long long U64;
extern "C" _declspec(dllexport) unsigned long long echoBit64(unsigned long long x)
{
	return x;
}

// typedef signed int S32;
extern "C" _declspec(dllexport) int echoEnum(int x)
{
	return x;
}

typedef struct SClass
{
	unsigned long long RefCnt;
	void* ClassTable;
} SClass;

typedef struct MyClass
{
	SClass Class;
	int data;
} MyClass;

extern "C" _declspec(dllexport) int _getInt(SClass* me_)
{
	MyClass* var = reinterpret_cast<MyClass*>(me_);
	return var->data;
}
