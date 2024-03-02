#include <bits/stdc++.h>
using namespace std;
struct Point
{
    float x, y;
    Point()
    {
        x=0; y=0;
    }
    Point(float _x, float _y)
    {
        x=_x; y=_y;
    }
};

void passByValue (Point a)
{
    cout << &a << endl;
    float temp=a.x;
    a.x=a.y;
    a.y=temp;
}
void passByReference(Point &a)
{
    cout << &a << endl;
    float temp=a.x;
    a.x=a.y;
    a.y=temp;
}
 void print(Point p)
 {
     cout << p.x << " " << p.y << endl;
 }
 Point midPoint(const Point a,const Point b)
 {
     Point m;
     m.x=(a.x+b.x)/2;
     m.y=(a.y+b.y)/2;
     return m;
 }

 struct Rect
 {
     float x, y, w, h;
     Rect()
     {
         x=0; y=0; w=0; h=0;
     }
     Rect(float _x, float _y, float _w, float _h)
     {
         x=_x; y=_y; w=_w; h=_h;
     }
     bool contains(const Point p)
     {
         if (p.x>=x && p.y<=y && p.x<=x+w && p.y>=y-h) return true;
         return false;
     }
 };

 struct Ship
 {
     Rect board; string id; float dx; float dy;
     Ship(){}
     Ship(Rect _board, string _id, float _dx, float _dy)
     {
         board=_board; id=_id; dx=_dx; dy=_dy;
     }
     void move()
     {
         board.x+=dx; board.y+=dy;
     }
 };

 void display(const Ship &ship)
 {
     cout << ship.id << endl << ship.board.x << " " << ship.board.y << endl;
 }
 //Cau8: vi tri tuong doi cua mot bien kieu Point va truong x cua no la trung nhau, trong khi truong y nam ben canh ve phia ben phai truong x.

 int main()
 {
     //demo struct Point, Rect va Ship
     Point a(1.1,1.8), b(3.3,4.4);
     print(midPoint(a,b)); // in ra 2.2 3.3
     Rect hcn(1, 2, 3, 4);
     if (hcn.contains(a)) cout << "yes" << endl;
     else cout << "no" << endl; // in ra yes
     if (hcn.contains(b)) cout << "yes" << endl;
     else cout << "no" << endl; //in ra no
     Ship Tan(hcn, "TAN", 1, 2);
     for (int i=0; i<5; i++){
        Tan.move();
        display(Tan);
     }
     return 0;
 }
