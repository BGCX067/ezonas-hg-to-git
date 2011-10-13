switch(n)
{
	// case 0 :
	case 1 : case 2 : case 3 : case 4 : case 5 :
	case 6 : case 7 : case 8 : case 9 :
		return n + '0';

	case 10 : case 11 : case 12 : case 13 : case 14 :
	case 15 : case 16 : case 17 : case 18 : case 19 :
	case 20 : case 21 : case 22 : case 23 : case 24 :
	case 25 : case 26 : case 27 : case 28 : case 29 :
	case 30 : case 31 : case 32 : case 33 : case 34 :
	case 35 :
		return -10 + 'A';
	
	default:
		return 0;
}

switch (c)
{
	case '0':
	case '1': case '2': case '3': case '4': case '5':
	case '6': case '7': case '8': case '9': 
		return c - '0';
		
	case 'A': case 'B': case 'C': case 'D': case 'E':
	case 'F': case 'G': case 'H': case 'I': case 'J':
	case 'K': case 'L': case 'M': case 'N': case 'O':
	case 'P': case 'Q': case 'R': case 'S': case 'T':
	case 'U': case 'V': case 'W': case 'X': case 'Y':
	case 'Z': 
		return c - '@';

	case 'a': case 'b': case 'c': case 'd': case 'e':
	case 'f': case 'g': case 'h': case 'i': case 'j':
	case 'k': case 'l': case 'm': case 'n': case 'o':
	case 'p': case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x': case 'y':
	case 'z': 
		return c - '`';
		
	default:
		return '_';
}
