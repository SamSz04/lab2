#include <string>
#include "Buffer.h"

class Editor {
private:
    Buffer *buffer;           //指针！！
    void dispatchCmd(const string &cmd);
    void cmdAppend();
    void cmdInsert();
    void cmdDelete(int start, int end);
    void cmdNumber(int start, int end);
    void cmdWrite(const string &filename);
    void cmdNull(int line);
public:
    Editor();
    ~Editor();
    void run();
};


/*lass out_of_range{
private:
    const char *message_oor;
public:
    out_of_range():message_oor("Line number out of range!"){}
    const char *what() const{return message_oor;}
};

class range_error{
private:
    const char *message_re;
public:
    range_error():message_re("range error!"){}
    const char *what() const{return message_re;}
};
//
try {
            dispatchCmd(cmd);
        } catch (const char *e) {
            cout << "? " << e << endl;
        } catch (const out_of_range &oor) {
            cout << "? " << oor.what() << endl;
        } catch (const range_error &re) {
            cout << "? " << re.what() << endl;
        };

 */