####二进制位操作 

+ __builtin_ffs(x) :返回x中最后一个为1的位是从后向前的第几位，从1开始计数

+ __builtin_popcount(x) :x中1的个数。

+ __builtin_ctz(x) :x末尾0的个数。x=0时结果未定义。

+ __builtin_clz(x) :x前导0的个数。x=0时结果未定义。

**上面的x都是unsigned int型的，如果传入signed或者是char型，会被强制转换成unsigned int**

+ __builtin_parity(x) :x中1的个数的奇偶性,返回1为奇。