/**倍增lca*/
const int maxn= " ";
const int N= "30";
int n;
int fa[maxn][N+5];
int deep[maxn];
vector<int>edge[maxn];

void dfs(int u,int pre){
  for(int i=0;i<edge[u].size();i++){
    int v=edge[u][i];
    if(v==pre) continue;
    fa[v][0]=u;//should give fa[v][0] value
    deep[v]=deep[u]+1; //also can preprocessing distance here
    dfs(v,u);
  }
}

void bz(){
 for(int j=1;j<=N;j++)
    for(int i=1;i<=n;i++)
      fa[i][j]=fa[fa[i][j-1]][j-1];
}

int lca(int u,int v){
  if(deep[u]<deep[v]) swap(u,v);
  int dc=deep[u]-deep[v];
  for(int i=0;i<N;i++){
    if((1<<i)&dc)//move u to dc+u
        u=fa[u][i];
  }
  if(u==v) return u;
  for(int i=N-1;i>=0;i--){
    if(fa[u][i]!=fa[v][i]){
        u=fa[u][i];v=fa[v][i];
    }
  }
  u=fa[u][0];//on the next level of lca,just move up one
  return u;
}

/*ST表预处理lca  o（nlogn+q）*/
vector<int> edge[maxn], sp;
int dep[maxn], dfn[maxn];
pair<int,int> dp[21][maxn << 1];
void init(int n)
{
    for (int i = 0; i < n; i++) edge[i].clear();
    sp.clear();
}
void dfs(int u, int fa)
{
    dep[u] = dep[fa] + 1;
    dfn[u] = sp.size();
    sp.push_back(u);
    for (auto& v : edge[u])
    {
        if (v == fa) continue;
        dfs(v, u);
        sp.push_back(u);
    }
}
void initrmq()
{
    int n = sp.size();
    for (int i = 0; i < n; i++) dp[0][i] = {dfn[sp[i]], sp[i]};
    for (int i = 1; (1 << i) <= n; i++)
        for (int j = 0; j + (1 << i) - 1 < n; j++)
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + (1 << (i - 1))]);
}
int lca(int u, int v)
{
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    int k = 31 - __builtin_clz(r - l + 1);
    return min(dp[k][l], dp[k][r - (1 << k) + 1]).sec;
}
