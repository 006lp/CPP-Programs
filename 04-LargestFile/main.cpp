#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h> // 用于设置控制台编码
#include <iomanip>   // 用于控制输出精度

namespace fs = std::filesystem;

// 函数：查找目录及其子目录中最大的文件大小
std::uintmax_t findLargestFile(const fs::path &directory, fs::path &largestFile)
{
    std::uintmax_t maxSize = 0; // 保存最大文件大小

    try
    {
        for (const auto &entry : fs::recursive_directory_iterator(directory))
        {
            if (fs::is_regular_file(entry))
            {                                                   // 判断是否为普通文件
                std::uintmax_t fileSize = fs::file_size(entry); // 获取文件大小
                if (fileSize > maxSize)
                { // 更新最大文件大小和对应文件路径
                    maxSize = fileSize;
                    largestFile = entry.path();
                }
            }
        }
    }
    catch (const fs::filesystem_error &e)
    { // 捕获文件系统相关的异常
        std::cerr << "文件系统错误: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    { // 捕获其他异常
        std::cerr << "一般错误: " << e.what() << std::endl;
    }

    return maxSize;
}

// 函数：将字节转换为KB、MB、GB，并根据大小选择合适的单位
void printFileSize(std::uintmax_t size)
{
    double sizeKB = size / 1024.0;
    double sizeMB = sizeKB / 1024.0;
    double sizeGB = sizeMB / 1024.0;

    if (sizeGB >= 1.0) // 如果文件大小大于或等于 1 GB
    {
        std::cout << "大小: " << std::fixed << std::setprecision(3) << sizeGB << " GB" << std::endl;
    }
    else if (sizeMB >= 1.0) // 如果文件大小大于或等于 1 MB 但小于 1 GB
    {
        std::cout << "大小: " << std::fixed << std::setprecision(3) << sizeMB << " MB" << std::endl;
    }
    else if (sizeKB >= 1.0) // 如果文件大小大于或等于 1 KB 但小于 1 MB
    {
        std::cout << "大小: " << std::fixed << std::setprecision(3) << sizeKB << " KB" << std::endl;
    }
    else // 如果文件大小小于 1 KB
    {
        std::cout << "大小: " << size << " B" << std::endl;
    }
}

int main()
{
    // 设置控制台编码为 UTF-8
    SetConsoleOutputCP(CP_UTF8);

    std::string directoryPath;
    std::cout << "请输入目录路径: ";
    std::getline(std::cin, directoryPath); // 获取用户输入的目录路径

    fs::path directory(directoryPath);

    if (!fs::exists(directory) || !fs::is_directory(directory))
    { // 验证路径是否有效
        std::cerr << "无效的目录路径。" << std::endl;
        return 1;
    }

    fs::path largestFile;                                                 // 保存最大文件的路径
    std::uintmax_t largestSize = findLargestFile(directory, largestFile); // 查找最大文件

    if (largestSize > 0)
    { // 输出结果
        std::cout << "最大的文件是: " << largestFile << std::endl;

        // 设置输出为自动显示必要的小数位数
        printFileSize(largestSize); // 输出文件大小的换算结果
    }
    else
    {
        std::cout << "目录中未找到任何文件。" << std::endl;
    }

    // 在程序结束前添加暂停，等待用户按键
    std::cout << "按任意键退出...";
    std::cin.get();

    return 0;
}
