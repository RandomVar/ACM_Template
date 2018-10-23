/* Dijkstra POJ - 2387*/
/* 复杂度 O (E log E) */
const int maxn = " ";
typedef pair<int,int> P;
int d[maxn];
int vis[maxn];
int n;
struct node{
	int to;int cost;
};
vector<node>g[maxn];
void dij(int s){
	memset(d,0x3f,sizeof(d));
	memset(vis,0,sizeof(vis));
    d[s]=0;
	priority_queue< P,vector<P>,greater<P> >que;
	que.push(P(0,1));
	while(!que.empty()){
       P a=que.top();que.pop();
       int u=a.second;
       if(vis[u])  continue;
        vis[u]=1; //or if(d[u]<a.first) continue; optimize in cf 938d
	   	for(int j=0;j<g[u].size();j++){
		   node e=g[u][j];
		  if(!vis[e.to]&&d[e.to]>e.cost+d[u]) {
		     d[e.to]=e.cost+d[u];
             que.push(P(d[e.to],e.to));
	      }
	}}
}

/****SPFA****/
/*若存在负环回路则返回1*/

const int maxn = " ";
struct node{
  int to,cost;
  node(int To,int Cost):to(To),cost(Cost){};
};
vector<node>edge[maxn];
int d[maxn];
int vis[maxn];//标记每个点是否在队列里
int cnt[maxn];//判断是否存在负环回路;若有点更新超过n次，则存在负环
int spfa(int x)
{
  memset(d,0x3f,sizeof(d));
  memset(vis,0,sizeof(vis));
  memset(cnt,0,sizeof(cnt));
  d[x]=0;
  queue<int>que;
  que.push(x);
  vis[x]=1;cnt[x]=1;
  while(!que.empty())
  {
    int t=que.front();
    que.pop();
    vis[t]=0;
    for(int i=0;i<edge[t].size;i++){
        node e=edge[t][i];
        if(d[e.to]>d[t]+e.cost){
            d[e.to]=d[t]+e.cost;
          if(!vis[e.to]){
            que.push(e.to);
            vis[e.to]=1;
            if(++cnt[e.to]>n) return 1;
         }}
      }
  }
 return 0;
 }

/****floyd****/
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        d[i][j]=min(d[i][j],d[i][k]+d[k][j]);