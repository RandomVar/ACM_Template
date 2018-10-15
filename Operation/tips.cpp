
printf("%04d\n",x);//输出4位,不足则前面填充0

/*c++格式化 long double的输出*/
 long double t1 = (l - t2 * v2) / v1;
cout << fixed << setprecision(10) << t1 << endl;//保留10位小数

/*枚举真子集*/
for(int i=x;i;i=(i-1)&x)
    cout<<i<<endl;

/*枚举大小为 k 的子集*/
void subset(int k, int n)
{
   int t = (1 << k) - 1;
   while (t < (1 << n))
   {
   // do something
   int x = t & -t, y = t + x;
 t = ((t & ~y) / x >> 1) | y;
  }
}

/**mt19937随机数*/
 unsigned seed=chrono::system_clock::now().time_since_epoch().count();
    mt19937 g1(seed);
    cout<<g1()<<endl;