/**求割点*/
vector<int>edge[maxn];
int low[maxn],dfn[maxn],tot;
bool iscut[maxn];//判断是不是割点
void init(){
    for(int i = 1; i <= n; i++)
        edge[i].clear();
        mem(low);
        mem(dfn);
        mem(iscut);
        tot = 0;
}
void dfs(int u,int fa){
    low[u] = dfn[u] = ++tot;
    int child=0;
    for(int i = 0; i < edge[u].size(); i++){
        int v = edge[u][i];
        if(!dfn[v]){
            dfs(v,u);
            child++;
            low[u] = min(low[u],low[v]);
            if(low[v] >= dfn[u])
                iscut[u] = true;
        }
        else if(v != fa){
            low[u] = min(low[u],dfn[v]);
        }
    }
    if(fa<0&&child == 1) iscut[u] = 0;
}

/****Tarjan求割点****/
/*int edge[1010][1010];
int vis[1010];
int n;int tdfn;
int son;//根结点的子女结点个数，son>=2表示根结点为割点
int dfn[1010];//结点dfs的编号
int low[1010];//每个结点最低能回到哪里
int subn[1010];//记录去掉某个节点后的连通分量数（需再+1），若为0，则表示不是割点
void dfs(int u){
 for(int v=1;v<=n;v++){
    if(edge[u][v]){
        if(!vis[v]){
            vis[v]=1;
            tdfn++;dfn[v]=low[v]=tdfn;
            dfs(v);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                if(u!=1) subn[u]++;
                if(u==1) son++;
            }
        }
        else low[u]=min(low[u],dfn[v]);
    }
 }
}
void init(){
 memset(vis,0,sizeof(vis));
 low[1]=dfn[1]=1;
 tdfn=1;son=0;
 vis[1]=1;
 memset(subn,0,sizeof(subn));
}
*/

/*强连通分量*/
/* Tarjan算法  * 复杂度O(N+M)*/
/*边双连通分量加一个!=pre即可*/
vector<int>edge[maxn];
stack<int>st;
int low[maxn],dfn[maxn];
int instack[maxn];
int tot;
int scc;//强连通分量个数
int belong[maxn];//记录每个点属于哪个连通分量
void init(){
 mem(dfn,0);
 mem(low,0);
 mem(instack,0);
 for(int i=0;i<maxn;i++)
    edge[i].clear();
 while(!st.empty())
    st.pop();
 tot=scc=0;
}

void tar(int u){
  dfn[u]=low[u]=++tot;
  st.push(u);
  instack[u]=1;
  for(int i=0;i<edge[u].size();i++){
     int v=edge[u][i];
     if(!dfn[v]){
        tar(v);
        if(low[u]>low[v])
            low[u]=low[v];
        }
     else if(instack[v]&&low[u]>dfn[v])
        low[u]=dfn[v];
        }
     if(low[u]==dfn[u]) {
        int v;
         scc++;
         do{
            v=st.top();
            st.pop();
            belong[v]=scc;
            instack[v]=0;
           }while(v!=u);
      }
     }

/**kangbin版*/
/*
const int MAXN = 10010;//点数
const int MAXM = 100010;//边数
struct Edge {
    int to,next;
}edge[MAXM];

int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN];
int Belong[MAXN];//属于哪个连通分量,Belong数组的值是1~scc
int Index,top;
int scc;//强连通分量的个数S
bool Instack[MAXN]; int num[MAXN];//各个强连通分量包含点的个数，数组编号1~scc //num数组不一定需要，结合实际情况

void addedge(int u,int v) {
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
    }

void Tarjan(int u) {
    int v;
    Low[u] = DFN[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    for(int i = head[u];i != -1;i = edge[i].next)  {
            v = edge[i].to;
     if(!DFN[v]){ //如果这个点未被访问过
            Tarjan(v);
    if( Low[u] > Low[v] )
        Low[u] = Low[v];   }
    else if(Instack[v] && Low[u] > DFN[v])//如果这个点在栈中
        Low[u] = DFN[v];
        }
    if(Low[u] == DFN[u]) {//如果节点u是强连通分量的根
            scc++;
    do   {
        v = Stack[--top];
        Instack[v] = false;
        Belong[v] = scc;
        num[scc]++;
        }while( v != u);  }
        }

void solve(int N) {
    memset(DFN,0,sizeof(DFN));
    memset(Instack,false,sizeof(Instack));
    memset(num,0,sizeof(num));
    Index = scc = top = 0;
    for(int i = 1;i <= N;i++)
        if(!DFN[i])
        Tarjan(i); }

void init() {
    tot = 0;  memset(head,-1,sizeof(head)); }
*/

/**倍增lca*/
const int maxn=40010;
struct node{
  int t,val;
};
int n;
int fa[maxn][40];
int deep[maxn],d[maxn];
vector<node>edge[maxn];
int cnt;
void addedge(int u,int v,int val){
//  e.pb(node{u,v,val});
  edge[u].push_back(node{v,val});
  edge[v].push_back(node{u,val});
}
void dfs(int u,int pre){
  for(int i=0;i<edge[u].size();i++){
    int v=edge[u][i].t;
    if(v==pre) continue;
    fa[v][0]=u;//should give fa[v][0] value
    d[v]=d[u]+edge[u][i].val;
    deep[v]=deep[u]+1;
    dfs(v,u);
  }
}

void bz(){
 for(int j=1;j<=30;j++)
    for(int i=1;i<=n;i++)
      fa[i][j]=fa[fa[i][j-1]][j-1];
}

int lca(int u,int v){
  if(deep[u]<deep[v]) swap(u,v);
  int dc=deep[u]-deep[v];
  for(int i=0;i<30;i++){
    if((1<<i)&dc)//move u to dc+u
        u=fa[u][i];
  }
  if(u==v) return u;
  for(int i=29;i>=0;i--){
    if(fa[u][i]!=fa[v][i]){
        u=fa[u][i];v=fa[v][i];
    }
  }
  u=fa[u][0];//on the next level of lca,just move up one
  return u;
}


/****二分图最大匹配 匈牙利算法****/
int line[50][50];
int used[50];//标记这条边有没有用过
int match[50];//标记右侧的点是否被匹配，以及匹配的是左侧哪个点
int nl;
int nr;
bool find(int x){
  for(int i=1;i<=nr;i++){
    if(line[x][i]&&!used[i]){
        used[i]=1;
        if(match[i]==0||find(match[i])){
            match[i]=x;
            return true;
        }
    }
  }
  return false;
}
int hungarian()
{
    int ans = 0;
    memset(match,0,sizeof(match));
    for (int i=1;i<=nl;i++) {
       memset(used,0,sizeof(used));
       if(find(i)) ans++;
    }
    return ans;
}


/* * 二分图匹配（Hopcroft-Carp算法）
  复杂度O(sqrt(n)*E)  邻接表存图 vector实现
  vector先初始化，然后假如边uN 为左端的顶点数，使用前赋值(点编号0开始)
  */
const int MAXN = 3000;
vector<int>G[MAXN];
int uN;
int Mx[MAXN],My[MAXN];
int dx[MAXN],dy[MAXN];
int dis;
bool used[MAXN];
bool SearchP() {
 queue<int>Q;
  dis = INF;
  memset(dx,-1,sizeof(dx));
  memset(dy,-1,sizeof(dy));
  for(int i = 0 ; i < uN; i++)
     if(Mx[i] == -1)  {
         Q.push(i);
        dx[i] = 0;  }
      while(!Q.empty()) {
          int u = Q.front();
          Q.pop();
      if(dx[u] > dis)
        break;
      int sz = G[u].size();
      for(int i = 0;i < sz;i++) {
            int v = G[u][i];
       if(dy[v] == -1)   {
            dy[v] = dx[u] + 1;
     if(My[v] == -1)dis = dy[v];
     else    {
        dx[My[v]] = dy[v] + 1;
        Q.push(My[v]);
         } } } }

return dis != INF;
}

 bool DFS(int u) {
     int sz = G[u].size();
     for(int i = 0;i < sz;i++) {
            int v = G[u][i];
       if(!used[v] && dy[v] == dx[u] + 1)  {
            used[v] = true;
       if(My[v] != -1 && dy[v] == dis)
          continue;
        if(My[v] == -1 || DFS(My[v]))  {
                My[v] = u;
               Mx[u] = v;
      return true;
      }   } }
return false; }


int MaxMatch() {
    int res = 0;
    memset(Mx,-1,sizeof(Mx));
     memset(My,-1,sizeof(My));
     while(SearchP()) {
        memset(used,false,sizeof(used));
        for(int i = 0;i < uN;i++)
        if(Mx[i] == -1 && DFS(i))
          res++;
          }
return res; }

/**拓扑排序**/
queue<int>q;
//priority_queue<int,vector<int>,greater<int>>q;
//优先队列的话，会按照数值大小有顺序的输出
//此处为了理解，暂时就用简单队列
int ind[maxn];//入度
int topo()
{
    for(int i=1;i<=n;i++)
    {
        if(ind[i]==0)
        {
            q.push(i);
        }
    }

    int temp;
    while(!q.empty())
    {
        temp=q.front();
        q.pop();
        //此处可输出排序结果temp
        for(int i=1;i<=n;i++)
        {
            if(edge[temp][i])
            {
                ind[i]--;
                if(ind[i]==0) q.push(i);
            }
        }
    }
}

/*并查集（有路径压缩）*/
void init()
{
    for(int i=0; i<=n*m+m; i++)
        p[i]=i;
}
int Find(int x)
{
    if(x==p[x])
        return p[x];
    int y=Find(p[x]);
    return p[x]=y;
}

int unin(int x,int y)
{
    int x1=Find(x);
    int y1=Find(y);
    if(x1==y1)
        return 0;
    p[x1]=y1;
      return 1;
}




/*带权并查集（食物链) 抄网上的*/
/*n个动物 k句话 有一种循环a吃b 吃c c吃a 开始不知道n种动物关系是什么
两种询问：d=1 x y为同类  d=2 x吃y 判断假话条数（关键之违背之前的关系）
并查集可以很好解决的满足区间传递关系的区间合并问题，注意一般是多棵树*/
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int Max=50010;
int fat[Max],ran[Max];
void Init(int n)//初始化重要
{
    for(int i=0; i<=n; i++)
    {
        fat[i]=i;//初始化都是指向（看做）自己
        ran[i]=0;//0同类 1吃父节点 2被父节点吃
    }
    return;
}
int Find(int x)//找寻父节点+路径压缩
{
    if(x==fat[x])
        return fat[x];
    int y=Find(fat[x]);
        ran[x]=(ran[x]+ran[fat[x]])%3;//递归后从祖先节点向后到每个孩子来计算
    return fat[x]=y;//路径压缩
}
int Union(int typ,int x,int y)//区间并与查询
{
    int x1=Find(x);
    int y1=Find(y);
    if(x1==y1)//共父节点才能判断出关系
    {
        if((ran[x]-ran[y]+3)%3==typ-1)
            return 0;
        return 1;
    }
    fat[x1]=y1;//连接两父节点
    ran[x1]=(-ran[x]+typ-1+ran[y]+3)%3;//使用类似向量方法来计算权值,虽然题目只有两个，但是会出现被吃这种情况，所以要变成3种情况，注意一定要处理负数的情况
    return 0;
}
int main()
{
    int n,k,ans;
    int typ,smt1,smt2;
    scanf("%d %d",&n,&k);
        Init(n);
        ans=0;
        for(int i=0; i<k; i++)
        {
            scanf("%d %d %d",&typ,&smt1,&smt2);
            if(smt1==smt2&&typ==2)
                ans++;
            else if(smt1>n||smt2>n)
                ans++;
            else
                ans+=Union(typ,smt1,smt2);
        }
        printf("%d\n",ans);
    return 0;
}

/**2-SAT**/
int n;
vector<int> g[maxn*2];
bool mark[maxn*2];
int s[maxn*2],c;
bool dfs(int x){
    if(mark[x^1]) return false;
    if(mark[x]) return true;
    mark[x]=true;
    s[c++]=x;
    for(int i=0;i<(int)g[x].size();i++)
        if(!dfs(g[x][i])) return false;
    return true;
}
void init(int n){

    for(int i=0;i<n*2;i++) g[i].clear();
    memset(mark,0,sizeof(mark));
}
void add_clause(int x,int y){//这个函数随题意变化
    g[x].push_back(y);//选了x就必须选y^1

}
bool solve(){
    for(int i=0;i<n*2;i+=2)
        if(!mark[i]&&!mark[i+1]){
            c=0;
            if(!dfs(i)){
                while(c>0) mark[s[--c]]=false;
                if(!dfs(i+1)) return false;
            }
        }
    return true;
}

