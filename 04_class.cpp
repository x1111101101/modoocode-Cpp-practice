#include <iostream>
#include <math.h>
#include <vector>
#define POW(x)    ((x)*(x))

using namespace std;

/*
일직선 상에 있는 점은 최대 두개라고 가정
*/



class Point {
    
public:
    int x, y;
    Point() {
        x = 0; y = 0;
    }
    Point(int pos_x, int pos_y) {
        x = pos_x;
        y = pos_y;
    }
    double getDistance(Point& other) {
        return sqrt(POW(other.x - x) + POW(other.y - y));
    }
};

class Exp {
private:
    double m, k;

public:
    Exp () = default;
    Exp(Point& a, Point& b) {
        m = ((double)(a.y - b.y)) / (a.x - b.x);
        // y= mx + k
        // k = y1 - mx1
        k = a.y - m * a.x;
    }
    bool isCrossing(Exp& other) {
        if (other.m != m) return true;
        return false;
    }
};

class Geometry {
public:
    Geometry() {
        num_points = 0;
    }

    void AddPoint(const Point& point) {
        point_array[num_points++] = new Point(point.x, point.y);
    }

    // 모든 점들 간의 거리를 출력하는 함수 입니다.
    void PrintDistance() {
        double dist = 0;
        for (int i = 0; i < num_points; i++) {
            for (int k = i + 1; k < num_points; k++) {
                Point* a = point_array[i];
                Point* b = point_array[k];
                dist += a->getDistance(*b);
            }
        }
        std::cout << "거리: " << dist << std::endl;
    }

    // 모든 점들을 잇는 직선들 간의 교점의 수를 출력해주는 함수 입니다.
    // 참고적으로 임의의 두 점을 잇는 직선의 방정식을 f(x,y) = ax+by+c = 0
    // 이라고 할 때 임의의 다른 두 점 (x1, y1) 과 (x2, y2) 가 f(x,y)=0 을 기준으로
    // 서로 다른 부분에 있을 조건은 f(x1, y1) * f(x2, y2) <= 0 이면 됩니다.
    void PrintNumMeets() {
        Exp exps[10000];
        int count = 0;
        for (int i = 0; i < num_points; i++) {
            for (int k = i + 1; k < num_points; k++) {
                Point* a = point_array[i];
                Point* b = point_array[k];
                exps[count++] = Exp(*a, *b);
            }
        }
        int cross = 0;
        for (int i = 0; i < count; i++) {
            for (int k = i + 1; k < count; k++) {
                if (exps[i].isCrossing(exps[k])) {
                    cross++;
                }
            }
        }
        std::cout << "교점의 수: " << cross << endl;
    }

private:
    // 점 100 개를 보관하는 배열.
    Point* point_array[100];
    int num_points;
};

int main() {
    Geometry geometry = Geometry();
    int n;
    std::cout << "점의 개수 입력" << endl;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cout << "x y 입력" << endl;
        int x, y;
        std::cin >> x >> y;
        Point* p = new Point(x,y);
        geometry.AddPoint(*p);
    }
    geometry.PrintDistance();
    geometry.PrintNumMeets();
    return 0;
}
