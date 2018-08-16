/*c++格式化 long double的输出*/
 long double t1 = (l - t2 * v2) / v1;
cout << fixed << setprecision(10) << t1 + t2 << endl;//保留10位小数

/*大小写转换函数*/
a=tolower(a);
b=toupper(b);

/**sstream**/
string  sstream
string str; getline(cin,str);
stringstream ss(str);//对string对象进行读写
while(ss>>x)
   s.compare(b);

ss.clear();//多次使用stringstream，要先清空下
/**stringstream可以用来把string类型的字符串转换成int **/
string s("12345");
int x;
stringstream ss(s);
ss>>x;
/**法二**/
string s("12345");
int x;
stringstream ss;
ss<<s;
ss>>x;

/**将多种数值转换成字符串**/
typename x=5.222;
cin>>x;
stringstream ss;
ss<<x;
string s;
s=ss.str(); //s="5.222"

/**字符串处理*/
    char s[] = "a,b*c,d";
    const char *sep = ",*"; //可按多个字符来分割
    char *p;
    p = strtok(s, sep);// 在第一次被调用的时间str是传入需要被切割字符串的首地址；在后面调用的时间传入NULL
    while(p){
        printf("%s ", p);
        p = strtok(NULL, sep);
    }

/*取子串*/
string sub1 = s.substr(5); //从下标为5开始一直到结尾
string sub2 = s.substr(5, 3); //从下标为5开始截取长度为3位


/*algorithm*/
sort(a,a+n);//n为数列长度，即a+n为最后一个数的位置+1
lower_bound(a,a+n,x)-a;//在已排序数组a中寻找x ,查找"大于或者等于x的第一个位置”。
upper_bound(a,a+n,x)-a;//返回第一个大于x的位置
vector<int>a a.push_back(); //尾部添入元素
            a.pop_back();
			a.clear(); a.empty(); a.size() a.resize();


/*set*/
set<string>dict; //自动从小到大排好序，每个元素至多出现一次
dict.insert(buf);
dict.erase(buf);
set<string>::iterator it;
for(it=dict.begin();it!=dict.end();it++)
  cout<<*it<<endl;


/**map**/
map<string,int>cnt;
cnt.size() cnt.count(r)//是否存在r
map<int, string>::iterator it;
       for(it=mp.begin();it!= mp.end();it++)
       {
          cout<<it->first<<"   "<<it->second<<endl;
       }

it=mp.find(1);
if(it!=mp.end()){//它返回的一个迭代器;如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器
    cout<<it->second()<<endl;
}

mp.count(1);//出现过则返回 1，未出现则返回0
mp.find(t)!=mp.end()//判断是否存在

/**queue and stack**/
queue<int>q;

priority_queue<int>s;
priority_queue<int，vector<int>，greater<int>>pq;//越小的整数优先级越大的优先队列

stack<int>st;
st.push();


/**去重操作*/
vector<int>v;
int getid(int x){
 return lower_bound(v.begin(),v.end(),x)-v.begin()+1;
}

 for(int i=1;i<=n;i++)
        scanf("%d",&a[i]),v.push_back(a[i]);
    sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end());

getid(x);//取x离散化后的下标
v[id];//找到其离散前的元素

/*bitset*/
bitset<100000>bt;
bt<<1;//整体移位
bt|=10;
bt.count();//b中置为1的二进制位的个数
bt.size();//b中二进制位的个数
bt[pos];//访问b中在pos处的二进制位
bt.test(pos);//b中在pos处的二进制位是否为1？
bt.set();//把b中所有二进制位都置为1
bt.set(pos);//把b中在pos处的二进制位置为1
bt.reset();//把b中所有二进制位都置为0
bt.reset(pos);//把b中在pos处的二进制位置为0