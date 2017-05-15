""" Decimal """
from decimal import Decimal as D, getcontext, FloatOperation
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
    # sin: i, lasts, s, fact, num, sign = 1, 0, x, 1, x, 1
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

""" Datetime """

from datetime import datetime as dt, timedelta as delta
d = dt(2017, 5, 15) # May 15, 2017, Monday
print(d.year, d.month, d.day, d.isoweekday())   # 2017 5 15 1
print(dt.fromordinal(d.toordinal() + 5))        # 2017-05-20
print(d + delta(5))                             # 2017-05-20
print(d + delta(5, 3600))               # 2017-05-20 01:00:00
print(d.replace(year=2018))                     # 2018-05-15

# only for years 1970 - 2038
timestamp = (d - dt(1970, 1, 1)) / delta(seconds=1)
print(timestamp)
print(dt.utcfromtimestamp(timestamp))
print(d.timetuple())

import calendar as cal
print(cal.isleap(2016)) # True
print(cal.leapdays(2000, 2016)) # 4 (leap years in [l, r))
print(cal.weekday(2017, 5, 15) + 1) # 1, Monday
print(cal.monthrange(2016, 2)) # (0, 29), 0 is for Monday
