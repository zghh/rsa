#include "common.h"

BigInteger Power(BigInteger a, BigInteger b, BigInteger mod)
{
    BigInteger ans(1);
    BigInteger one(1);
    for (; b > 0;)
    {
        if (b.IsOdd())
        {
            ans = ans * a % mod;
            if (ans == one)
                return ans;
        }
        a = a * a % mod;
        b = b >> 1;
    }
    return ans;
}

BigInteger GCD(BigInteger a, BigInteger b)
{
    for (; b != 0;)
    {
        BigInteger t = a % b;
        a = b;
        b = t;
    }
    return a;
}

void ExGCD(BigInteger a, BigInteger b, BigInteger &x, BigInteger &y)
{
    if (b == 0)
    {
        x = BigInteger(1);
        y = BigInteger((int)0);
        return;
    }
    BigInteger p(1), q((int)0);
    BigInteger result[2];
    x = BigInteger((int)0);
    y = BigInteger(1);
    a.DivideAndRemainder(b, result);
    for (; result[1] > 0;)
    {
        BigInteger m = x, n = y;
        x = p - x * result[0], y = q - y * result[0];
        p = m, q = n;
        a = b, b = result[1];
        a.DivideAndRemainder(b, result);
    }
}