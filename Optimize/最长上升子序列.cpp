/*最长上升子序列 o(nlogn) */
const int maxn= " "; 
int a[maxn],b[maxn];

int lis(int n) {
    b[1]=a[1];
    int len=1;
    for(int i=2;i<=n;i++) 
    {
        if(a[i]>=b[len])
		 { 
             len=len+1; 
             b[len]=a[i]; 
         }
        else
        { 
            int pos=upper_bound(b+1,b+1+len,a[i])-b;
            b[pos]=a[i];
		}
    }
  return len; 
  }