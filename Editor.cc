#include <iostream>
#include <sstream>
#include "Editor.h"

using namespace std;

Editor::Editor()
{
    buffer = new Buffer();
}
Editor::~Editor()
{
    // TODO: Implement destructor
    //相当于清空链表！！
}

void Editor::run()
{
    string cmd;
    while (true)
    {
        cout << "cmd> ";
        cout.flush();           //刷新缓冲区
        getline(cin, cmd);
        if (cmd == "Q")
            break;
        dispatchCmd(cmd);
    }
}
void Editor::cmdAppend()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    while (true)
    {
        string text;
        getline(cin, text);     //getline(cin,str)可以接受空行
        if (text == ".")
            break;
        buffer->appendLine(text);
    }
}

void Editor::cmdInsert()
{
    cout << "It's input mode now. Quit with a line with a single dot(.)" << endl;
    bool firstLine = true;
    while (true)
    {
        string text;
        getline(cin, text);     //getline(cin,str)可以接受空行
        if (text == ".")
            break;
        if (firstLine){            //如果有首行的话，就正常的调用insert函数（插入在前面）
            buffer->insertLine(text);
            firstLine = false;
        }
        else {
            buffer->appendLine(text);       //如果没有，就把输入的第一行当作“首行”
            // 有了“首行”之后，接下来输入的就接在该“首行”后面，因此调用append函数
        }
    }
}

void Editor::cmdDelete(int start, int end)
{
    buffer->deleteLines(start, end);
}

void Editor::cmdNull(int line)
{
    buffer->moveToLine(line);
}

void Editor::cmdNumber(int start, int end)
{
    buffer->showLines(start, end);
}

void Editor::cmdWrite(const string &filename)
{
    buffer->writeToFile(filename);
}

void Editor::dispatchCmd(const string &cmd)         //用于区分指令
{
    if (cmd == "a") {
        cmdAppend();
        return;
    }
    if (cmd == "i") {
        cmdInsert();
        return;
    }
    if (cmd[0] == 'w' && cmd[1] == ' ') {
        // TODO: call cmdWrite with proper arguments
        return;
    }
    // TODO: handle special case "1,$n".
    int start, end;
    char comma, type = ' ';
    stringstream ss(cmd);
    ss >> start;
    if (ss.eof()){          //说明指令是 cmd>3 这种的，因此调用cmdNull函数
        cmdNull(start);
        return;
    }
    ss >> comma >> end >> type;

    if (ss.good()) {
        if (type == 'n') {          //说明指令是 cmd>1，4n 这种的，因此调用cmdNull函数
            cmdNumber(start, end);
            return;
        }
        else if (type == 'd') {   //说明指令是 cmd>1，4d 这种的，因此调用cmdDelete函数
            cmdDelete(start, end);
            return;
        }
    }
    else if (ss.fail()) {                           //说明指令是 1,$n
        cmdNumber(1,totalLineNum);
        return;
    }
    //还要考虑buffer为空的异常处理!!
    else throw "Bad/Unknown command";
}
