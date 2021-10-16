//Name: Guoyi Tang
//ID: a1756700

#include <iostream>

using namespace std;

//initialize an empty AVL tree node
class Node
{
public:
    int number;
    int height;
    Node *right;
    Node *left;
};

//calculate the height of tree
int height(Node *N)
{
    //if N has element then return its height otherwise return 0
    if (N != NULL)
    {
        return N->height;
    }
    else
    {
        return 0;
    }
}

//get balance value of the node
int balance_value(Node *N)
{
    if (N != NULL)
    {
        return (height(N->left) - height(N->right));
    }
    else
    {
        return 0;
    }
}

//function to update height for node
void updateHeight(Node *N)
{
    if (N != NULL || N->right != NULL || N->left != NULL)
    {
        int curr = max(height(N->right), height(N->left));
        N->height = 1 + curr;
    }
}

//check and return maximum value from the left subtree for AVL tree
Node *leftMaxValue(Node *N)
{
    Node *curr = N;

    while (curr->right != NULL)
    {
        curr = curr->right;
    }

    return curr;
}

//return right rotate
Node *rightRotate(Node *x)
{
    Node *y = x->left;
    Node *w = y->right;

    //rotate
    y->right = x;
    x->left = w;

    updateHeight(x);
    updateHeight(y);

    return y;
}

//return left rotate
Node *leftRotate(Node *y)
{
    Node *x = y->right;
    Node *w = x->left;

    //rotate
    x->left = y;
    y->right = w;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node *insertion(Node *N, int number)
{
    //if empty then use default value
    if (N == NULL)
    {
        N = new Node();
        N->number = number;
        N->left = NULL;
        N->right = NULL;
        N->height = 1;
        return N;
    }

    if (number > N->number)
    {
        N->right = insertion(N->right, number);
    }
    else if (number < N->number)
    {
        N->left = insertion(N->left, number);
    }
    else
    {
        return N;
    }

    if (N != NULL)
        //update height
        updateHeight(N);

    //check balance
    int balance = balance_value(N);
    //if balance value less than -1
    if (balance < -1)
    {
        //left rotate needed because right imbalanced
        if (number > N->right->number)
        {
            return leftRotate(N);
        }
        //right then left rotate needed
        if (number < N->right->number)
        {
            N->right = rightRotate(N->right);
            return leftRotate(N);
        }
    }
    //if balance value more than 1
    if (balance > 1)
    {
        //left rotate needed because right imbalanced
        if (number < N->left->number)
        {
            return rightRotate(N);
        }
        //left then right rotate needed
        if (number > N->left->number)
        {
            //left rotate
            N->left = leftRotate(N->left);
            return rightRotate(N);
        }
    }
    return N;
}

Node *deletion(Node *N, int number)
{
    Node *curr;
    //default
    if (N == NULL)
    {
        return N;
    }

    //if target is greater
    //traverse right
    if (number > N->number)
    {
        N->right = deletion(N->right, number);
    }
    //target less than root then traverse left
    else if (number < N->number)
    {
        N->left = deletion(N->left, number);
    }
    //target found
    else if (number == N->number)
    {
        if ((N->right == NULL) && (N->left == NULL))
        {
            N = NULL;
        }
        //left child
        else if ((N->right == NULL) && (N->left != NULL))
        {
            N = N->left;
        }
        //right child
        else if ((N->right != NULL) && (N->left == NULL))
        {
            N = N->right;
        }
        //2 children
        else
        {
            curr = leftMaxValue(N->left);              //find max from left subtree
            N->number = curr->number;                  //swap
            N->left = deletion(N->left, curr->number); //remove
        }
    }

    if (N != NULL)
        updateHeight(N); //update height

    //check balance
    int balance = balance_value(N);
    //if balance value less than -1
    if (balance < -1)
    {
        //left rotate needed because right imbalanced
        if (balance_value(N->right) <= 0)
        {
            return leftRotate(N);
        }
        //right then left rotate needed
        if (balance_value(N->right) > 0)
        {
            N->right = rightRotate(N->right);
            return leftRotate(N);
        }
    }
    //if balance value more than 1
    if (balance > 1)
    {
        //left rotate needed because right imbalanced
        if (balance_value(N->left) >= 0)
        {
            return rightRotate(N);
        }
        //left then right rotate needed
        if (balance_value(N->left) < 0)
        {
            //left rotate
            N->left = leftRotate(N->left);
            return rightRotate(N);
        }
    }
    return N;
}

//method for pre order
void pre_order(Node *N)
{
    if (N != NULL)
    {
        cout << N->number << " ";
        pre_order(N->left);
        pre_order(N->right);
    }
    else
    {
        return;
    }
}

//method for in order
void in_order(Node *N)
{
    if (N != NULL)
    {
        in_order(N->left);
        cout << N->number << " ";
        in_order(N->right);
    }
    else
    {
        return;
    }
}

//method for psot order
void post_order(Node *N)
{
    if (N != NULL)
    {
        post_order(N->left);
        post_order(N->right);
        cout << N->number << " ";
    }
    else
    {
        return;
    }
}

//main function
int main()
{
    Node *N = NULL;
    //initialize string to store "instructions" and the number
    string wordInput, intFromInput;
    string input_1 = "PRE";
    string input_2 = "IN";
    string input_3 = "POST";

    int num = 1;

    while (num != 0)
    {
        //take input
        cin >> wordInput;

        //4 cases pre post in and no tree
        if (input_1 == wordInput)
        {
            pre_order(N);
            if (N == NULL)
            {
                cout << "EMPTY" << endl;
            }
            break;
        }
        else if (input_2 == wordInput)
        {
            in_order(N);
            if (N == NULL)
            {
                cout << "EMPTY" << endl;
            }
            break;
        }
        else if (input_3 == wordInput)
        {
            post_order(N);
            if (N == NULL)
            {
                cout << "EMPTY" << endl;
            }
            break;
        }

        int inputSize = wordInput.size();              //store length of input
        intFromInput = wordInput.substr(1, inputSize); //take the number starting from index 1
        int intInput = stoi(intFromInput.c_str());     //conver string to int

        //perform insertion and deletion based on the instructions from input (first letter)
        if (wordInput[0] == 'A')
        {
            N = insertion(N, intInput);
        }

        if (wordInput[0] == 'D')
        {
            N = deletion(N, intInput);
        }
    }
    return -1;
}