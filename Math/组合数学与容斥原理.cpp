/* 容斥原理  UVA-10325 */
for(int i=1;i<(1<<m);i++){
    ll ans=1;int ant=0;
    for(int j=0;j<m;j++){
        if(i&(1<<j)){
           ans=lcm(ans,a[j]);
            ant++;
            }
         }
            if((ant-1)%2) num-=(n/ans);
           else num+=(n/ans);
}

/* 组合数预处理 */
/* c(n,m) n>m */
const int N=50;
for(int j=0;j<N;j++)
    c[j][0]=1;
for(int i=0;i<N;i++)
   for(int j=1;j<N;j++)
    {
     if(i==j) c[i][j]=1;
      else if(i<j) c[i][j]=0;
      else c[i][j]=(c[i-1][j-1]+c[i-1][j])%mod; 
    }

/*Lucas 组合数取模*/
/* 模数p<=1e5 */
const int maxn="1e5";
ll fac[maxn];
void getf(ll p)
{
    fac[0]=1;
    for(int i=1;i<=p;i++)
        fac[i]=fac[i-1]*i%p;
}

ll quickmod(ll a,ll b,ll c){
	ll res=1;
	while(b){
		if(b&1)
		  res=res*a%c;
		a=a*a%c;
		b>>=1;
	}
	return res;
}

ll lucas(ll n,ll m,ll p)
{
    ll ans=1;
    while(n&&m)
    {
        ll a=n%p;
        ll b=m%p;
        if(a<b) return 0;
        ans=(ans*fac[a]*quickmod(fac[b]*fac[a-b]%p,p-2,p))%p;
        n/=p;
        m/=p;
    }
    return ans;
}