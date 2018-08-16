/***dinic算法 HDU - 1532****/
/*复杂度o(n^2*m)*/
struct edge{
 int to,cap;
 int rev;//反向边的序号
};
vector<edge>edges[maxn];
int level[maxn];

void addnode(int u,int v,int cap){
 edges[u].push_back((edge){v,cap,edges[v].size()});
 edges[v].push_back((edge){u,0,edges[u].size()-1});
}
void bfs(int s){
  memset(level,-1,sizeof(level));
  level[s]=0;
  queue<int>que;
  que.push(s);
  while(!que.empty()){
    int u=que.front();que.pop();
  for(int i=0;i<edges[u].size();i++){
    edge e=edges[u][i];
    if(e.cap>0&&level[e.to]==-1){
      level[e.to]=level[u]+1;
      que.push(e.to);}
  }
}
}
int dfs(int u,int t,int f){
  if(u==t) return f;
  for(int i=0;i<edges[u].size();i++){
    edge e=edges[u][i];
    if(level[e.to]==level[u]+1&&e.cap>0){
        int d=dfs(e.to,t,min(f,e.cap));
        if(d>0){
            edges[u][i].cap-=d;
            edges[e.to][e.rev].cap+=d;
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
    while((f=dfs(s,t,INF))>0)
        flow+=f;
    }
    return flow;
 }
