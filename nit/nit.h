/////////////////////////////////////////////////////////////////////////////////////////
// NIT
// scalable network resource sharing library
// chat, mail, threaded conversations, categorized ads and resilient file sharing
/*
Scalable ?
- NIT uses very recent top notch existing techologies like clustered filesystems, 
distributed indexing algorithms, hacking proof encryption and is programmed with C++

What makes NIT interesting is that it allows the user to set different type of network
read/writes priorities.
The best example if bittorrent: everything is smooth because it loads files by itself.
This is not ideal for apps like mail, chat and forum because those need quicker routines/methods for
writing, authing and other procedures, while bittorrent just enable the sharing of a file.

NIT allows to set different priorities on a certain type of network transaction also considering its type (mail, chat, forum, ads, etc), enabling some boost up by adding centralized hosting when it's preferred.

U-N-IFIED: choose several priorities for your data transfers and message posting.
-I-NFITE: data is hosted on all computers with redundancy, so nobody can take it down.
-T-RANSACTIONS: everything is encrypted, from the ID names to the content so even evesdropping a lot of machines cannot allow one to catch one particular information.

*/
/////////////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <string>
using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define DEF_IP "82.242.58.229"

#define printerr(n) printf("err%d: %s\n", strerror(n))
