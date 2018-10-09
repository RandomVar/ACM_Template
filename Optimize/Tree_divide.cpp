/*树上点分治*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e4+5;
struct Edge
{
    int to,cost;
};
vector<Edge> G[maxn];
int N,K,root;
int vis[maxn];
int sz[maxn],maxson[maxn];
int dep[maxn];
int total;
ll ans;
vector<int> deep;
void getroot(int u,int fa)
{
    sz[u]=1,maxson[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i].to;
        if(v==fa||vis[v])
            continue;
        getroot(v,u);
        sz[u]+=sz[v];
        maxson[u]=max(maxson[u],sz[v]);
    }
    maxson[u]=max(maxson[u],total-sz[u]);
    if(maxson[u]<maxson[root])
        root=u;
}
void getdeep(int u,int fa)
{
    deep.push_back(dep[u]);
    sz[u]=1;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i].to;
        if(v==fa||vis[v])
            continue;
        dep[v]=dep[u]+G[u][i].cost;
        getdeep(v,u);
        sz[u]+=sz[v];
    }
}
ll cal(int u,ll init)
{
    deep.clear();
    dep[u]=init;
    getdeep(u,0);
    sort(deep.begin(),deep.end());
    ll res=0;
    for(int l=0,r=deep.size()-1;l<r;)
    {
        if(deep[l]+deep[r]<=K)
        {
            res+=r-l;
            l++;
        }
        else
            r--;
    }
    return res;
}
void solve(int u)
{
    ans+=cal(u,0);
    vis[u]=1;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i].to;
        if(!vis[v])
        {
            ans-=cal(v,G[u][i].cost);
            maxson[0]=total=sz[v];
            getroot(v,root=0);
            solve(root);
        }
    }
}
int main()
{
    while(scanf("%d%d",&N,&K)!=EOF,N+K)
    {
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=N;i++)
            G[i].clear();
        for(int i=1;i<=N-1;i++)
        {
            int u,v,c;
            scanf("%d%d%d",&u,&v,&c);
            G[u].push_back({v,c});
            G[v].push_back({u,c});
        }
        root=0;
        maxson[root]=N;
        getroot(1,root);
        ans=0;
        solve(root);
        printf("%lld\n",ans);
    }
    return 0;
}