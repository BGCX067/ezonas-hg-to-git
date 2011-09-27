#include "jokoon.h"
#include <vector>
int main()
{
	char ctrl_chr[][4] =
	{
		"NUL",   // "Null character",
		"SOH",   // "Start of Header",          
		"STX",   // "Start of Text",            
		"ETX",   // "End of Text",              
		"EOT",   // "End of Transmission",      
		"ENQ",   // "Enquiry",                  
		"ACK",   // "Acknowledgment",           
		"BEL",   // "Bell",                     
		"BS",    // "Backspace",                
		"HT",    // "Horizontal Tab",           
		"LF",    // "Line feed",                
		"VT",    // "Vertical Tab",             
		"FF",    // "Form feed",                
		"CR",    // "Carriage return",          
		"SO",    // "Shift Out",                
		"SI",    // "Shift In",                 
                 // "Data Link Escape",         
		"DLE",   // "Device Control 1",         
		"DC1",   // "Device Control 2",         
		"DC2",   // "Device Control 3",         
		"DC3",   // "Device Control 4",         
		"DC4",   // "Negative Acknowledgement", 
		"NAK",   // "Synchronous idle",         
		"SYN",   // "End of Transmission Block",
		"ETB",   // "Cancel",                   
		"CAN",   // "End of Medium",            
		"EM",    // "Substitute",               
		"SUB",   // "Escape",                   
		"ESC",   // "File Separator",           
		"FS",    // "Group Separator",          
		"GS",    // "Record Separator",         
		"RS",    // "Unit Separator",           
		"US"     // "Delete"                    
	};
	
	char ctrl_chr_name[][32] = 
	{
		"Null character",
		"Start of Header",
		"Start of Text",
		"End of Text",
		"End of Transmission",
		"Enquiry",
		"Acknowledgment",
		"Bell",
		"Backspace",
		"Horizontal Tab",
		"Line feed",
		"Vertical Tab",
		"Form feed",
		"Carriage return",
		"Shift Out",
		"Shift In",
		"Data Link Escape",
		"Device Control 1",
		"Device Control 2",
		"Device Control 3",
		"Device Control 4",
		"Negative Acknowledgement",
		"Synchronous idle",
		"End of Transmission Block",
		"Cancel",
		"End of Medium",
		"Substitute",
		"Escape",
		"File Separator",
		"Group Separator",
		"Record Separator",
		"Unit Separator",
		"Delete"
	};
	
	vector<string> fds;
	vector<string> fds2;
	// FOR
	FOR(32) fds.push_back(ctrl_chr[i]);
	FOR(32) fds2.push_back(ctrl_chr_name[i]);
	
	FOR(32)
	{
		if(i % 16 == 0)
			prln;
		printf("%s ", fds[i].c_str());
		if(fds[i].length() == 2)
			printf(" ");
	}
	// FOR(32) fds.push((ctrl_chr[i]));
	// FOR(32) fds2.push(string(ctrl_chr_name[i]));
	FORG(32, 128)
	{
		if(i % 16 == 0) prln;
		printf("%c   ", (unsigned char)i);
	}
	prln;
}