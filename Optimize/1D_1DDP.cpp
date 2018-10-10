//HDU3507
#include<bits/stdc++.h>
#define pb(x) push_back(x)
#define fir first
#define sec second
#define mem(a,x) memset(a,x,sizeof(a))
#define mpr make_pair
typedef long long ll;
using namespace std;
const int inf=0x3f3f3f3f;
const ll INF= 0x3f3f3f3f3f3f3f3f;
const double pi = acos(-1.0);
const int maxn=500100;
int que[maxn];
ll dp[maxn];
ll sum[maxn];
int n,m;
ll c[maxn];
ll getup(int j,int k)
{
    return dp[j]+sum[j]*sum[j]-(dp[k]+sum[k]*sum[k]);
}
ll getdown(int j,int k)
{
  return 2*(sum[j]-sum[k]);
}
ll getdp(int i,int j)
{
     return dp[j]+m+(sum[i]-sum[j])*(sum[i]-sum[j]);
}
int main(){
    while(scanf("%d%d",&n,&m)==2)
    {
        for(int i=1;i<=n;i++)
          scanf("%lld",&c[i]),sum[i]=sum[i-1]+c[i];
       int s=0;int t=-1;
       sum[0]=dp[0]=0;
       que[++t]=0;
       for(int i=1;i<=n;i++)
       {
           while(s<t&&getup(que[s+1],que[s])<=sum[i]*getdown(que[s+1],que[s]))
             s++;
            dp[i]=getdp(i,que[s]);
            while(s<t&&getup(i,que[t])*getdown(que[t],que[t-1])<=getup(que[t],que[t-1])*getdown(i,que[t]))
               t--;
            que[++t]=i;
       }
       printf("%d\n",dp[n]);
    }
 return 0;
  }
