#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>  // Bao gồm thư viện này
#include <iomanip>
using namespace std;

class Object {
private:
    string path, name;
    string posX, posY, posZ;
    string scaleX, scaleY, scaleZ;
    string rotX, rotY, rotZ;

public:
    Object(string path, string name, string posX, string posY, string posZ,
           string scaleX, string scaleY, string scaleZ,
           string rotX, string rotY, string rotZ)
            : path(path), name(name), posX(posX), posY(posY), posZ(posZ),
              scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ),
              rotX(rotX), rotY(rotY), rotZ(rotZ) {
        // Constructor đã sử dụng initializer list để gán giá trị
    }

    // Các phương thức getter
    string getName() { return name; }
    string getPosX() { return posX; }
    string getPosY() { return posY; }
    string getPosZ() { return posZ; }
    string getScaleX() { return scaleX; }
    string getScaleY() { return scaleY; }
    string getScaleZ() { return scaleZ; }
    string getRotX() { return rotX; }
    string getRotY() { return rotY; }
    string getRotZ() { return rotZ; }

    // Các phương thức setter
    void setPosX(string x) { posX = x; }
    void setPosY(string y) { posY = y; }
    void setPosZ(string z) { posZ = z; }
    void setScaleX(string x) { scaleX = x; }
    void setScaleY(string y) { scaleY = y; }
    void setScaleZ(string z) { scaleZ = z; }
    void setRotX(string x) { rotX = x; }
    void setRotY(string y) { rotY = y; }
    void setRotZ(string z) { rotZ = z; }
};


class Map {
private:
    string name;
    vector<Object> objList;
    string matrix[10][10];
public:
    Map(string index) {
        name = index;
    }

    string getIndex() {
        return name;
    };

    vector<Object> getList() {
        return objList;
    }

    void setObj(vector<Object> list) {
        objList = list;
    }

    void setMatrix() {
        for (int i = 0; i < objList.size(); i++) {
            int x = stoi(objList[i].getPosX());
            int y = stoi(objList[i].getPosY());
            matrix[x][y] = objList[i].getName();
        }
    }


    void printMatrix() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                // Set width to 5 for each cell (including brackets and padding) and fill with spaces for alignment
                if (matrix[i][j] == "") {
                    cout << setw(6) << " 0"; // Centering '0' with spaces
                } else {
                    // Print the content with brackets and ensure it's padded to width 5
                    cout << setw(3) << "[" << matrix[i][j][0] << matrix[i][j][matrix[i][j].size() - 1] << "]";
                }
            }
            cout << endl;
        }
        cout << endl;
    }
};

vector<Map> mapList;

bool readFile(const string &filename) {
    string line, nameMap, objID, objName, modelName;
    string posX, posY, posZ, scaleX, scaleY, scaleZ, rotX, rotY, rotZ;
    fstream input;
    input.open(filename, ios::in);

    if (!input.is_open()) {
        cout << "FILE ERROR. Cannot open file: " << filename << ". Please try again!\n";
        return false;
    }

    Map curMap(""); // Tạo một bản đồ tạm
    vector<Object> curObjList;
    while (getline(input, line)) {
        if (line.empty()) { // Khi gặp một dòng trống(chuyển sang map khác)
            if (!curMap.getIndex().empty()) { // Kiểm tra xem có bản đồ hiện tại không
                curMap.setObj(curObjList);
                curMap.setMatrix();
                mapList.push_back(curMap); // Lưu bản đồ hiện tại vào danh sách
                curMap = Map(""); // Reset bản đồ hiện tại
                curObjList.clear();
            }
            continue;
        }

        if (line[0] == 'M') { // Đây là tên bản đồ
            nameMap = line.substr(3); // tên bản đồ bắt đầu sau 3 ký tự đầu
            curMap = Map(nameMap); // Tạo một bản đồ mới với tên được đọc
        } else if (line[0] == 'O' && line[1] == 'B' && line[2] == 'J') {
            // Đọc thông tin đối tượng
            objID = line;
            getline(input, objName);
            getline(input, posX, ',');
            getline(input, posY, ',');
            getline(input, posZ);
            getline(input, scaleX, ',');
            getline(input, scaleY, ',');
            getline(input, scaleZ);
            getline(input, rotX, ',');
            getline(input, rotY, ',');
            getline(input, rotZ);
            getline(input, modelName);

            // Tạo đối tượng và thêm vào danh sách đối tượng hiện tại
            Object obj(modelName, objName, posX, posY, posZ, scaleX, scaleY, scaleZ, rotX, rotY, rotZ);
            curObjList.push_back(obj); // Thêm đối tượng vào bản đồ hiện tại
        }
        // Tiếp tục đọc các dòng tiếp theo
    }

    if (!curMap.getIndex().empty()) { // Lưu bản đồ cuối cùng nếu có
        curMap.setObj(curObjList);
        mapList.push_back(curMap);
    }

    input.close();
    return true;
}


int main() {
    readFile("map.txt");
    for (int i = 0; i < mapList.size(); i++) {
        mapList[i].printMatrix();
    }
}