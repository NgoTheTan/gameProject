#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>

using namespace std;

/*Cau 1:
    a.Khi khai bao mang ngoai ham main, cac gia tri cua mang duoc gan voi gia tri mac dinh la 0. Nguoc lai trong ham main thi gia tri la cac so sinh ngau nhien.
    b.Khi N>4, cac gia tri khac cua mang deu bang 0 du khai bao trong hay ngoai ham main. Khi N<4 se bi loi tran mang va run-time vi so luong phan tu trong day khai bao nhieu hon
    so kich thuoc khai bao cua mang.
    c. Khi khai bao theo dang a[]={1,2,3,4} thi du o trong hay ngoai ham main, mang chi co 4 phan tu la 1 2 3 4.
  Cau 2:
    a.Neu khong khoi tao gia tri thi trong hay ngoai ham main deu gap loi bien dich vi thieu kich thuoc cua mang a.
    b. char a[N]="abcd" neu N>4 thi khong co loi, nho hon hoac bang 4 thi co loi tran kich thuoc mang. Gia tri cua mang van la {'a','b','c','d','/0'} du trong hay ngoai main;
    c. Kich thuoc mang thuc la 5. tim bang phep tinh sizeof(a)/sizeof(char);
    => Mang co kich thuoc N luu duoc xau co do dai toi da N-1;
  Cau 3:
    a. Hieu qua khoi tao la nhu nhau
    b. Voi cach khoi tao chia thanh 2 mang con thi khi xoa bot phan tu, phan tu khong nhan gia tri tai moi mang se nhan gia tri bang 0. Con voi cach khai bao gop lai thanh 1 thi
    khi xoa bot phan tu, cac phan tu co gia tri bang 0 nam o cuoi dong 2 (tuc o vi tri cuoi cung cua mang).
    c. Chi co the bo bot so cot 12 di.
  Cau 4:
    a. Khong bi loi (vi C++ khong check tran mang). Cac gia tri in ra la ngau nhien (khac gia tri khoi tao la 0) nen biet duoc rang dang truy cap ngoai mang, chi duy co truong hop
    chi so <0 nhu -1 -2 -3 thi in ra gia tri bang 0.
    c. Mang nhieu chieu co dinh so phan tu dung bang gia tri da khai bao, khong bi tran mang.
  Cau 5:

*/

string findDuplicate(const int a[],const int n)
{
    bool seen[n]={};
    for (int i=0; i<n; i++){
        if (seen[a[i]-1]) return "Yes";
        seen[a[i]-1]=true;
    }
    return "No";
}
string xauDoiXung(const char a[], const int len)
{
    int i=0, j=len-1;
    while (i<j){
        if (a[i]!=a[j]) return "No";
        i++; j--;
    }
    return "Yes";
}
bool checkSoDoiGuong(const int n)
{
    int temp1=n, temp2=n, reversedN=0, cnt=0;
    while (temp1!=0){
        cnt++;
        temp1/=10;
    }
    while (temp2!=0){
        int digit=temp2%10;
        if (digit!=0){
            for (int i=0; i<cnt-1; i++){
                digit*=10;
            }
            reversedN+=digit;
        }
        cnt--;
        temp2/=10;
    }
    if (reversedN==n) return true;
    return false;
}
int soDoiGuong(const int a,const int b)
{
    int cnt=0;
    for (int i=a; i<=b; i++){
        if (checkSoDoiGuong(i)) cnt++;
    }
    return cnt;
}
void mineSwepper(char a[][10], const int m, const int n)
{
    if (a[0][0]!='*'){
        int cnt=0;
        if (a[0][1]=='*') cnt++;
        if (a[1][0]=='*') cnt++;
        if (a[1][1]=='*') cnt++;
        a[0][0]=cnt+'0';
    }
    if (a[m-1][0]!='*'){
        int cnt=0;
        if (a[m-2][0]=='*') cnt++;
        if (a[m-1][1]=='*') cnt++;
        if (a[m-2][1]=='*') cnt++;
        a[m-1][0]=cnt+'0';
    }
    if (a[0][n-1]!='*'){
        int cnt=0;
        if (a[0][n-2]=='*') cnt++;
        if (a[1][n-1]=='*') cnt++;
        if (a[1][n-2]=='*') cnt++;
        a[0][n-1]=cnt+'0';
    }
    if (a[m-1][n-1]!='*'){
        int cnt=0;
        if (a[m-1][n-2]=='*') cnt++;
        if (a[m-2][n-1]=='*') cnt++;
        if (a[m-2][n-2]=='*') cnt++;
        a[m-1][n-1]=cnt+'0';
    }
    for (int i=1; i<m-1; i++){
        if (a[i][0]!='*'){
            int cnt=0;
            if (a[i-1][0]=='*') cnt++;
            if (a[i-1][1]=='*') cnt++;
            if (a[i][1]=='*') cnt++;
            if (a[i+1][0]=='*') cnt++;
            if (a[i+1][1]=='*') cnt++;
            a[i][0]=cnt+'0';
        }
    }
    for (int i=1; i<m-1; i++){
        if (a[i][n-1]!='*'){
            int cnt=0;
            if (a[i-1][n-1]=='*') cnt++;
            if (a[i-1][n-2]=='*') cnt++;
            if (a[i][n-2]=='*') cnt++;
            if (a[i+1][n-1]=='*') cnt++;
            if (a[i+1][n-2]=='*') cnt++;
            a[i][n-1]=cnt+'0';
        }
    }
    for (int i=1; i<n-1; i++){
        if (a[0][i]!='*'){
            int cnt=0;
            if (a[0][i+1]=='*') cnt++;
            if (a[0][i-1]=='*') cnt++;
            if (a[1][i]=='*') cnt++;
            if (a[1][i-1]=='*') cnt++;
            if (a[1][i+1]=='*') cnt++;
            a[0][i]=cnt+'0';
        }
    }
    for (int i=1; i<n-1; i++){
        if (a[m-1][i]!='*'){
            int cnt=0;
            if (a[m-1][i+1]=='*') cnt++;
            if (a[m-1][i-1]=='*') cnt++;
            if (a[m-2][i]=='*') cnt++;
            if (a[m-2][i-1]=='*') cnt++;
            if (a[m-2][i+1]=='*') cnt++;
            a[m-1][i]=cnt+'0';
        }
    }
    for (int i=1; i<m-1; i++){
        for (int j=0; j<n-1; j++){
            if (a[i][j]!='*'){
                int cnt=0;
                if (a[i-1][j-1]=='*') cnt++;
                if (a[i-1][j]=='*') cnt++;
                if (a[i-1][j+1]=='*') cnt++;
                if (a[i][j-1]=='*') cnt++;
                if (a[i][j+1]=='*') cnt++;
                if (a[i+1][j-1]=='*') cnt++;
                if (a[i+1][j]=='*') cnt++;
                if (a[i+1][j+1]=='*') cnt++;
                a[i][j]=cnt+'0';
            }
        }
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
void snailArray(const int m, const int n)
{
    int a[m][n]={{},{}};
    int maximum=m*n, k=1;
    int chieu_dai=n, chieu_rong=m, i=0, j=0, rounds1=0, rounds2=1;
    while (k<=maximum){
        while (j<chieu_dai){
            a[i][j]=k;
            k++;
            j++;
        }
        if (k>maximum) break;
        j--; k--;
        while (i<chieu_rong){
            a[i][j]=k;
            k++;
            i++;
        }
        if (k>maximum) break;
        i--; k--;
        while (j>=rounds1){
            a[i][j]=k;
            k++;
            j--;
        }
        if (k>maximum) break;
        j++; k--;
        while (i>=rounds2){
            a[i][j]=k;
            k++;
            i--;
        }
        if (k>maximum) break;
        i++; k--;
        chieu_dai--; chieu_rong--; rounds1++; rounds2++;
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
void magicalArray(const int n)
{
    int count=1;
    int a[n][n];
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            a[i][j]=0;
        }
    }
    a[0][n/2]=1;
    int x=0;
    int y=n/2;

    for(int i=0; i<n*n; i++){
        if(x==0 and (y!=n-1) and a[n-1][y+1]==0){
            x=n-1;
            y++;
            count++;
            a[x][y]=count;
        } else if(x!=0 and y!=n-1 and a[x-1][y+1]==0){
            x=x-1;
            y++;
            count++;
            a[x][y]=count;
        } else if(x!=0 and y==n-1 and a[x-1][0]==0){
            x=x-1;
            y=0;
            count++;
            a[x][y]=count;
        } else if(x!=0 and y!=n-1 and a[x-1][y+1]!=0){
            x=x+1;
            count++;
            a[x][y]=count;
        } else if(x==0 and y==n-1){
            x=x+1;
            count++;
            a[x][y]=count;
        }
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}
int main()
 {
    /* cau 6 phan a
    int n=30;
    srand(time(NULL));
    int a[n];
    for (int i=0; i<n; i++){
        a[i]=rand()%10;
    }
    for (int i=0; i<n; i++){
        cout << a[i] << " ";
    }
    cout << endl;
    for (int k = n - 1; k > 0; k--){
        bool swapped = false;
        for (int i = 1; i <= k; i++){
            if (a[i-1] > a[i]){
                int temp = a[i];
                a[i] = a[i-1];
                a[i-1] =  temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
    for (int i=0; i<n; i++){
        cout << a[i] << " ";
    }*/
    int n; cin >> n;
    magicalArray(n);
    return 0;
 }
