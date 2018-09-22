#include<cstdio>
#include<iostream>
#include<queue>
#include<cmath>
#include<cstring>
#include<algorithm>
//#define ll long long
#define pb(x) push_back(x)
#define fir first
#define sec second
using namespace std;

//freopen("data.in","r",stdin);
//freopen("data.out","w",stdout);
//ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);


const int INF=0x3f3f3f3f;
const int maxn=5010;
struct seg{
   int l,r,h;
   int s;
}s[maxn<<1];
int cn[maxn*3];
unsigned char rnum[maxn*3],lnum[maxn*3];
int col[maxn*3];
int sum[maxn*3];

int cmp(seg a,seg b){
return a.h<b.h;
}
void pushup(int rt,int l,int r){
   if(col[rt]) {sum[rt]=r-l+1;//[ )
                cn[rt]=1;rnum[rt]=lnum[rt]='1';}
   else if(l==r) {sum[rt]=0;cn[rt]=0;rnum[rt]=lnum[rt]='0';}
   else {sum[rt]=sum[rt<<1]+sum[rt<<1|1];
          lnum[rt]=lnum[rt<<1];rnum[rt]=rnum[rt<<1|1];
          cn[rt]=cn[rt<<1]+cn[rt<<1|1]-(rnum[rt<<1]-'0')&&(lnum[rt<<1|1]-'0');
          }
}

void update(int l,int r,int c,int rt,int ll,int rr){//l,r is fresh area
  if(ll>=l&&rr<=r){
    col[rt]+=c;
    pushup(rt,ll,rr);
    return;
  }
  int mid=(ll+rr)/2;
  if(l<=mid) update(l,r,c,rt*2,ll,mid);
  if(r>mid) update(l,r,c,rt*2+1,mid+1,rr);
  pushup(rt,ll,rr);
}


int main(){
    int n;int k=0;
    while(scanf("%d",&n)==1&&n){
            k++;
            int cnt=0;int ll=INF;int rr=-INF;
        for(int i=0;i<n;i++){
            int a,b,c,d;
            scanf("%d%d%d%d",&a,&b,&c,&d);
            //cin>>a>>b>>c>>d;
            s[cnt++]=seg{a,c,b,1};//bottom line

            s[cnt++]=seg{a,c,d,-1};//top line
            ll=min(ll,a);
            rr=max(rr,c);
          //  x[cnt++]=c;
        }
       // sort(x,x+cnt);
        sort(s,s+cnt,cmp);

        memset(col,0,sizeof(col));
        memset(sum,0,sizeof(sum));
        //memset(rnum,'0',sizeof(rnum));
        //memset(lnum,'0',sizeof(lnum));
        memset(cn,0,sizeof(cn));
        for(int i=0;i<maxn*3;i++){
            rnum[i]=lnum[i]='0';
        }
        int ans=0;int pre=0;
        for(int i=0;i<cnt-1;i++){
            update(s[i].l,s[i].r-1,s[i].s,1,ll,rr);
            ans+=abs(sum[1]-pre)+cn[1]*2*(s[i+1].h-s[i].h);
            pre=sum[1];
        }
        ans+=sum[1];
        printf("%d\n",ans);
        //cout<<ans<<endl;
    }
return 0;
}
