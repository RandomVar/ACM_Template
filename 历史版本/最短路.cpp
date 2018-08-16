/*����ž��Ѹ�Ϊ��1��ʼ*/
/*****Dijkstra POJ - 2387*****/
/*ע���ظ��ߵ��������*/
int cost[maxn][maxn];
int dis[maxn];
int vis[maxn];
void dij(int x){
  memset(vis,0,sizeof(vis));
  vis[x]=1;
  for(int i=1;i<=n;i++)
    dis[i]=cost[x][i];
  dis[x]=0;
  for(int i=1;i<n;i++){
    int min=INF;int u=-1;
    for(int j=1;j<=n;j++){
        if(!vis[j]&&dis[j]<min) {
            min=dis[j];u=j;
        }
    }
    vis[u]=1;
    for(int j=1;j<=n;j++){
        if(!vis[j]&&cost[u][j]+dis[u]<dis[j])
            dis[j]=cost[u][j]+dis[u];
    }
  }
}

/* Dijkstar �㷨+���Ż� ʹ�����ȶ����Ż������Ӷ� O (E log E) */
const int INF=0x3f3f3f3f;
const int maxn=1110;
int d[maxn];
int n;
typedef pair<int,int>P;
struct node{
	int to;int cost;
};
vector<node>g[maxn];
void dij(){
	memset(d,0x3f,sizeof(d));
	d[1]=0;
	priority_queue< P,vector<P>,greater<P> >que;
	que.push(P(0,1));
	while(!que.empty()){
       P a=que.top();que.pop();
       int u=a.second;
       //if(d[u]<a.first) continue; optimize in cf 938d
	   	for(int j=0;j<g[u].size();j++){
		   node e=g[u][j];
		 if(d[e.to]>e.cost+d[u]) {
		 d[e.to]=e.cost+d[u];que.push(P(d[e.to],e.to));
	   }
	}
}}

/****Bellman-Ford****/
/*��Դ����*/
/*o(n^3)�㷨*/
int dis[maxn];
int cost[maxn][maxn];
void bell(int x){

  for(int i=1;i<=n;i++){
    dis[i]=cost[x][i];
    }
   for(int k=2;k<n;k++){
    for(int i=1;i<=n;i++){
        if(i!=x){
      for(int j=1;j<=n;j++)
        dis[i]=min(dis[i],dis[j]+cost[j][i]);
  }}
}}

/*o(nm)*/
struct edge{
 int s,e,w
}edges[maxm];
int dis[maxn];
void bell(int x){
    for(int i=1;i<=n;i++)
      dis[i]=INF;
    dis[x]=0;
  for(int k=1;k<n;k++){
    for(int i=1;i<=m;i++){
        if(edges[i].w!=INF&&dis[edges[i].e]>dis[edges[i].s]+edges[i].w)
            dis[edges[i].e]=dis[edges[i].s]+edges[i].w;
    }
  }
}

/*���ж����޸�����·*/
/*����1����ڸ�����·*/
struct edge{
 int s,e,w
}edges[maxm];
int dis[maxn];
int bell(int x){
    for(int i=1;i<=n;i++)
      dis[i]=INF;
    dis[x]=0;
  for(int k=1;k<=n;k++){
    for(int i=1;i<=m;i++){
        if(edges[i].w!=INF&&dis[edges[i].e]>dis[edges[i].s]+edges[i].w){
            dis[edges[i].e]=dis[edges[i].s]+edges[i].w;
            if(k==n) return 1;/*����n��ѭ����ʱ��·�����������̣�˵�����ڸ�����·*/
        }
    }
  }
  return 0;
}

/****SPFA****/
/*�����ڸ�����·�򷵻�1*/
struct edge{
  int to,cost;
  edge(int To,int Cost):to(To),cost(Cost){};
};
vector<edge>edges[maxn];
int dis[maxn];
int vis[maxn]//���ÿ�����Ƿ��ڶ�����
int cnt[maxn]//�ж��Ƿ���ڸ�����·;���е���³���n�Σ�����ڸ���
int spfa(int x){
  memset(dis,0x3f,sizeof(dis));
  memset(vis,0,sizeof(vis));
  memset(cnt,0,sizeof(cnt));
  dis[x]=0;
  queue<int>que;
  que.push(x);
  vis[x]=1;cnt[x]=1;
  while(!que.empty()){
    int t=que.top;que.pop();vis[t]=0;
    for(int i=0;i<edges[t].size;i++){
        node e=edges[t][i];
        if(dis[e.to]>dis[t]+e.cost){
            dis[e.to]=dis[t]+e.cost;
          if(!vis[e.to]){
            que.push(e.to);
            vis[e.to]=1;
            if(++cnt[e.to]>n) return 1;
        }
    }
  }
  }
 return 0;}

/****floyd****/
for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
      for(int j=1;j<=n;j++)
        dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
