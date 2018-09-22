//CF 600E
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
vector<int> G[maxn];
int v[maxn];
int sz[maxn];
int f[maxn];
int son[maxn];
int vis[maxn];
int cnt[maxn];
typedef long long ll;
ll ans[maxn];
ll sum;
ll mx;
void lh(int u,int fa)
{
    sz[u]=1;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa)
            continue;
        lh(v,u);
        sz[u]+=sz[v];
        if(son[u]==0||sz[v]>sz[son[u]])
        {
            son[u]=v;
        }
    }
}
void add(int u,int fa,int val)
{
    cnt[v[u]]+=val;
    if(cnt[v[u]]>mx)
    {
        sum=v[u],mx=cnt[v[u]];
    }
    else if(cnt[v[u]]==mx)
    {
        sum+=v[u];
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v!=fa&&vis[v]==0)
            add(v,u,val);
    }
}
void dfs(int u,int fa,int flag)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v!=fa&&v!=son[u])
            dfs(v,u,0);
    }
    if(son[u])
        dfs(son[u],u,1),vis[son[u]]=1;
    add(u,fa,1);
    ans[u]=sum;
    if(son[u])
        vis[son[u]]=0;
    if(flag==0)
        add(u,fa,-1),sum=0,mx=-1;
}
int main()
{
    int N;
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
        scanf("%d",&v[i]);
    for(int i=1;i<=N-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    lh(1,0);
    dfs(1,0,1);
    for(int i=1;i<=N;i++)
        printf("%lld ",ans[i]);
    printf("\n");
    //scanf("%d",&N);
    return 0;
}
