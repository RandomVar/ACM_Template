/* 单点更新 */

int lowbit(int x){
return x&(-x);
}
T sum(int x){
  T ret=0;
  while(x>0){
    ret+=bit[x];
    x-=lowbit(x);
  }
return ret;
}

void add(int x,T d){
    if(x<0) return;
   while(x<=n){
    bit[x]+=d;
    x+=lowbit(x);
   }
}

/**区间更新区间查询 **/
int lowbit(int x){
return x&(-x);
}

void add(int x,int y){
   for(int i=x;i<=n;i+=lowbit(i))
    for(int j=y;j<=n;j+=lowbit(j))
       bit[i][j]++;
}

T sum(int x,int y){
   T ret=0;
   for(int i=x;i>0;i-=lowbit(i))
     for(int j=y;j>0;j-=lowbit(j))
       ret+=bit[i][j];
   return ret;
}
