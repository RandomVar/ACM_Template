/****������� �����ѯ HDU - 1166****/
int tree[maxn<<2];

void pushup(int rt){
  tree[rt]=tree[rt*2]+tree[rt*2+1];
}

void build(int l,int r,int rt){
  if(l==r) {scanf("%d",&tree[rt]);return;}
  int mid=(l+r)/2;
  build(l,mid,rt*2);
  build(mid+1,r,rt*2+1);
  pushup(rt);
}

int query(int l,int r,int ll,int rr,int rt){//l,rΪ��ǰ�߽�
 if(l>=ll&&r<=rr) return tree[rt];
 int ans=0;int mid=(l+r)/2;
 if(ll<=mid){
    ans+=query(l,mid,ll,rr,rt*2);
 }
 if(rr>mid){
    ans+=query(mid+1,r,ll,rr,rt*2+1);
 }
 return ans;
}

void update(int l,int r,int index,int add,int rt){
  if(l==r) {
    tree[rt]+=add;return;
  }
  int mid=(l+r)/2;
  if(index<=mid){
    update(l,mid,index,val,rt*2);
  }
  else update(mid+1,r,index,val,rt*2+1);
  pushup(rt);
}


/****������� poj-3468****/
int tree[maxn<<2];
int seg[maxn<<2];
void pushup(int rt){
 tree[rt]=tree[rt*2]+tree[rt*2+1];

}
void pushdown(int len,int rt){
  if(seg[rt]){
    seg[rt*2]+=seg[rt];
    seg[rt*2+1]+=seg[rt];
    tree[rt*2]+=(len-len/2)*seg[rt];
    tree[rt*2+1]+=len/2*seg[rt];
    seg[rt]=0;
  }
}
void build(int l,int r,int rt){
  seg[rt]=0;
  if(l==r) {
    scanf("%d",&tree[rt]);return;}
  int mid=(l+r)/2;
  build(l,mid,rt*2);
  build(mid+1,r,rt*2+1);
  pushup(rt);
}
void update(int l,int r,int ll,int rr,int add,int rt){//l,rΪ��ǰ���䣬ll,rrΪ���µ�����
  if(l>=ll&&r<=rr) {
    seg[rt]+=add;tree[rt]+=(r-l+1)*add;
    return;
  }
  pushdown(r-l+1,rt);
  int mid=(l+r)/2;
  if(ll<=mid) {
    update(l,mid,ll,rr,add,rt*2);
  }
  if(rr>mid){
    update(mid+1,r,ll,rr,add,rt*2+1);
  }
  pushup(rt);
}

int query(int l,int r,int ll,int rr,int rt){//ll,rrΪ��ѯ������
  if(l>=ll&&r<=rr){
     return tree[rt];
  }
  int ans=0;
  pushdown(r-l+1,rt);
  int mid=(l+r)/2;
  if(ll<=mid) ans+=query(l,mid,ll,rr,rt*2);
  if(rr>mid) ans+=query(mid+1,r,ll,rr,rt*2+1);
  return ans;
}

/**��ϯ��������£������k�� POJ 2104*/
int n,m,cnt;
int root[maxn],a[maxn];
int x,y,k;
struct node{
  int l,r,sum;
}T[maxn*40];
vector<int>v;
/*������ɢ��*/
int getid(int x){
 return lower_bound(v.begin(),v.end(),x)-v.begin()+1;

}
void init()
{
    cnt=0;
    root[0]=0;
    T[0].l = T[0].r = T[0].sum = 0;
    v.clear();
}

void update(int l,int r,int &x,int y,int pos){
  T[++cnt]=T[y];
  T[cnt].sum++;
  x=cnt;
  if(l==r) return ;
  int mid=(l+r)/2;
  if(mid>=pos) update(l,mid,T[x].l,T[y].l,pos);
  else update(mid+1,r,T[x].r,T[y].r,pos);

}
int query(int l,int r,int x,int y,int k){
  if(l==r) return l;
  int mid=(l+r)/2;
  int sum=T[T[y].l].sum-T[T[x].l].sum;
  if(sum>=k) return query(l,mid,T[x].l,T[y].l,k);
  else return query(mid+1,r,T[x].r,T[y].r,k-sum);

}
int main(){
  while(scanf("%d%d",&n,&m)==2){
    init();
    //cnt=0;
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),v.push_back(a[i]);
    sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());

    for(int i=1;i<=n;i++)
         update(1,n,root[i],root[i-1],getid(a[i]));
    while(m--){
        int l,r,k;
        scanf("%d%d%d",&x,&y,&k);
        printf("%d\n",v[query(1,n,root[x-1],root[y],k)-1]);
    }
  }
return 0;
}



/**��ϯ��������� HDU 4348*/
const int maxn=1e5+100;
struct node{
 int l;int r;
 ll lazy;
 ll sum;

}T[maxn*40];
int cnt;
int root[maxn];
void pushup(int x,int len){
   T[x].sum=T[T[x].l].sum+T[T[x].r].sum+T[x].lazy*len;

}

void build(int l,int r,int &x){
   x=++cnt;
   if(l==r) {
    T[x].lazy=0;
      scanf("%lld",&T[x].sum);
      return ;
   }
   int mid=(l+r)/2;
   build(l,mid,T[x].l);
   build(mid+1,r,T[x].r);
   pushup(x,r-l+1);
}

void update(int l,int r,int L,int R,int &x,int y,int val){
   T[++cnt]=T[y];
   x=cnt;
   if(l>=L&&r<=R){
      T[x].lazy+=val;
      T[x].sum+=(r-l+1)*val;
      return;
   }
   int mid=(l+r)/2;
   if(mid>=L)   update(l,mid,L,R,T[x].l,T[y].l,val);
   if(mid<R) update(mid+1,r,L,R,T[x].r,T[y].r,val);
  pushup(x,r-l+1);

}
ll query(int l,int r,int L,int R,ll adv,int x){
 if(l>=L&&r<=R){
    return T[x].sum+adv*(r-l+1);

 }
  adv+=T[x].lazy;
  int mid=(l+r)/2;
  ll sum=0;
  if(L<=mid) sum+=query(l,mid,L,R,adv,T[x].l);
   if(R>mid) sum+=query(mid+1,r,L,R,adv,T[x].r);
 return sum;
}
