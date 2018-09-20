#include<bits/stdc++.h>
using namespace std;
#define lson rt<<1
#define rson rt<<1|1
#define Lson L,mid,lson
#define Rson mid+1,R,rson
const int maxn=1e5+10;
typedef unsigned long long ull;
ull INF=0xffffffffffffffff;
int top[maxn],son[maxn],dep[maxn],f[maxn];
int sz[maxn],key[maxn];
int id[maxn];
vector<int> G[maxn];
int N;
int tot;
ull sum[maxn*4];
ull add[maxn*4];
ull mul[maxn*4];
void pushup(int rt)
{
    sum[rt]=sum[lson]+sum[rson];
}
void pushdown(int rt,int len)
{
    if(add[rt]!=0||mul[rt]!=1)
    {
        add[rt<<1]=(add[rt<<1]*mul[rt]+add[rt]);
        add[rt<<1|1]=(add[rt<<1|1]*mul[rt]+add[rt]);
        mul[rt<<1]=(mul[rt<<1]*mul[rt]);
        mul[rt<<1|1]=(mul[rt<<1|1]*mul[rt]);
        sum[rt<<1]=(add[rt]*(len-(len>>1))+sum[rt<<1]*mul[rt]);
        sum[rt<<1|1]=((add[rt]*(len>>1))+sum[rt<<1|1]*mul[rt]);
        add[rt]=0;
        mul[rt]=1;
    }
}
void init()
{
    memset(son,0,sizeof(son));
    memset(sz,0,sizeof(sz));
    for(int i=0;i<maxn;i++)
        G[i].clear();
    tot=0;
    dep[1]=0;
}
void build(int L,int R,int rt)
{
    add[rt]=0;
    mul[rt]=1;
    if(L==R)
    {
        sum[rt]=0;
        return ;
    }
    int mid=(L+R)>>1;
    build(Lson);
    build(Rson);
    pushup(rt);
}
void dfs1(int u,int fa)
{
    sz[u]=1;
    f[u]=fa;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa)
            continue;
        dep[v]=dep[u]+1;
        dfs1(v,u);
        sz[u]+=sz[v];
        if(son[u]==0||sz[v]>sz[son[u]])
        {
            son[u]=v;
        }
    }
}
void dfs2(int u,int fa)
{
    top[u]=fa;
    id[u]=++tot;
    if(son[u])
        dfs2(son[u],fa);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==f[u])
            continue;
        if(v!=son[u])
            dfs2(v,v);
    }
}
void updateplus(int l,int r,ull val,int L,int R,int rt)
{
    if(l<=L&&r>=R)
    {
        add[rt]+=val;
        sum[rt]+=val*(R-L+1);
        return ;
    }
    pushdown(rt,R-L+1);
    int mid=(L+R)>>1;
    if(l<=mid)
        updateplus(l,r,val,Lson);
    if(r>mid)
        updateplus(l,r,val,Rson);
    pushup(rt);
}
void updatemul(int l,int r,ull val,int L,int R,int rt)
{
    if(l<=L&&r>=R)
    {
        add[rt]*=val;
        mul[rt]*=val;
        sum[rt]*=val;
        return ;
    }
    pushdown(rt,R-L+1);
    int mid=(L+R)>>1;
    if(l<=mid)
        updatemul(l,r,val,Lson);
    if(r>mid)
        updatemul(l,r,val,Rson);
    pushup(rt);
}
void changeadd(int x,int y,ull val)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        updateplus(id[top[x]],id[x],val,1,N,1);
        x=f[top[x]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    updateplus(id[x],id[y],val,1,N,1);
}
void changemul(int x,int y,ull val)
{
    //cout<<x<<" "<<y<<" "<<val<<endl;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        updatemul(id[top[x]],id[x],val,1,N,1);
        x=f[top[x]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    updatemul(id[x],id[y],val,1,N,1);
}
ull query(int l,int r,int L,int R,int rt)
{
    if(l<=L&&r>=R)
    {
        return sum[rt];
    }
    pushdown(rt,R-L+1);
    int mid=(L+R)>>1;
    ull res=0;
    if(l<=mid)
        res+=query(l,r,Lson);
    if(r>mid)
        res+=query(l,r,Rson);
    return res;
}
ull get(int x, int y)
{
    ull res=0;
    while(top[x] != top[y])
    {
        if(dep[top[x]] < dep[top[y]])
            swap(x, y);
        res+=query(id[top[x]],id[x],1,N,1);
        x = f[top[x]];
    }
    if(dep[x] > dep[y])
         swap(x, y);
    res+=query(id[x],id[y],1,N,1);
    return res;
}
