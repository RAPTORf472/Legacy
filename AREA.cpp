#include <bits/stdc++.h>
#define db long double
#define int long long
#define fs first
#define sc second

using namespace std;

const double PI = 3.14159265358979323846;
const int INF = 1e9;
const int N = 1005;

struct Point {
    
    db x, y;
    
    bool operator == (const Point &p) {
        
        return (x == p.x && y == p.y);
        
    }
    
    bool operator != (const Point &p) {
        
        return (x != p.x) || (y != p.y);
        
    }
    
    bool operator < (const Point &p) {
        
        return (x == p.x) ? (y < p.y) : (x < p.x);
        
    }
    
    Point operator + (const Point &p) {
        
        return {x + p.x, y + p.y};
        
    }

    db dist(Point &p) {
     
        return sqrt((x - p.x) * (x - p.x) + (y - p.y) * (y - p.y));
        
    }
    
    
};

struct Line {
    
    db a, b, c;

    
};

struct Segment {
    
    db x1, y1, x2, y2;
    
    Point d1, d2;
    
    Segment(db x1, db y1, db x2, db y2) {
        
        this -> x1 = x1;
        this -> y1 = y1;
        this -> x2 = x2;
        this -> y2 = y2;
        
    }
    
    void process() {
        
        d1 = {x1, y1};
        d2 = {x2, y2};
        
        if (d2 < d1) {
            
            swap(x1, x2);
            swap(y1, y2);
            swap(d1, d2);
            
        }
        
    }
    
    Line getLine() {
     
        return {(y1 - y2), (x2 - x1), (x1 * y2 - x2 * y1)};
        
    }
    
    bool operator == (const Segment &s) {
        
        return (x1 == s.x1) && (y1 == s.y1) && (x2 == s.x2);
        
    }
    
    bool isPoint() {
        
        return (x1 == x2) && (y1 == y2);
        
    }
    
    db slope() {
        
        if (x1 == x2) return INF;
        return (y2 - y1) / double(x2 - x1);
        
    }
    
    db len() {
        
        return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
        
    }
    
    bool perpen(Segment &s) {
        
        db sl1 = slope(), sl2 = s.slope();
        
        if (sl1 > sl2) swap(sl1, sl2);
        
        return (sl1 * sl2 == -1) || (sl1 == 0.0 && sl2 == INF);
        
    }
    
    bool in(Point a) {
    
        return ((a.x - x1) * (a.x - x2) <= 0) && ((a.y - y1) * (a.y - y2) <= 0);
        
    }
    
};

db S3raw(Point a, Point b, Point c) {
    
    return (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
    
}

db S3(Point a, Point b, Point c) {
    
    return abs(S3raw(a, b, c));
    
}

bool cw(Point a, Point b, Point c) {
    
    return S3raw(a, b, c) > 0;
    
}

bool ccw (Point a, Point b, Point c) {
    
    return S3raw(a, b, c) < 0;
    
}

void convexHull(vector<Point> &p) {
    
    if (p.size() == 1) return;
    
    sort(p.begin(), p.end());
    
    Point p1 = p[0], p2 = p.back();

    vector<Point> up, down;
    
    up.push_back(p1), down.push_back(p1);
    
    for (int i = 1; i < p.size(); i++) {
        
        if (i == p.size() - 1 || cw(p1, p[i], p2)) {
            
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], p[i])) 
                up.pop_back();
                
            up.push_back(p[i]);
            
        }
        
        if (i == p.size() - 1 || ccw(p1, p[i], p2)) {
            
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], p[i]))
                down.pop_back();
            
            down.push_back(p[i]);

        }
        
    }
    
    p.clear();
    
    for (int i = 0; i < down.size(); i++) p.push_back(down[i]);
    for (int i = up.size() - 2; i > 0; i--) p.push_back(up[i]);
    auto it = unique(p.begin(), p.end());
    p.resize(distance(p.begin(), it));
    
}

struct Triangle {
    
    db x1, y1, x2, y2, x3, y3;
    
    Point p1, p2, p3;
    
    void create(db x1, db y1, db x2, db y2, db x3, db y3) {
        
        this -> x1 = x1;
        this -> y1 = y1;
        this -> x2 = x2;
        this -> y2 = y2;
        this -> x3 = x3;
        this -> y3 = y3;
        
        this -> p1 = {x1, y1};
        this -> p2 = {x2, y2};
        this -> p3 = {x3, y3};
        
    }
    
    db S() {
        
        return abs(p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
        
    }
    
    db S(Point a, Point b, Point c) {
        
        return abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0;
        
    }
    
    db P() {
        
        return p1.dist(p2) + p2.dist(p3) + p3.dist(p1);
        
    }
    
    bool in(Point &a) {
        
        return (S(p1, a, p2) + S(p2, a, p3) + S(p3, a, p1) == S(p1, p2, p3));
        
    }
    
    bool cover(Triangle &t) {
        
        return in(t.p1) && in(t.p2) && in(t.p3);
        
    }
    
     bool in(Triangle &t) {
        
        return t.in(p1) && t.in(p2) && t.in(p3);
        
    }
    
};

db S(vector<Point> &pt) {
    
    db area = 0;
    int sz = pt.size();
    pt.push_back(pt[0]);
    
    for (int i = 0; i < sz; i++) {
        
        area += ((pt[i + 1].x - pt[i].x) * (pt[i + 1].y + pt[i].y));

    }
    
    return abs(area) / 2;
    
}

db P(vector<Point> &pt) {
    
    db peri = 0;
    int sz = pt.size() - 1;
    
    for (int i = 0; i < sz; i++) {
        
        peri += pt[i].dist(pt[i + 1]);
    }
    
    return peri;
    
}

Point inter(Segment &s1, Segment &s2) {
    
    Line l1 = s1.getLine(), l2 = s2.getLine();
    
    db D = l1.a * l2.b - l2.a * l1.b;
    db Dx = l1.b * l2.c - l2.b * l1.c;
    db Dy = l1.c * l2.a - l2.c * l1.a;
    
    if (D == 0) return {-INF, -INF};
    
    Point p = {Dx / D, Dy / D};
    
    if (s1.in(p) && s2.in(p)) return p;
    
    return {-INF, -INF};
    
}

int n;

signed main() {
    
    freopen("AREA.INP", "r", stdin);
    freopen("AREA.OUT", "w", stdout);
    
    cout << fixed << setprecision(3);
    
    string s; cin >> s;
    
    int n = s.size();
    
    Point P[n + 1];
    
    P[0] = {0, 0};
    Point nil = {-INF, -INF};
    
    for (int i = 1; i <= n; i++) {
        
        Point rp = {1, 0}, up = {0, 1};
        
        if (s[i - 1] == 'R') P[i] = P[i - 1] + rp;
        else P[i] = P[i - 1] + up;
        
    }
    
    Segment s2(0, 0, P[n].x, P[n].y);
     
    vector<Point> sofar;
    sofar.push_back({0, 0});
    
    db res = 0;
    
    for (int i = 1; i <= n; i++) {
        
        Segment s1(P[i-1].x, P[i-1].y, P[i].x, P[i].y);
        
        Point p = inter(s1, s2);
        
        if (p != nil && i > 1) {
            
            sofar.push_back(p);
            res += S(sofar);

            sofar.clear();
            sofar.push_back(p);
            
        }
        
        sofar.push_back(P[i]);
        
    }
    
    cout << res << endl;
    
}
