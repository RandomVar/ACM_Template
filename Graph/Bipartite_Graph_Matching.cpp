
/****二分图最大匹配 匈牙利算法****/
/*o(VE)*/
int line[maxn][maxn];
int used[maxn];//标记这条边有没有用过
int match[maxn];//标记右侧的点是否被匹配，以及匹配的是左侧哪个点
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
  dis = inf;
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

return dis != inf;
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


/*KM算法*/
/**二分图最佳匹配**/
/*steal from csl*/
const int maxn = "";
int nx, ny;                           //两边的点数
int g[maxn][maxn];                    //二分图描述
int linker[maxn], lx[maxn], ly[maxn]; //y中各点匹配状态,x,y中的点标号
int slack[N];
bool visx[N], visy[N];
bool dfs(int x)
{
    visx[x] = true;
    for (int y = 0; y < ny; y++)
    {
        if (visy[y]) continue;
        int tmp = lx[x] + ly[y] - g[x][y];
        if (tmp == 0)
        {
            visy[y] = true;
            if (linker[y] == -1 || dfs(linker[y]))
            {
                linker[y] = x;
                return true;
            }
        }
        else if (slack[y] > tmp)
            slack[y] = tmp;
    }
    return false;
}
int KM()
{
    mem(linker, -1), mem(ly, 0);
    for (int i = 0; i < nx; i++)
    {
        lx[i] = -inf;
        for (int j = 0; j < ny; j++)
            if (g[i][j] > lx[i]) lx[i] = g[i][j];
    }
    for (int x = 0; x < nx; x++)
    {
        mem(slack, 0x3f);
        for (;;)
        {
            mem(visx, 0), mem(visy, 0);
            if (dfs(x)) break;
            int d = inf;
            for (int i = 0; i < ny; i++)
                if (!visy[i] && d > slack[i]) d = slack[i];
            for (int i = 0; i < nx; i++)
                if (visx[i]) lx[i] -= d;
            for (int i = 0; i < ny; i++)
                if (visy[i])
                    ly[i] += d;
                else
                    slack[i] -= d;
        }
    }
    int res = 0;
    for (int i = 0; i < ny; i++)
        if (~linker[i]) res += g[linker[i]][i];
    return res;
}