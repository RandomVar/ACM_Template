#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cctype>
#define MAXBIT 1007
using namespace std;

class BigInt {
private:
    int bit[MAXBIT];
    bool negative;              //负数标志

public:
    BigInt();               //默认构造函数，值为0
    BigInt(int);            //构造函数
    BigInt(const char *);   //构造函数
    BigInt(const BigInt &); //复制构造函数

    //重载赋值运算符
    BigInt& operator=(const BigInt&);
    BigInt& operator=(int);

    //重载算术运算符
    BigInt operator+(const BigInt& ) const;
    BigInt operator+(int           ) const;
    BigInt operator-(const BigInt& ) const;
    BigInt operator-(int           ) const;
    BigInt operator*(const BigInt& ) const;
    BigInt operator*(int           ) const;
    BigInt operator/(int           ) const;
    int    operator%(int           ) const;

    //重载比较运算符
    bool operator>(const BigInt&   ) const;
    bool operator>(int             ) const;
    bool operator>=(const BigInt&  ) const;
    bool operator>=(int            ) const;
    bool operator<(const BigInt&   ) const;
    bool operator<(int             ) const;
    bool operator<=(const BigInt&  ) const;
    bool operator<=(int            ) const;
    bool operator==(const BigInt&  ) const;
    bool operator==(int            ) const;
    bool operator!=(const BigInt&  ) const;
    bool operator!=(int            ) const;

    void print()        const;//输出数值
    bool isZero()       const;//是否为0
    bool isPositive()   const;//是否为正数
    bool isNegative()   const;//是否为负数
    bool nonNegative()  const;//是否为非负数

private:
    BigInt opposite() const;                           //取相反数
    BigInt absoluteAdd(const BigInt&      ) const;     //加上绝对值
    BigInt absoluteMinus(const BigInt&    ) const;     //减去绝对值小于自身的数的绝对值
    bool absoluteEqual(const BigInt&      ) const;     //绝对值等于
    bool absoluteGreater(const BigInt&    ) const;     //绝对值大于
    bool absoluteEqualGreater(const BigInt&)const;     //绝对值大于等于
};

BigInt::BigInt() {
    memset(bit,0,sizeof(bit));
    negative = false;
}

BigInt::BigInt(int n) {
    memset(bit,0,sizeof(bit));
    if(n >= 0) {
        negative = false;
    }
    else {
        negative = true;
        n = -n;
    }
    int pos = 0;
    while(n) {
        bit[pos++] = n%10;
        n /= 10;
    }
}

BigInt::BigInt(const char *s) {
    int len = strlen(s);
    bool valid = true;//符合数字格式
    //判断该字符串是否符合数字格式
    if(len >= 2) {
        if( (s[0] != '+')&&(s[0] != '-')&&(!isdigit(s[0])) ) {
            valid = false;
        }
        for(int i = 1; i < len; i++) {
            if(!isdigit(s[i])) {
                valid = false;
            }
        }
    }
    else if(len == 1) {
        if(!isdigit(s[0])) {
            valid = false;
        }
    }
    //如果字符串长度为0或者不符合数字格式，将BigInt对象初始化为0
    //并且返回主调函数
    if(len==0 || !valid) {
        memset(bit,0,sizeof(bit));
        negative = false;
        return ;
    }

    //如果符合数字格式，则继续执行初始化过程
    int beg = 0, end = len - 1;
    if(s[0] == '+') {
        negative = false;
        beg++;
    }
    else if(s[0] == '-') {
        bool zeroFlag = true;
        for(int i = 1; i < len; i++) {
            if(s[0] != '0') {
                zeroFlag = false;
                break;
            }
        }
        if(zeroFlag) {
            negative = false;
        }
        else {
            negative = true;
        }
        beg++;
    }
    else {
        negative = false;
    }
    memset(bit,0,sizeof(bit));
    for(int i = beg; i <= end; i++) {
        bit[len - 1 - i] = s[i] - '0';
    }
}

BigInt::BigInt(const BigInt& n) {
    memcpy(bit,n.bit,sizeof(bit));
    negative = n.negative;
}

BigInt& BigInt::operator=(const BigInt& n) {
    memcpy(bit,n.bit,sizeof(bit));
    negative = n.negative;
    return *this;
}

BigInt& BigInt::operator=(int n) {
    return *this = BigInt(n);
}

BigInt BigInt::operator+(const BigInt& n) const {
    if(negative == n.negative) {
        return absoluteAdd(n);
    }
    else {
        if(absoluteEqual(n)) {
            return BigInt();
        }
        else if(absoluteEqualGreater(n)) {
            return absoluteMinus(n);
        }
        else {
            return n.absoluteMinus(*this);
        }
    }
}

BigInt BigInt::operator+(int n) const {
    return *this + BigInt(n);
}

BigInt BigInt::operator-(const BigInt& n) const {
    return *this + n.opposite();
}

BigInt BigInt::operator-(int n) const {
    return *this - BigInt(n);
}

BigInt BigInt::operator*(const BigInt& n) const {
    if(isZero() || n.isZero()) {
        return BigInt();
    }
    BigInt bi = BigInt();
    if(negative == n.negative) {
        bi.negative = false;
    }
    else {
        bi.negative = true;
    }
    for(int i = 0; i < MAXBIT; i++) {
        for(int j = 0; j < MAXBIT - i; j++) {
            bi.bit[i + j] += bit[i]*n.bit[j];
        }
    }
    for(int i = 0; i < MAXBIT - 1; i++) {   //进位
        bi.bit[i + 1] += bi.bit[i] / 10;
        bi.bit[i] %= 10;
    }
    return bi;
}

BigInt BigInt::operator*(int n) const {
    return *this * BigInt(n);
}

BigInt BigInt::operator/(int n) const {
    //除以0直接返回0
    if(isZero() || n==0) {
        return BigInt();
    }
    BigInt bi = BigInt();
    if((!negative && n>0) || (negative && n<0)) {
        bi.negative = false;
    }
    else {
        bi.negative = true;
    }
    int div = 0;    //累计除数
    for(int i = MAXBIT - 1; i >= 0; i--) {
        div = div * 10 + bit[i];
        bi.bit[i] = div / n;
        div %= n;
    }
    return bi;
}

int BigInt::operator%(int n) const {
    int mod = 0;    //累计余数
    for(int i = MAXBIT - 1; i >= 0; i--) {
        mod = ((mod * 10) + bit[i]) % n;
    }
    return mod;
}

bool BigInt::operator>(const BigInt& n) const {
    if(!negative && n.negative) {
        return true;
    }
    else if(negative && !n.negative) {
        return false;
    }
    else if(!negative && negative) {
        return absoluteGreater(n);
    }
    else {
        return n.absoluteGreater(*this);
    }
}

bool BigInt::operator>(int n) const {
    return *this > BigInt(n);
}


bool BigInt::operator>=(const BigInt& n) const {
    if(!negative && n.negative) {
        return true;
    }
    else if(negative && !n.negative) {
        return false;
    }
    else if(!negative && !n.negative) {
        return absoluteEqualGreater(n);
    }
    else {
        return n.absoluteEqualGreater(*this);
    }
}

bool BigInt::operator>=(int n) const {
    return *this >= BigInt(n);
}

bool BigInt::operator<(const BigInt& n) const {
    return n > *this;
}

bool BigInt::operator<(int n) const {
    return *this < BigInt(n);
}

bool BigInt::operator<=(const BigInt &n) const {
    return n >= *this;
}

bool BigInt::operator<=(int n) const {
    return *this <= BigInt(n);
}

bool BigInt::operator==(const BigInt& n) const {
    if(negative != negative) {
        return false;
    }
    for(int i = 0; i < MAXBIT; i++) {
        if(bit[i] != n.bit[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::operator==(int n) const {
    return *this == BigInt(n);
}

bool BigInt::operator!=(const BigInt& n) const {
    return !(*this == n);
}

bool BigInt::operator!=(int n) const {
    return *this != BigInt(n);
}

void BigInt::print() const {
    if(negative) {
        printf("-");
    }
    int pos = MAXBIT - 1;
    for(; pos > 0; pos--) {
        if(bit[pos] != 0) {
            break;
        }
    }
    for(int i = pos; i >= 0; i--) {
        printf("%d",bit[i]);
    }
}

bool BigInt::isZero() const {
    bool zeroFlag = true;
    for(int i = 0; i < MAXBIT; i++) {
        if(bit[i] != 0) {
            zeroFlag = false;
            break;
        }
    }
    return zeroFlag;
}

bool BigInt::isPositive() const {
    return !negative && !isZero();
}

bool BigInt::isNegative() const {
    return negative;
}

bool BigInt::nonNegative() const {
    return !negative;
}

BigInt BigInt::opposite() const {
    BigInt n(*this);
    if(!n.isZero()) {
        n.negative = !n.negative;
    }
    return n;
}

BigInt BigInt::absoluteAdd(const BigInt& n) const {
    BigInt bi;
    //这个函数操作的两个对象符号是相同的，所以令返回值的符号等于任一操作数的符号即可
    bi.negative = this->negative;
    int next = 0;   //进位
    for(int i = 0; i < MAXBIT; i++) {
        bi.bit[i] = bit[i] + n.bit[i] + next;
        next = bi.bit[i] / 10;
        bi.bit[i] /= 10;
    }
}

BigInt BigInt::absoluteMinus(const BigInt& n) const {
    //绝对值相减，绝对值大的减去绝对值小的那个
    BigInt bi(*this);
    int borrow;     //借位
    for(int i = MAXBIT - 1; i >= 0; i--) {
        if(bi.bit[i] >= n.bit[i]) {
            bi.bit[i] -= n.bit[i];
        }
        else {
            borrow = i + 1;
            while(bi.bit[borrow] == 0) {
                borrow++;
            }
            bi.bit[borrow]--;
            for(int j = i + 1; j < borrow; j++) {
                bi.bit[j] = 9;
            }
            bi.bit[i] = bi.bit[i] + 10 - n.bit[i];
        }
    }
    return bi;
}

bool BigInt::absoluteEqual(const BigInt& n) const {
    for(int i = 0; i < MAXBIT; i++) {
        if(bit[i] != n.bit[i]) {
            return false;
        }
    }
    return true;
}

bool BigInt::absoluteGreater(const BigInt& n) const {
    for(int i = MAXBIT - 1; i >= 0; i--) {
        if(bit[i] > n.bit[i]) {
            return true;
        }
        else if(bit[i] < n.bit[i]) {
            return false;
        }
    }
    return false;
}

bool BigInt::absoluteEqualGreater(const BigInt& n) const {
    for(int i = MAXBIT - 1; i >= 0; i--) {
        if(bit[i] > n.bit[i]) {
            return true;
        }
        else if(bit[i] < n.bit[i]) {
            return false;
        }
    }
    return true;
}


#endif // BIGINT_H_INCLUDED
