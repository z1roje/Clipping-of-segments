
#include <iostream> // cout
#include <string>   // string
#include <vector>   // vector
#include <fstream>  // ifstream
#include <iomanip>
using namespace std;
int main()
{
    //cout << fixed << setprecision(20);
    ifstream file("C:\\Users\\Артем\\source\\repos\\Сlipping of segments\\problem.txt"); // Открываем файл
    vector <vector<pair<long float, long float>>> lines;
    vector <pair<long float, long float>> rectangle;

    long float x1, y1, x2, y2;
    int n;
    file >> x1 >> y1 >> x2 >> y2;
    rectangle.push_back(make_pair(x1, y1));
    rectangle.push_back(make_pair(x2, y2));
    
    file >> n;
    while (!file.eof()) {
        vector <pair<long float, long float>> tmp;
        file >> x1 >> y1 >> x2 >> y2;
        tmp.push_back(make_pair(x1, y1));
        tmp.push_back(make_pair(x2, y2));
        lines.push_back(tmp);
    }
   
    //cout << lines[0][0].first << endl;
    //cout << lines[1][1].second;
    vector <vector<int>> code;
    for (auto& line : lines) {
        vector<int> tmp;
        for (auto& point : line) {
            if ((rectangle[0].first <= point.first) && (point.first <= rectangle[1].first) &&
                (rectangle[0].second <= point.second) && (point.second <= rectangle[1].second)) {

                tmp.push_back(0);
            }
            else if ((point.first < rectangle[0].first) &&
                (rectangle[0].second <= point.second) && (point.second <= rectangle[1].second)) {

                tmp.push_back(1);
            }
            else if ((point.first > rectangle[1].first) &&
                (rectangle[0].second <= point.second) && (point.second <= rectangle[1].second)) {
                tmp.push_back(2);
            }
            else if ((rectangle[0].first <= point.first) && (point.first <= rectangle[1].first) &&
                (point.second < rectangle[0].second)) {
                tmp.push_back(4);
            }
            else if ((point.first < rectangle[0].first) && (point.second < rectangle[0].second)) {
                tmp.push_back(5);
            }
            else if ((point.first > rectangle[1].first) && (point.second < rectangle[0].second)) {
                tmp.push_back(6);
            }
            else if ((rectangle[0].first <= point.first) && (point.first <= rectangle[1].first) &&
                (point.second > rectangle[1].second)) {
                tmp.push_back(8);
            }
            else if ((point.first < rectangle[0].first) && (point.second > rectangle[1].second)) {
                tmp.push_back(9);
            }
            else {
                tmp.push_back(10);
            }
        }
        code.push_back(tmp);

    }
    for (auto& v : code) {
        cout << v[0] << " " << v[1] << endl;
    }
    
    //dfdkmndkdfgjfdgjdfgodgjkdofgjfkgjfdgjdkfgjfd
}
