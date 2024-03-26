#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

/* Phan A:
    Cau 1:
    - Dia chi cua cac phan tu trong mang se tang dan, hon kem nhau dung bang so byte dung de luu tru kieu do, vi du int la 4 byte.
    - Cac bien duoc khai bao truoc, sau hoac giua hai mang tren co vi tri tuong doi cach nhau tuy thuoc vao so phan tu trong mang (tat nhien theo so byte luu tru cua kieu du lieu)
    Cau 2:
    Cac chuoi gia tri dia chi duoc in ra cach deu nhau mot khoang 40 (theo he hexa). Kich thuoc cua mot stack frame cho ham factorial la khoang 64 byte khi dung kieu long long va 48 byte
    khi dung kieu int.
    Cau 3:
    void passByValue(int n)
    {
    cout << &n << endl;
    }
    void passByReference(int &n)
    {
    cout << &n << endl;
    }
    int main()
    {
    int n; cin >> n;
    cout << &n << endl;
    passByReference(n); passByValue(n);
    return 0;
    }
    output cho ra 0x61fe1c 0x61fe1c 0x61fdf0
    Cau 4:
    a, Mang duoc truyen vao ham theo co che pass-by-reference
    b, C++ string duoc truyen vao ham theo co che pass-by-value
    Cau 5:
    int main()
    {
        int a=4, c=5;
        int &b=a;
        cout << &a << " "<< &b << endl;
        b=c;
        cout << &c << " " << &b << endl;
    }
    a, Bien tham chieu va bien ma no chieu toi la cung mot bien trong bo nho.
    b, Khong the khai bao mot bien tham chieu ma chua chieu ngay no toi mot bien thuong.
    c, Khong the chieu mot tham chieu toi mot bien khac voi dich ban dau cua no, tuc nhu o doan code tren, b van chieu toi a sau khi da gan voi c.
    Cau 6:
    Khi chay xong ham f, ham f duoc giai phong khoi bo nho va chay den ham g, khi do ham g lai the cho vao bo nho cua ham f (nhat la khi hai ham cung kieu void, tham so
    giong nhau cung dang int) nen ket qua dua ra 2 dia chi giong nhau.

*/
bool majority(bool a, bool b, bool c)
{
    return a&&b || b&&c || a&&c;
}
bool eq(int a[], int size_a, int b[], int size_b, int n)
{
    int cnt=0, i=0, j=0;
    sort(a, a+size_a); sort(b, b+size_b);
    while (i<size_a && j <size_b){
        if (a[i]==b[j]){
            cnt++;
            if (cnt==n) return true;
            i++; j++;
        }
        else{
            cnt=0; i++;
        }
    }
    return false;
}
bool checkPrime(int n)
{
    for (int i=0; i<=sqrt(n); i++){
        if (n%i==0)return false;
    }
    return n>1;
}
void swap(int *a, int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
int gcd(int a, int b)
{
    if (a<b){
        swap(a,b);
    }
    int r=a%b;
    while (r!=0){
        a=b;
        b=r;
        r=a%b;
    }
    return b;
}
void printLine(int m, int n)
{
    for (int i=0; i<m; i++){
        cout << " ";
    }
    for (int i=0; i<n; i++){
        cout << "*";
    }
    cout << endl;
}
void printTriangle(int lines)
{
    for (int i=0; i<lines; i++){
        printLine(lines-i-1, 2*i+1);
    }
}
int function_rnd(double x)
{
    int res;
    if (x+0.5 < ceil(x))
    {
        res=floor(x);
    }
    else{
        res=ceil(x);
    }
    return res;
}
int basic_rnd(double x)
{
    int temp=(int)x;
    if (x-(double)temp >= 0.5) return temp+1;
    return temp;
}
int lessThan(int n)
{
    return rand()%n;
}
void threeDivide25(int a[], int n)
{
    for (int i=0; i<n; i++){
        for (int j=i+1; j<n; j++){
            for (int k=j+1; k<n; k++){
                if ((a[i]+a[j]+a[k])%25==0) cout << a[i] << " " << a[j] << " " << a[k] << endl;
            }
        }
    }
}
string tenToTwo(int n)
{
    string binary="";
    while (n!=0){
        if (n%2==0) binary+='0';
        else binary+='1';
        n/=2;
    }
    reverse(binary.begin(), binary.end());
    return binary;
}
int twoToTen(string binary)
{
    int decimal=0;
    int len=binary.length();
    reverse(binary.begin(), binary.end());
    for (int i=0; i<len; i++){
        if (binary[i]=='1') decimal+=pow(2,i);
    }
    return decimal;
}
int factorial(int n)
{
    int res=1;
    for (int i=1; i<=n; i++){
        res*=i;
    }
    return res;
}
int toHop(int k, int n)
{
    return factorial(n)/(factorial(k)*(factorial(n-k)));
}
int kiemtra(int k, int n)
{
    if (k>=0 && k<=n && n>=1 && n<=20) return 1;
    return 0;
}
//void nhapKN(int k[], int n[], int *soPhanTu)
//{
//    *soPhanTu=0;
//    while (true){
//        cin >> k[*soPhanTu] >> n[*soPhanTu];
//        if (k[*soPhanTu]==-1 || n[*soPhanTu]==-1) break;
//        soPhanTu++;
//    }
//}
int main()
{
    srand(time(NULL));
    int n; cin >> n;
    int a[n];
    for (int i=0; i<n; i++){
        a[i]=rand()%50;
    }
    threeDivide25(a,n);
}
