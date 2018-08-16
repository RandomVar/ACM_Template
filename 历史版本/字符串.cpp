/****kmp(����δ��֤�棩****/
const int maxn=100;
int f[maxn];
void getft(const string &a){
  memset(f,0,sizeof(f));
  f[0]=-1;
  int i=0,k=-1;
  while(i<a.size()-1){
    if(k==-1||a[i]==a[k])
        f[++i]=f[++k];
    else k=f[k];
  }
}
int kmp(const string &t,const string &pat,int pos=0){
  getft(pat);
  int i=0,j=0;
  while(i<t.size()&&j<pat.size()&&pat.size()-j<=t.size()-i){
    if(j==-1||t[i]==pat[j]){
        i++;j++;
    }
    else{
        j=f[j];
    }
  }
  if(j<pat.size())
    return -1;
  else return i-j;
}



/****AC�Զ���HUD-2222****/
struct trie{
   int next[maxn][26],fail[maxn],ed[maxn];
   int root,cnt;
   int newnode(){
      for(int i=0;i<26;i++)
        next[cnt][i]=-1;
      ed[cnt++]=0;
      return cnt-1;

   }
   void init(){
      cnt=0;
      root=newnode();

   }
   void inser(char* buf){
     int len=strlen(buf);
     int now=root;
     for(int i=0;i<len;i++){
         if(next[now][buf[i]-'a']==-1)
             next[now][buf[i]-'a']=newnode();
         now=next[now][buf[i]-'a'];
     }
     ed[now]++;

   }
   void build(){
     queue<int>que;
     fail[root]=root;
     for(int i=0;i<26;i++){
        if(next[root][i]==-1)
             next[root][i]=root;
        else{
            fail[next[root][i]]=root;
            que.push(next[root][i]);
        }}
        while(!que.empty()){
            int now=que.front();
            que.pop();
            for(int i=0;i<26;i++){
                if(next[now][i]==-1)
                    next[now][i]=next[fail[now]][i];
                else{
                    fail[next[now][i]]=next[fail[now]][i];
                    que.push(next[now][i]);

                }
            }
        }
     }

  int query(char* buf){
    int len=strlen(buf);
    int now=root;
    int res=0;
    for(int i=0;i<len;i++){
        now=next[now][buf[i]-'a'];
        int temp=now;
        while(temp!=root){
            res+=ed[temp];
            ed[temp]=0;
            temp=fail[temp];
        }
    }
  return res;
  }
};
char buf[maxn];
trie ac;
int main(){
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    ac.init();
    for(int i=0;i<n;i++)
        cin>>buf,ac.inser(buf);
    ac.build();
    cin>>buf;
    cout<<ac.query(buf);


  }

return 0;
}

/*后缀数组 DA倍增算法 o(n*log(n))*/
const int maxn = "Edit";
char s[maxn];
int sa[maxn], t[maxn], t2[maxn], c[maxn], ran[maxn], height[maxn];
/*
sa为后缀数组，保存sa[第i个名次]=是i开头后缀
rank为名次数组rank[i开头的后缀]=的名次
height为相邻两个后缀的最长公共前缀
*/
//n为字符串的长度,字符集的值为0~m-1

void build_sa(int m, int n)
{
    n++;
    int *x = t, *y = t2;
    //基数排序
    for (int i = 0; i < m; i++) c[i] = 0;
    for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
    for (int i = 1; i < m; i++) c[i] += c[i - 1];
    for (int i = n - 1; ~i; i--) sa[--c[x[i]]] = i;
    for (int k = 1; k <= n; k <<= 1)
    {
        //直接利用sa数组排序第二关键字
        int p = 0;
        for (int i = n - k; i < n; i++) y[p++] = i;
        for (int i = 0; i < n; i++)
            if (sa[i] >= k) y[p++] = sa[i] - k;
        //基数排序第一关键字
        for (int i = 0; i < m; i++) c[i] = 0;
        for (int i = 0; i < n; i++) c[x[y[i]]]++;
        for (int i = 0; i < m; i++) c[i] += c[i - 1];
        for (int i = n - 1; ~i; i--) sa[--c[x[y[i]]]] = y[i];
        //根据sa和y数组计算新的x数组
        swap(x, y);
        p = 1;
        x[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
        if (p >= n) break; //以后即使继续倍增，sa也不会改变，推出
        m = p;             //下次基数排序的最大值
    }
    n--;
    int k = 0;
    for (int i = 0; i <= n; i++) ran[sa[i]] = i;
    for (int i = 0; i < n; i++)
    {
        if (k) k--;
        int j = sa[ran[i] - 1];
        while (s[i + k] == s[j + k]) k++;
        height[ran[i]] = k;
    }
}

int dp[maxn][30];
void initrmq(int n)
{
    for (int i = 1; i <= n; i++)
        dp[i][0] = height[i];
    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 1; i + (1 << j) - 1 <= n; i++)
            dp[i][j] = min(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}
int rmq(int l, int r)
{
    int k = 31 - __builtin_clz(r - l + 1);//__builtin_clz二进制中前导零的个数
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
}
int lcp(int a, int b)
{ // 求两个后缀的最长公共前缀
    a = ran[a], b = ran[b];
    if (a > b) swap(a, b);
    return rmq(a + 1, b);
}