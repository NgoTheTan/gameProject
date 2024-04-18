#include <bits/stdc++.h>
#include <cstring>

using namespace std;

char* concat(const char* s1, const char* s2)
{
    int len1=strlen(s1), len2=strlen(s2);
    char* res=new char[len1+len2];
    strncpy(res, s1, len1);
    strncpy(res+len1, s2, len2);
    res[len1+len2]='\0';
    return res;
}

void test()
{
    int a=100;
    int *p=&a;
    delete p;
    cout << a << endl;
}
// bien dia phuong a ngay lap tuc mat di bo nho de luu du lieu va khong in ra duoc gia tri cua a.

int Strlen(const char* s)
{
    int len=0;
    while ((*s)!='\0'){
        len++;
        s++;
    }
    return len;
}

void Strncpy(char* dest, const char* source, int len)
{
    while (len--){
        *dest=*source;
        dest++; source++;
    }
}

char* Reverse(const char* a)
{
    int len=Strlen(a);
    char *res=new char[len+1];
    a+=(len-1);
    for (int i=0; i<len; i++){
        *res=*a;
        a--; res++;
    }
    *res='\0';
    res=res-len;
    return res;
}

char* delete_char(const char* a, char c)
{
    int cnt=0;
    int len=Strlen(a);
    for (int i=0; i<len; i++){
        if (*a==c) cnt++;
        a++;
    }
    a-=len;
    char *res=new char[len-cnt+1];
    for (int i=0; i<len; i++){
        if (*a!=c){
            *res=*a;
            res++;
        }
        a++;
    }
    *res='\0';
    res=res-(len-cnt);
    return res;
}

char* pad_right(const char *a, int n)
{
    int len=Strlen(a);
    char *res=new char [n+1];
    Strncpy(res, a, len);
    if (len>=n) return res;
    res+=len;
    while (len<n){
        *res='_';
        res++; len++;
    }
    *res='\0';
    res-=len;
    return res;
}

char* pad_left(const char *a, int n)
{
    int len=Strlen(a);
    char *res=new char [n+1];
    *(res+n)='\0';
    if (len>=n){
        Strncpy(res, a, len);
        return res;
    }
    for (int i=len; i<n; i++){
        *res='_';
        res++;
    }
    Strncpy(res, a, len);
    res-=(n-len);
    return res;
}

char *truncate(const char* a, int n)
{
    int len=Strlen(a);
    char *res=new char[n+1];
    if (len<=n){
        Strncpy(res, a, len);
        return res;
    }
    Strncpy(res, a, n);
    *(res+n)='\0';
    return res;
}

char *trim_right(const char *a)
{
    int len=Strlen(a);
    char *res=new char[len+1];
    Strncpy(res, a, len);
    res+=(len-1);
    while (*res==' '){
        *res='\0';
        res--;
        len--;
    }
    res-=len;
    return res;
}

char* trim_left(const char *a)
{
    int len=Strlen(a);
    int cnt=0;
    while (*a!='\0'){
        if (*a!=' ') cnt++;
        a++;
    }
    a-=(len+1);
    char *res=new char[cnt+1];
    *(res+cnt)='\0';
    while (*a!='\0'){
        if (*a!=' '){
            *res=*a;
            res++;
        }
        a++;
    }
    res-=cnt;
    return res;
}

int main()
{
//    char s1[]="Hello", s2[]="World";
//    cout << concat(s1, s2);


//    int* p = new int;
//    int* p2 = p;
//    *p = 10;
//    delete p;
//    *p2 = 100; // loi o dong nay vi ta da xoa vung bo nho cap phat cho p, do do p2 tro thanh con tro vao vung bo nho khong con hieu luc, vi the viec gan gia tri cho *p2 se bi loi.
//    cout << *p2;
//    delete p2;


//    char* a = new char[10];
//    char* c = a + 3;
//    for (int i = 0; i < 9; i++) a[i] = 'a';
//    a[9] = '\0';
//    cerr <<"a: " << "-" << a << "-" << endl;
//    cerr <<"c: " << "-" << c << "-" << endl;
//    delete c;
//    cerr << "a after deleting c:" << "-" << a << "-" << endl; // dong cerr cuoi cung nay khong cho ra ket qua nhu y muon. Loi xay ra o day la khi delete c, ta cung da delete
//    vung bo nho ma a dang tro vao (vi chung ta cho c tro vao vung bo nho cua a+3). Day la loi giai phong bo nho sai cach

// Ham reverse
//    char s[]="Hello";
//    cout << Reverse(s) << endl;

// Ham delete_char
//    char s[]="testinghehe";
//    cout << delete_char(s, 'e');

// Ham pad_right
//    char s[]="test";
//    cout << pad_right(s, 10) << endl;
//    cout << pad_right(s, 3) << endl;

// Ham pad_left
    char s[]="test";
    cout << pad_left(s, 10) << endl;
    cout << pad_left(s, 4) << endl;

// Ham truncate
//    char s[]="HelloMyDarling";
//    cout << truncate(s, 7) << endl;
//    cout << truncate(s, 14) << endl;

// Ham trim_right(left)
//    char s[]="     Hello    ";
//    cout <<"-" << trim_right(s) << "-" << endl;
//    cout << "-" << trim_left(s) << "-" << endl;
}
