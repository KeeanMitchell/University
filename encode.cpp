#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
#include <iomanip>

using namespace std;

#define SIZE 26

int n = 0;

map<char, string> theDictionary;

class TreeNode
{
public:
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    char value = '*';
    int frequency = -1;
    string binaryVal = "";

    TreeNode(char val, int freq)
    {
        this->value = val;
        this->frequency = freq;
    }

    bool operator<(const TreeNode &other)
    {
        if (frequency < other.frequency)
        {
            return true;
        }
        else if (frequency > other.frequency)
        {
            return false;
        }
        else if (value < other.value)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void preorder()
    {
        cout << value << "[" << frequency << "] ";
        if (left)
            left->preorder();
        if (right)
            right->preorder();
    }
};

TreeNode *merge(TreeNode &t1, TreeNode &t2)
{
    // Return a new node with t1 and t2 as children
    if (t1.right == nullptr)
    {
        //cout << "fuck this shit" << endl;
    }
    TreeNode *output = new TreeNode('*', t1.frequency + t2.frequency);

    output->left = &t1;
    output->right = &t2;
    return output;
}

void theDict(char letter, string binary)
{
    if (letter == '*')
    {
        return;
    }
    pair<char, string> aLetter;
    aLetter.first = letter;
    aLetter.second = binary;
    theDictionary.insert(aLetter);
}

void inOrderTraversal(TreeNode *subtree)
{

    if (subtree->left != nullptr)
    {
        //cout << "go left" << endl;

        subtree->left->binaryVal = subtree->binaryVal + "0";
        theDict(subtree->left->value, subtree->left->binaryVal);
        //cout << "( " << subtree->value << ' ' << subtree->frequency << ' ' << subtree->binaryVal << " ) ";
        inOrderTraversal(subtree->left);
    }
    //cout << "middle" << endl;
    //cout << "( " << subtree->value << ' ' << subtree->frequency << ' ' << subtree->binaryVal << " ) ";
    if (subtree->right != nullptr)
    {
        //cout << "go right" << endl;
        subtree->right->binaryVal = subtree->binaryVal + "1";
        theDict(subtree->right->value, subtree->right->binaryVal);
        //cout << "( " << subtree->value << ' ' << subtree->frequency << ' ' << subtree->binaryVal << " ) ";
        inOrderTraversal(subtree->right);
    }
}

list<TreeNode *>::iterator locateIndex(list<TreeNode *> *q, int freq)
{
    for (auto it = q->begin(); it != q->end(); it++)
    {
        //cout << "tenaya is lame" << endl;
        if ((*it)->frequency > freq)
        {
            return it;
        }
    }
    return q->end();
}

list<TreeNode *> *sortingQ(list<TreeNode *> *q)
{
    if (q->size() == 1)
    {
        return q;
    }
    TreeNode *t1 = q->front();
    q->pop_front();
    TreeNode *t2 = q->front();
    q->pop_front();
    TreeNode *newNode = merge(*t1, *t2);
    q->insert(locateIndex(q, newNode->frequency), newNode);
    return sortingQ(q);
}

list<TreeNode *> *prepareQ(int size, vector<pair<char, int>> sorted)
{
    list<TreeNode *> *queue = new list<TreeNode *>();
    for (int i = 0; i < size; i++)
    {
        char val = sorted[i].first;
        int freq = sorted[i].second;
        TreeNode *temp = new TreeNode(val, freq);
        queue->push_back(temp);
    }
    // for (auto &it : *queue)
    // {
    //     cout << it->value << ' ' << it->frequency << endl;
    // }
    return queue;
}

bool compare(pair<char, int> a, pair<char, int> b)
{
    return a.second < b.second;
}

list<TreeNode *> *sortMap(string str)
{
    map<char, int> freqTable;
    for (char i : str)
    {
        freqTable[i]++;
        n++;
    }
    vector<pair<char, int>> sorting;
    for (auto &it : freqTable)
    {
        sorting.push_back(it);
    }
    sort(sorting.begin(), sorting.end(), compare);
    for (auto &it : sorting)
    {
        cout << it.first << ' ';
    }
    cout << endl;
    for (auto &it : sorting)
    {
        cout << it.second << ' ';
    }
    cout << endl;
    //cout << sorting.size() << endl;
    return prepareQ(sorting.size(), sorting);
}

// // void CharFreq(string str)
// // {
// //     map<char, int> freqTable;
// //     for (char i : str)
// //     {
// //         freqTable[i]++;
// //     }

// //     // for (map<char,int>::const_iterator it = freqTable.begin();
// //     //     it!=freqTable.end(); it++){
// //     //         cout << it->first << " " <<it->second << endl;
// //     //     }
// //     //     cout << "---------------------------------" << endl;
// //     sortMap(freqTable);
// // }

int main()
{
    string line;
    string decoded;
    getline(cin, line);
    list<TreeNode *> *q = sortMap(line);
    TreeNode *root = sortingQ(q)->front();
    inOrderTraversal(root);
    for (char i : line)
    {
        for (map<char, string>::const_iterator it = theDictionary.begin(); it != theDictionary.end(); it++)
        {
            if (i == it->first)
            {
                decoded = decoded + it->second;
            }
        }
    }
    //cout << "after all this time" << endl;
    cout << decoded << endl;
    cout << "Total Bits (Original):" << n*8 << endl;
    cout << "Total Bits (coded):" << decoded.size() << endl;
    // theDictionary.insert(theDict())
    // cout << "==================================" << endl;
    //cout << root.right->right->value << ' ' << root.right->right->frequency << endl;

    // Build frequency table

    // Create the tree

    // Encode the string

    // Output encoding

    return 0;
}
