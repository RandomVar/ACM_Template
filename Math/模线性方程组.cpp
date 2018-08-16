/*中国剩余定理*/
/*x=bi(mod m0i)*/
/*x0+=biMiyi*/
ll m0[maxn];
ll b[maxn];
ll ChinaRemainder(int n){
	ll m=1,a=0;
	for (int i=1; i<=n; i++)  m=m*m0[i];
	for (int i=1; i<=n; i++) {
		ll MM=m/m0[i];
		ll x=inv(MM,m0[i]);
		a=(a+MM*x*b[i]) % m;
	}
	return a;
}
/*不互质的中国剩余定理*/
ll m0[maxn];
ll b[maxn];

ll china(ll n)
{
    ll a,bb,d,x,y,dm;
    ll c,c1,c2;
    ll dg;//lcm
    a=m0[1]; c1=b[1];
    for (int i=2; i<=n; i++)
    {
        bb=m0[i]; c2=b[i];
        d=ex_gcd(a, bb,x, y);
        dm=bb/d;
        c=c2-c1;
        if (c%d) return -1;//无解
        x=((x*c/d)%dm+dm)%dm;//x可能为负
        c1=a*x+c1;
        a=a*bb/d;
    }
    dg=a;//dg是最大公约数
    if (!c1)//考虑c1为0的情况
    {
        c1=1;
        for (int i=1; i<=n; i++)
        {
            c1=c1*m0[i]/__gcd(c1, m0[i]);
        }
        dg=c1;//此时dg为最小公倍数
    }
    return c1;//c1为最小的X
}
