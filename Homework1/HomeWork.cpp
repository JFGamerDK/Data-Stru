#include <iostream>
using namespace std;
long long t=1;
long long arrack[5][10000];
long long ackermanfunction(int m,int n)//一般遞迴函式
{
    
    //cout<<"t= "<<t<<"  "<<m<<","<<n<<endl;
    if(m==0)
    {
        //cout<<"Ackermanfunction = "<<n+1<<endl;
        t++;
        return n+1;
    }
    else if(m>0 && n == 0)
    {
        //cout<<"Ackermanfunction = ("<<m-1<<","<<n<<" )"<<endl;
        t++;
        return ackermanfunction(m-1,1);
    }
    else if(m>0&&n>0)
    {
        //cout<<"Ackermanfunction = ("<<m-1<<", next function )"<<endl;
        t++;
        return ackermanfunction(m-1,ackermanfunction(m,n-1));
    }
}
long long aryackmanfunction(int m,int n)//採用矩陣優化
{
    if(arrack[m][n]!=-1)//排除掉計算過的
    {
        return arrack[m][n];
    }

    if(m == 0)
    {
        arrack[m][n] = n + 1;
        t++;
    }
    else if(m>0 && n == 0)
    {
        arrack[m][n] = aryackmanfunction(m - 1, 1);
        t++;
    }
    else if((m>0 && n>0))
    {
        arrack[m][n] = aryackmanfunction(m - 1, aryackmanfunction(m, n - 1));
        t++;
    }
    return arrack[m][n];
}
int main()
{
    for (int i = 0; i < 5; i++)//初始化矩陣元素皆為-1
    {
        for (int j = 0; j < 10000; j++) 
        {
            arrack[i][j] = -1;
        }    
    }
    int num=0,m=0,n=0;
    cout<<"輸入阿克曼函數(m,n)數值\n";
    cin>>m>>n;
    cout<<"m= "<<m<<"  n= "<<n<<endl;
    int rem=m,ren=n;
    cout<<"Ackermann's function = "<< ackermanfunction(m,n) <<" 函數計算次數為 "<<t<<endl;t=0;
    cout<<"Array Ackermann's function = "<< aryackmanfunction(rem,ren) <<"  函數計算次數為 "<<t<<endl;
}