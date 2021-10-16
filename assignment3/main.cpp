//Name: Guo Yi Tang
//ID: a1756700

#include <iostream>
#include <sstream>
#include <list>
#include <string>
#include <cstring>

using namespace std;

//initialise static const slots in hash table
static const int slots = 26;

//class hashtable with constructor
class HashTable
{
public:
    char key;
    string status;
    string value;
};

//class hashmaptable
class HashMapTable
{

public:
    //initialise arr with 26 slots
    HashTable arr[slots];

public:

    //initialise arr value as null and status as never used
    HashMapTable()
    {
        for (int i = 0; i < slots; i++)
        {
            arr[i].value = '\0';
            arr[i].status = "never used";
        }
    }

    //hash function to find index for the key
    int hashFunction(char key)
    {
        return key % slots;
    }

    //first perform searching according to its status and the occurrence of value, then decide whether to insert based on boolean check
    void insertion(char key, string value)
    {
        //initialise boolean check and hashValue
        bool check = true; 
        int current = key - 97;

        //use do while statement to perform insertion with boolean check
        do
        {
            if (arr[current].status == "occupied" && arr[current].value == value)
            {
                //return 
                check = false;
            }
            else if (arr[current].status == "never used" || arr[current].status == "tombstone")
            {
                //update value and status, then return
                check = false;
                arr[current].value = value;
                arr[current].status = "occupied";
            }
            else
            {
                //otherwise move to next slot or find the next available slot
                current = hashFunction(current + 1);
            }
        } while (check);
    }

    //perform searching with boolean check and deletion and update status
    void deletion(char key, string value)
    {
        //initialise boolean check and int current without last letter
        bool check = true;
        int current = key - 97;

        //use do while statement to iterate through table to perform delection and change status
        do
        {
            //when slot is empty
            if (arr[current].status == "never used")
            {
                //true because nothing to delete
                check = false;
            }
            //when slot has something that match the value
            else if (arr[current].status == "occupied" && arr[current].value == value)
            {
                //found change status and return
                check = false;
                arr[current].status = "tombstone";
            }
            else
            {
                //otherwise move to next slot or find the next available slot
                current = hashFunction(current + 1);
            }
        } while (check);
    }

    void display()
    {
        //display the value for output
        for (int i = 0; i < slots; i++)
        {
            //check to make sure there are something in the slot
            if (arr[i].status == "occupied")
            {
                cout << arr[i].value << " ";
            }
        }
    }
};

int main()
{

    //initialize string input and use getline function
    string input;
    getline(cin, input);
    //create new table with NULL
    HashMapTable *table = new HashMapTable();

    //can only keep 10 values
    char value[10];
    int i, j, length;

    //use for loop with i and j variables according to input size which is not longer than 11 including 'A' or 'D'
    for (i = 0, j = 0; i <= input.size(); i++)
    {
        //if getting all the input, continue
        if (input[i] == '\0' || input[i] == ' ')
        {

            //value in J is null
            value[j] = '\0';

            //initialise input length, first letter for 'A' and 'D', key being the last letter and newValue for insertion and deletion
            length = strlen(value);
            char firstLetter = value[0];
            char key = value[length - 1];
            string newValue(&value[1]);

            //if firstletter is A then insertion, D is deletion
            if (firstLetter == 'A')
            {
                table->insertion(key, newValue);
            }

            if (firstLetter == 'D')
            {
                table->deletion(key, newValue);
            }

            //reset J to 0
            j = 0;
        }
        else
        {
            //continue to add input
            value[j++] = input[i];
        }
    }

    //display
    table->display();
    cin >> input;

    return 0;
}
