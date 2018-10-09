
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
/**二分图最佳完美匹配**/
//求权值和最大的完美匹配
//完美匹配：所有点都是匹配点
/*steal from csl*/
const int maxn = " ";
int n;
int cost[maxn][maxn];
int lx[maxn], ly[maxn], match[maxn], slack[maxn];
int prev[maxn];
bool vy[maxn];

void augment(int root)
{
    fill(vy + 1, vy + n + 1, false);
    fill(slack + 1, slack + n + 1, inf);
    int py;
    match[py = 0] = root;
    do
    {
        vy[py] = true;
        int x = match[py], yy;
        int delta = inf;
        for (int y = 1; y <= n; y++)
        {
            if (!vy[y])
            {
                if (lx[x] + ly[y] - cost[x][y] < slack[y])
                    slack[y] = lx[x] + ly[y] - cost[x][y], prev[y] = py;
                if (slack[y] < delta) delta = slack[y], yy = y;
            }
        }
        for (int y = 0; y <= n; y++)
        {
            if (vy[y])
                lx[match[y]] -= delta, ly[y] += delta;
            else
                slack[y] -= delta;
        }
        py = yy;
    } while (match[py] != -1);
    do
    {
        int pre = prev[py];
        match[py] = match[pre], py = pre;
    } while (py);
}
int KM()
{
    for (int i = 1; i <= n; i++)
    {
        lx[i] = ly[i] = 0;
        match[i] = -1;
        for (int j = 1; j <= n; j++) lx[i] = max(lx[i], cost[i][j]);
    }
    int answer = 0;
    for (int root = 1; root <= n; root++) augment(root);
    for (int i = 1; i <= n; i++) answer += lx[i], answer += ly[i];
    return answer;
}
