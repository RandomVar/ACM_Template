/**lower_bound ��>=t�ĵ�һ��Ԫ��*/
 int lb=-1,ub=res;
  while(ub-lb>1){
    int mid=(lb+ub)/2;
    if(x[mid]>=t) ub=mid;
    else lb=mid;
  }
  return ub;

/*另一种好用的*/
int l=0;int r=res;
while(l<=r)
{
  int mid=(l+r)/2;
  if(ok) l=mid+1,ans=mid;
  else r=mid-1;
}
return ans;

/**浮点数二分*/
 for(int i = 0; i < 100; i++) {
      mid = (l + r) / 2.0;
      if(check(mid) ) r = mid;
      else l = mid;
  }
/*�����������o nlogn*/


const int MAXN=500010; int a[MAXN],b[MAXN];
//�ö��ֲ��ҵķ����ҵ�һ��λ�ã�ʹ��num>b[i-1] ����num<b[i],����num����b[i]
int Search(int num,int low,int high) {
  int mid;
  while(low<=high)  {
    mid=(low+high)/2;
	if(num>=b[mid])  low=mid+1;
	else   high=mid-1;
	}
	 return low;
	 }
int DP(int n) {
    int i,len,pos;
    b[1]=a[1];
    len=1;
    for(i=2;i<=n;i++) {
        if(a[i]>=b[len])//���a[i]��b[]��������󻹴�ֱ�Ӳ��뵽���漴��
		 {
        len=len+1; b[len]=a[i];  }
        else//�ö��ֵķ�����b[]�������ҳ���һ����a[i]���λ�ò�����a[i]������λ��
        { pos=Search(a[i],1,len);
        b[pos]=a[i];
			   }}
    return len; }


/*0-1����*/
for(int i=0;i<n;i++)
    for(int j=v;j>=c[i];j--)
       dp[j]=max(dp[j],dp[j-c[i]]+w[i]);

/*��ȫ����*/
for(int i=0;i<n;i++)
 for(int j=c[i];j<=v;j++)
   dp[j]=max(dp[j],dp[j-c[i]]+w[i]);

/*
������� c(m,n)=c(m-1,n)+c(m-1,n-1);
*/

/*�����������*/
void lcs(){
  memset(dp,0,sizeof(dp));
  int n=strlen(s1);
  for(int i=0;i<=n;i++)
    for(int j=0;j<=n;j++)
  {

      if(i==0||j==0) {
            dp[i][j]=0;}
      else if(s1[i-1]==s2[j-1]) dp[i][j]=dp[i-1][j-1]+1;
      else {dp[i][j]=max(dp[i-1][j],dp[i][j-1]);}
  }
}

/*��λdp   HDU-2089 ��Ҫ62 */
int bit[30];
ll dp[30][2][2];
ll dfs(int pos,int st,int flag){
   if(pos==0) return 1;
   if(flag&&dp[pos][st][flag]!=-1)
      return dp[pos][st][flag];
   int u=flag?9:bit[pos];
   ll ans=0;
   for(int i=0;i<=u;i++){
      if(i==4) continue;
      else if(st==0&&i==2) continue;
      else if(i!=6) ans+=dfs(pos-1,1,flag||i<u);
      else if(i==6) ans+=dfs(pos-1,0,flag||i<u);
   }
return ans;
}

ll solve(int n){
  int len=0;
  while(n){
     bit[++len]=n%10;
     n/=10;
  }
  return dfs(len,1,0);
}
