####bitset
+ bitset<100000>bt;
+ bt<<1; //整体移位
+ bt|=10;
+ bt.count(); //b中置为1的二进制位的个数
+ bt.size(); //b中二进制位的个数
+ bt[pos]; //访问b中在pos处的二进制位
+ bt.test(pos); //b中在pos处的二进制位是否为1
+ bt.set(); //把b中所有二进制位都置为1
+ bt.set(pos); //把b中在pos处的二进制位置为1
+ bt.reset(); //把b中所有二进制位都置为0
+ bt.reset(pos); //把b中在pos处的二进制位置为0