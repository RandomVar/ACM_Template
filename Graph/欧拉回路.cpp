#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+10;
struct edge
{
    int to;
    int id;
    edge(){}
    edge(int to,int id):to(to),id(id){}
};
int top;
vector<edge> G[maxn];
vector<int> J[maxn],ans[maxn];
int N,M;
int tot;
int cnt;
int s[maxn*5];
int vis[maxn*5];
int deg[maxn];
int f[maxn];
int Find(int x)
{
    if(f[x]==x)
        return f[x];
    return f[x]=Find(f[x]);
}
void dfs(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        edge e=G[u][i];
        if(vis[e.id>>1])
            continue;
        vis[e.id>>1]=1;
        dfs(e.to);
        if(e.id%2==1)
            s[++top]=(-(e.id>>1));
        else
            s[++top]=(e.id>>1);
    }
}
void init()
{
    for(int i=0;i<maxn;i++)
    {
        f[i]=i;
        G[i].clear();
        J[i].clear();
        ans[i].clear();
    }
    memset(vis,0,sizeof(vis));
    memset(deg,0,sizeof(deg));
}
int main()
{
    //freopen("1003.in","r",stdin);
    while(scanf("%d%d",&N,&M)!=EOF)
    {
        init();
        tot=1;
        for(int i=1;i<=M;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(edge(v,++tot));
            G[v].push_back(edge(u,++tot));
            deg[u]++;
            deg[v]++;
            f[Find(u)]=Find(v);
        }
        for(int i=1;i<=N;i++)
        {
            if(deg[i]%2==1)
                J[Find(i)].push_back(i);
        }
        cnt=0;
        for(int i=1;i<=N;i++)
        {
            if(f[i]==i)
            {
                if(!J[i].size())
                {
                    top=0;
                    dfs(i);
                    cnt++;
                    while(top)
                    {
                        ans[cnt].push_back(s[top--]);
                    }
                }
                else
                {
                    top=0;
                    for(int j=0;j<J[i].size();j+=2)
                    {
                        int u=J[i][j],v=J[i][j+1];
                        G[u].push_back(edge(v,++tot));
                        G[v].push_back(edge(u,++tot));
                    }
                    dfs(i);
                    vector<int> pos;
                    for(int i=top;i;i--)
                    {
                        if(s[i]>M||s[i]<-M)
                            pos.push_back(i);
                    }
                    for(int i=0;i<pos.size()-1;i++)
                    {
                        cnt++;
                        for(int j=pos[i]-1;j>pos[i+1];j--)
                            ans[cnt].push_back(s[j]);
                    }
                    cnt++;
                    for(int j=pos[pos.size()-1]-1;j;j--)
                        ans[cnt].push_back(s[j]);
                    for(int j=top;j>pos[0];j--)
                        ans[cnt].push_back(s[j]);
                }
            }
        }
        int k=cnt;
        for(int i=1;i<=cnt;i++)
            if(ans[i].size()==0)
                k--;
        printf("%d\n",k);
        for(int i=1;i<=cnt;i++)
        {
            if(ans[i].size()!=0)
            {
                printf("%d",ans[i].size());
                for(int j=0;j<ans[i].size();j++)
                    printf(" %d",ans[i][j]);
                printf("\n");
            }
        }
    }
    return 0;
}
