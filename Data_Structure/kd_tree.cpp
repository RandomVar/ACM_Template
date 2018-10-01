//求最近点
//hdu5992
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll INF=0x3f3f3f3f3f3f3f3f;
const int maxn=2e5+100;
struct Point
{
    int xy[2];
    int l,r,id;
    int c;
    void read(int i)
    {
        id=i;
        scanf("%d%d%d",&xy[0],&xy[1],&c);
    }
}p[maxn];
Point result;
int cmpw;//标记是哪一维的比较
ll ans;
int cost;
bool cmp(const Point &a,const Point &b)
{
    return a.xy[cmpw]<b.xy[cmpw];
}
int build(int l,int r,int w)
{
    int m=(l+r)/2;cmpw=w;
    nth_element(p+l,p+m,p+1+r,cmp);
    if(l!=m)
      p[m].l=build(l,m-1,!w);
    else p[m].l=0;
   if(r!=m)
     p[m].r=build(m+1,r,!w);
     else p[m].r=0;
     return m;
}
ll dis(ll x,ll y=0)
{
    return x*x+y*y;
}
void  query(int rt,int w,ll x,ll y)
{
    ll tmp=dis(x-p[rt].xy[0],y-p[rt].xy[1]);
    if(cost<p[rt].c)
     tmp=INF;
    if(tmp<ans||(tmp!=INF&&tmp==ans&&p[rt].id<result.id))
     result=p[rt];
    ans=min(ans,tmp);
    if(p[rt].l&&p[rt].r)
    {
        bool flag;ll d;
        if(!w)
        {
            flag=(x<=p[rt].xy[0]);
            d=dis(x-p[rt].xy[0]);
        }
        else
        {
            flag=(y<=p[rt].xy[1]);
            d=dis(y-p[rt].xy[1]);
        }

       query(flag?p[rt].l:p[rt].r,!w,x,y);
       if(d<ans)
         query(flag?p[rt].r:p[rt].l,!w,x,y);
    }
    else if(p[rt].l) query(p[rt].l,!w,x,y);
    else if(p[rt].r) query(p[rt].r,!w,x,y);
    
}
int main()
{
   int t,n,q;
   scanf("%d",&t);
   while(t--)
   {
       scanf("%d%d",&n,&q);
       for(int i=1;i<=n;i++)
         p[i].read(i);
         int rt=build(1,n,0);
        
       for(int i=1;i<=q;i++)
       {
           ans=INF;
           int x,y;
           scanf("%d%d%d",&x,&y,&cost);
           query(rt,0,x,y);
           printf("%d %d %d\n",result.xy[0],result.xy[1],result.c);
       }
   }
}