#include "BTree.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*! \mainpage BTree
\section Introduction

For creating BTree you should use standart constructor. This BTree implementation has minimum t keys in every Node, and maximum 2t. t is order of BTree.

Here is a simple example of inserting keys in BTree:

\code{.cpp}
BTree b = BTree(2);
b.Insert(3);
b.Insert(22);
b.Insert(10);
b.Insert(2);
b.Insert(17);
b.Insert(5);
\endcode

Then you can output BTree to consol:

\code{.cpp}
b.Output();
\endcode

\code{.unparsed}
BTree:
10 
Children : 2
2 3 5 
17 22
\endcode

And also see some statistic:

\code{.cpp}
b.Statistic();
\endcode

\code{.unparsed}
BTree statistic:
Nodes: 3
Keys: 6
Height: 2
\endcode

Then you can try deleteing some elements, for example:

\code{.cpp}
b.Delete(22);
b.Output();
\endcode

\code{.unparsed}
BTree:
5 
Children : 2
2 3 
10 17 
\endcode

You can also see, if this BTree contains some key:

\code{.cpp}
cout << string(b.Search(10) ? "BTree contains 10!" : "BTree doesn't contain 10") << endl;
cout << string(b.Search(12) ? "BTree contains 12!" : "BTree doesn't contain 12") << endl;
\endcode

\code{.unparsed}
BTree contains 10!
BTree doesn't contain 12
\endcode

And finally you can write your BTree to file, using method OutputToFile("output.txt", true), where second argument is used to indicate whether you want to append otuput to file or rewrite it.

\code{.cpp}
b.OutputToFile("output.txt", false);
\endcode

output.txt will look the same as previous BTree.Output().
And here's all code used in this example:

\code{.cpp}
#include "BTree.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int main(){
    BTree b = BTree(2);
    b.Insert(3);
    b.Insert(22);
    b.Insert(10);
    b.Insert(2);
    b.Insert(17);
    b.Insert(5);
    b.Output();
    b.Statistic();
    b.Delete(22);
    b.Output();
    cout << string(b.Search(10) ? "BTree contains 10!" : "BTree doesn't contain 10") << endl;
    cout << string(b.Search(12) ? "BTree contains 12!" : "BTree doesn't contain 12") << endl;
    b.OutputToFile("output.txt", false);
    return 0;
}
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
