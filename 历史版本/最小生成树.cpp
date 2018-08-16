

/***���鼯****/
void init(){
  for(int i=1;i<=n;i++)
    p[i]=i;/*���ڵ��ʼ��Ϊ�Լ�*/
}
int find(int x){
 return x==p[x]?x:find(p[x]);
}
void unin(int x,int y){
  x=find(x);y=find(y);
  if(x!=y) p[x]=y;
}

/****��С������Kruskal poj2421****/
/*ʱ�临�Ӷ�ȡ���ڱ���*/
#define maxm 55//������
#define maxn 11//��ඥ����
struct edge{
  int u,v,w;
}edges[maxm];
int p[maxn];
int n,m;
void init(){
  for(int i=1;i<=n;i++)
    p[i]=i;
}
int find(int x){
 return x==p[x]?x:find(p[x]);
}
void unin(int x,int y){
  x=find(x);y=find(y);
  if(x!=y) p[x]=y;
}
int cmp(edge a,edge b){
 return a.w<b.w;
}
void kruskal(){
  int sumweight=0;//����������Ȩֵ
  int num=0;//��ѡ�õıߵ���Ŀ
  init();//��ʼ��
  sort(edges,edges+m,cmp);
  for(int i=0;i<m;i++){
        int u=edges[i].u;int v=edges[i].v;int w=edges[i].w;
    if(find(u)!=find(v)) {
        unin(u,v);num++;sumweight+=w;
  }
  if(num==n-1) break;
}
}

/*****��С������Prim *****/
/*ʱ�临�Ӷ�ȡ���ڶ�����*/
int cost[maxn][maxn];
int lowcost[maxn];
int prim(){
  for(int i=2;i<=n;i++)
    lowcost[i]=cost[0][i];
  lowcost[1]=-1;
  int sum=0;
  for(int i=1;i<n;i++){
        int min=INF;int u;
    for(int j=1;j<=n;j++){
        if(lowcost[j]!=-1&&lowcost[j]<min){
            min=lowcost[j];u=j;
        }}
    if(min==INF) return -1;
    lowcost[u]=-1;
    sum+=min;

  for(int j=1;j<=n;j++){
    if(lowcost[j]!=-1&&lowcost[j]>cost[u][j]){
        lowcost[j]=cost[u][j];
    }
  }
  }
  return sum;
}

