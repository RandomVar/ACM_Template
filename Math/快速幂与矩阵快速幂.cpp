/* 快速幂 */
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

/****矩阵快速幂***/
typedef vector<ll> vec;
typedef vector<vec> mat;
const ll mod=" ";
//A*B
mat mul(mat &A,mat &B){
	mat C(A.size(),vec(B[0].size()));
	for(int i=0;i<A.size();i++)
	  for(int k=0;k<B.size();k++)
	    for(int j=0;j<B[0].size();j++)
	      C[i][j]=(C[i][j]+A[i][k]*B[k][j])%mod;
	return C;
}
//A^n
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
ll n;
void solve(){
	mat A(2,vec(2));//行数，列数
	A[0][0]=1;A[0][1]=1;
	A[1][0]=1;A[1][1]=0;
	A=pow(A,n);
	cout<<A[1][0]<<endl;
}
