/*
莫队算法复杂度 O(n*sqrt(n))
NBUT-1457
*/
ll lastans;
int block;

struct node{
 int l,r,id;
 int pos;//分块
 void init(){
  pos=l/block;
 }
 bool operator<(const node &a)const{
   if(pos==a.pos) return r<a.r;
   return pos<a.pos;
 }
}q[maxn];

void addl(){

}
void dell(){

}
void addr(){

}
void delr(){

}

  block=sqrt(n+0.5);//
  for(int i=1;i<=m;i++)
  {
    scanf("%d%d",&q[i].l,&q[i].r);
    q[i].id=i;
    q[i].init();
   }
   sort(q+1,q+m+1);
  int lastl=2,lastr=1;
   lastans=0;
    for(int i=1;i<=m;i++)
     {
        while(lastl>q[i].l) dell(--lastl);
        while(lastr<q[i].r) addr(++lastr);
        while(lastl<q[i].l) addl(lastl++);
        while(lastr>q[i].r) delr(lastr--);
       ans[q[i].id]=lastans;
     }
  for(int i=1;i<=m;i++)
    printf("%lld\n",ans[i]);

