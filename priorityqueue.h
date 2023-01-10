// priorityqueue.h
//
// Nikos Kotsopulos priorityqueue
#pragma once

#include <iostream>
#include <sstream>
#include <set>

using namespace std;

template <typename T>
class priorityqueue
{
private:
    struct NODE
    {
        int priority; // used to build BST
        T value;      // stored data for the p-queue
        bool dup;     // marked true when there are duplicate priorities
        NODE *parent; // links back to parent
        NODE *link;   // links to linked list of NODES with duplicate priorities
        NODE *left;   // links to left child
        NODE *right;  // links to right child
    };
    NODE *root; // pointer to root node of the BST
    int size;   // # of elements in the pqueue
    NODE *curr; // pointer to next item in pqueue (see begin and next)

    NODE *leftNode(NODE *node)
    {
        while (node != NULL && node->left != NULL)
            node = node->left;
        return node;
    }

    NODE *rightNode(NODE *node)
    {
        while (node != NULL && node->right != NULL)
            node = node->right;
        return node;
    }

    NODE *inOrderHelper(NODE *node)
    {
        if (root == NULL)
            return NULL;
        // if(root==node ||)
    }

    void postOrderClear(NODE *node)
    {
        if (node == nullptr)
            return;
        postOrderClear(node->left);
        if(node->link!=NULL){
            NODE* prev;
            while(node->link!=NULL){
                prev = node;
                node = node->link;
            }
            postOrderClear(node->link);
        }
        postOrderClear(node->right);
        delete node;
    }

    void toStringHelper(ostream &output, NODE *node)
    {
        if (node == nullptr)
            return;
        toStringHelper(output, node->left);
        output << node->priority << " value: " << node->value << endl;
        if (node->dup == true)
            toStringHelper(output, node->link);
        toStringHelper(output, node->right);
    }

    bool _equality(NODE *mycur, NODE *othercur) const
    {
        if (mycur == nullptr && othercur == nullptr) // both empty
            return true;
        else if (mycur == nullptr) // left empty
            return false;
        else if (othercur == nullptr) // right empty
            return false;
        else
        {
            if (_equality(mycur->link, othercur->link) &&
                mycur->priority == othercur->priority &&
                mycur->value == othercur->value &&
                _equality(mycur->left, othercur->left) &&
                _equality(mycur->right, othercur->right))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

public:
    //
    // default constructor:
    //
    // Creates an empty priority queue.
    // O(1)
    //
    priorityqueue()
    {
        root = nullptr;
        size = 0;
        curr = nullptr;
    }

    //
    // operator=
    //
    // Clears "this" tree and then makes a copy of the "other" tree.
    // Sets all member variables appropriately.
    // O(n), where n is total number of nodes in custom BST
    //
    priorityqueue &operator=(const priorityqueue &other)
    {
        if (this != &other)
        {
            this->clear();
            this->root = other.root;
            this->size = other.size;
            this->curr = other.curr;
        }
        return *this;
    }

    //
    // clear:
    //
    // Frees the memory associated with the priority queue but is public.
    // O(n), where n is total number of nodes in custom BST
    //
    void clear()
    {
        postOrderClear(root);
        root = nullptr;
        curr = nullptr;
        size = 0;
    }

    //
    // destructor:
    //
    // Frees the memory associated with the priority queue.
    // O(n), where n is total number of nodes in custom BST
    //
    ~priorityqueue()
    {
        delete root;
    }

    //
    // enqueue:
    //
    // Inserts the value into the custom BST in the correct location based on
    // priority.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    void enqueue(T value, int priority)
    {
        NODE *previous;
        curr = root;
        if (curr == nullptr)
        {
            NODE *temp = new NODE;
            temp->value = value;
            temp->priority = priority;
            temp->parent = nullptr;
            temp->left = nullptr;
            temp->right = nullptr;
            temp->dup = false;
            root = temp;
            size++;
            return;
        }
        NODE *insert = new NODE;
        while (curr != nullptr)
        {
            previous = curr;
            if (priority < curr->priority)
            {
                curr = curr->left;
            }
            else if (priority > curr->priority)
            {

                curr = curr->right;
            }
            else if (priority == curr->priority)
            {
                curr->dup = true;
                while (curr != nullptr)
                {
                    previous = curr;
                    curr = curr->link;
                }
                previous->dup = true;
                previous->link = insert;
                insert->dup = true;
                insert->link = NULL;
                break;
            }
        }
        if (priority < previous->priority)
        {
            previous->left = insert;
            insert->dup = false;
        }
        else if (priority > previous->priority)
        {
            previous->right = insert;
            insert->dup = false;
        }
        insert->value = value;
        insert->priority = priority;
        insert->parent = previous;
        insert->left = nullptr;
        insert->right = nullptr;
        size++;
    }

    //
    // dequeue:
    //
    // returns the value of the next element in the priority queue and removes
    // the element from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T dequeue()
    {
        curr = root;
        if (curr == NULL)
            return NULL;
        while (curr->left != NULL)
            curr = curr->left;
        // smallest node reached

        // check duplicates
        if (curr->link != NULL)
        {
            NODE *previous = curr;
            while (curr->link != NULL)
            {
                previous = curr;
                curr = curr->link;
            }
            NODE *temp = curr;
            delete curr->link;
            size--;
            return temp->value;
        }
        // if one child is null
        if (curr->left == NULL)
        {
            NODE *temp = curr;
            delete curr;
            size--;
            return temp->value;
        }
        else if (curr->right == NULL)
        {
            NODE *temp = curr;
            delete curr;
            size--;
            return temp->value;
        }

        // curr has two children
        else
        {
            NODE *rootTracker = root;
            NODE *currParent = rootTracker;
            NODE *nextNode = rootTracker->right;
            while (nextNode->left != NULL)//find next node to dequeue
            {
                currParent = nextNode;
                nextNode = nextNode->left;
            }
            if (currParent != rootTracker)//checking if root
                currParent->left = nextNode;
            else
                currParent->right = nextNode->right;
            rootTracker->value = nextNode->value;
            delete nextNode;
            size--;
            return rootTracker->value;
        }
    }

    //
    // Size:
    //
    // Returns the # of elements in the priority queue, 0 if empty.
    // O(1)
    //
    int Size()
    {
        return size;
    }

    //
    // begin
    //
    // Resets internal state for an inorder traversal.  After the
    // call to begin(), the internal state denotes the first inorder
    // node; this ensure that first call to next() function returns
    // the first inorder node value.
    //
    // O(logn), where n is number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (tree.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    void begin()
    {
        NODE *previous;
        if (root == nullptr)
            return;
        curr = root;
        while (curr->left != nullptr)//go to minimum priority node
            curr = curr->left;
        if (curr->dup == true)//handles duplicates
        {
            while (curr != nullptr)
            {
                previous = curr;
                curr = curr->link;
            }
            curr = previous;
        }
    }

    //
    // next
    //
    // Uses the internal state to return the next inorder priority, and
    // then advances the internal state in anticipation of future
    // calls.  If a value/priority are in fact returned (via the reference
    // parameter), true is also returned.
    //
    // False is returned when the internal state has reached null,
    // meaning no more values/priorities are available.  This is the end of the
    // inorder traversal.
    //
    // O(logn), where n is the number of unique nodes in tree
    //
    // Example usage:
    //    pq.begin();
    //    while (pq.next(value, priority)) {
    //      cout << priority << " value: " << value << endl;
    //    }
    //    cout << priority << " value: " << value << endl;
    //
    bool next(T &value, int &priority)
    {
        value = curr->value;
        priority = curr->priority;
        NODE *p = curr->parent;
        if (curr->link != NULL)
        {
            curr = curr->link;
            return true;
        }
        else
        {
            while (curr == p->link)
                curr = p;
            curr = curr->parent;
        }
        if (curr->right != NULL)
        {
            NODE *temp = curr->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            curr = temp;
            return true;
        }
        while (p != NULL)
        {
            // once last node is reached go back up the tree until p is null and curr is set to root
            if (curr == p->right)
            {
                curr = p;
                p = p->parent;
            }
            // put duplicate check here

            // go up tree from left
            else
            {
                curr = p;
                return true;
            }
        }
        return false;
    }

    //
    // toString:
    //
    // Returns a string of the entire priority queue, in order.  Format:
    // "1 value: Ben
    //  2 value: Jen
    //  2 value: Sven
    //  3 value: Gwen"
    //

    string toString()
    {
        stringstream ss("");
        toStringHelper(ss, root);
        return ss.str();
    }

    //
    // peek:
    //
    // returns the value of the next element in the priority queue but does not
    // remove the item from the priority queue.
    // O(logn + m), where n is number of unique nodes in tree and m is number of
    // duplicate priorities
    //
    T peek()
    {
        curr = root;
        if (curr == NULL)
        {
            return NULL;
        }
        while (curr->left != NULL)
        {
            curr = curr->left;
        }
        return curr->value;
    }

    //
    // ==operator
    //
    // Returns true if this priority queue as the priority queue passed in as
    // other.  Otherwise returns false.
    // O(n), where n is total number of nodes in custom BST
    //
    bool operator==(const priorityqueue &other) const
    {
        return _equality(this->root, other.root);
    }

    //
    // getRoot - Do not edit/change!
    //
    // Used for testing the BST.
    // return the root node for testing.
    //
    void *getRoot()
    {
        return root;
    }
};
