import zlib
# s = "Hello I'm nafnaf I'm a cat, I'm beige, and I have a brother named dandan, and he is also beige."
# s = "Hello"
# s = '''d'''
# print z
for a in range(26):
 	for b in zlib.compress(chr(a + ord('A'))):
		print b, ord(b),
	print
# print zlib.decompress(z)