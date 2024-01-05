#include <iostream>
#include "Array.h"

double calculateAvg(Array arr)
{
    double avg = 0;
    if (arr.Size() == 0) return 0;

    for (int i = 0; i < arr.Size(); i++)
        avg += arr[i];
    avg /= arr.Size();
    return avg;
}
int main() {
    using std::cout;
    using std::cin;
    using std::endl;

    Array arr_1(10, 0);
    Array arr_2(10, 0);
    cout << "Creating an array of random numbers: ";
    arr_1.RandArray(0, 100);
    arr_1.Print();
    cout << "Creating an array of random numbers in increasing order: ";
    arr_1.RandArrayIns(-50, 100);
    arr_1.Print();
    cout << "Creating an array of random numbers in descending order: ";
    arr_1.RandArrayDes(-50, 100);
    arr_1.Print();
    cout << endl;

    arr_2.RandArray(0, 100);
    cout << "Swap contents of masives:\narr_1: " << arr_1 << "arr_2: " << arr_2;
    arr_1.Swap(arr_2);
    cout << "Result:\narr_1: " << arr_1 << "arr_2: " << arr_2;
    cout << endl;

    int el = 50;
    cout << "Searching for the index of an element in an array:\nThe desired element: "<<el<<"\n";
    int index= arr_1.ISearch(el);
    if (index == -1) cout << "There are no occurrences\n";
    else cout<<"It's index: " << index;
    cout << endl;

    cout << "Sort the array arr_1: ";
    arr_1.Sort();
    cout << arr_1;
    cout << endl;

    el = 125; index = 5;
    cout << "Insert an element by index:\nelement - "<<el<<", index - "<<index<< endl;
    if (!arr_1.Insert(el, index)) cout<<"There is no such index\n";
    else cout << arr_1;
    cout << endl;

    el = 225; index = 20;
    cout << "Insert an element by index:\nelement - " << el << ", index - " << index << endl;
    if (!arr_1.Insert(el, index)) cout << "There is no such index\n";
    else cout << arr_1;
    cout << endl;

    index = 1;
    cout << "Delete an element on the index: " << index<<endl;
    if (!arr_1.DelbyIndex(index)) cout << "There is no such index\n";
    else cout << arr_1;

    return 0;

}
