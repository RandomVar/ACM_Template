/****һ���ȽϿ�������ж�****/
/*�����ж�һ�� < 2^63 �����ǲ������� */
/*�÷����� miller_rabin(n)Ϊ1����nΪ���� */
ll mul(ll x,ll y,ll Z)//�������ȡģ
{
    ll tmp=x/(long double)Z*y+1e-3;
    return (x*y+Z-tmp*Z)%Z;
}
ll MUL(ll x,ll p,ll Z)
{
    ll y=1;
    while(p)
    {
        if(p&1)y=mul(y,x,Z);
        x=mul(x,x,Z);
        p>>=1;
    }
    return y;
}
bool miller_rabin(ll n)
{
    if(n<=1)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    ll p=n-1;
    srand(time(NULL));
    int TIMES=8;
    for(int i=1;i<=TIMES;i++)
    {
        ll x=rand()%(n-1)+1;
        if(MUL(x,p,n)!=1)return 0;
    }
    return 1;
}

/****�������****/
/*notprimeΪtrue��ʾ�������� */
const int MAXN=1000010;
bool notprime[MAXN];
void init() {
    memset(notprime,false,sizeof(notprime));
    notprime[0]=notprime[1]=true;
    for(int i=2;i<MAXN;i++)
        if(!notprime[i]) {
            if(i>MAXN/i)continue;//��ֹ���,����i,j��long long
        for(int j=i*i;j<MAXN;j+=i)
           notprime[j]=true;
           }
  }

/**����ɸѡ���hash**/
const int MAXN=10000010;
bool has[MAXN];//i�ǲ�������
int prime[MAXN/10];//���i������
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

/*������*/
/****����ɸѡ�ͺ����ֽ� ****/
/* ����ɸѡ
 prime�����С�ڵ���MAXN������ prime[0] ����������ĸ��� */
const int MAXN=10000;
int prime[MAXN+1];
void getPrime() {
    memset(prime,0,sizeof(prime));
    for(int i=2;i<=MAXN;i++) {
            if(!prime[i])
                prime[++prime[0]]=i;
    for(int j=1;j<=prime[0]&&prime[j]<=MAXN/i;j++)  {
          prime[prime[j]*i]=1;
    if(i%prime[j]==0) break;
      } }
}

//factor[0]�д������� factor[1]�д��������ĸ���
long long factor[100][2];
int fatCnt;
int getFactors(long long x) {
    fatCnt=0;
    long long tmp=x;
    for(int i=1;prime[i]<=tmp/prime[i];i++) {
        factor[fatCnt][1]=0;
        if(tmp%prime[i]==0){
            factor[fatCnt][0]=prime[i];
            while(tmp%prime[i]==0){
            factor[fatCnt][1]++;
            tmp/=prime[i]; }
            fatCnt++;
        } }
       if(tmp!=1)  {
         factor[fatCnt][0]=tmp;
         factor[fatCnt++][1]=1;
         }
         return fatCnt;
    }


/*��ʽɸ o(n) Ԥ����n�����������������ӣ�����vector*/
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
      }
   }
}

/**�󵥸�Ԫ�ص�������*/
void getFactors(long long x) {

    long long tmp=x;
    for(int i=2;i<=tmp/i;i++) {
        if(tmp%i==0){
            while(tmp%i==0){
              mp[i]++;
            tmp/=i;
            }
        } }
       if(tmp!=1)  {
         mp[tmp]++;
         }

    }

/**�����Ԥ����*/
 for(int j=0;j<50;j++)
        c[0][j]=1;
  for(int i=1;i<50;i++)
    for(int j=0;j<50;j++)
  {
     if(i==j) c[i][j]=1;
     else if(j<i) c[i][j]=0;
      else c[i][j]=(c[i-1][j-1]+c[i][j-1])%mod;
     // cout<<j<<" "<<i<<" "<<c[i][j]<<endl;
  }
