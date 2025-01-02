#include <stdio.h>
#include <string.h>

// 结构体用于存储单词及其出现的位置
typedef struct
{
    char word[100];     // 假设单词最大长度为99
    int positions[100]; // 假设最多记录100个位置
    int count;
} WordInfo;

// 函数声明
void readNovel(FILE *file, WordInfo words[], int wordCount, int *totalChars);
void countWords(WordInfo words[], int wordCount);
void extractSection(FILE *file, const char *startMarker, const char *endMarker, const char *outputFilename);

int main()
{
    FILE *file = fopen("a.txt", "r");
    if (file == NULL)
    {
        printf("无法打开文件\n");
        return -1;
    }

    // 定义要检索的单词和它们的结构体
    WordInfo words[10]; // 假设我们要检索10个单词
    int wordCount = 10; // 单词总数
    int totalChars = 0; // 字数统计

    // 初始化单词结构体，假设这些是我们要检索的形容词
    const char *sampleWords[] = {"美丽", "悲伤", "快乐", "孤独", "温暖", "冷漠", "深刻", "简单", "复杂", "真实"};

    for (int i = 0; i < wordCount; i++)
    {
        strcpy(words[i].word, sampleWords[i]); // 替换为实际词语
        words[i].count = 0;
    }

    // 读取小说并统计单词和字数
    readNovel(file, words, wordCount, &totalChars);
    countWords(words, wordCount);

    // 输出总字数
    printf("小说总字数: %d\n", totalChars);

    // 关闭文件
    fclose(file);

    // 重新打开文件以截取文档部分
    file = fopen("呐喊.txt", "r");
    if (file == NULL)
    {
        printf("无法重新打开文件\n");
        return -1;
    }

    // 截取文档部分并输出到doc文档
    extractSection(file, "五、故乡", "六、孔乙己", "故乡.doc");

    // 关闭文件
    fclose(file);

    return 0;
}

// 读取小说文本并统计单词出现位置和字数的函数
void readNovel(FILE *file, WordInfo words[], int wordCount, int *totalChars)
{
    char line[256];
    int lineNumber = 0;

    while (fgets(line, sizeof(line), file))
    {
        lineNumber++;
        *totalChars += strlen(line); // 统计字数

        for (int i = 0; i < wordCount; i++)
        {
            if (strstr(line, words[i].word) != NULL)
            {
                words[i].positions[words[i].count] = lineNumber; // 记录行号
                words[i].count++;
            }
        }
    }
}

// 统计每个单词出现次数的函数
void countWords(WordInfo words[], int wordCount)
{
    for (int i = 0; i < wordCount; i++)
    {
        printf("单词 \"%s\" 出现 %d 次。\n", words[i].word, words[i].count);
        if (words[i].count > 0)
        {
            printf("出现位置: ");
            for (int j = 0; j < words[i].count; j++)
            {
                printf("%d ", words[i].positions[j]);
            }
            printf("\n");
        }
    }
}

// 截取文档部分并输出到指定文件的函数
void extractSection(FILE *file, const char *startMarker, const char *endMarker, const char *outputFilename)
{
    FILE *outputFile = fopen(outputFilename, "w");
    if (outputFile == NULL)
    {
        printf("无法打开输出文件\n");
        return;
    }

    char line[256];
    int foundStart = 0; // 修正：添加分号
    while (fgets(line, sizeof(line), file))
    {
        // 检查是否找到起始标记
        if (strstr(line, startMarker) != NULL)
        {
            foundStart = 1; // 找到起始标记
        }

        // 如果已经找到起始标记，则写入输出文件
        if (foundStart)
            // 如果已经找到起始标记，则写入输出文件
            if (foundStart)
            {
                // 检查是否找到结束标记
                if (strstr(line, endMarker) != NULL)
                {
                    break; // 找到结束标记，停止读取
                }
                fprintf(outputFile, "%s", line); // 写入当前行到输出文件
            }
    }

    fclose(outputFile); // 关闭输出文件
}
