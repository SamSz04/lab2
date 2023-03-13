#pragma once

#include <string>

using std::string;

static int totalLineNum = 0;        //用来记录总行数（注意：非const类型的静态全局变量要拿到类外定义！！）

class Buffer {
private:
    int currentLineNum;
    // TODO: add a List here for storing the input lines
    struct Listnode{
        string content;       //保存每一行的文本内容
        int lineNum;          //保存当前的行号
        Listnode* next;
    };
    Listnode* head;       //链表的头结点
public:
    Buffer();
    ~Buffer();

    void writeToFile(const string &filename) const;

    void moveToLine(int idx) const;

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
};
