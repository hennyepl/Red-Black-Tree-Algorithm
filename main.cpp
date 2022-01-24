//************************************************************************|
//          University of Lethbridge, Lethbridge, AB, Canada              |
//                        CPSC3620 Project                                |
//             Created by Henok Lamiso on 2021-11-25                      |
//************************************************************************|


#include "RedBlackTree.h" //Header file that contains the implemantation
#include <iostream>
using namespace std;

int main() {
    int option;
    cout<<"\n\n*******************************************************"<<endl;
    cout<<"*\tCPSC3620 Project by Henok Lamiso and Liam Thoren  *\t\n*\t\t\t\tRed-Black Tree Algorithm\t\t\t  *\n*\t\t\t\t\t\tFall 2021\t\t\t\t\t  *\n*\t\t\t\tUniversity of Lethbridge\t\t\t  *"<<endl;
    cout<<"*******************************************************\n"<<endl;

    RedBlackTree t;

    cout<<"*******************************************************"<<endl;
    cout<<"*\t\tOprations  *";
    cout<<"\n*\t1.Insert\t\t\t\t\t\t\t\t\t\t  *";
    cout<<"\n*\t2.Delete\t\t\t\t\t\t\t\t\t\t  *";
    cout<<"\n*\t3.Print Tree\t\t\t\t\t\t\t\t\t  *";
    cout<<"\n*\t4.Exit\t\t\t\t\t\t\t\t\t\t\t  *"<<endl;
    cout<<"*******************************************************\n"<<endl;

    do {
        cout<<"Please select one: ";
        cin>>option;
        if(option == 1) {
            int insertKey;
            cout << "Enter key: ";
            cin>>insertKey;
            t.insert(insertKey);
        }
        else if (option == 2) {
            int deleteKey;
            cout << "Which Node do you want to delete? ";
            cin>>deleteKey;
            t.deleteNode(deleteKey);
        }
        if (option == 3) {
            t.printTree();
        }
        } while(option != 4);
        cout << "\n****************** PROGRAM TERMINATED *****************\n\n"<<endl;
    return 0;
}
