typedef complex<double> cd;
void fft(cd *a, int n,int f) {
   for(int i = 0;i < n;i ++)
         if(i < rev[i])
             swap(a[i], a[rev[i]]);
     for(int i = 1;i < n;i <<= 1) {
         cd wn(cos(pi / i), sin(f * pi / i)), x, y;
         for(int j = 0;j < n;j += (i << 1)) {
             cd w(1, 0);
             for(int k = 0;k < i;k ++, w *= wn) {
                 x = a[j + k], y = w * a[i + j + k];
                 a[j + k] = x + y;
                 a[i + j + k] = x - y;
             }
         }
     }
 }

  for(N = 1;N <= (M + 1) * 2;N <<= 1) bit++; //bit为数组的大小
  
  for(int i = 0;i < N;i ++)
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (bit - 1));

  for(int i=0;i<N;i++)
      d[i]=(ll)(c[i].real()/N+0.5);//四舍五入