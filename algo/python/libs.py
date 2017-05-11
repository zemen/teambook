""" Decimal """
from decimal import Decimal as D
from decimal import getcontext
from decimal import FloatOperation
from decimal import ROUND_DOWN
getcontext().prec = 50
getcontext().traps[FloatOperation] = True
#getcontext().rounding = ROUND_05UP

a = D('3.14') # Correct
#a = D(3.14)  # Wrong!
print(a ** D('0.123'))
print(a % D('1.5'))
print(D(2).sqrt())
print(D(1).exp())
print(D('10').ln())
print(D('10').log10())
print(D('3.15').quantize(D('0.1'))) # 3.2
print(D('3.15').quantize(D('0.1'), rounding=ROUND_DOWN)) # 3.1
print()

def pi():
    """Compute Pi to the current precision. """
    getcontext().prec += 2 # extra digits for intermediate steps
    three = D(3)     # substitute "three=3.0" for regular floats
    lasts, t, s, n, na, d, da = 0, three, 3, 1, 0, 0, 24
    while s != lasts:
        lasts = s
        n, na = n+na, na+8
        d, da = d+da, da+32
        t = (t * n) / d
        s += t
    getcontext().prec -= 2
    return +s             # unary plus applies the new precision

def cos(x):
    """Return the cosine of x as measured in radians.
    The Taylor series approximation works best for a small x.
    For larger values, first compute x = x % (2 * pi). """
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 0, 0, 1, 1, 1, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

def sin(x):
    """Return the sine of x as measured in radians.
    The Taylor series approximation works best for a small x.
    For larger values, first compute x = x % (2 * pi). """
    getcontext().prec += 2
    i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
    while s != lasts:
        lasts = s
        i += 2
        fact *= i * (i-1)
        num *= x * x
        sign *= -1
        s += num / fact * sign
    getcontext().prec -= 2
    return +s

""" Fraction """

from fractions import Fraction as F
from math import pi
print(F(16, -10)) # -8/5
print(F(123)) # 123
print(F('-.125')) # -1/8
print(F(pi).limit_denominator(30)) # 22/7
print(F(1, 2) ** 31) # 1/2147483648
