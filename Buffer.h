#pragma once

#include <string>

using std::string;

static int totalLineNum = 0;        //用来记录总行数（注意：非const类型的静态全局变量要拿到类外定义！！

class Buffer {
private:
    int currentLineNum;
    // TODO: add a List here for storing the input lines
    struct Listnode{
        string content;       //保存每一行的文本内容
        int lineNum;             //保存当前的行号
        Listnode* next;
    };
    //构造函数？
    //头指针？
    //
public:
    Listnode* head = nullptr;       //指向链表表头的头指针
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    const string &moveToLine(int idx) const;

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
