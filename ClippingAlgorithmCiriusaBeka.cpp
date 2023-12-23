#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;
double skalar(pair<double, double> vec1, pair<double, double> vec2) {
    return vec1.first * vec2.first + vec1.second * vec2.second;
}
pair<double, double> raznost(pair<double, double> vec1, pair<double, double> vec2) {
    pair<double, double> tmp;
    tmp.first = vec1.first - vec2.first;
    tmp.second = vec1.second - vec2.second;
    return tmp;
}
pair<double, double> line_value(vector<pair<double, double>> line, double t) {
    pair<double, double> tmp;
    tmp.first = line[0].first + (line[1].first - line[0].first) * t;
    tmp.second = line[0].second + (line[1].second - line[0].second) * t;
    return tmp;
}
int main()
{
    ifstream file("problem.txt"); // Открываем файл
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

    vector <pair<double, double>> top_normal; // нормали соответствующие правой вверхней точке те нормали (-1;0),(0;-1)
    vector <pair<double, double>> bottom_normal;// нормали соответствующие левой нижней точке те нормали(1; 0), (0; 1)
    top_normal.push_back(pair<double, double> {-1, 0});
    top_normal.push_back(pair<double, double> {0, -1});
    bottom_normal.push_back(pair<double, double> {1, 0});
    bottom_normal.push_back(pair<double, double> {0, 1});
    vector <vector<pair<double, double>>> resLines;

    
    int i = 0;
    double t;
    for (auto& line : lines) {
        vector <double> tmp;
        bool flag1 = true, flag2 = true; // flag1(2) - 1ая(2) точка отрезка внутри прямоугольника
        
        for (auto& normal : top_normal) {
            t = -skalar(normal, raznost(line[0], rectangle[1])) / skalar(raznost(line[1], line[0]), normal);
            pair<double, double> point = line_value(line, t);

            if ((t <= 1) && (t >= 0) && ((((point.second==rectangle[0].second) || (point.second==rectangle[1].second)) && (point.first <=rectangle[1].first) && (point.first >=rectangle[0].first)) || (((point.first == rectangle[0].first) || (point.first == rectangle[1].first)) &&
                (point.second <= rectangle[1].second) && (point.second >= rectangle[0].second)))) {
                tmp.push_back(t);
            }
            if (skalar(normal, raznost(line[0], rectangle[1])) < 0) {
                flag1 = false;
            }
            if (skalar(normal, raznost(line[1], rectangle[1])) < 0) {
                flag2 = false;
            }
        }
        for (auto& normal : bottom_normal) {
            t = -skalar(normal, raznost(line[0], rectangle[0])) / skalar(raznost(line[1], line[0]), normal);
            pair<double, double> point = line_value(line, t);
            if ((t <= 1) && (t >= 0) && ((((point.second == rectangle[0].second) || (point.second == rectangle[1].second)) && (point.first <= rectangle[1].first) && (point.first >= rectangle[0].first)) || (((point.first == rectangle[0].first) || (point.first == rectangle[1].first)) &&
                (point.second <= rectangle[1].second) && (point.second >= rectangle[0].second)))) {
                tmp.push_back(t);
            }
            if (skalar(normal, raznost(line[0], rectangle[0])) < 0) {
                flag1 = false;
            }
            if (skalar(normal, raznost(line[1], rectangle[0])) < 0) {
                flag2 = false;
            }
        }
        
        sort(tmp.begin(), tmp.end());
        //cout << "line: " << i << " " << flag1 << " " << flag2 << endl;
        //for (auto& value : tmp) {
        //    cout <<"value: $" << value << "$ " << line_value(line, value).first << " " << line_value(line, value).second << endl;
        //}
        //cout << endl;
        if ((flag1) && (flag2)) {
            i++;
            resLines.push_back(vector<pair<double, double>> {line[0], line[1]});
            continue;
        }
        if (tmp.size() != 0) {
            if ((flag1) && (!flag2)) {
                resLines.push_back(vector<pair<double, double>> {line[0], line_value(line, tmp[0])});
            }
            else if ((!flag1) && (flag2)) {
                resLines.push_back(vector<pair<double, double>> {line_value(line, tmp[0]), line[1]});
            }
            else {
                resLines.push_back(vector<pair<double, double>> {line_value(line, tmp[0]), line_value(line, tmp[1])});
            }
        }

        i++;
    }
    
    cout << resLines.size() << endl;
    for (auto& line : resLines) {
        cout << line[0].first << " " << line[0].second << " " << line[1].first << " " << line[1].second << endl;
    }
    
    
}

