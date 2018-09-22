/*第k短路*/
const int MAXM= "" ;
const int MAXN= "" ;
struct node
{
    int v, w, next;
}edge[MAXM], revedge[MAXM];
struct A
{
    ll f, g, v;
    bool operator <(const A a)const {
        if(a.f == f) return a.g < g;
        return a.f < f;
    }
};
int e, vis[MAXN], q[MAXM * 5];
ll d[MAXN];
int head[MAXN], revhead[MAXN];
int n, m, s, t, k;
void init()
{
    e = 0;
    memset(head, -1, sizeof(head));
    memset(revhead, -1, sizeof(revhead));
}
void insert(int x, int y, int w)//插入边
{
    edge[e].v = y;
    edge[e].w = w;
    edge[e].next = head[x];
    head[x] = e;
    revedge[e].v = x;
    revedge[e].w = w;
    revedge[e].next =revhead[y];
    revhead[y] = e++;
}
void spfa(int src)
{
    for(int i = 1; i <= n; i++) d[i] = INF;
    memset(vis, 0, sizeof(vis));
    vis[src] = 0;
    int h = 0, t = 1;
    q[0] = src;
    d[src] = 0;
    while(h < t)
    {
        int u = q[h++];
        vis[u] = 0;
        for(int i = revhead[u] ; i != -1; i = revedge[i].next)
        {
            int v = revedge[i].v;
            int w = revedge[i].w;
            if(d[v] > d[u] + w)
            {
                d[v] = d[u] + w;
                if(!vis[v])
                {
                    q[t++] = v;
                    vis[v] = 1;
                }
            }
        }
    }
}
ll Astar(int src, int des)
{
    int cnt = 0;
    priority_queue<A>Q;
    if(src == des) k++;
    if(d[src] == INF) return -1;
    A t, tt;
    t.v = src, t.g = 0, t.f = t.g + d[src];
    Q.push(t);
    while(!Q.empty())
    {
        tt = Q.top();
        Q.pop();
        if(tt.v == des)
        {
            cnt++;
            if(cnt == k)
                return tt.g;
        }
        for(int i = head[tt.v]; i != -1; i = edge[i].next)
        {
            t.v = edge[i].v;
            t.g = tt.g + edge[i].w;
            t.f = t.g + d[t.v];
            Q.push(t);
        }
    }
    return -1;
}
int main()
{
        init();
        scanf("%d%d%d", &s, &t, &k);
        for(int i = 1; i <= m; i++)
        {
            int x,y,w;
            scanf("%d%d%d", &x, &y, &w);
            insert(x, y, w);
        }
        spfa(t);
        ll ans=Astar(s,t);
    return 0;
}
