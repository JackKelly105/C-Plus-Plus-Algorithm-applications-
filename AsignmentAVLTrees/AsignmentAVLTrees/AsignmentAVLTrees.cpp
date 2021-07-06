// AsignmentAVLTrees.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "AVL.h"

using namespace std;
typedef int ItemType;
TreeType<string>tree;
int main()
{
    char selection;
    string i;
    string value;
    string DeleteValue;

    do
    {

        cout << "\n Welcome to AVL Trees Menu\n";
        cout << "  ====================================\n";
        cout << "  1.  Insert into AVL Tree\n";
        cout << "  2.  Print the contents of the AVL Tree\n";
        cout << "  3.  Search AVL Tree for Node\n";
        cout << "  4.  Delete Node from AVL Tree\n";
        cout << "  5.  Exit\n";
        cout << "  ====================================\n";
        cout << "  Enter your selection: ";
        cin >> selection;
        cout << endl;

        switch (selection)
        {
        case '1':
            
            cout << "\t(Type quit to terminate)\n\n";
            do
            {
                cout << "\tEnter a Value: ";
                cin >> value;
                if (value != "quit")
                {
                    tree.InsertItem(value);
                }
            } while (value != "quit");
            break;

        case '2':
            cout << "Inorder traversal of the "
                "constructed AVL tree is \n\n";
            cout << "Node:\tLeft:\tRight:" << endl;
            tree.Print();
            cout << "\n";
            tree.PrintBalanceFactorsInOrder();
            cout << endl;
            break;
        case '3':
        {
            cout << "\nSearch by name." << endl;
            cout << "\nEnter Name: ";
            string name;
            cin >> name;
            bool found = false;
            if (found = true)
            {
                tree.GetItem(name, found);
            }
            if(found == false)
            {
                cout << "\nNode not found.\n" << endl;
            }
                
        }
            break;
        case '4':
        {
            cout << "\t(Type quit to terminate)\n\n";
            do
            {
                cout << "\tEnter a Value For Deletion: ";
                cin >> DeleteValue;
                if (DeleteValue != "quit")
                {
                    tree.DeleteItem(DeleteValue);
                }
            } while (DeleteValue != "quit");
            break;
            
        }
        break;
        case '5':
            cout << "Goodbye.\n";
            break;
        default: cout << selection << " is not a valid menu item.\n";

            cout << endl;
        }

    } while (selection != '5');

    return 0;
}



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
