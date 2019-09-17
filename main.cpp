#include "stdafx.h"
#include "Core.h"
void StartHeapControl();

int main(int argc, char* argv[])
{
	srand(int(time(nullptr)));
	{ // make sure stack objects go out of scope before _CrtDumpMemoryLeaks is called
		StartHeapControl();

		Core core{Window{"The Sweet Darkness - Cem Alagozlu - 1DAE16", 1280.0f, 720.0f}};
		core.Run();
	}
	//	_CrtDumpMemoryLeaks(); 
	return 0;
}

void StartHeapControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation(nullptr, HeapEnableTerminationOnCorruption, nullptr, 0);

	// Report detected leaks when the program exits
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc(5222);
#endif
}
