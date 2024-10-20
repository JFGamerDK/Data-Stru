#include <iostream>
#include <vector>
#include <string>
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
void generatesubsets(vector<string>&s, vector<string>&nowSet, int index, vector<vector<string>>&allsubsets)
{
    allsubsets.push_back(nowSet);
    for (int i = index; i < s.size(); ++i) 
    {
        nowSet.push_back(s[i]);//將目前的元素加入到子集合中
        generatesubsets(s, nowSet, i + 1, allsubsets);// 遞迴生成包含目前元素的子集
        nowSet.pop_back();// 回朔，移除當前元素，繼續生成其他子集
    }
}
int main()
{
    int num=0;
    vector<string> s;
    vector<vector<string>> allsubsets;
    vector<string> nowSet;
    for (int i = 0; i < 5; i++)//初始化矩陣元素皆為-1
    {
        for (int j = 0; j < 10000; j++) 
        {
            arrack[i][j] = -1;
        }    
    }
    int m=0,n=0;
    cout<<"輸入阿克曼函數(m,n)數值\n";
    cin>>m>>n;
    cout<<"m= "<<m<<"  n= "<<n<<endl;

    cout << "請输入集合中的元素,元素可以是數字或是字母,以空格分隔,結束輸入按下Enter: ";
    string input;
    while (cin >> input) 
    {
        s.push_back(input);
        if (cin.peek() == '\n') break; // 按下Enter結束輸入
    }
    generatesubsets(s, nowSet, 0, allsubsets);
    cout<<"所有子集合為: "<<endl;
    for (const auto& subset : allsubsets) 
    {
        cout << "{ ";
        for (const auto& elem : subset) 
        {
            cout << elem << " ";
        }
        cout << "}" << endl;
    }
    int rem=m,ren=n;
    cout<<"Ackermann's function = "<< ackermanfunction(m,n) <<" ,函數計算次數為 "<<t<<endl;t=0;
    cout<<"Array Ackermann's function = "<< aryackmanfunction(rem,ren) <<"  ,函數計算次數為 "<<t<<endl;
}