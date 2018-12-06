/***Dinic算法 HDU - 1532****/
/*复杂度o(n^2*m)*/
/*steal from csl*/
const int maxn = " ";
struct Edge
{
    int from, to, cap, flow;
    Edge(int u, int v, int c, int f)
        : from(u), to(v), cap(c), flow(f) {}
};
struct Dinic
{
    int n, m, s, t;      //结点数，边数（包括反向弧），源点编号和汇点编号
    vector<Edge> edges;  //边表。edge[e]和edge[e^1]互为反向弧
    vector<int> G[maxn]; //邻接表，G[i][j]表示节点i的第j条边在e数组中的序号
    bool vis[maxn];      //BFS使用
    int d[maxn];         //从起点到i的距离
    int cur[maxn];       //当前弧下标
    void init(int n)
    {
        this->n = n;
        for (int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from, int to, int cap)
    {
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
        m = edges.size();
        G[from].push_back(m - 2);
        G[to].push_back(m - 1);
    }
    bool BFS()
    {
        memset(vis, 0, sizeof(vis));
        memset(d, 0, sizeof(d));
        queue<int> q;
        q.push(s);
        d[s] = 0;
        vis[s] = 1;
        while (!q.empty())
        {
            int x = q.front();
            q.pop();
            for (int i = 0; i < G[x].size(); i++)
            {
                Edge& e = edges[G[x][i]];
                if (!vis[e.to] && e.cap > e.flow)
                {
                    vis[e.to] = 1;
                    d[e.to] = d[x] + 1;
                    q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    int DFS(int x, int a)
    {
        if (x == t || a == 0) return a;
        int flow = 0, f;
        for (int& i = cur[x]; i < G[x].size(); i++)
        { //从上次考虑的弧
            Edge& e = edges[G[x][i]];
            if (d[x] + 1 == d[e.to] && (f = DFS(e.to, min(a, e.cap - e.flow))) > 0)
            {
                e.flow += f;
                edges[G[x][i] ^ 1].flow -= f;
                flow += f;
                a -= f;
                if (a == 0) break;
            }
        }
        return flow;
    }
    int Maxflow(int s, int t)
    {
        this->s = s, this->t = t;
        int flow = 0;
        while (BFS())
        {
            memset(cur, 0, sizeof(cur));
            flow += DFS(s, INF);
        }
        return flow;
    }
};


/*ISAP*/
const int maxn= " ";
struct Edge{
	int from,to,cap,flow;
	Edge(int u,int v,int c,int f):from(u),to(v),cap(c),flow(f){}
};
struct ISAP{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int > G[maxn];
	bool vis[maxn];
	int d[maxn],cur[maxn];
	int p[maxn],num[maxn];
	void init(int n)
	{
		this ->n=n;
		for(int i=0;i<=n;i++)
		 	G[i].clear();
		edges.clear();
		memset(d,0x3f3f3f3f,sizeof(d));
	}
	void addedge(int from,int to,int cap)
	{
		edges.push_back(Edge(from,to,cap,0));
		edges.push_back(Edge(to,from,0,0));
		m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	bool BFS()
	{
		memset(vis,false,sizeof(vis));
		queue<int >q;
		q.push(t);
		d[t]=0;
		vis[t]=true;
		while(!q.empty())
		{
			int u=q.front();
			q.pop();
			for(int i=0;i<G[u].size();i++)
			{
				Edge &e=edges[G[u][i]^1];
				if(!vis[e.from]&&e.cap>e.flow)
				{
					vis[e.from]=true;
					d[e.from]=d[u]+1;
					q.push(e.from);
				}
			}
		}
		return vis[s];
	}
	int Augment()
	{
		int flow=inf;
		for(int u=t;u!=s;u=edges[p[u]].from)
		{
			Edge &e=edges[p[u]];
			flow=min(flow,e.cap-e.flow);
		}
		for(int u=t;u!=s;u=edges[p[u]].from)
		{
			edges[p[u]].flow+=flow;
			edges[p[u]^1].flow-=flow;
		}
		return flow;
	} 
	int Maxflow(int s,int t)//cal
	{
		this->s=s;
		this ->t=t;
		int flow=0;
		BFS();
		if(d[s]>=n)
			return 0;
		memset(num,0,sizeof(num));
		for(int i=0;i<n;i++)
			if(d[i]<INF)
				num[d[i]]++;
		int u=s;
		memset(cur,0,sizeof(cur));
		while(d[s]<n)
		{
			if(u==t)
			{
				flow+=Augment();
				u=s;
			}
			int ok=0;
			for(int i=cur[u];i<G[u].size();i++)
			{
				Edge &e=edges[G[u][i]];
				if(e.cap>e.flow && d[u]==d[e.to]+1)
				{
					ok=1;
					p[e.to]=G[u][i];
					cur[u]=i;
					u=e.to;
					break;
				}
			}
			if(!ok)
			{
				int m=n-1;
				for(int i=0;i<G[u].size();i++)
				{
					Edge &e=edges[G[u][i]];
					if(e.cap>e.flow)
						m=min(m,d[e.to]);
				}
				if(--num[d[u]]==0)
					break;
				++num[d[u]=m+1];
				cur[u]=0;
				if(u!=s)
					u=edges[p[u]].from;
			}
		}
		return flow;
	}
};
