/* 素数判断 */
ull mul(ull x,ull y,ull Z)
{
    ull tmp=x/(long double)Z*y+1e-3;
    return (x*y+Z-tmp*Z)%Z;
}
ull MUL(ull x,ull p,ull Z)
{
    ull y=1;
    while(p)
    {
        if(p&1)y=mul(y,x,Z);
        x=mul(x,x,Z);
        p>>=1;
    }
    return y;
}
bool miuller_rabin(ull n)
{
    if(n<=1)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    ull p=n-1;
    srand(time(NULL));
    int TIMES=8;
    for(int i=1;i<=TIMES;i++)
    {
        ull x=rand()%(n-1)+1;
        if(MUL(x,p,n)!=1)return 0;
    }
    return 1;
}

/* 埃式筛 */
/*值为false表示素数，值为true表示非素数 */
/* 复杂度O(n*log(logn)) */

const int MAXN = " 1e6 ";
bool notprime[MAXN];
void init()
 {
    memset(notprime,false,sizeof(notprime));
    notprime[0]=notprime[1]=true;
    for(int i=2;i<MAXN;i++)
        if(!notprime[i])
        {
            if(i>MAXN/i)  continue;//防爆 long long
          for(int j=i*i;j<MAXN;j+=i)
             notprime[j]=true;
      }
}

/* 区间内素数筛选 埃式筛 */
/*prime[0]存素数个数，prime[i]为1-MAXN间第i个素数*/
/* hash[i]=flase 表示i为素数 */
/* 每个合数都只会被其最小质因子筛到 复杂度线性 */
const int MAXN = "1e7";
bool has[MAXN+1];
int prime[MAXN/10+1];
void getPrime()
{
    memset(prime,0,sizeof(prime));
    memset(has,false,sizeof(has));
    for(int i=2;i<=MAXN;i++)
    {
        if(!has[i]) prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i;j++)
        {
            has[prime[j]*i]=true;
            if(i%prime[j]==0)
                break;
        }
    }
}

/*合数分解*/
/* fat[i][0]表示第i个质因子，fat[i][1]表示该质因子的个数 */
ll fat[100][2];
int fcnt;
int getfats(ll x)
{
    fcnt=0;
    ll tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++) 
    // if x is larger than 1e7,may need add condition i<prime[0]
    {
        fat[fcnt][1]=0;
        if(tmp%prime[i]==0)
        {
            fat[fcnt][0]=prime[i];
            while(tmp%prime[i]==0)
             {
            fat[fcnt][1]++;
            tmp/=prime[i];
             }
            fcnt++;
        }
    }
       if(tmp!=1)
       {
         fat[fcnt][0]=tmp;
         fat[fcnt++][1]=1;
        }
   return fcnt;
}

/* 预处理1-n所有数的质因子 接近o(n) */
const int maxn = " ";
vector<int>d[maxn];
int vis[maxn];
void init(){
    memset(vis,0,sizeof(vis));
   for(int i=2;i<maxn;i++){
      if(!vis[i]){
        for(int j=i;j<maxn;j+=i)
        {
            d[j].push_back(i);
            vis[j]=1;
        }
      }}
}
