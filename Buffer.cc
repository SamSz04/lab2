#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer

Buffer::Buffer() {
    head = new Listnode;
    head->lineNum = 0;
    head->next = nullptr;
    currentLineNum = 0;
}

Buffer::~Buffer() {
    for(Listnode* p=head->next;p!= nullptr;p=p->next){
        delete p;
    }
}

void Buffer::writeToFile(const string &filename) const {        //应该是要用到fstream

}

void Buffer::showLines(int from, int to){            //将相应的文本行以规定格式打印出来，遇见异常应该要抛出
    Listnode *p,*q,*tmp;
    if(to > totalLineNum){
        std::cout << "? Line number out of range" << std::endl;
        return;
    }
    else{
        if(from > to){
            std::cout << "? Number range error" << std::endl;
            return;
        }
        else{
            for(p=head->next;p!=nullptr;p=p->next){
                if(p->lineNum == from)   break;
            }
            for(q=head->next;q!=nullptr;q=q->next){
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
    int del;
    if(to > totalLineNum){
        std::cout << "? Line number out of range" << std::endl;
        return;
    }
    else{
        if(from > to) {
            std::cout<< "? Delete range error" << std::endl;
            return;
        }
        else{
            for(p=head->next;p!=nullptr;p=p->next){
                if(p->lineNum == from-1)   break;
            }
            for(q=head->next;q!=nullptr;q=q->next){
                if(q->lineNum == to)   break;
            }
            //找到了链表中相应的行数，接下来依次删除节点
            p->next = q->next;
            for(tmp=p->next;tmp!=q->next;tmp=tmp->next){
                delete tmp;
            }
            //修改行号和总行数
            del = to - from + 1;
            totalLineNum -= del;
            for(tmp=tmp=p->next;tmp!=nullptr;tmp=tmp->next){
                tmp->lineNum -= del;
            }
        }
    }
}

void Buffer::insertLine(const string &text){        //注意：insert的text要插入在当前行之前！
    Listnode *p;
    for(p=head->next;p!=nullptr;p=p->next) {
        if (p->lineNum == currentLineNum - 1) break;
    }
    //定位到了currentline的前一行
    Listnode* i = new Listnode;
    i->next = p->next;
    p->next = i;
    i->content = text;
    i->lineNum = p->lineNum + 1;
    currentLineNum = i->lineNum;
    ++totalLineNum;
    //std::cout << totalLineNum << std::endl;
    for(Listnode* tmp=i->next;tmp!= nullptr;tmp=tmp->next)
    {
        ++tmp->lineNum;
    }
}

void Buffer::appendLine(const string &text){        //注意：append的text要插入在当前行之后！
    Listnode *p;
    //如果buffer里什么都没有的话
    if (currentLineNum == 0){
        Listnode *first = new Listnode;
        head->next = first;
        first->lineNum = 1;
        first->content = text;
        first->next = nullptr;
        ++currentLineNum;
        ++totalLineNum;
        //std::cout << totalLineNum << std::endl;
    }
    else{
        for(p=head->next;p!=nullptr;p=p->next) {
            if (p->lineNum == currentLineNum) break;
        }
        //定位到了currentLine的一行
        Listnode* a = new Listnode;
        a->next = p->next;
        p->next = a;
        a->content = text;
        a->lineNum = p->lineNum + 1;
        ++totalLineNum;
        currentLineNum = a->lineNum;
        //std::cout << totalLineNum << std::endl;
        //修改行号，插入的行的后面所有行行号都要加1
        for(Listnode* tmp=a->next;tmp!= nullptr;tmp=tmp->next)
        {
            ++tmp->lineNum;
        }
    }
}

void Buffer::moveToLine(int idx) const{
    Listnode *p;
    if(idx < 0 || idx > totalLineNum) {
        std::cout << "? Line number out of range" << std::endl;
        return;
    }
    for(p=head->next;p!=nullptr;p=p->next){
        if(p->lineNum == idx)   break;
    }
    std::cout << p->content << std::endl;
}
