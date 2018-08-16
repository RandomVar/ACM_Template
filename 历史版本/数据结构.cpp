/*RMQ HDU-4123*/
void ST(int n) {

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
               dp[i][j][0] = max(dp[i][j - 1][0], dp[i + (1 << (j - 1))][j - 1][0]);
               dp[i][j][1] = min(dp[i][j - 1][1], dp[i + (1 << (j - 1))][j - 1][1]);

        }
    }
}
int RMQ(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) k++;

    return max(dp[l][k][0], dp[r - (1 << k) + 1][k][0])-min(dp[l][k][1], dp[r - (1 << k) + 1][k][1]);
}

/*����lca  HDU-2586**/
const int maxn=41000;
struct node{
  int t,val;
};
int n;
int fa[maxn][25];//fa[i][j]Ϊ�ڵ�i�ĵ�2^j�����ȣ��丸�׽ڵ�Ϊfa[i][0]
int deep[maxn],d[maxn];//deep�洢�ڵ����
vector<node>edge[maxn];
int cnt;
void addedge(int u,int v,int val){
//  e.pb(node{u,v,val});
  edge[u].push_back(node{v,val});
  edge[v].push_back(node{u,val});
}
void dfs(int u,int pre){
   for(int i=0;i<edge[u].size();i++){
        node t=edge[u][i];
       if(t.t==pre) continue;
       d[t.t]=d[u]+t.val;
       deep[t.t]=deep[u]+1;
       fa[t.t][0]=u;
      dfs(t.t,u);
   }
}
void bz(){
   for(int i=1;i<=20;i++)
      for(int j=1;j<=n;j++)
          fa[j][i]=fa[fa[j][i-1]][i-1];
}
int lca(int a,int b){
  if(deep[a]>deep[b]) swap(a,b);
  int dc=deep[b]-deep[a];
  for(int i=0;i<=20;i++)
     if((1<<i)&dc)
         b=fa[b][i];
  if(a==b) return a;
  for(int i=20;i>=0;i--){
      if(fa[a][i]!=fa[b][i])
      {
         a=fa[a][i];
         b=fa[b][i];
  }
}
a=fa[a][0];
return a;
}

/*��״����*/
int lowbit(int x){
return x&(-x);
}
int sum(int x){//���
  int ret=0;
  while(x>0){
    ret+=tree[x];
    x-=lowbit(x);
  }
return ret;
}

void update(int x,int d){//���½ڵ���Ϣ
    if(x<0) return;
   while(x<=n){
    tree[x]+=d;
    x+=lowbit(x);
   }
}

/**��ά��״����*/
int lowbit(int x){
return x&(-x);
}

void add(int x,int y){
   for(int i=x;i<=n;i+=lowbit(i))
    for(int j=y;j<=n;j+=lowbit(j))
       tree[i][j]++;
}

int sum(int x,int y){
   int ret=0;
   for(int i=x;i>0;i-=lowbit(i))
     for(int j=y;j>0;j-=lowbit(j))
       ret+=tree[i][j];
   return ret;
}

/**笛卡尔树**/
/**
 * 中序遍历得到的序列为原数组序列
 * 节点的key值要大于其左右子节点的key值
 * 利用单调栈建树
 **/
void build() {
	int top=0;
	for(int i=1;i<=n;i++)
      l[i]=0,r[i]=0,vis[i]=0;
	for(int i=1;i<=n;i++)
     {
		int k=top;
		while (k>0&&a[stk[k-1]]<a[i]) --k;
		if (k) r[stk[k-1]]=i;//找出i左边第一个比它大的数，把i连到它的右子树
		if (k<top) l[i]=stk[k];//将该数字原来的右子树连到i的左子树
		stk[k++]=i;
		top=k;
	}
    for(int i=1;i<=n;i++)
	   vis[l[i]]=vis[r[i]]=1;
	int rt=0;
    for(int i=1;i<=n;i++)
       if (vis[i]==0)  rt=i;
}