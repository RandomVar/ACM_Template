/*****ŷ�����շת���****/
ll gcd(ll a,ll b){
         if(a < b){
                   swap(a,b);
         }
         while(a % b){
             ll r = a % b;
                   a = b;
                   b = r;
         }
         return b;
}

/****��չŷ�����****/
/*��ax+by=c��xy ����c%gcd(a,b)==0ʱ���н�
  �����Ϊ�ؽ�x0,y0 */
ll ex_gcd(ll a,ll b,ll &x,ll &y)
{
    if(a==0&&b==0) return -1;//�����Լ��
    if(b==0){x=1;y=0;return a;}
    ll d=ex_gcd(b,a%b,y,x);
    y-=a/b*x;
    return d;
  }

/*����С��������x;���޽ⷵ��false*/

/*������ؽ� x0,y0 ��t=c/d,��ͨ��Ϊ x=t*x0+b/d*k; y=t*y0-a/d*k; kΪ��������
��С�������� x=x0*t; x=(x%s+s)%s;*/

  bool min_x(int a,int b,int &x,int &y,int c)
{
    int d=ex_gcd(a,b,x,y);
    if(c%d) return false;
    x=x*c/d;
    int s=b/d;
    s=s>0?s:-1*s;
    x=(x%s+s)%s;
    y=(c-a*x)/b;
    //cout<<"x = "<<x<<endl;
    //cout<<"y = "<<y<<endl;
    return true;
}

/****����Ԫ��****/
/*ax = 1(mod n) ����ax+ny=1��x�Ľ�*/
ll mod_reverse(ll a,ll n) {
  ll x,y;
  ll d=ex_gcd(a,n,x,y);
  if(d==1) return (x%n+n)%n;
  else return -1;
}

/*���д�� ��ax = 1( mod m) ��xֵ  Ҫ�� 0<a<m ��a,m���� */
ll inv(ll a,ll m){
  if(a == 1) return 1;
  return inv(m%a,m)*(m-m/a)%m;
  }

/****����С��������Ԫ****/
/*modΪ����,����a��m���� a^(p-1)=1(mod p) */
ll inv(ll a,ll mod) {
    return pow_m(a,mod-2,mod);
   }

/*线性递推求逆元*/
void init()
{
    inv[1]=1;
   for(int i=2;i<=1e6;i++)
   inv[i]=inv[mod%i]*(mod-mod/i)%mod;

}

/*�й�ʣ�ඨ��*/
/*x=bi(mod m0i)*/
/*x0+=biMiyi*/
ll ChinaRemainder(ll m0[],ll b[],int n){
	ll m=1,a=0;s
	int i;
	for (i=1; i<=n; i++)  m=m*m0[i];
	for (i=1; i<=n; i++) {
		ll MM=m/m0[i];
		ll x=mod_reverse(MM,m0[i]);
		a=(a+MM*x*b[i]) % m;
	}
	return a;
}


/****������****/
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

/****��������ݣ�ժ��****/
typedef vector<int> vec;
typedef vector<vec> mat;
const int MOD=10000;
//����A*B
mat mul(mat &A,mat &B){
	mat C(A.size(),vec(B[0].size()));
	for(int i=0;i<A.size();i++)
	  for(int k=0;k<B.size();k++)
	    for(int j=0;j<B[0].size();j++)
	      C[i][j]=(C[i][j]+A[i][k]*B[k][j])%MOD;
	return C;
}
//���� A^n
mat pow(mat A,ll n){
	mat B(A.size(),vec(A.size()));
	for(int i=0;i<A.size();i++)
	  B[i][i]=1;
	while(n>0){
		if(n&1) B=mul(B,A);
		A=mul(A,A);
		n>>=1;
	}
	return B;
}
//����
ll n;
void solve(){
	mat A(2,vec(2));//����������
	A[0][0]=1;A[0][1]=1;
	A[1][0]=1;A[1][1]=0;
	A=pow(A,n);
	cout<<A[1][0]<<endl;
}

/***������ ɸ��ŷ������***/
/*
1. i mod p==0 phi(i * p) == p * phi(i)
2. i mod p!=0 phi(i * p) == phi(i) * (p-1)
�㷨���ǽ� X �е���������pi��1��������ͬ����������ֻ��1����1
*/
int euler[3000001];
void getEuler() {
    memset(euler,0,sizeof(euler));
    euler[1] = 1;
    for(int i = 2;i <= 3000000;i++)
        if(!euler[i])
          for(int j = i;j <= 3000000; j += i){
            if(!euler[j])
              euler[j] = j;
            euler[j] = euler[j]/i*(i-1);
           }
 }


/*�󵥸�����ŷ������*/
/*
phi(n)=n*((u(d)/d)֮��d|n)
*/
ll eular(ll n) {
    ll ans = n;
    for(ll i = 2;i*i <= n;i++) {
        if(n % i == 0)  {
          ans -= ans/i;
          while(n % i == 0)
            n /= i; } }
       if(n > 1)ans -= ans/n;
    return ans;
     }

/**�ݳ�ԭ��**/
/**
����С�ڵ���x����p���ʵ����ĸ���
vector<int>d[p]�д�p��������
**/
ll cal(ll x,int p){
    int m=d[p].size();
    ll num=0;
    for(int i=1;i<(1<<m);i++){
         ll ans=1;int ant=0;
         for(int j=0;j<m;j++){
            if(i&(1<<j)){
                ans*=d[p][j];
                ant++;
            }
         }
            if((ant-1)%2) num-=(x/ans);
           else num+=(x/ans);
     }
  return x-num;
}
