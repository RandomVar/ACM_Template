
ll gcd(ll a,ll b){
    if(a < b)
         swap(a,b);
    while(a%b){
        ll r = a % b;
        a = b;
        b = r;
     }
   return b;
}

/*求ax+by=c的xy 其中c%gcd(a,b)==0时才有解 
解出的为特解x0,y0 */
ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
    if(a==0&&b==0) return -1;
    if(b==0){x=1;y=0;return a;}
    ll d=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
}

/*求最小正整数解x;若无解返回false*/
/*已求出特解 x0,y0 设t=c/d,则通解为 x=t*x0+b/d*k; y=t*y0-a/d*k; k为任意整数
最小正整数解 x=x0*t; x=(x%s+s)%s;*/
  bool min_x(int a,int b,int &x,int &y,int c)
{
    int d=ex_gcd(a,b,x,y);
    if(c%d) return false;
    x=x*c/d;
    int s=b/d;
    s=s>0?s:-1*s;
    x=(x%s+s)%s;
    y=(c-a*x)/b;
    return true;
}

/****费马小定理求逆元****/
/*mod为素数,而且a和m互质 a^(p-1)=1(mod p) */
ll inv(ll a,ll mod) {
    return quickmod(a,mod-2,mod);
}

/*线性递推求逆元*/
void init()
{
    inv[1]=1;
   for(int i=2;i<=1e6;i++)
   inv[i]=inv[mod%i]*(mod-mod/i)%mod;

}

