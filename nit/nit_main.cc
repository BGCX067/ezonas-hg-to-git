#include "nit.h"
#include "nit_recv.h"
#include "nit_send.h"
#define print(s) printf("%s\n", s);

int main(int argn, char * args[])
{
	if(!argn) {
		printf("NIT\nP2P networking library\n\
			   Copyright Jonas ORINOVSKI jorinovski@gmail.com zonas.free.fr\n\n\
			   Usage: ./a.out r to start the receiver, s for the sender\n");
	}
	if (argn == 1) {
		print("No arguments given, making receiver");
		receiver obj(string("80"));
		
	}	
	if (argn == 2) {
		if(*args[1] == 'r') {
			print("Using receiver mode");
			
		}
		else
		if(*args[1] == 's') {
			print("Using sender mode, default target adress, 82.242.58.229");
		}
		else
			print("Use r or s to use sender or receiver mode");

	}	
	if (argn == 3) {
		if(*args[1] == 'r') {
			print("Using receiver mode");
			string ip = string(args[1]);
			receiver obj(string("80"));
		}
		else
		if(*args[1] == 's') {
			print("Using sender mode");
			string ip = string(args[1]);
			sender obj(string("80"));
		}
	}
}