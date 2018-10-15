/* 区间不同数 */
/*树状数组*/
const int maxn=" ";
int bit[maxn];
int a[maxn];
int ans[maxn];
map<int,int>mp;
struct node{
    int l,r,id;
    bool operator<(const node &t)const{
        return r<t.r;
    }
}q[maxn];
int sum(int x);
void add(int x,int val);
int main()
{
       for(int i=1;i<=n;i++)
         scanf("%d",&a[i]);//输入数组
      sort(q+1,q+1+Q);//将询问离散
      int pre=1;
     for(int i=1;i<=Q;i++)
     {
         for(int j=pre;j<=q[i].r;j++)
         {
             if(mp[a[j]])
             {
                 add(mp[a[j]],-1);
             }
             add(j,1);
             mp[a[j]]=j;
         }
         pre=q[i].r+1;
        ans[q[i].id]=sum(q[i].r)-sum(q[i].l-1);
     }
     for(int i=1;i<=Q;i++)
       printf("%d\n",ans[i]);
}

/*主席树*/
const int maxn="";
int n,cnt;
int root[maxn],a[maxn];
map<int,int>mp;
struct node{
  int l,r,sum;
}T[maxn*40];
void init()
{
    cnt=0;
    mp.clear();
    root[0]=0;
    T[0].l = T[0].r = T[0].sum = 0;
}

void update(int l,int r,int &x,int y,int pos,int val){
  T[++cnt]=T[y];
  T[cnt].sum+=val;
  x=cnt;
  if(l==r) return ;
  int mid=(l+r)/2;
  if(mid>=pos) update(l,mid,T[x].l,T[y].l,pos,val);
  else update(mid+1,r,T[x].r,T[y].r,pos,val);

}

int query(int l,int r,int pos,int y){
  if(l==r) return T[y].sum;
  int mid=(l+r)/2;
  if(pos <= mid)
        return query(l,mid,pos,T[y].l) + T[T[y].r].sum;
  else
      return query(mid+1,r,pos, T[y].r);
}

int main(){
    init();
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    int tmp;
    for(int i=1;i<=n;i++){
        if(mp[a[i]]==0){
           update(1,n,root[i],root[i-1],i,1);
          mp[a[i]]=i;
        }
        else{
            update(1,n,tmp,root[i-1],mp[a[i]],-1);
            update(1,n,root[i],tmp,i,1);
            mp[a[i]]=i;
         }
    }
    for(int i=1;i<=q;i++)
    {
        int l,r;
        scanf("%d%d",&l,&r);
        printf("%d\n",query(1,n,l,root[r]));
    }
  }
