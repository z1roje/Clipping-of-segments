#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;
//rectangle[0].first ~ x_a, rectangle[0].second ~ y_a

//rectangle[1].first ~ x_b, rectangle[1].second ~ y_b

//point.first ~ x_cur, point.second ~ y_cur

int code_generation(double x_cur, double y_cur, double x_a, double y_a, double x_b, double y_b) {
    int res = 10;
    if ((x_a <= x_cur) && (x_cur <= x_b) &&
        (y_a <= y_cur) && (y_cur <= y_b)) {

        res = 0;
    }
    else if ((x_cur < x_a) &&
        (y_a < y_cur) && (y_cur < y_b)) {

        res = 1;
    }
    else if ((x_cur > x_b) &&
        (y_a < y_cur) && (y_cur < y_b)) {
        res = 2;
    }
    else if ((x_a < x_cur) && (x_cur < x_b) &&
        (y_cur < y_a)) {
        res = 4;
    }
    else if ((x_cur <= x_a) && (y_cur <= y_a)) {
        res = 5;
    }
    else if ((x_cur >= x_b) && (y_cur <= y_a)) {
        res = 6;
    }
    else if ((x_a < x_cur) && (x_cur < x_b) &&
        (y_cur > y_b)) {
        res = 8;
    }
    else if ((x_cur <= x_a) && (y_cur >= y_b)) {
        res = 9;
    }
    return res;

}

double distance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
bool find_el(vector<int> tmp, int target) {
    for (auto& el : tmp) {
        if (el == target) {
            return true;
        }
    }
    return false;
}
void print_all_cords(vector<vector<pair<double, double>>> lines) {
    int i = 0;
    for (auto& line : lines) {
        cout << lines[i][0].first << " " << lines[i][0].second << " " << lines[i][1].first << " " << lines[i][1].second << endl;
        i++;
    }
}
int main()
{
    //cout << fixed << setprecision(10);
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

    /*int j = 0;
    for (auto& v : code) {
        cout << "1st point : " << lines[j][0].first << " " << lines[j][0].second << ", 2ndd point : " << lines[j][1].first << " " << lines[j][1].second << " code: " << v[0] << " " << v[1] << endl;
        j++;
    }*/

    //отсечение отрезков
    int i = 0;
    vector<int> garbageindexes;
    for (auto& v : code) {
        //cout << "code " << v[0] << " " << v[1] << endl;
        if ((v[0] == 0) && (v[1] == 0)) {
            i++;
            continue;
        }
        else if (v[0] & v[1]) {
            garbageindexes.push_back(i);
        }
        else {
            //cout << "segment " << "1st point : " << lines[i][0].first << " " << lines[i][0].second << " 2nd point  " << lines[i][1].first << " " << lines[i][1].second << "code " << v[0] << " " << v[1] << endl;
            
            while ((v[0] != 0 || v[1] != 0) && ((v[0] & v[1]) == 0)) {
                int flag = 0;
                if (v[1] != 0) {
                    flag = 1;
                }
                double min_distance = 99999;
                vector<pair<double, double>> ans;

                double x_a = rectangle[0].first, x_b = rectangle[1].first,
                    y_a = rectangle[0].second, y_b = rectangle[1].second, x_1 = lines[i][0].first,
                    y_1 = lines[i][0].second, x_2 = lines[i][1].first, y_2 = lines[i][1].second;
                
                double new_x=0, new_y=0;
                ans.push_back(make_pair(x_a, (y_2 - y_1) / (x_2 - x_1) * (x_a - x_1) + y_1));
                ans.push_back(make_pair(x_b, (y_2 - y_1) / (x_2 - x_1) * (x_b - x_1) + y_1));
                ans.push_back(make_pair((x_2 - x_1) / (y_2 - y_1) * (y_a - y_1) + x_1, y_a));
                ans.push_back(make_pair((x_2 - x_1) / (y_2 - y_1) * (y_b - y_1) + x_1, y_b));

                
                for (auto& point : ans) {
                    //cout << x_1<<"<="<<point.first << "<= " << x_2 <<"  "<< y_1 << "<=" << point.second << "<=" << y_2 << " " << distance(point.first, point.second, lines[i][flag].first, lines[i][flag].second) << endl;
                    if ((min(x_1,x_2) <= point.first) && (point.first <= max(x_1,x_2)) && (min(y_1,y_2) <= point.second) && (point.second <= max(y_1,y_2)) &&
                        (distance(point.first, point.second, lines[i][flag].first, lines[i][flag].second)!=0) && (min_distance > distance(point.first, point.second, lines[i][flag].first, lines[i][flag].second))) {
                        
                        min_distance = distance(point.first, point.second, lines[i][flag].first, lines[i][flag].second);
                        new_x = point.first;
                        new_y = point.second;
                        //cout << point.first << " " << point.second << "  d fdfgdfgdg" << endl;
                    }
                }
                lines[i][flag].first = new_x;
                lines[i][flag].second = new_y;
                v[flag] = code_generation(new_x, new_y,
                    rectangle[0].first, rectangle[0].second, rectangle[1].first, rectangle[1].second);
                
                /*cout << "segment: 1st point" << lines[i][0].first << " " << lines[i][0].second << ",2nd point " << lines[i][1].first << " " << lines[i][1].second << endl;
                cout << "cod1 = " << v[0] << " cod2 = " << v[1] << endl;
                cout << endl;*/
            }
            if ((v[0] != 0) && (v[1] != 0)) {
                garbageindexes.push_back(i);
            }
        }
        i++;
    }
    //print_all_cords(lines);
    //фильтрация точек лежащие по одну сторону прямоугольника или в процессе преобразовавния отрезка стали по одну сторону прямогольника (формирование ответа)
    
    vector <vector<pair<double, double>>> reslines;
    i = 0;
    for (auto& line : lines) {
        if (!find_el(garbageindexes, i)) {
            reslines.push_back(line);
        }
        i++;
    }

    //вывод ответа
    //cout << endl;
    cout << reslines.size() << endl;
    print_all_cords(reslines);

}