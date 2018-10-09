
printf("%04d\n",x);//输出4位,不足则前面填充0

/*c++格式化 long double的输出*/
 long double t1 = (l - t2 * v2) / v1;
cout << fixed << setprecision(10) << t1 << endl;//保留10位小数

for(int i=x;i;i=(i-1)&x) //i二进制中为1的位在x中必定为1，从大到小输出所有符合条件的i
    cout<<i<<endl;