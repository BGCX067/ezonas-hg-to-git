import sys

def encode_fib(n):
    # Return string with Fibonacci encoding for n (n >= 1).
    result = ""
    if n >= 1:
        a = 1
        b = 1
        c = a + b   # next Fibonacci number
        fibs = [b]  # list of Fibonacci numbers, starting with F(2), each <= n
        while n >= c:
            fibs.append(c)  # add next Fibonacci number to end of list
            a = b
            b = c
            c = a + b
        result = "1"  # extra "1" at end
        for fibnum in reversed(fibs):
            if n >= fibnum:
                n = n - fibnum
                result = "1" + result
            else:
                result = "0" + result
    return result
 
# sys.argv
# print encode_fib(int(sys.argv[1]))
for a in range(1,101):
	print a, encode_fib(a)