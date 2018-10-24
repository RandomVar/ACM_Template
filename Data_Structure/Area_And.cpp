/*矩形面积并*/
//hdu1542
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
vector<double>v;
int cmp(seg a,seg b){
return a.h<b.h;
}
void pushup(int rt,int l,int r){
   if(col[rt]) sum[rt]=v[r+1]-v[l];//[)
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
int getid(double x)
{
    return lower_bound(v.begin(),v.end(),x)-v.begin();
}
int main(){
    int n;int k=0;
    while(cin>>n&&n){
            k++;
            int cnt=0;
            v.clear();
        for(int i=0;i<n;i++){
            double a,b,c,d;
            cin>>a>>b>>c>>d;
            s[cnt++]=seg{a,c,b,1};//bottom line
            s[cnt++]=seg{a,c,d,-1};//top line
           v.push_back(a);v.push_back(c);
        }
        sort(v.begin(),v.end());v.erase(unique(v.begin(),v.end()),v.end());
        sort(s,s+cnt,cmp);
        res=v.size();
        memset(col,0,sizeof(col));
        memset(sum,0,sizeof(sum));
        double ans=0;
        for(int i=0;i<cnt-1;i++){
            int l=getid(s[i].l);
            int r=getid(s[i].r)-1;
            update(l,r,s[i].s,1,0,res);
            ans+=sum[1]*(s[i+1].h-s[i].h);
        }
        printf("Test case #%d\nTotal explored area: %.2lf\n\n",k,ans);

    }

}
