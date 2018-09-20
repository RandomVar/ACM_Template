#include<bits/stdc++.h>
using namespace std;
const int maxn=2010;
struct seg{
   double l,r,h;
   int s;
}s[maxn];
int res;
int col[maxn<<2];
double sum[maxn<<2];
double x[maxn<<2];
int cmp(seg a,seg b){
return a.h<b.h;
}
void pushup(int rt,int l,int r){
   if(col[rt]) sum[rt]=x[r+1]-x[l];//[ )
   else if(l==r) sum[rt]=0;
   else sum[rt]=sum[rt<<1]+sum[rt<<1|1];
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

int bfind(double t){
  /*int lb=0,rb=res;
  while(lb<=rb){
    int mid=(lb+rb)/2;
    if(x[mid]>t) rb=mid-1;
    else lb=mid+1;
  }
  return lb;*/
  int lb=-1,ub=res;
  while(ub-lb>1){
    int mid=(lb+ub)/2;
    if(x[mid]>=t) ub=mid;
    else lb=mid;
  }
  return ub;
}

int main(){
    int n;int k=0;
    while(cin>>n&&n){
            k++;
            int cnt=0;
        for(int i=0;i<n;i++){
            double a,b,c,d;
            cin>>a>>b>>c>>d;
            s[cnt]=seg{a,c,b,1};//bottom line
            x[cnt++]=a;
            s[cnt]=seg{a,c,d,-1};//top line
            x[cnt++]=c;
        }
        sort(x,x+cnt);
        sort(s,s+cnt,cmp);
       // int
         res=0;
        for(int i=1;i<cnt;i++){
            if(x[i]!=x[i-1]){
                x[++res]=x[i];
            }
        }
        memset(col,0,sizeof(col));
        memset(sum,0,sizeof(sum));
        double ans=0;
        for(int i=0;i<cnt-1;i++){
            //cout<<1<<endl;
            int l=bfind(s[i].l);
            int r=bfind(s[i].r)-1;
            update(l,r,s[i].s,1,0,res);
            ans+=sum[1]*(s[i+1].h-s[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",k,ans);

    }

}
