/* hash */
const int maxn = "1e5";
const int seed=31;
ull h[maxn];
ull base[maxn];
typedef pair<int,int> P;
void init()
{
  base[0]=1;
  for(int i=1;i<maxn;i++)
    base[i]=base[i-1]*seed;
}
ull str_hash(int l,int r){
  return h[r]-h[l-1]*base[r-l+1];
}
void Hash()
 {
   for(int i=0;i<len;i++)
      h[i+1]=h[i]*seed+s[i]-'a'+1; 
  }

  /* 随机数双哈希（csl）Gym101808B */
  map<pair<int,int>,pair<ull,ull> dic;

  inline pair<ull,ull>gethash(int x,int y)
  {
    if(x>y) swap(x,y);
    if(dic.find({x,y})!=dic.end())
        return dic[{x,y}];
    ull h1=1;
    ull h2=1;
    for(int i=0;i<5;i++) h1*=rand();
    for(int i=0;i<5;i++) h2*=rand();//用随机数hash
    return dic[{x,y}]={h1,h2};
  }

  map<pair<ull,ulll>,int> cnt[maxn];

   dic.clear();
  for(int i=0;i<n;i++)
    a[i]=gethash(x,y);

for(int i=0;i<n;i++)
{
  ull hash1=0,hash2=0;
  for(int j=i;j<n;j++)
  {
    hash1+=a[j].first;hash2+=a[j].second;
   ans+=cnt[j-i][{hash1,hash2}];
    cnt[j-i][{hash1,hash2}]++;//长度相同的放在一个map
  }
}

/* 双哈希（csl）*/

const int seed1= "19260817" ;
const int mod1= "1e9+7";
const int seed2= "23333333";
const int mod2= "1e9+9" ;
int base1[maxn],base2[maxn];

map<pair<int,int>,int> dic;
inline int getid(int x,int y)
{
  if(x>y) swap(x,y);
  if(dic[{x,y}])  return dic[{x,y}];
  return dic[{x,y}]=dic.size();
}

void init(int n)
{
  base1[0]=1,base2[0]=1;
  for(int i=1;i<=n;i++)
    base1[i]=(1LL*base1[i-1]*seed1);
    base2[i]=(1LL*base2[i-1]*seed2);
}

dic.clear();
for(int i=0;i<n;i++)
    a[i]=getid(x,y);

map<pair<int,int>,int> cnt[maxn];
for(int i=0;i<n;i++)
{
  int sum1=0,sum2=0;
  for(int j=i;j<n;j++)
  {
    sum1=(sum1+base1[a[j]])%mod1;
    sum2=(sum2+base2[a[j]])%mod2;
     ans+=cnt[j-i][{sum1,sum2}];
    cnt[j-i][{sum1,sum2}]++;//长度相同的放在一个map
  }
}