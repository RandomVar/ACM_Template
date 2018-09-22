/* 区间不同数 */
/*主席树*/
#include<bits/stdc++.h>
using namespace std;
const int maxn=2*1e5+100;
int data[maxn];
int a[maxn];
int ans[maxn];
map<int,int>mp;
void init()
{
    for(int i=0;i<maxn;i++)
      data[i]=0;
    mp.clear();
}
struct node{
    int l,r,id;
    bool operator<(const node &t)const{
        return l<t.l;
    }
}q[maxn];
int sum(int i){
    int ans=0;
    while(i>0){
        ans+=data[i];
        i-=i&-i;
    }
    return ans;
}
void add(int i,int x){
    while(i<maxn){
        data[i]+=x;
        i+=i&-i;
    }
}

int main()
{
   // ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
   int n,Q;
   while(scanf("%d%d",&n,&Q)==2)
   {
       init();
       for(int i=1;i<=n;i++)
         scanf("%d",&a[i]),a[i+n]=a[i];

      for(int i=1;i<=Q;i++)
      {
          scanf("%d%d",&q[i].l,&q[i].r);
        q[i].l=q[i].l+n;
        q[i].id=i;
      }

      sort(q+1,q+1+Q);
      int pre=1;
     for(int i=1;i<=Q;i++)
     {
         for(int j=pre;j<=q[i].l;j++)
         {
             if(mp[a[j]])
             {
                 add(mp[a[j]],-1);
             }
             add(j,1);
             mp[a[j]]=j;
         }
         pre=q[i].l+1;

        ans[q[i].id]=sum(q[i].l)-sum(q[i].r-1);
     }

     for(int i=1;i<=Q;i++)
       printf("%d\n",ans[i]);
       //cout<<ans[i]<<endl;
   }
}
/*
树状数组

*/
#include<cstdio>
#include<iostream>
#include<queue>
#include<stack>
#include<cmath>
#include<cstring>
#include<string>
#include<map>
#include<sstream>
#include<algorithm>
#define pb(x) push_back(x)
#define fir first
#define sec second
#define mem(a,x) memset(a,x,sizeof(a))
typedef long long ll;
using namespace std;
const int inf=0x3f3f3f3f;
const ll INF= 0x3f3f3f3f3f3f3f3f;
/*
 #ifndef ONLINE_JUDGE
    freopen("data.in","r",stdin);
     freopen("data.out","w",stdout);
    #endif
*/
const int maxn=2*1e5+100;
int n,m,cnt;
int root[maxn],a[maxn];
int x,y,k;
map<int,int>mp;
struct node{
  int l,r,sum;
}T[maxn*40];
void init()
{
    cnt=0;
    mp.clear();
    root[0]=0;
    T[0].l = T[0].r = T[0].sum = 0;
}

void update(int l,int r,int &x,int y,int pos,int val){
  T[++cnt]=T[y];
  T[cnt].sum+=val;
  x=cnt;
  if(l==r) return ;
  int mid=(l+r)/2;
  if(mid>=pos) update(l,mid,T[x].l,T[y].l,pos,val);
  else update(mid+1,r,T[x].r,T[y].r,pos,val);

}

int query(int l,int r,int pos,int y){
  if(l==r) return T[y].sum;
  int mid=(l+r)/2;
  if(pos <= mid)
        return query(l,mid,pos,T[y].l) + T[T[y].r].sum;
  else
      return query(mid+1,r,pos, T[y].r);
}

int main(){
   //ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int q;
    while(scanf("%d%d",&n,&q)==2)
    {
        init();
        for(int i=1;i<=n;i++)
          scanf("%d",&a[i]),a[i+n]=a[i];
         int m=n;
         n*=2;
         int tmp;
         for(int i=1;i<=n;i++){
           if(mp[a[i]]==0){
             update(1,n,root[i],root[i-1],i,1);
            mp[a[i]]=i;
           }
           else{
               update(1,n,tmp,root[i-1],mp[a[i]],-1);
               update(1,n,root[i],tmp,i,1);
                mp[a[i]]=i;
         }
         }

        for(int i=1;i<=q;i++)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            l+=m;
            printf("%d\n",query(1,n,r,root[l]));
        }
    }

 return 0;
  }
