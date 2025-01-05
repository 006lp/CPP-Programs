#include <iostream>
#include <filesystem>
#include <string>
#include <windows.h> // 用于设置控制台编码
#include <iomanip>   // 用于控制输出精度

namespace fs = std::filesystem;

// 函数：查找目录及其子目录中最大的文件大小
std::uintmax_t findLargestFile(const fs::path &directory, fs::path &largestFile, bool scanRecycleBin, bool showFilesOnly)
{
    std::uintmax_t maxSize = 0; // 保存最大文件大小

    try
    {
        for (const auto &entry : fs::recursive_directory_iterator(directory))
        {

            // 如果用户选择不扫描回收站，则排除回收站目录
            if (!scanRecycleBin && entry.path().string().find("$RECYCLE.BIN") != std::string::npos)
                continue;

            if (fs::is_regular_file(entry)) // 如果是普通文件
            {
                std::uintmax_t fileSize = fs::file_size(entry); // 获取文件大小
                if (fileSize > maxSize)
                { // 更新最大文件大小和对应文件路径
                    maxSize = fileSize;
                    largestFile = entry.path();
                }
            }

            // 如果用户选择只显示文件夹，则跳过文件输出
            if (!showFilesOnly && fs::is_regular_file(entry)) // 只有当 showFilesOnly 为 false 时，才输出文件
            {
                continue; // 跳过文件
            }

            // 动态输出当前扫描的文件夹或文件
            std::cout << "正在扫描: " << entry.path() << std::endl;
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
        std::cout << "大小: " << std::fixed << sizeGB << " GB" << std::endl;
    }
    else if (sizeMB >= 1.0) // 如果文件大小大于或等于 1 MB 但小于 1 GB
    {
        std::cout << "大小: " << std::fixed << sizeMB << " MB" << std::endl;
    }
    else if (sizeKB >= 1.0) // 如果文件大小大于或等于 1 KB 但小于 1 MB
    {
        std::cout << "大小: " << std::fixed << sizeKB << " KB" << std::endl;
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
    bool scanRecycleBin = false; // 默认不扫描回收站
    bool showFilesOnly = false;  // 默认只显示文件夹

    std::cout << "查找路径内最大的文件 Powered By 006lp." << std::endl;
    std::cout << std::endl;
    std::cout << "请输入目录路径（若扫描根路径请带上\"\\\", 例如 F:\\）：";
    std::getline(std::cin, directoryPath); // 获取用户输入的目录路径

    // 询问用户是否要扫描回收站
    std::string choice;
    std::cout << "是否扫描回收站文件夹 (y/n，默认不扫描): ";
    std::getline(std::cin, choice); // 使用 std::getline 读取用户输入

    // 如果用户输入 'y' 或 'Y'，则扫描回收站
    if (choice == "y" || choice == "Y")
    {
        scanRecycleBin = true;
    }

    // 询问用户是否只输出文件夹或文件
    std::cout << "是否显示具体文件名 (y/n，默认只显示文件夹): ";
    std::getline(std::cin, choice); // 使用 std::getline 读取用户输入

    if (choice == "y" || choice == "Y")
    {
        showFilesOnly = true;
    }

    fs::path directory(directoryPath);

    if (!fs::exists(directory) || !fs::is_directory(directory))
    { // 验证路径是否有效
        std::cerr << "无效的目录路径。" << std::endl;
        return 1;
    }

    fs::path largestFile;                                                                                // 保存最大文件的路径
    std::uintmax_t largestSize = findLargestFile(directory, largestFile, scanRecycleBin, showFilesOnly); // 查找最大文件

    if (largestSize > 0)
    { // 输出结果
        std::cout << "最大的文件是: " << largestFile << std::endl;

        // 输出文件大小的换算结果
        printFileSize(largestSize);
    }
    else
    {
        std::cout << "目录中未找到任何文件。" << std::endl;
    }

    // 在程序结束前添加暂停，等待用户按键
    std::cout << "按任意键退出...";
    std::cin.get(); // 等待用户输入

    return 0;
}
