#include <bits/stdc++.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
void f(int a[])
{
    cout << sizeof(a) << endl; // in ra dung kich thuoc cua mot bien int* la 8, du kich thuoc cua mang truyen vao co la bao nhieu di nua
}
int count_even(int* a, int n)
{
    int even=0;
    for (int i=0; i<n; i++){
        if (a[i]%2==0) even++;
    }
    return even;
}
bool binarySearch(int *a, int l, int r, int x)
{
    if (l>r) return false;
    int m=l+(r-l)/2;
    if (a[m]==x) return true;
    if (a[m]>x) binarySearch(a, l, r-m-1, x);
    if (a[m]<x) binarySearch(a, l+m+1, r, x);
}
char* weird_string() {
   char c[] = "12345";
   return c;
}// khong in ra gi
//int main(int argc, const char * argv[]) {
//	cout << "Number of command-line arguments: " << argc << endl;
//	for (int i = 0; i < argc; i++) {
//		cout << "Argument #" << i << ": _" << argv[i] << "_\n";
//	}
//	return 0;
//}
int demSoLanXuatHien(const char* a, const char* b)
{
    int cnt=0;
    int lenA=strlen(a);
    int lenB=strlen(b);
    for (int i=0; i<lenB; i++){
        char temp1[lenA], temp2[lenA];//em khong hieu vi sao co bien temp2 thi code cho ra ket qua dung
        for (int j=0; j<lenA; j++){
            temp1[j]=b[j+i];
        }
        if (strcmp(temp1,a)==0){
            cnt++;
        }
    }
    return cnt;
}
int main()
{
    char a[100], b[1000]; cin >> a >> b;
    cout << demSoLanXuatHien(a,b) << endl;
}
