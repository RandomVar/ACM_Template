
const double eps = 1e-8;
const double PI = acos(-1.0);
int sgn(double x) {/*判断x的正负性*/
    if(fabs(x) < eps) return 0;
    if(x < 0)return -1;
    else return 1;
     }

/****Point 定义*****/
struct Point {
    double x,y;
    Point(){};
    Point(double _x,double _y){x=_x;y=_y;}
    Point operator- (const Point &b){
     return Point(x-b.x,y-b.y);
    }

    double operator^ (const Point &b){
    return x*b.y-y*b.x;
    }
    double operator*(const Point &b){
    return x*b.x+y*b.y;
    }
    };

/*判断点c是否在线段ab上 已验证*/
bool onseg(Point a,Point b,Point c){
 if(sgn((b-a)^(c-a))==0&&
    sgn((c.x-a.x)*(c.x-b.x))<= 0 && sgn((c.y-a.y)*(c.y-b.y))<= 0)
        return 1;
 return 0;
}

/****Line 定义****/
struct Line{
 Point s,t;
 Line(){};
 Line(Point _s,Point _t){s=_s;t=_t;}
};

/*判断线段是否相交 51Nod - 1264 已验证*/
/*为1则相交*/
bool inter(Line l1,Line l2){
 if(sgn((l1.s-l2.s)^(l1.s-l1.t))*sgn((l1.s-l1.t)^(l1.s-l2.t))<0) return 0;
 if(sgn((l2.s-l1.s)^(l2.s-l2.t))*sgn((l2.s-l2.t)^(l2.s-l1.t))<0) return 0;
 if(min(l1.s.x,l1.t.x)<=max(l2.s.x,l2.t.x)&&min(l1.s.y,l1.t.y)<=max(l2.s.y,l2.t.y)
    &&min(l2.s.x,l2.t.x)<=max(l1.s.x,l1.t.x)&&min(l2.s.y,l2.t.y)<=max(l1.s.y,l1.t.y))
        return 1;
 return 0;
}

/*计算多边形面积*/
double calarea(Point p[],int n){
 double res=0;
 for(int i=0;i<n;i++){
    res+=(p[i]^p[(i+1)%n])/2;
 }
 return fabs(res);
}

int gcd ( int a,int b){
	if(b==0) return a;
	else return gcd(b,a%b);
}

/*多边形边上整点数*/
int onedge(Point p[],int n){
 int ans=0;
 for(int i=0;i<n;i++){
    ans+=gcd(fabs(p[(i+1)%n].x-p[i].x),fabs(p[(i+1)%n].y-p[i].y));
 }
 return ans;
}
/*多边形内部整点数 s（面积）=l/2（边上整点数/2）+n(内部整点数）-1*/
int inside(Point p[],int n){
 return calarea(p,n)+1-onedge(p,n)/2;
}

/*点在多边形内 ZOJ - 1081 已验证*/
/*射线法，poly[]的顶点数要大于等于3,点的编号0~n-1*/
/*返回值 -1:点在凸多边形外 0:点在凸多边形边界上 1:点在凸多边形内*/
int inPoly(Point p,Point poly[],int n){
 Point p1(-INF+100,p.y);
 Line ray(p,p1);
 Line side;
 int cnt=0;
 for(int i=0;i<n;i++){
    side.s=poly[i];
    side.t=poly[(i+1)%n];
    if(onseg(side.s,side.t,p)) return 0;
    if(sgn(side.s.y-side.t.y)==0) continue;//平行轴不考虑

    if(onseg(ray.s,ray.t,side.s)){
       if(sgn(side.s.y-side.t.y)>0) cnt++;}
   else if(onseg(ray.s,ray.t,side.t)){
      if(sgn(side.t.y-side.s.y)>0) cnt++;}
    else if(inter(side,ray)) cnt++;
 }
  if(cnt%2) return 1;
 return -1;
}

/*判断凸多边形*/
/*点的编号1~n-1 凸边形为true*/
bool isconvex(Point poly[],int n) {
    bool s[3];
    memset(s,false,sizeof(s));
    for(int i = 0;i < n;i++)  {
            s[sgn( (poly[(i+1)%n]-poly[i])^(poly[(i+2)%n]-poly[i]) )+1] = true;
  if(s[0] && s[2])
    return false;  }
return true; }



double dissq(Point a,Point b){
return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
/*求凸包，Graham算法*/
/*返回凸包结果st[0~top-1]为凸包边上的点编号 top为凸包边上的点的总数*/
Point lis[maxn];
int st[maxn],top;
bool cmp(Point a,Point b){
    int flag=sgn((a-lis[0])^(b-lis[0]));
 if(flag>0) return 1;
 if(flag==0&&sgn(dissq(a,lis[0])-dissq(b,lis[0]))<=0) return 1;
 return 0;
}

void graham(int n){
  Point p0;
  p0=lis[0];int k=0;
  for(int i=1;i<n;i++){
    if((p0.y>lis[i].y)||(p0.y==lis[i].y&&p0.x>lis[i].x)){
        p0=lis[i];
        k=i;
    }
  }
  lis[k]=lis[0];
  lis[0]=p0;
  sort(lis+1,lis+n,cmp);
  if(n==1){
    st[0]=0;
    top=1;
    return;
  }
  if(n==2){
    st[0]=0;
    st[1]=1;
    top=2;
    return;
  }
  st[0]=0;
  st[1]=1;
  top=2;
  for(int i=2;i<n;i++){
   while(top>1&&sgn((lis[st[top-1]]-lis[st[top-2]])^(lis[i]-lis[st[top-2]]))<=0)
        top--;
    st[top++]=i;


  }

}

