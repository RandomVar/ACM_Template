/****最小生成树Kruskal poj2421****/
/*时间复杂度取决于边数 o(E logE)*/
const int maxm=" ";
const int maxn=" ";

struct node{
  int u,v,w;
  bool operator<(const node &b)const{
      return w<b.w;
  }
}edge[maxm];
int p[maxn];
void init(int n)
{
    for(int i=0; i<=n; i++)
        p[i]=i;
}
int Find(int x)
{
    if(x==p[x])
        return p[x];
    int y=Find(p[x]);
    return p[x]=y;
}

int Union(int x,int y)
{
    int x1=Find(x);
    int y1=Find(y);
    if(x1==y1)
        return 0;
    p[x1]=y1;
      return 1;
}

void kruskal(int n,int m)
{
  int sum=0;//生成树的总权值
  int num=0;//已选用的边的数目
  init(n);
  sort(edge,edge+m);
  for(int i=0;i<m;i++)
  {
    int u=edge[i].u;
    int v=edge[i].v;
    int w=edge[i].w;
    if(Find(u)!=Find(v)) {
        Union(u,v);
        num++;sum+=w;
      }
  if(num==n-1) break;
  }  
}

/*****最小生成树Prim *****/
/*时间复杂度取决于顶点数 O(V^2)*/
const int maxn = " ";
int cost[maxn][maxn];
int lowc[maxn];
int prim(int n){
  for(int i=2;i<=n;i++)
    lowc[i]=cost[0][i];
  lowc[1]=-1;//tag visited
  int sum=0;
  for(int i=1;i<n;i++){
      int min=inf;
      int u;
     for(int j=1;j<=n;j++){
        if(lowc[j]!=-1&&lowc[j]<min){
            min=lowc[j];u=j;
        }
       }
    if(min==inf) return -1;
    lowc[u]=-1;
    sum+=min;

  for(int j=1;j<=n;j++){
    if(lowc[j]!=-1&&lowc[j]>cost[u][j])
        lowc[j]=cost[u][j];
   }
  }
  return sum;
}


