/*
专用于块状链表计算的rope容器 
平衡树实现，各种操作的复杂度都是O(log n)
*/
//头文件
#include <ext/rope>
using namespace __gnu_cxx;

rope<int> T;

T.push_back(x);//在末尾添加x

T.insert(pos,x);//在pos插入x

T.erase(pos,x);//从pos开始删除x个

T.copy(pos,len,x);//从pos开始到pos+len为止用x代替

T.replace(pos,x);//从pos开始换成x

T.substr(pos,x);//提取pos开始x个

T.at(x)/[x];//访问第x个元素

printf("%d\n",T[i]) //输出T[i]
cout<<T<<endl;//输出T    

/* 2018nowcoder多校3 https://www.nowcoder.com/acm/contest/141/C */
#include <bits/stdc++.h>
#include <ext/rope>//函数头文件
using namespace __gnu_cxx;
using namespace std;
const int maxn=1e5+10;
rope<int> T;
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;u<=n;i++)
     T.push_back(i);
     while(m--)
     {
         int p,s;
         scanf("%d%d",&p,&s);
         p--;
         T=T.substr(p,s)+T.substr(0,p)+T.substr(p+s,n-p-s);
     }
     for(int i=0;i<n;i++)
      printf("%d ",T[i]);
      return 0;
}