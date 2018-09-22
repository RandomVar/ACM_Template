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
