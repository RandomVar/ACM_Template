#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
const int maxn=1000+5;
int N,M;
int f[maxn];
int judge[maxn];
int depth[maxn];
int gra[maxn][18];
int maxd[maxn][18];
struct Edge
{
    int u,v,d;
    Edge(int from,int to,int cost):u(from),v(to),d(cost){}
    bool operator <(const Edge &a) const
    {
        return d<a.d;
    }
};
vector<Edge> edges;
vector<Edge> G[maxn];
void init()
{
    for(int i=0;i<maxn;i++)
        f[i]=i;
    memset(judge,0,sizeof(judge));
    memset(depth,0,sizeof(depth));
    depth[1]=1;
    edges.clear();
    for(int i=0;i<maxn;i++)
        G[i].clear();
}
int Find(int x)
{
    if(f[x]==x)
        return f[x];
    return f[x]=Find(f[x]);
}
void unit(int x,int y)
{
    x=Find(x);
    y=Find(y);
    if(x==y)
        return ;
    f[x]=y;
}
bool same(int x,int y)
{
    return Find(x)==Find(y);
}
int Kruskal()
{
    sort(edges.begin(),edges.end());
    int res=0;
    for(int i=0;i<edges.size();i++)
    {
        Edge e=edges[i];
        if(!same(e.u,e.v))
        {
            res+=e.d;
            G[e.u].push_back(Edge(e.u,e.v,e.d));
            G[e.v].push_back(Edge(e.v,e.u,e.d));
            judge[i]=1;
            unit(e.u,e.v);
        }
    }
    return res;
}
void dfs(int x,int fa)
{
    for(int i=0;i<G[x].size();i++)
    {
        Edge e=G[x][i];
        if(e.v==fa)
            continue;
        depth[e.v]=depth[x]+1;
        gra[e.v][0]=x;
        maxd[e.v][0]=e.d;
        dfs(e.v,x);
    }
}
void solve()
{
    for(int i=1;(1<<i)<=N;i++)
    {
        for(int u=1;u<=N;u++)
        {
            gra[u][i]=gra[gra[u][i-1]][i-1];
            maxd[u][i]=max(maxd[u][i-1],maxd[gra[u][i-1]][i-1]);
        }
    }
}
int lca(int u,int v)
{
    if(depth[u]<depth[v])
        swap(u,v);
    int d=depth[u]-depth[v];
    for(int i=0;(1<<i)<=d;i++)
    {
        if((1<<i)&d)
            u=gra[u][i];
    }
    if(u==v)
        return u;
    for(int i=(int)log(N);i>=0;i--)
    {
        if(gra[u][i]!=gra[v][i])
            u=gra[u][i],v=gra[v][i];
    }
    return gra[u][0];
}
int qmax(int u,int v)
{
    int tmp=-0x3f3f3f3f;
    for(int i=0;(1<<i)<=N;i++)
    {
        if(depth[gra[u][i]]>=depth[v])
            tmp=max(tmp,maxd[u][i]);
    }
    //cout<<u<<" "<<v<<" "<<tmp<<endl;
    return tmp;
}
int main()
{
    ios::sync_with_stdio(0);
    int T;
    cin>>T;
    while(T--)
    {
        cin>>N>>M;
        int u,v,c;
        init();
        while(M--)
        {
            cin>>u>>v>>c;
            edges.push_back(Edge(u,v,c));
            //edges.push_back(Edge(v,u,c));
        }
        int MST=Kruskal();
        dfs(1,-1);
        solve();
        int ans=0x3f3f3f3f;
        for(int i=0;i<edges.size();i++)
        {
            if(judge[i]==1)
                continue;
            Edge e=edges[i];
            u=e.u,v=e.v,c=e.d;
            int LCA=lca(u,v);
            int maxu=qmax(u,LCA);
            int maxv=qmax(v,LCA);
            ans=min(ans,c-max(maxu,maxv));
        }
        cout<<MST<<" "<<ans+MST<<endl;
    }
    return 0;
}
