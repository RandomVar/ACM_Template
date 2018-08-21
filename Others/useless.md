###求不相交的路径数
[lemma](https://en.wikipedia.org/wiki/Lindstr%C3%B6m%E2%80%93Gessel%E2%80%93Viennot_lemma):用来求n个起点到n个终点的不相交路径数

若起点集合 A = {a1, a2} and 终点集合 B = {b1, b2} ,答案即为
$\begin{vmatrix}
f(a1,b1) & f(a1,b2)\\ 
f(a2,b1) & f(a2,b2)
\end{vmatrix}$

f(x, y) 表示x到y的路径数,可用组合数计算。对于每一种相交的情况，它们都对应一种将两个终点反转的情况。
#####相关题目
+ [Turtles (CF348D)](https://codeforces.com/problemset/problem/348/D)
+ [Monotonic Matrix (2018牛客多校第一场A)](https://www.nowcoder.com/acm/contest/139/A)


###约瑟夫环问题
+ o(n)递推：共a个人，每b个去掉一个
```
 for(int i = 2;i <= a;i++)
    result = (result+b) %i;
```
详见[约瑟夫环](https://blog.csdn.net/tingyun_say/article/details/52343897)

###[斐波那契数列](https://www.cnblogs.com/Milkor/p/4734763.html)

