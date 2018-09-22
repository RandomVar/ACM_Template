/***筛法欧拉函数***/
/*
1. i mod p==0 phi(i * p) == p * phi(i)
2. i mod p!=0 phi(i * p) == phi(i) * (p-1)
算法就是将 X 中的素数因子pi减1，并且相同的素数因子只有1个减1
*/
const int maxn= "3e5+10";
int euler[maxn];
void getEuler() {
    memset(euler,0,sizeof(euler));
    euler[1] = 1;
    for(int i = 2;i < maxn;i++)
        if(!euler[i])
          for(int j = i;j < maxn; j += i){
            if(!euler[j])
              euler[j] = j;
            euler[j] = euler[j]/i*(i-1);
           }
 }

/*求单个数的欧拉函数*/
/*
phi(n)=n*((u(d)/d)之和d|n)
*/
ll eular(ll n) {
    ll ans = n;
    for(int i = 2;i*i <= n;i++)
     {
        if(n % i == 0)  
        {
          ans -= ans/i;
          while(n % i == 0)
            n /= i; 
         } 
    }
  if(n > 1)  ans -= ans/n;
   return ans;
   }

/*
其他结论：
 phi(mn)=d*phi(m)*phi(n)/pi(d)   d=(m,n)
*/