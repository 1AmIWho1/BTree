#include "BTree.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*! \mainpage BTree
\section Introduction
Simple console application

\section Fast Start
For creating BT you should use standart constructor
\code{.cpp}
Expression expression = Expression("2+2");
\endcode
Then you can immediately get the answer
\code{.cpp}
float result = expression.do_calculations();
\endcode

\section Details
You can transform your expression to postfix or infix using these commands:
\code{.cpp}
expression.transfer_to_infix();
expression.transfer_to_postfix();
\endcode
And, more importantly, you can print both infix and postfix
\code{.cpp}
expression.print_infix();
expression.print_postfix();
\endcode
*/



int main(){
    ifstream file;
    file.open("input.txt"); // has same input as in the presentation
    int order;
    file >> order;
    BTree b(order);
    char type;
    do{
        file >> type;
        if(type == 'i'){
            int n, key;
            file >> n;
            for(int i = 0; i < n; ++i){
                file >> key;
                b.Insert(key);
            }
        }
        else if(type == 'd'){
            int n, key;
            file >> n;
            for(int i = 0; i < n; ++i){
                file >> key;
                b.Delete(key);
            }
        }
        else if(type == 'o')
            b.Output();
        else if(type == 'f'){
            bool append;
            string file_name;
            file >> append >> file_name;
            b.OutputToFile(file_name, append);
        }
        else if(type == 's')
            b.Statistic();
    } while(type != 'e');
    file.close();
    return 0;
}
