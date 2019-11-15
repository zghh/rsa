#include "integer.h"
#include "const.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define ULL unsigned long long

using namespace std;

BigInteger::BigInteger()
{
    this->flag = 0;
    this->len = 1;
    this->value[0] = 0;
}

BigInteger::BigInteger(const char s[])
{
    if (s[0] == '-')
    {
        this->flag = 1;
        s++;
    }
    else
        this->flag = 0;
    int len = strlen(s);
    if (len == 1 && s[0] == '0')
    {
        this->len = 1;
        this->value[0] = 0;
        return;
    }
    this->len = 0;
    int j = 0;
    UI t = 0;
    for (int i = len - 1; ~i; i--)
    {
        if (s[i] >= 'A' && s[i] <= 'F')
            t |= (UI)(s[i] - 'A' + 10) << (j << 2);
        else if (s[i] >= 'a' && s[i] <= 'f')
            t |= (UI)(s[i] - 'a' + 10) << (j << 2);
        else
            t |= (UI)(s[i] - '0') << (j << 2);
        if ((++j) == (BASE_BIT >> 2))
        {
            this->value[this->len++] = t;
            j = t = 0;
        }
    }
    if (t)
        this->value[this->len++] = t;
}

BigInteger::BigInteger(int a)
{
    if (a == 0)
    {
        this->len = 1;
        this->flag = 0;
        this->value[0] = 0;
        return;
    }
    if (a < 0)
    {
        this->flag = 1;
        a = -a;
    }
    else
        this->flag = 0;
    this->len = 0;
    for (; a > 0;)
    {
        this->value[this->len++] = a & MAX_IN_BIT;
        // a >>= BASE_BIT;
        a = 0;
    }
}

BigInteger::BigInteger(UI a, bool flag)
{
    if (a == 0)
    {
        this->len = 1;
        this->flag = 0;
        this->value[0] = 0;
        return;
    }
    this->flag = flag;
    this->len = 0;
    for (; a > 0;)
    {
        this->value[this->len++] = a & MAX_IN_BIT;
        // a >>= BASE_BIT;
        a = 0;
    }
}

BigInteger::BigInteger(const BigInteger &a)
{
    this->len = a.len;
    this->flag = a.flag;
    for (int i = 0; i < a.len; i++)
        this->value[i] = a.value[i];
}

BigInteger::BigInteger(const char s[], int len)
{
    this->flag = 0;
    this->len = 0;
    int t = BASE_BIT >> 3;
    for (int i = 0; i < len; i += t)
    {
        UI u = 0, v = 1;
        for (int j = i; j < min(i + t, len); j++, v <<= 8)
            u = u | ((UI)(unsigned char)s[j] * v);
        this->value[this->len++] = u;
    }
}

BigInteger::~BigInteger()
{
}

BigInteger &BigInteger::operator=(const BigInteger &a)
{
    this->len = a.len;
    this->flag = a.flag;
    for (int i = 0; i < a.len; i++)
        this->value[i] = a.value[i];
    return *this;
}

BigInteger BigInteger::operator+(const BigInteger &a) const
{
    BigInteger result;
    if (this->flag == a.flag)
    {
        result = Add(*this, a);
        result.flag = this->flag;
        return result;
    }
    if (this->flag)
    {
        BigInteger t = -(*this);
        int c = CompareTo(t, a);
        if (c < 0)
        {
            result = Sub(a, t);
            result.flag = 0;
        }
        else if (c > 0)
        {
            result = Sub(t, a);
            result.flag = 1;
        }
        else
        {
            result = BigInteger((int)0);
        }
        return result;
    }
    else
    {
        BigInteger t = -a;
        int c = CompareTo(t, (*this));
        if (c < 0)
        {
            result = Sub(*this, t);
            result.flag = 0;
        }
        else if (c > 0)
        {
            result = Sub(t, *this);
            result.flag = 1;
        }
        else
        {
            result = BigInteger((int)0);
        }
        return result;
    }
}

BigInteger BigInteger::operator+(const int &a) const
{
    BigInteger result;
    if (this->flag && a < 0 || !this->flag && a >= 0)
    {
        result = Add(*this, a >= 0 ? a : -a);
        result.flag = this->flag;
        return result;
    }
    if (this->flag)
    {
        BigInteger t = -(*this);
        int c = CompareTo(t, a);
        if (c < 0)
        {
            result = Sub(BigInteger(a), t);
            result.flag = 0;
        }
        else if (c > 0)
        {
            result = Sub(t, a);
            result.flag = 1;
        }
        else
        {
            result = BigInteger((int)0);
        }
        return result;
    }
    else
    {
        BigInteger t = BigInteger(-a);
        int c = CompareTo(t, (*this));
        if (c < 0)
        {
            result = Sub(*this, t);
            result.flag = 0;
        }
        else if (c > 0)
        {
            result = Sub(t, *this);
            result.flag = 1;
        }
        else
        {
            result = BigInteger((int)0);
        }
        return result;
    }
}

BigInteger BigInteger::operator-(const BigInteger &a) const
{
    BigInteger result;
    if (this->flag == a.flag)
    {
        if (this->flag)
        {
            int c = CompareTo((*this), a);
            if (c < 0)
            {
                result = Sub(*this, a);
                result.flag = 1;
                return result;
            }
            else if (c > 0)
            {
                result = Sub(a, *this);
                result.flag = 0;
                return result;
            }
            else
            {
                result = BigInteger((int)0);
                return result;
            }
        }
        else
        {
            int c = CompareTo((*this), a);
            if (c < 0)
            {
                result = Sub(a, (*this));
                result.flag = 1;
                return result;
            }
            else if (c > 0)
            {
                result = Sub((*this), a);
                result.flag = 0;
                return result;
            }
            else
            {
                result = BigInteger((int)0);
                return result;
            }
        }
    }
    if (this->flag)
    {
        BigInteger t = -(*this);
        result = Add(a, t);
        result.flag = 1;
        return result;
    }
    else
    {
        BigInteger t = -a;
        result = Add((*this), t);
        result.flag = 0;
        return result;
    }
}

BigInteger BigInteger::operator-(const int &a) const
{
    BigInteger result;
    if (this->flag && a < 0 || !this->flag && a >= 0)
    {
        if (this->flag)
        {
            int c = CompareTo((*this), a);
            if (c < 0)
            {
                result = Sub(*this, -a);
                result.flag = 1;
                return result;
            }
            else if (c > 0)
            {
                result = Sub(BigInteger(-a), *this);
                result.flag = 0;
                return result;
            }
            else
            {
                result = BigInteger((int)0);
                return result;
            }
        }
        else
        {
            int c = CompareTo((*this), a);
            if (c < 0)
            {
                result = Sub(BigInteger(a), (*this));
                result.flag = 1;
                return result;
            }
            else if (c > 0)
            {
                result = Sub((*this), a);
                result.flag = 0;
                return result;
            }
            else
            {
                result = BigInteger((int)0);
                return result;
            }
        }
    }
    if (this->flag)
    {
        BigInteger t = -(*this);
        result = Add(t, a);
        result.flag = 1;
        return result;
    }
    else
    {
        result = Add((*this), -a);
        result.flag = 0;
        return result;
    }
}

BigInteger BigInteger::operator*(const BigInteger &a) const
{
    BigInteger result = Mul((*this), a);
    result.flag = this->flag != a.flag;
    return result;
}

BigInteger BigInteger::operator*(const int &a) const
{
    BigInteger result = Mul((*this), a < 0 ? -a : a);
    result.flag = (this->flag && a > 0 || !this->flag && a < 0);
    return result;
}

BigInteger BigInteger::operator/(const BigInteger &a) const
{
    BigInteger zero((int)0);
    if ((*this) == zero)
    {
        return zero;
    }
    if (a == zero)
    {
        throw "Division by zero condition!";
    }
    BigInteger result = Div((*this), a);
    result.flag = this->flag != a.flag;
    if (result.len == 1 && result.value[0] == 0)
        result.flag = 0;
    return result;
}

BigInteger BigInteger::operator/(const int &a) const
{
    BigInteger zero((int)0L);
    if ((*this) == zero)
    {
        return zero;
    }
    if (a == 0)
    {
        throw "Division by zero condition!";
    }
    BigInteger result = Div((*this), a < 0 ? -a : a);
    result.flag = (this->flag && a > 0 || !this->flag && a < 0);
    if (result.len == 1 && result.value[0] == 0)
        result.flag = 0;
    return result;
}

BigInteger BigInteger::operator%(const BigInteger &a) const
{
    BigInteger zero((int)0);
    if ((*this) == zero)
    {
        return zero;
    }
    if (a == zero)
    {
        throw "Division by zero condition!";
    }
    BigInteger result = Mod((*this), a);
    if (this->flag && result != 0)
        result = Sub(a, result);
    result.flag = 0;
    return result;
}

BigInteger BigInteger::operator%(const int &a) const
{
    BigInteger zero((int)0);
    if ((*this) == zero)
    {
        return zero;
    }
    if (a == 0)
    {
        throw "Division by zero condition!";
    }
    UI q = a < 0 ? -a : a;
    UI mod = Mod((*this), q);
    if (this->flag && mod != 0)
        mod = q - mod;
    BigInteger result(mod, false);
    return result;
}

BigInteger BigInteger::operator<<(const int &a) const
{
    if (a >= BASE_BIT)
    {
        throw "<< too much.";
    }
    BigInteger result = (*this);
    int len = result.len;
    result.value[len] = (result.value[len - 1] >> (BASE_BIT - a));
    for (int i = len - 1; i; i--)
        result.value[i] = ((result.value[i] << a) & MAX_IN_BIT) | (result.value[i - 1] >> (BASE_BIT - a));
    result.value[0] = ((result.value[0] << a) & MAX_IN_BIT);
    while (result.value[len])
        len++;
    result.len = len;
    return result;
}

BigInteger BigInteger::operator>>(const int &a) const
{
    if (a >= BASE_BIT)
    {
        throw "<< too much.";
    }
    BigInteger result = (*this);
    int len = result.len;
    LL t = (1LL << a) - 1;
    for (int i = 0; i < len - 1; i++)
        result.value[i] = (result.value[i] >> a) | ((result.value[i + 1] & t) << (BASE_BIT - a));
    result.value[len - 1] >>= a;
    while (len > 1 && result.value[len - 1] == 0)
        len--;
    result.len = len;
    return result;
}

BigInteger BigInteger::operator-() const
{
    BigInteger result = *this;
    result.flag = !this->flag;
    return result;
}

bool BigInteger::operator<(const BigInteger &a) const
{
    if (this->flag != a.flag)
    {
        if (this->flag)
            return true;
        else
            return false;
    }
    bool result = !this->flag;
    if (this->len < a.len)
        return result;
    if (this->len > a.len)
        return !result;
    for (int i = this->len - 1; ~i; i--)
        if (this->value[i] < a.value[i])
            return result;
        else if (this->value[i] > a.value[i])
            return !result;
    return false;
}

bool BigInteger::operator<(const int &a) const
{
    BigInteger t(a);
    return (*this) < t;
}

bool BigInteger::operator<=(const BigInteger &a) const
{
    if (this->flag != a.flag)
    {
        if (this->flag)
            return true;
        else
            return false;
    }
    bool result = !this->flag;
    if (this->len < a.len)
        return result;
    if (this->len > a.len)
        return !result;
    for (int i = this->len - 1; ~i; i--)
        if (this->value[i] < a.value[i])
            return result;
        else if (this->value[i] > a.value[i])
            return !result;
    return true;
}

bool BigInteger::operator<=(const int &a) const
{
    BigInteger t(a);
    return (*this) <= t;
}

bool BigInteger::operator>(const BigInteger &a) const
{
    if (this->flag != a.flag)
    {
        if (this->flag)
            return false;
        else
            return true;
    }
    bool result = !this->flag;
    if (this->len < a.len)
        return !result;
    if (this->len > a.len)
        return result;
    for (int i = this->len - 1; ~i; i--)
        if (this->value[i] > a.value[i])
            return result;
        else if (this->value[i] < a.value[i])
            return !result;
    return false;
}

bool BigInteger::operator>(const int &a) const
{
    BigInteger t(a);
    return (*this) > t;
}

bool BigInteger::operator>=(const BigInteger &a) const
{
    if (this->flag != a.flag)
    {
        if (this->flag)
            return false;
        else
            return true;
    }
    bool result = !this->flag;
    if (this->len < a.len)
        return !result;
    if (this->len > a.len)
        return result;
    for (int i = this->len - 1; ~i; i--)
        if (this->value[i] > a.value[i])
            return result;
        else if (this->value[i] < a.value[i])
            return !result;
    return true;
}

bool BigInteger::operator>=(const int &a) const
{
    BigInteger t(a);
    return (*this) >= t;
}

bool BigInteger::operator==(const BigInteger &a) const
{
    if (this->len != a.len || this->flag != a.flag)
        return false;
    for (int i = this->len - 1; ~i; i--)
        if (this->value[i] != a.value[i])
            return false;
    return true;
}

bool BigInteger::operator==(const int &a) const
{
    BigInteger t(a);
    return (*this) == t;
}

bool BigInteger::operator!=(const BigInteger &a) const
{
    if (this->len != a.len || this->flag != a.flag)
        return true;
    for (int i = this->len - 1; ~i; i--)
        if (this->value[i] != a.value[i])
            return true;
    return false;
}

bool BigInteger::operator!=(const int &a) const
{
    BigInteger t(a);
    return (*this) != t;
}

void BigInteger::Print() const
{
    if (this->len == 1 && this->value[0] == 0)
    {
        printf("%d\n", 0);
        return;
    }
    if (this->flag)
        printf("-");
    bool flag = false;
    for (int i = this->len - 1; ~i; i--)
        for (int j = (BASE_BIT >> 2) - 1; ~j; j--)
        {
            int t = (this->value[i] >> (j << 2)) & 0xF;
            if (flag)
                printf("%c", OUT[t]);
            else if (!flag && t)
            {
                printf("%c", OUT[t]);
                flag = true;
            }
        }
    printf("\n");
}

void BigInteger::Out(char *s) const
{
    if (this->len == 1 && this->value[0] == 0)
    {
        (*s++) = '0';
        (*s++) = 0;
        return;
    }
    if (this->flag)
        (*s++) = '-';
    bool flag = false;
    for (int i = this->len - 1; ~i; i--)
        for (int j = (BASE_BIT >> 2) - 1; ~j; j--)
        {
            int t = (this->value[i] >> (j << 2)) & 0xF;
            if (flag)
                (*s++) = OUT[t];
            else if (!flag && t)
            {
                (*s++) = OUT[t];
                flag = true;
            }
        }
    (*s++) = 0;
}

BigInteger BigInteger::GenerateRandomInteger() const
{
    if ((*this) <= 1)
        throw "Generate random integer error.";
    BigInteger result;
    int len = this->len;
    bool flag = false;
    for (int i = len - 1; ~i; i--)
        if (!flag)
        {
            int r = rand() % (this->value[i] + 1);
            result.value[i] = r;
            if (r < this->value[i])
                flag = true;
        }
        else
        {
            int r = rand() % BASE;
            result.value[i] = r;
        }
    while (len > 1 && result.value[len - 1] == 0)
        len--;
    result.len = len;
    if (!flag)
        result = result - 1;
    if (result == 0)
        result = result + 1;
    return result;
}

bool BigInteger::IsOdd() const
{
    return this->value[0] & 1L;
}

int BigInteger::GetLength() const
{
    return this->len;
}

void BigInteger::DivideAndRemainder(const BigInteger &a, BigInteger result[]) const
{
    if ((*this) < 0 || a < 0)
        throw "DivideAndRemainder Error.";
    DivideAndRemainder((*this), a, result);
}

void BigInteger::ToString(char result[]) const
{
    int index = 0;
    for (int i = 0; i < this->len; i++)
    {
        UI t = this->value[i];
        for (int j = 0; j < (BASE_BIT >> 3); j++, t >>= 8)
            result[index++] = t & 0xFF;
    }
    result[index++] = 0;
}

void BigInteger::ToHex(char result[]) const
{
    bool flag = false;
    int index = 0;
    for (int i = this->len - 1; ~i; i--)
        for (int j = (BASE_BIT >> 2) - 1; ~j; j--)
        {
            UI t = (this->value[i] >> (j << 2)) & 0xF;
            if (flag)
                result[index++] = OUT[t];
            else if (!flag && t)
            {
                result[index++] = OUT[t];
                flag = true;
            }
        }
    result[index++] = 0;
}

BigInteger BigInteger::Add(const BigInteger &a, const BigInteger &b) const
{
    BigInteger result;
    int len = max(a.len, b.len);
    for (int i = 0; i <= len; i++)
        result.value[i] = 0;
    for (int i = 0; i < len; i++)
    {
        LL t = (LL)(i < a.len ? a.value[i] : 0) + (LL)(i < b.len ? b.value[i] : 0) + result.value[i];
        result.value[i] = t & MAX_IN_BIT;
        result.value[i + 1] = t >> BASE_BIT;
    }
    result.len = result.value[len] > 0 ? len + 1 : len;
    return result;
}

BigInteger BigInteger::Add(const BigInteger &a, const UI &b) const
{
    BigInteger result;
    int len = a.len;
    UI up = b;
    result.value[0] += b;
    for (int i = 0; i < len; i++)
    {
        LL t = (LL)a.value[i] + up;
        result.value[i] = t & MAX_IN_BIT;
        up = t >> BASE_BIT;
    }
    while (up)
    {
        result.value[len++] = up & MAX_IN_BIT;
        // up = up >> BASE_BIT;
        up = 0;
    }
    result.len = len;
    return result;
}

BigInteger BigInteger::Sub(const BigInteger &a, const BigInteger &b) const
{
    BigInteger result;
    int len = a.len;
    UI last = 0;
    for (int i = 0; i < len; i++)
    {
        LL t = (LL)a.value[i] - (LL)(i < b.len ? b.value[i] : 0) - last;
        if (t < 0)
        {
            result.value[i] = t + BASE;
            last = 1;
        }
        else
        {
            result.value[i] = (UI)t;
            last = 0;
        }
    }
    while (len > 1 && result.value[len - 1] == 0)
        len--;
    result.len = len;
    return result;
}

BigInteger BigInteger::Sub(const BigInteger &a, const UI &b) const
{
    BigInteger result;
    int len = a.len;
    UI last = b;
    for (int i = 0; i < len; i++)
    {
        LL t = (LL)a.value[i] - last;
        if (t < 0)
        {
            if (t % BASE == 0)
            {
                result.value[i] = 0;
                last = -t / BASE;
            }
            else
            {
                result.value[i] = t % BASE + BASE;
                last = -t / BASE + 1;
            }
        }
        else
        {
            result.value[i] = (UI)t;
            last = 0;
        }
    }
    while (len > 1 && result.value[len - 1] == 0)
        len--;
    result.len = len;
    return result;
}

BigInteger BigInteger::Mul(const BigInteger &a, const BigInteger &b) const
{
    BigInteger zero((int)0);
    BigInteger one(1);
    if (a == zero || b == zero)
    {
        return zero;
    }
    if (a == one)
    {
        BigInteger result = b;
        return result;
    }
    if (b == one)
    {
        BigInteger result = a;
        return result;
    }
    BigInteger result;
    int len = a.len + b.len;
    for (int i = 0; i <= len; i++)
        result.value[i] = 0;
    for (int i = 0; i < a.len; i++)
    {
        LL up = 0;
        for (int j = 0; j < b.len; j++)
        {
            int w = i + j;
            ULL u = (ULL)a.value[i] * (ULL)b.value[j];
            UI v = u >> BASE_BIT;
            up = up + (LL)(u & MAX_IN_BIT) + result.value[w];
            result.value[w] = up & MAX_IN_BIT;
            up = (up >> BASE_BIT) + v;
        }
        if (up)
            result.value[i + b.len] = up;
    }
    while (len > 1 && result.value[len - 1] == 0)
        len--;
    result.len = len;
    return result;
}

BigInteger BigInteger::Mul(const BigInteger &a, const UI &b) const
{
    BigInteger zero((int)0);
    BigInteger one(1);
    if (a == zero || b == 0)
    {
        return zero;
    }
    if (a == one)
    {
        BigInteger result(b);
        return result;
    }
    if (b == 1)
    {
        BigInteger result = a;
        return result;
    }
    BigInteger result;
    int len = a.len;
    LL up = 0;
    for (int i = 0; i < len; i++)
    {
        ULL u = (ULL)a.value[i] * (ULL)b;
        LL v = u >> BASE_BIT;
        up = up + (LL)(u & MAX_IN_BIT);
        result.value[i] = up & MAX_IN_BIT;
        up = (up >> BASE_BIT) + v;
    }
    while (up)
    {
        result.value[len++] = up & MAX_IN_BIT;
        up >>= BASE_BIT;
    }
    result.len = len;
    return result;
}

BigInteger BigInteger::Div(const BigInteger &a, const BigInteger &b) const
{
    BigInteger result[2];
    DivideAndRemainder(a, b, result);
    return result[0];
}

BigInteger BigInteger::Div(const BigInteger &a, const UI &b) const
{
    BigInteger result;
    UI mod;
    DivideAndRemainder(a, b, result, mod);
    return result;
}

BigInteger BigInteger::Mod(const BigInteger &a, const BigInteger &b) const
{
    BigInteger result[2];
    DivideAndRemainder(a, b, result);
    return result[1];
}

UI BigInteger::Mod(const BigInteger &a, const UI &b) const
{
    BigInteger result;
    UI mod;
    DivideAndRemainder(a, b, result, mod);
    return mod;
}

void BigInteger::DivideAndRemainder(const BigInteger &a, const BigInteger &b, BigInteger result[]) const
{
    if (CompareToWithoutSign(a, b) < 0)
    {
        result[0] = BigInteger((int)0);
        result[1] = a;
        return;
    }
    if (b.len == 1)
    {
        UI mod;
        DivideAndRemainder(a, b.value[0], result[0], mod);
        result[1] = BigInteger(mod, false);
        return;
    }
    BigInteger u, v;
    int len = a.len;
    int n = b.len;
    UI d = 1;
    if (b.value[n - 1] < (BASE >> 1))
    {
        d = BASE / (b.value[n - 1] + 1);
        u = Mul(a, d);
        v = Mul(b, d);
        len = u.len;
        n = v.len;
    }
    else
    {
        u = a;
        v = b;
    }
    BigInteger r((int)0);
    for (int i = len - 1; ~i; i--)
    {
        Append(r, u.value[i]);
        if (CompareToWithoutSign(r, v) < 0)
        {
            result[0].value[i] = 0;
            continue;
        }
        UI x = n < r.len ? r.value[n] : 0, y = n - 1 < r.len ? r.value[n - 1] : 0;
        LL q = ((ULL)x * BASE + y) / v.value[n - 1];
        q = min(q, BASE - 1);

        BigInteger t = Mul(v, q);
        while (CompareToWithoutSign(t, r) > 0)
            q--, t = Sub(t, v);

        result[0].value[i] = q;
        r = Sub(r, t);
    }
    while (len > 1 && result[0].value[len - 1] == 0)
        len--;
    result[0].len = len;

    if (d == 1)
        result[1] = r;
    else
    {
        BigInteger temp;
        UI mod;
        DivideAndRemainder(r, d, temp, mod);
        result[1] = temp;
    }
}

void BigInteger::DivideAndRemainder(const BigInteger &a, const UI &b, BigInteger &result, UI &mod) const
{
    if (CompareToWithoutSign(a, b) < 0)
    {
        result = BigInteger((int)0);
        mod = ToUI(a);
        return;
    }
    int len = a.len;
    ULL r = 0;
    for (int i = len - 1; ~i; i--)
    {
        r = (r << BASE_BIT) | a.value[i];
        LL t = r / b;
        result.value[i] = t;
        r = r - b * t;
    }
    while (len > 1 && result.value[len - 1] == 0)
        len--;
    result.len = len;
    mod = r;
}

void BigInteger::Append(BigInteger &a, const UI &b) const
{
    if (a.len == 1 && a.value[0] == 0)
    {
        a.value[0] = b;
        return;
    }
    int len = a.len;
    for (int i = len; i; i--)
        a.value[i] = a.value[i - 1];
    a.value[0] = b;
    a.len++;
}

UI BigInteger::ToUI(const BigInteger &a) const
{
    // UI result = 0;
    // for (int i = a.len - 1; ~i; i--)
    //     result = (result << BASE_BIT) | a.value[i];
    // return result;
    return a.value[0];
}

int BigInteger::CompareTo(const BigInteger &a, const BigInteger &b) const
{
    if (a.flag != b.flag)
    {
        if (a.flag)
            return -1;
        else
            return 1;
    }
    int result = a.flag ? 1 : -1;
    if (a.len < b.len)
        return result;
    if (a.len > b.len)
        return -result;
    for (int i = a.len - 1; ~i; i--)
        if (a.value[i] < b.value[i])
            return result;
        else if (a.value[i] > b.value[i])
            return -result;
    return 0;
}

int BigInteger::CompareTo(const BigInteger &a, const int &b) const
{
    return CompareTo(a, BigInteger(b));
}

int BigInteger::CompareToWithoutSign(const BigInteger &a, const BigInteger &b) const
{
    if (a.len < b.len)
        return -1;
    if (a.len > b.len)
        return 1;
    for (int i = a.len - 1; ~i; i--)
        if (a.value[i] < b.value[i])
            return -1;
        else if (a.value[i] > b.value[i])
            return 1;
    return 0;
}

int BigInteger::CompareToWithoutSign(const BigInteger &a, const int &b) const
{
    return CompareToWithoutSign(a, BigInteger(b));
}