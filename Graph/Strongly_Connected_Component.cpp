/**求割点*/
/*根节点的儿子数量>=2即为割点*/
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
    if(fa<0&&child == 1) iscut[u] = 0;//根节点
}



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