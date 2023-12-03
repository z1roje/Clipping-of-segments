
#include <iostream> // cout
#include <string>   // string
#include <vector>   // vector
#include <fstream>  // ifstream
#include <iomanip>
//rectangle[0].first ~ x_a, rectangle[0].second ~ y_a

//rectangle[1].first ~ x_b, rectangle[1].second ~ y_b

//point.first ~ x_cur, point.second ~ y_cur
using namespace std;
int code_generation(double x_cur, double y_cur, double x_a, double y_a, double x_b, double y_b) {
    int res = 10;
    if ((x_a <= x_cur) && (x_cur <= x_b) &&
        (y_a <= y_cur) && (y_cur <= y_b)) {

        res = 0;
    }
    else if ((x_cur < x_a) &&
        (y_a <= y_cur) && (y_cur <= y_b)) {

        res = 1;
    }
    else if ((x_cur > x_b) &&
        (y_a <= y_cur) && (y_cur <= y_b)) {
        res = 2;
    }
    else if ((x_a <= x_cur) && (x_cur <= x_b) &&
        (y_cur < y_a)) {
        res = 4;
    }
    else if ((x_cur < x_a) && (y_cur < y_a)) {
        res= 5;
    }
    else if ((x_cur > x_b) && (y_cur < y_a)) {
        res = 6;
    }
    else if ((x_a <= x_cur) && (x_cur <= x_b) &&
        (y_cur > y_b)) {
        res = 8;
    }
    else if ((x_cur < x_a) && (y_cur > y_b)) {
        res = 9;
    }
    return res;

}
int main()
{
    //cout << fixed << setprecision(20);
    ifstream file("C:\\Users\\Артем\\source\\repos\\Сlipping of segments\\problem.txt"); // Открываем файл
    vector <vector<pair<double, double>>> lines;
    vector <pair<double, double>> rectangle;

    double x1, y1, x2, y2;
    int n;
    file >> x1 >> y1 >> x2 >> y2;
    rectangle.push_back(make_pair(x1, y1));
    rectangle.push_back(make_pair(x2, y2));
    
    file >> n;
    while (!file.eof()) {
        vector <pair<double, double>> tmp;
        file >> x1 >> y1 >> x2 >> y2;
        tmp.push_back(make_pair(x1, y1));
        tmp.push_back(make_pair(x2, y2));
        lines.push_back(tmp);
    }
   
    //Создание кодов для точек
    vector <vector<int>> code;
    for (auto& line : lines) {
        vector<int> tmp;
        for (auto& point : line) {
            tmp.push_back(code_generation(point.first, point.second, rectangle[0].first,
                rectangle[0].second, rectangle[1].first, rectangle[1].second));
        }
        code.push_back(tmp);

    }

    //Отсечение отрезков
    int i = 0;
    vector<int> garbageIndexes;
    for (auto& v : code) {
        if (v[0] == 0 && v[1] == 0) {
            continue;
        }
        else if (v[0] & v[1]) {
            garbageIndexes.push_back(i);
        }
        else {
            while (((v[0] & v[1])==0) && (v[0] !=0 && v[1]!=0)) {
                vector<pair<double, double>> ans;
                int flag = 0;
                double x_a = rectangle[0].first, x_b = rectangle[1].first,
                    y_a = rectangle[0].second, y_b = rectangle[1].second, x_1 = lines[i][0].first,
                    y_1 = lines[i][0].second, x_2 = lines[i][1].first, y_2 = lines[i][1].second;

                ans.push_back(make_pair(x_a, (y_2 - y_1) / (x_2 - x_1) * (x_a - x_1) + y_1));
                ans.push_back(make_pair(x_b, (y_2 - y_1) / (x_2 - x_1) * (x_b - x_1) + y_1));
                ans.push_back(make_pair((x_2 - x_1) / (y_2 - y_1) * (y_a - y_1) + x_1, y_a));
                ans.push_back(make_pair((x_2 - x_1) / (y_2 - y_1) * (y_b - y_1) + x_1, y_b));

                for (auto& point : ans) {
                    if ((flag < 1) && (x_1 <= point.first) && (point.first <= x_2) && (y_1 <= point.second) &&
                        (point.second <= y_2)) {
                        lines[i][flag].first = point.first;
                        lines[i][flag].second = point.second;
                        v[flag] = code_generation(lines[i][flag].first, lines[i][flag].second,
                            rectangle[0].first, rectangle[0].second, rectangle[1].first,
                            rectangle[1].second);
                        flag++;
                    }
                }
            }
        }
        i++;
    }
    
    //удаление точек лежащие по одну сторону прямоугольника (формирование ответа)
    vector <vector<pair<double, double>>> resLines;
    i = 0;
    for (auto& line : lines) {
        if ()
    }
}
