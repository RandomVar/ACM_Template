/***Dinic算法 HDU - 1532****/
/*复杂度o(n^2*m)*/
struct E{
 int to,cap;
 int rev;//反向边的序号
};
vector<E>edge[maxn];
int level[maxn];

void addedge(int u,int v,int cap){
 edge[u].push_back((E){v,cap,edge[v].size()});
 edge[v].push_back((E){u,0,edge[u].size()-1});
}
void bfs(int s){
  memset(level,-1,sizeof(level));
  level[s]=0;
  queue<int>que;
  que.push(s);
  while(!que.empty()){
    int u=que.front();que.pop();
  for(int i=0;i<edge[u].size();i++){
    E e=edge[u][i];
    if(e.cap>0&&level[e.to]==-1){
      level[e.to]=level[u]+1;
      que.push(e.to);}
  }
}
}
int dfs(int u,int t,int f){
  if(u==t) return f;
  for(int i=0;i<edge[u].size();i++){
    E e=edge[u][i];
    if(level[e.to]==level[u]+1&&e.cap>0){
        int d=dfs(e.to,t,min(f,e.cap));
        if(d>0){
            edge[u][i].cap-=d;
            edge[e.to][e.rev].cap+=d;
            return d;
        }
    }
  }
  return 0;
}

int max_flow(int s,int t){
   int flow=0;
 while(1){
    bfs(s);
    if(level[t]<0) return flow;
    int f;
    while((f=dfs(s,t,inf))>0)
        flow+=f;
    }
    return flow;
 }


/*ISAP*/
/*steal from csl*/
const int maxn = " ";
struct Edge
{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f)
        : from(u), to(v), cap(c), flow(f) {}
};
struct ISAP
{
    int n, m, s, t;      //结点数，边数（包括反向弧），源点编号和汇点编号
    vector<Edge> edges;  //边表。edges[e]和edges[e^1]互为反向弧
    vector<int> G[maxn]; //邻接表，G[i][j]表示结点i的第j条边在e数组中的序号
    bool vis[maxn];      //BFS使用
    int d[maxn];         //起点到i的距离
    int cur[maxn];       //当前弧下标
    int p[maxn];         //可增广路上的一条弧
    int num[maxn];       //距离标号计数
    void init(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cap)
    {
        edges.pb(Edge(from, to, cap, 0));
        edges.pb(Edge(to, from, 0, 0));
        int m = edges.size();
        G[from].pb(m - 2);
        G[to].pb(m - 1);
    }
    int Augumemt()
    {
        int x = t, a = inf;
        while (x != s)
        {
            Edge& e = edges[p[x]];
            a = min(a, e.cap - e.flow);
            x = edges[p[x]].from;
        }
        x = t;
        while (x != s)
        {
            edges[p[x]].flow += a;
            edges[p[x] ^ 1].flow -= a;
            x = edges[p[x]].from;
        }
        return a;
    }
    void BFS()
    {
        mem(vis, 0);
        mem(d, 0);
        queue<int> q;
        q.push(t);
        d[t] = 0;
        vis[t] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            int len = G[x].size();
            for (int i = 0; i < len; i++)
            {
                Edge& e = edges[G[x][i]];
                if (!vis[e.from] && e.cap > e.flow)
                {
                    vis[e.from] = 1;
                    d[e.from] = d[x] + 1;
                    q.push(e.from);
                }
            }
        }
    }
    int Maxflow(int s, int t)
    {
        this->s = s;
        this->t = t;
        int flow = 0;
        BFS();
        mem(num, 0);
        for (int i = 0; i < n; i++)
            if (d[i] < inf) num[d[i]]++;
        int x = s;
        mem(cur, 0);
        while (d[s] < n)
        {
            if (x == t)
            {
                flow += Augumemt();
                x = s;
            }
            int ok = 0;
            for (int i = cur[x]; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]];
                if (e.cap > e.flow && d[x] == d[e.to] + 1)
                {
                    ok = 1;
                    p[e.to] = G[x][i];
                    cur[x] = i;
                    x = e.to;
                    break;
                }
            }
            if (!ok) //Retreat
            {
                int m = n - 1;
                for (int i = 0; i < G[x].size(); i++)
                {
                    Edge& e = edges[G[x][i]];
                    if (e.cap > e.flow) m = min(m, d[e.to]);
                }
                if (--num[d[x]] == 0) break; //gap优化
                num[d[x] = m + 1]++;
                cur[x] = 0;
                if (x != s) x = edges[p[x]].from;
            }
        }
        return flow;
    }
};