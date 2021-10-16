#include <iostream>
#include <string>
#include <sstream>

#define max(a, b) ((a) > (b) ? (a) : (b))

using namespace std;

string school_addition(string v1, string v2, int base)
{
    //initialise int for length, carry and answer. string for results
    unsigned int length = max(v1.size(), v2.size());
    int carry = 0;
    int answer;
    string results;

    // insert 0 at the front when size is different
    while (v1.size() < length)
        v1.insert(0, "0");

    while (v2.size() < length)
        v2.insert(0, "0");

    // calculating from back to front
    for (int i = length - 1; i >= 0; i--)
    {
        answer = (v1[i] - '0') + (v2[i] - '0') + carry;
        carry = answer / base;
        results.insert(0, to_string(answer % base));
    }

    if (carry != 0)
        results.insert(0, to_string(carry));

    //remove the zeros at the front
    return results.erase(0, min(results.find_first_not_of('0'), results.size() - 1));
}

string school_subtraction(string v1, string v2, int base)
{
    //initialize the int and string
    int difference;
    string results;
    unsigned int length = max(v1.size(), v2.size());

    //add 0 at the front if different size
    while (v1.size() < length)
        v1.insert(0, "0");

    while (v2.size() < length)
        v2.insert(0, "0");

    //calculate from the the back to left
    for (int i = length - 1; i >= 0; i--)
    {
        //subtract one by one
        difference = (v1[i] - '0') - (v2[i] - '0');

        //if statement, more than 0 will insert result
        if (difference < 0)
        {
            //take from the column before
            int k = i - 1;

            while (k >= 0)
            {
                v1[k] = ((v1[k] - '0') - 1) % base + '0';
                if (v1[k] != (base - 1))
                {
                    break;
                }
                else
                {
                    k--;
                }
            }
            results.insert(0, to_string(difference + base));
        }
        else
        {
            results.insert(0, to_string(difference));
        }
    }
    //remove 0 at the front
    return results.erase(0, min(results.find_first_not_of('0'), results.size() - 1));
}

string multiplication(string v1, string v2, int base)
{

    //initialize size for the results to prevent segmentation fault
    string results(v1.size() + v2.size(), 0);

    int temp;

    //calculate from right to left, nested for loop
    for (int i = v1.size() - 1; i >= 0; i--)
    {
        for (int j = v2.size() - 1; j >= 0; j--)
        {

            //number minus 0 and multiply with each other
            temp = (v1[i] - '0') * (v2[j] - '0') + results[i + j + 1];

            results[i + j + 1] = temp % base;

            results[i + j] += temp / base;
        }
    }
    for (int i = 0; i < results.size(); i++)
    {
        results[i] += '0';
    }
    if (results[0] == '0')
    {
        return results.substr(1);
    }
    return results;
}

string karatsuba_multi(string v1, string v2, int base)
{
    //initialize integers, string, and convert int to string
    unsigned int length = max(v1.size(), v2.size());
    unsigned int left = length / 2;
    unsigned int right = length - length / 2;
    string same_base;
    stringstream ss;
    ss << base;
    ss >> same_base;

    //base case
    if (v1.size() == 1 || v2.size() == 1)
    {
        return multiplication(v1, v2, base);
    }

    //insert 0 at the front if size is different
    while (v1.size() < length)
    {
        v1.insert(0, "0");
    }

    while (v2.size() < length)
    {
        v2.insert(0, "0");
    }

    //split into a0,a1,b1,b2
    string v1h0 = v1.substr(0, left);
    string v1l1 = v1.substr(left, right);
    string v2h0 = v2.substr(0, left);
    string v2l1 = v2.substr(left, right);

    string c1 = karatsuba_multi(v1h0, v2h0, base);                                                           //c1 = a0 * b0
    string c2 = karatsuba_multi(v1l1, v2l1, base);                                                           //c2=a1*b1
    string c3 = karatsuba_multi(school_addition(v1h0, v1l1, base), school_addition(v2l1, v2h0, base), base); //c3=(a1+a0)*(b1+b0)
    string c4 = school_subtraction(c3, school_addition(c1, c2, base), base);                                 //c4 = (c3 - (c1+c2))

    //Calculate c1*B^2k
    for (int i = 0; i < 2 * right; i++)
        c1 = multiplication(c1, same_base, base);

    for (int i = 0; i < right; i++)
        c4 = multiplication(c4, same_base, base);

    string results = school_addition(school_addition(c1, c2, base), c4, base);
    return results.erase(0, min(results.find_first_not_of('0'), results.size() - 1));
}

//compare the size of both numbers
int compare_size(string v1, string v2)
{
    if (v1.size() > v2.size())
        return 1;
    if (v1.size() < v2.size())
        return -1;
    long int i;
    for (i = 0; i < v1.size(); i++)
    {
        if (v1[i] > v2[i])
            return 1;
        if (v1[i] < v2[i])
            return -1;
    }
    return 0;
}

string division(string v1, string v2, int base)
{

    //initialize int and strings for loop, results and quotient
    int i;
    string results;
    string quotient;

    for (int i = 0; i <= v1.size(); i++)
    {
        //initialize count variable for loop
        int count = 0;

        while (compare_size(results, v2) >= 0)
        {
            //bring in subtraction method to generate recursive results
            results = school_subtraction(results, v2, base);
            for (i = 0; i <= results.size(); i++)
            {
                if (results[i] < base)
                    results[i] = results[i] + '0';
                else
                {
                    results[i] += '1';
                }
            }
            count++;
        }
        //add count times into quotient, v1[i] goes into results variable with increment
        quotient += "0";
        quotient[i] = count;
        results = results + v1[i];
    }

    //for loop if quotient number i is less than base, it will add a zero
    for (i = 0; i <= quotient.size(); i++)
    {
        if (quotient[i] < base)
            quotient[i] = quotient[i] + '0';
        else
        {
            quotient[i] += '1';
        }
    }

    for (i = 0; i <= quotient.length(); i++)
    {
        if (quotient[i] > '0')
            break;
    }

    return quotient.erase(0, i);
}

int main()
{
    string s1, s2;
    int base;

    //take 3 input
    cin >> s1 >> s2 >> base;

    //execute add and karasuba multi
    cout << school_addition(s1, s2, base);
    cout << " ";
    cout << karatsuba_multi(s1, s2, base);
    cout << " ";
    cout << division(s1, s2, base);

    return 0;
}