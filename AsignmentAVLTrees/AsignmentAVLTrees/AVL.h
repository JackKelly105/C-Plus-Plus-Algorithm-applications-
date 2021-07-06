
#include <iostream>

using namespace std;
typedef enum { LH, EH, RH } Balfactor;
template <class ItemType>
struct TreeNode
{
    ItemType info;
    TreeNode* left;
    TreeNode* right;
    Balfactor bf;
};

template <class ItemType>
class TreeType
{
public:
    
    void InsertItem(ItemType item);
    void Print();
    void PrintBalanceFactorsInOrder();
    void GetItem(ItemType item, bool& found);
    void DeleteItem(ItemType item);

    
    
private:
    TreeNode <ItemType>* root;
};

template <class ItemType>
void TreeType<ItemType> ::InsertItem(ItemType item)
// Calls recursive function Insert to insert item into tree.
{
    bool taller = false;
    Insert(root, item, taller);
}

template <class ItemType>
void Insert(TreeNode<ItemType>*& tree, ItemType item, bool& taller)
// Inserts item into tree.
{
    if (tree == NULL)
    {    
        tree = new TreeNode<ItemType>;
        tree->left = NULL;
        tree->right = NULL;
        tree->info = item;
        tree->bf = EH;
        taller = true;
    }
    else if (item == tree->info)
        cout << "Duplicate key is not allowed in AVL tree." << endl;
    else if (item < tree->info)
    {
        Insert(tree->left, item, taller);
        // Insert into left subtree
        if (taller)
            switch (tree->bf)
            {
            case LH: LeftBalance(tree, taller);
                break;
            case EH: tree->bf = LH;
                break;
            case RH: tree->bf = EH;
                taller = false;
                break;
            }
    }
    else
    {
        Insert(tree->right, item, taller);
        // Insert into right subtree
        if (taller)
            switch (tree->bf)
            {
            case RH: RightBalance(tree, taller);
                break;
            case EH: tree->bf = RH;
                break;
            case LH: tree->bf = EH;
                taller = false;
                break;
            }

    }
}
template <class ItemType>
void TreeType<ItemType> ::Print()
{
    PrintInorder(root);
}
template <class ItemType>
void PrintInorder(TreeNode<ItemType>*& tree)
{

    if (tree == NULL)
        return;

    PrintInorder(tree->left);

    TreeNode<ItemType>* ls = tree->left;
    TreeNode<ItemType>* rs = tree->right;
    ItemType left;
    ItemType right;

    if (rs == NULL)
    {
        right = "-";
    }
    else
    {
        right = rs->info;
    }
    if (ls == NULL)
    {
        left = "-";
    }
    else
    {
        left = ls->info;
    }
    cout << tree->info << "\t" << left << "\t" << right << endl;
    PrintInorder(tree->right);
}

template <class ItemType>
void RotateLeft(TreeNode<ItemType>*& tree)
{
    TreeNode<ItemType>* rs;
    if (tree == NULL)
        cout << "It is impossible to rotate an empty tree in RotateLeft" << endl;
    else if (tree->right == NULL)
        cout << "It is impossible to make an empty subtree the root in RotateLeft" << endl;
    else
    {
        rs = tree->right;
        tree->right = rs->left;
        rs->left = tree;
        tree = rs;

    }
}

template <class ItemType>
void RotateRight(TreeNode<ItemType>*& tree)
{
    TreeNode<ItemType>* ls;
    if (tree == NULL)
        cout << "It is impossible to rotate an empty tree in RotateRight" << endl;
    else if (tree->left == NULL)
        cout << "It is impossible to make an empty subtree the root in RotateRight" << std::endl;
    else
    {
        ls = tree->left;
        tree->left = ls->right;
        ls->right = tree;
        tree = ls;

    }

}

template <class ItemType>
void RightBalance(TreeNode<ItemType>*& tree, bool& taller)
{
    TreeNode<ItemType>* rs = tree->right;
    TreeNode<ItemType>* ls;
    switch (rs->bf)
    {
    case RH:
        tree->bf = rs->bf = EH;
        RotateLeft(tree);
        taller = false;
        break;
    case EH:
        cout << "Tree already balanced " << endl;
        break;
    case LH:
        ls = rs->left;
        switch (ls->bf)
        {
        case RH:
            tree->bf = LH;
            rs->bf = EH;
            break;
        case EH:
            tree->bf = rs->bf = EH;
            break;
        case LH:
            tree->bf = EH;
            rs->bf = RH;
            break;
        }
        ls->bf = EH;
        RotateRight(tree->right);
        RotateLeft(tree);
        taller = false;
    }
}


template <class ItemType>
void LeftBalance(TreeNode<ItemType>*& tree, bool& taller)
{
    TreeNode<ItemType>* ls = tree->left;
    TreeNode<ItemType>* rs;
    switch (ls->bf)
    {
    case LH:
        tree->bf = ls->bf = EH;
        RotateRight(tree);
        taller = false;
        break;
    case EH:
        cout << "Tree already balanced " << endl;
        break;
    case RH:
        rs = ls->right;
        switch (rs->bf)
        {
        case LH:
            tree->bf = RH;
            ls->bf = EH;
            break;
        case EH:
            tree->bf = ls->bf = EH;
            break;
        case RH:
            tree->bf = EH;
            ls->bf = LH;
            break;

        }
        rs->bf = EH;
        RotateLeft(tree->left);
        RotateRight(tree);
        taller = false;
    }

}



template <class ItemType>
void TreeType<ItemType>::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
    Retrieve(root, item, found);
}
template <class ItemType>
void Retrieve(TreeNode<ItemType>*& tree, ItemType& item, bool& found)
{
    if (tree == nullptr)
        found = false;
    else if (item < tree->info)
    {
        Retrieve(tree->left, item, found);
        
        
    }
    else if (item > tree->info)
    {
        Retrieve(tree->right, item, found);
        
    }
    else
    {
        item = tree->info;
        found = true;
        cout << "\nThe Node " + item + " you have searched for has been found\n";
    }
}
template <class ItemType>
void TreeType<ItemType> ::PrintBalanceFactorsInOrder()
{
    InOrderPrintBF(root);
}
template <class ItemType>
void InOrderPrintBF(TreeNode<ItemType>*& tree)

{
    if (tree != NULL)
    {
        InOrderPrintBF(tree->left);
        // Print left subtree.
        PrintOrderedBF(tree);
        InOrderPrintBF(tree->right);
        // Print right subtree.
    }
}
template <class ItemType>
void PrintOrderedBF(TreeNode<ItemType>*& tree)
{
    cout << tree->info << " BF: ";
    switch (tree->bf)
    {
    case LH:
        cout << "Left High" << endl;
        break;
    case RH:
        cout << "Right High" << endl;
        break;
    case EH:
        cout << "Equal High" << endl;
        break;
    }
    if (tree->left != nullptr)
        cout << " left child : " << tree->left->info << endl;
    if (tree->right != nullptr)
        cout << "right child : " << tree->right->info << endl;
    if (tree->left == nullptr && tree->right == nullptr)
        cout << "This is a Leaf Node." << endl;
    cout << endl;
}
template <class ItemType>
void TreeType<ItemType> ::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
    bool shorter;
    Delete(root, item, shorter);
}

template <class ItemType>
void Delete(TreeNode<ItemType>*& tree, ItemType item, bool& shorter)
{
    if (tree != NULL)
    {
        if (item < tree->info)
        {
            Delete(tree->left, item, shorter);
            // Look in left subtree.
            if (shorter)
                switch (tree->bf)
                {
                case LH: tree->bf = EH; break;
                case EH: tree->bf = RH; shorter = false;
                    break;
                case RH: DelRightBalance(tree, shorter);
                } // END SWITCH	
        }
        else if (item > tree->info)
        {
            Delete(tree->right, item, shorter);
            // Look in right subtree.
            if (shorter)
                switch (tree->bf)
                {
                case LH: DelLeftBalance(tree, shorter);
                break;				
                case EH: tree->bf = LH; shorter = false; 							
                break;
                case RH: tree->bf = EH; 
                break;
                } // END SWITCH
        }
        else
            DeleteNode(tree, shorter);
        // Node found; call DeleteNode.
    } // END if (tree != NULL)
    else
    {
        cout << "\nNOTE: " << item
            << " not in the tree so cannot be deleted.";
    }
}

template <class ItemType>
void DeleteNode(TreeNode <ItemType>*& tree, bool& shorter)
// Delete the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no longer in the tree. // If tree is a leaf node or has only one non-NULL child pointer, the node 
// pointed to by tree is deleted; otherwise, the user's data is replaced by its
// logical predecessor and the predecessor's node is deleted.
{
    ItemType data;	TreeNode <ItemType>* tempPtr;
    tempPtr = tree;
    if (tree->left == NULL)
    {
        tree = tree->right;
        delete tempPtr;
        shorter = true;
    }
    else if (tree->right == NULL)
    {
        tree = tree->left;
        delete tempPtr;
        shorter = true;
    }
    else
    {
        GetPredecessor(tree, data);
        tree->info = data;
        Delete(tree->left, data, shorter);
        // Delete the predecessor node
        if (shorter)
            switch (tree->bf)
            {
            case LH: tree->bf = EH; break;
            case EH: tree->bf = RH; shorter = false;
                break;
            case RH: DelRightBalance(tree, shorter);
            }
    }
}

template <class ItemType>
void GetPredecessor(TreeNode<ItemType>* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
    tree = tree->left;
    while (tree->right != NULL)
        tree = tree->right;
    data = tree->info;
}

template <class ItemType>
void DelRightBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
    TreeNode<ItemType>* rs = tree->right;
    TreeNode<ItemType>* ls;
    switch (rs->bf)
    {
    case RH:	tree->bf = rs->bf = EH;
        RotateLeft(tree);
        shorter = true; break;
    case EH:	tree->bf = RH;
        rs->bf = LH;
        RotateLeft(tree);
        shorter = false; break;
    case LH:	ls = rs->left;
        switch (ls->bf)
        {
        case RH:	tree->bf = LH;
            rs->bf = EH; break;
        case EH:	tree->bf = rs->bf = EH;
            break;
        case LH:	tree->bf = EH;
            rs->bf = RH; break;
        } // END SWITCH

        ls->bf = EH;
        RotateRight(tree->right);
        RotateLeft(tree);
        shorter = true;
    }
}

template <class ItemType>
void DelLeftBalance(TreeNode<ItemType>*& tree, bool& shorter)
{
    TreeNode<ItemType>* ls = tree->left;
    TreeNode<ItemType>* rs;
    switch (ls->bf)
    {
    case LH:	tree->bf = ls->bf = EH;
        RotateRight(tree);
        shorter = true; break;
    case EH:	tree->bf = LH;
        ls->bf = RH;
        RotateRight(tree);
        shorter = false; break;
    case RH:	rs = ls->right;
        switch (rs->bf)
        {
        case LH:	tree->bf = RH;
            ls->bf = EH; break;
        case EH:	tree->bf = ls->bf = EH;
            break;
        case RH:	tree->bf = EH;
            ls->bf = LH; break;
        } // END SWITCH
        rs->bf = EH;
        RotateLeft(tree->left);
        RotateRight(tree);
        shorter = true;
    }
}
