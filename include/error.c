#include "error.h"

void bsod(int error){
	clear_screen();
	print("***CODEOS ERROR***");
	print("CodeOS Encountered an error and needed to stop your computer.");
	print("\n\nError Code:");
	//printInt(error,0x1f);
	for(;;);
}

void bsodmsg(string message){
	clear_screen();
	print("***CODEOS ERROR***");
	print("CodeOS Encountered an error and needed to stop your computer.");
	print("\n\nError Code: ");
	print(message);
	for(;;);
}
