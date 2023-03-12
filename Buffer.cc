#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    currentLineNum = 0;
}

Buffer::~Buffer() {
    for(Listnode* p=head;p!= nullptr;p->next){
        delete p;
    }
}

void Buffer::writeToFile(const string &filename) const {        //应该是要用到fstream

}

void Buffer::showLines(int from, int to){            //将相应的文本行以规定格式打印出来，遇见异常应该要抛出
    Listnode *p,*q,*tmp;
    if(to > totalLineNum)   throw{};
    else{
        if(from > to)   throw{};
        else{
            for(p=head;p!=nullptr;p=p->next){
                if(p->lineNum == from)   break;
            }
            for(q=head;q!=nullptr;q=q->next){
                if(q->lineNum == to)   break;
            }
            //别忘了设定currentLineNum的值
            currentLineNum = to;
            //找到了链表中相应的行数，接下来遍历并输出出来
            for(tmp=p;tmp!=q->next;tmp=tmp->next){
                std::cout << tmp->lineNum << "    " << tmp->content << std::endl;
            }
        }
    }
}

void Buffer::deleteLines(int from, int to){
    Listnode *p,*q,*tmp;
    if(to > totalLineNum)   throw{};
    else{
        if(from > to)   throw{};
        else{
            for(p=head;p!=nullptr;p=p->next){
                if(p->lineNum == from)   break;
            }
            for(q=head;q!=nullptr;q=q->next){
                if(q->lineNum == to)   break;
            }
            //找到了链表中相应的行数，接下来依次删除节点
            p->next = q->next;
            for(tmp=p;tmp!=q->next;tmp=tmp->next){
                delete tmp;
            }
        }
    }
}

void Buffer::insertLine(const string &text){        //注意：insert的text要插入在当前行之前！
    Listnode *p;
    for(p=head;p!=nullptr;p=p->next) {
        if (p->lineNum == currentLineNum - 1) break;
    }
    //定位到了currentline的前一行
    Listnode* i = new Listnode;
    i->next = p->next;
    p->next = i;
    i->content = text;
    i->lineNum = p->lineNum + 1;
    currentLineNum = i->lineNum;
    
}

void Buffer::appendLine(const string &text){        //注意：append的text要插入在当前行之后！
    Listnode *p;
    for(p=head;p!=nullptr;p=p->next) {
        if (p->lineNum == currentLineNum) break;
    }
    //定位到了currentline的一行
    Listnode* a = new Listnode;
    a->next = p->next;
    p->next = a;
    a->content = text;
    a->lineNum = p->lineNum + 1;
    currentLineNum = a->lineNum;
}

const string &Buffer::moveToLine(int idx) const{
    Listnode *p;
    if(idx < 0 || idx > totalLineNum)   throw{};
    for(p=head;p!=nullptr;p=p->next){
        if(p->lineNum == idx)   break;
    }
    return p->content;
}
