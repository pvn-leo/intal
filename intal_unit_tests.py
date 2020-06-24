from ctypes import *
import sys
from random import randrange
Intal = cdll.LoadLibrary("./libIntal.so")

# char* intal_add(const char* intal1, const char* intal2);
# int intal_compare(const char* intal1, const char* intal2);
# char* intal_diff(const char* intal1, const char* intal2);
# char* intal_multiply(const char* intal1, const char* intal2);
# char* intal_mod(const char* intal1, const char* intal2);
# char* intal_pow(const char* intal1, unsigned int n);
# char* intal_gcd(const char* intal1, const char* intal2);
# char* intal_fibonacci(unsigned int n);
# char* intal_factorial(unsigned int n);
# char* intal_bincoeff(unsigned int n, unsigned int k);
# int intal_max(char **arr, int n);
# int intal_min(char **arr, int n);
# int intal_search(char **arr, int n, const char* key);
# int intal_binsearch(char **arr, int n, const char* key);
# void intal_sort(char **arr, int n);
# char* coin_row_problem(char **arr, int n);

intal_add = Intal.intal_add
intal_add.argtypes = [c_char_p, c_char_p]
intal_add.restype = c_char_p

intal_compare = Intal.intal_compare
intal_compare.argtypes = [c_char_p, c_char_p]
intal_compare.restype = c_int

intal_diff = Intal.intal_diff
intal_diff.argtypes = [c_char_p, c_char_p]
intal_diff.restype = c_char_p

intal_multiply = Intal.intal_multiply
intal_multiply.argtypes = [c_char_p, c_char_p]
intal_multiply.restype = c_char_p

intal_mod = Intal.intal_mod
intal_mod.argtypes = [c_char_p, c_char_p]
intal_mod.restype = c_char_p

intal_pow = Intal.intal_pow
intal_pow.argtypes = [c_char_p, c_uint]
intal_pow.restype = c_char_p

intal_gcd = Intal.intal_gcd
intal_gcd.argtypes = [c_char_p, c_char_p]
intal_gcd.restype = c_char_p

intal_fibonacci = Intal.intal_fibonacci
intal_fibonacci.argtypes = [c_uint]
intal_fibonacci.restype = c_char_p

intal_factorial = Intal.intal_factorial
intal_factorial.argtypes = [c_uint]
intal_factorial.restype = c_char_p

intal_bincoeff = Intal.intal_bincoeff
intal_bincoeff.argtypes = [c_uint, c_uint]
intal_bincoeff.restype = c_char_p

intal_max = Intal.intal_max
intal_max.argtypes = [c_void_p, c_int]
intal_max.restype = c_int

intal_min = Intal.intal_min
intal_min.argtypes = [c_void_p, c_int]
intal_min.restype = c_int

intal_search = Intal.intal_search
intal_search.argtypes = [c_void_p, c_int, c_char_p]
intal_search.restype = c_int

intal_binsearch = Intal.intal_binsearch
intal_binsearch.argtypes = [c_void_p, c_int, c_char_p]
intal_binsearch.restype = c_int

intal_sort = Intal.intal_sort
intal_sort.argtypes = [c_void_p, c_int]
intal_sort.restype = None

intal_coin_row_problem = Intal.coin_row_problem
intal_coin_row_problem.argtypes = [c_void_p, c_int]
intal_coin_row_problem.restype = c_char_p

def call_intal_add(a, b):
    return intal_add(a.encode("ascii"), b.encode("ascii")).decode("ascii")

def call_intal_compare(a, b):
    return intal_compare(a.encode("ascii"), b.encode("ascii"))

def call_intal_diff(a, b):
    return intal_diff(a.encode("ascii"), b.encode("ascii")).decode("ascii")

def call_intal_multiply(a, b):
    return intal_multiply(a.encode("ascii"), b.encode("ascii")).decode("ascii")

def call_intal_mod(a, b):
    return intal_mod(a.encode("ascii"), b.encode("ascii")).decode("ascii")

def call_intal_pow(a, b):
    return intal_pow(a.encode("ascii"), c_uint(b)).decode("ascii")

def call_intal_gcd(a, b):
    return intal_gcd(a.encode("ascii"), b.encode("ascii")).decode("ascii")

def call_intal_fibonacci(a):
    return intal_fibonacci(c_uint(a)).decode("ascii")

def call_intal_factorial(a):
    return intal_factorial(c_uint(a)).decode("ascii")

def call_intal_bincoeff(a, b):
    return intal_bincoeff(c_uint(a), c_uint(b)).decode("ascii")

def call_intal_max(a):
    n = len(a)
    a = [i.encode("ascii") for i in a]
    arr = (c_char_p * n)(*a)
    return intal_max(arr, c_int(n))

def call_intal_min(a):
    n = len(a)
    a = [i.encode("ascii") for i in a]
    arr = (c_char_p * n)(*a)
    return intal_min(arr, c_int(n))

def call_intal_search(a, key):
    n = len(a)
    a = [i.encode("ascii") for i in a]
    arr = (c_char_p * n)(*a)
    return intal_search(arr, c_int(n), key.encode("ascii"))

def call_intal_binsearch(a, key):
    n = len(a)
    a = [i.encode("ascii") for i in a]
    arr = (c_char_p * n)(*a)
    return intal_binsearch(arr, c_int(n), key.encode("ascii"))

def call_coin_row_problem(a):
    n = len(a)
    a = [i.encode("ascii") for i in a]
    arr = (c_char_p * n)(*a)
    return intal_coin_row_problem(arr, c_int(n)).decode("ascii")

def search(a, key):
    for i in range(len(a)):
        if a[i] == key:
            return i
    return -1

def compare(a, b):
    if (a < b):
        return -1
    elif (a > b):
        return 1
    else:
        return 0

def gcd(a, b):
    if (b == 0):
        return a
    else:
        return gcd(b, a % b)

def fibonacci(n):
    p1 = 0
    p0 = 1
    if (n == 0):
        return p1
    if (n == 1):
        return p0
    for i in range(n):
        tmp = p0 + p1
        p0 = p1
        p1 = tmp
    return p1

def factorial(a):
    if (a == 0):
        return 1
    return a * factorial(a - 1)

def binary_coefficient(n, k):
    C = [[0 for x in range(k+1)] for x in range(n+1)]
    for i in range(n+1):
        for j in range(min(i, k)+1):
            if j == 0 or j == i:
                C[i][j] = 1
            else:
                C[i][j] = C[i-1][j-1] + C[i-1][j]
    return C[n][k]

def coin_row_problem(a):
    n = len(a)
    f = list()
    f.append(0)
    f.append(a[0])
    for i in range(2, n + 1):
        f.append(max(a[i - 1] + f[i - 2], f[i - 1]))
    return f[n]

def test_intal_add(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_add(str(a), str(b))) != a + b):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name, "PASSED!")

def test_intal_compare(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_compare(str(a), str(b))) != compare(a, b)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_diff(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_diff(str(a), str(b))) != abs(a - b)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_multiply(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_multiply(str(a), str(b))) != a * b):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_mod(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_mod(str(a), str(b))) != a % b):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_pow(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_pow(str(a), b)) != a ** b):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_gcd(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        b = randrange(b_range[0], b_range[1])
        if (int(call_intal_gcd(str(a), str(b))) != gcd(a, b)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_fibonacci(a_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        if (int(call_intal_fibonacci(a)) != fibonacci(a)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_factorial(a_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        if (int(call_intal_factorial(a)) != factorial(a)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_bincoeff(a_range, b_range, num_iters):
    fail = False
    for i in range(num_iters):
        a = randrange(a_range[0], a_range[1])
        if a < b_range[0]:
            b_range[0] = a
        b = randrange(b_range[0], a + 1)
        val = int(call_intal_bincoeff(a, b))
        if (val != binary_coefficient(a, b)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_max(a_range, num, num_iters):
    fail = False
    for i in range(num_iters):
        a = []
        for i in range(num):
            a.append(str(randrange(a_range[0], a_range[1])))
        val = int(call_intal_max(a))
        if (int(a[val]) != max([int(i) for i in a])):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_min(a_range, num, num_iters):
    fail = False
    for i in range(num_iters):
        a = []
        for i in range(num):
            a.append(str(randrange(a_range[0], a_range[1])))
        val = int(call_intal_min(a))
        if (int(a[val]) != min([int(i) for i in a])):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_search(a_range, num, num_iters):
    fail = False
    for i in range(num_iters):
        get_key = (randrange(0, 10) % 2) == 0
        a = []
        for i in range(num):
            a.append(str(randrange(a_range[0], a_range[1])))
        if (get_key):
            key = a[randrange(0, num)]
        else:
            key = str(randrange(a_range[0], a_range[1]))
        val = int(call_intal_search(a, key))
        if (val != search(a, key)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_intal_binsearch(a_range, num, num_iters):
    fail = False
    for i in range(num_iters):
        get_key = (randrange(0, 10) % 2) == 0
        a = []
        for i in range(num):
            a.append(str(randrange(a_range[0], a_range[1])))
        if (get_key):
            key = a[randrange(0, num)]
        else:
            key = str(randrange(a_range[0], a_range[1]))
        a = [int(i) for i in a]
        a.sort()
        a = [str(i) for i in a]
        val = int(call_intal_binsearch(a, key))
        if (val != search(a, key)):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

def test_coin_row_problem(a_range, num, num_iters):
    fail = False
    for i in range(num_iters):
        a = []
        for i in range(num):
            a.append(str(randrange(a_range[0], a_range[1])))
        val = int(call_coin_row_problem(a))
        if (val != coin_row_problem([int(i) for i in a])):
            fail = True
            print(sys._getframe().f_code.co_name, "Failed!")
    if (not fail):
        print(sys._getframe().f_code.co_name,"PASSED!")

test_intal_add([10**9, 10**990], [0, 10**990], 100)
test_intal_compare([10**0, 10**1], [10**0, 10**1], 50)
test_intal_compare([10**0, 10**999], [10**0, 10**999], 100)
test_intal_diff([10**9, 10**990], [0, 10**990], 100)
test_intal_multiply([10**9, 10**990], [0, 10**990], 50)
test_intal_mod([10**9, 10**990], [1, 10**10], 5)
test_intal_pow([0, 10**5], [0, 30], 100)
test_intal_pow([0, 10**1], [0, 3000], 100)
test_intal_gcd([10**9, 10**990], [1, 10**9], 10)
test_intal_fibonacci([0, 10**2], 10)
test_intal_factorial([0, 10**2], 10)
test_intal_max([0, 10**295], 50, 50)
test_intal_min([0, 10**295], 50, 50)
test_intal_search([0, 10**990], 100, 50)
test_intal_binsearch([0, 10**990], 100, 50)
test_coin_row_problem([0, 10**295], 50, 50)
test_intal_bincoeff([0, 2*(10**3)], [0, 2*(10**3)], 10)
