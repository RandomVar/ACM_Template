/****单点更新 HDU - 1166****/
T tree[maxn<<2];

void pushup(int rt){
  tree[rt]=tree[rt*2]+tree[rt*2+1];
}

void build(int l,int r,int rt){
  if(l==r) {
      //scanf("%d",&tree[rt]);
      return;
      }
  int mid=(l+r)/2;
  build(l,mid,rt*2);
  build(mid+1,r,rt*2+1);
  pushup(rt);
}

T query(int l,int r,int L,int R,int rt){
 if(l>=L&&r<=R) 
       return tree[rt];
 T ans=0;
 int mid=(l+r)/2;
 if(L<=mid){
    ans+=query(l,mid,L,R,rt*2);
 }
 if(R>mid){
    ans+=query(mid+1,r,L,R,rt*2+1);
 }
 return ans;
}

void update(int l,int r,int index,T add,int rt){
  if(l==r) {
    tree[rt]+=add;
    return;
  }
  int mid=(l+r)/2;
  if(index<=mid)
    update(l,mid,index,add,rt*2);

  else update(mid+1,r,index,add,rt*2+1);
  pushup(rt);
}


/****区间更新 poj-3468****/
T tree[maxn<<2];
T seg[maxn<<2];
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
    //scanf("%d",&tree[rt]);
    return;}
  int mid=(l+r)/2;
  build(l,mid,rt*2);
  build(mid+1,r,rt*2+1);
  pushup(rt);
}
void update(int l,int r,int L,int R,T add,int rt){
  if(l>=L&&r<=R) {
    seg[rt]+=add;
    tree[rt]+=(r-l+1)*add;
    return;
  }
  pushdown(r-l+1,rt);
  int mid=(l+r)/2;
  if(L<=mid) 
    update(l,mid,L,R,add,rt*2);
  
  if(R>mid)
    update(mid+1,r,L,R,add,rt*2+1);
  
  pushup(rt);
}

T query(int l,int r,int L,int R,int rt){
  if(l>=L&&r<=R){
     return tree[rt];
  }
  T ans=0;
  pushdown(r-l+1,rt);
  int mid=(l+r)/2;
  if(L<=mid) ans+=query(l,mid,L,R,rt*2);
  if(R>mid) ans+=query(mid+1,r,L,R,rt*2+1);
  return ans;
}
