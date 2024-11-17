#include <iostream>
#include <fstream>
#include <windows.h>
#include "C:\mingw64\include\json.hpp"

using namespace std;
using json = nlohmann::json;

int main()
{
    SetConsoleOutputCP(65001);

    // 打开并读取JSON文件
    ifstream file("playlist.json");
    if (!file.is_open())
    {
        cerr << "无法打开文件" << endl;
        return 1;
    }

    // 解析JSON文件内容
    json playlist;
    file >> playlist;
    file.close(); // 关闭输入文件

    // 打开输出文件result.txt
    ofstream resultFile("result.txt");
    if (!resultFile.is_open())
    {
        cerr << "无法创建或打开result.txt文件" << endl;
        return 1;
    }

    // 获取并遍历歌曲列表，将结果写入文件
    auto songList = playlist["data"]["list"];
    int index = 1;
    for (const auto &song : songList)
    {
        string name = song["name"];
        string singer = song["singer"];
        resultFile << index++ << ". " << name << " " << singer << endl;
    }

    // 关闭输出文件
    resultFile.close();
    cout << "结果已写入result.txt文件" << endl;

    return 0;
}
