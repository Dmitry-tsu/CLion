#include<iostream>
#include "Array.h"
template <typename T>

double calculateAvg(Array<T> arr)
{
    double avg = 0;
    if (arr.Size() == 0) return 0;

    for (int i = 0; i < arr.Size(); i++)
        avg += arr[i];
    avg /= arr.Size();
    return avg;
}
int main()
{
    using std::cout;
    using std::cin;
    using std::endl;

    Array<int> arr_1(10, 0);
    Array<int> arr_2(10, 0);
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
    cout << "Swap contents of arrays:\narr_1: " << arr_1 << "arr_2: " << arr_2;
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

    index = 2;
    cout << "Delete an element on the index: " << index<<endl;
    if (!arr_1.DeleteByIndex(index)) cout << "There is no such index\n";
    else cout << arr_1;
    cout << endl;

    el = 125;
    cout << "Delete an element by value: " << el << endl;
    if (!arr_1.DeleteElement(el)) cout << "There is no such element\n";
    else cout << arr_1;
    cout << endl;


    Array<int> arr_3(5);
    arr_3[0] = 1; arr_3[1] = 2; arr_3[2] = 3; arr_3[3] = 4; arr_3[4] = 5;
    cout << arr_3;
    el = 3;
    cout << "Deleting array: "<<el<<endl;
    arr_3.DeleteAllElements(el);
    cout << arr_3;
    cout << endl;


    cout << "Operators == and !=: \n";
    Array<int> arr_4(10), arr_5(10), arr_6(10), arr_7(10);
    arr_5.RandArray(-10, 10);
    arr_6 = arr_5;
    cout << "Array 1: " << arr_5 << "Array 2: " << arr_6 << "Array 3: " << arr_7 << "Array 4: " << arr_4;
    if (arr_5 == arr_6) cout << "Array 1 == Array 2\n";
    else  cout << "Array 1 != Array 2\n";
    if (arr_5 != arr_6) cout << "Array 1 != Array 2\n";
    else  cout << "Array 1 == Array 2\n";
    if (arr_5 == arr_7) cout << "Array 1 == Array 3\n";
    else  cout << "Array 1 != Array 2\n";
    if (arr_5 == arr_4) cout << "Array 1 == Array 4\n";
    else  cout << "Array 1 != Array 4\n";
    cout << endl;

    Array<int> arr_8(20, 0);
    arr_8.RandArray(-10, 10);
    cout << arr_8 << "Search for the maximum/minimum element: "<<endl;
    int i_max = arr_8.IMax();
    if (i_max==-1) cout << "The array is empty" << endl;
    else cout << "Maximum element: " << arr_8[i_max] << endl;
    int i_min = arr_8.IMin();
    if (i_min==-1) cout << "The array is empty" << endl;
    else cout << "Minimum element: " << arr_8[i_min] << endl;
    cout << endl;


    cout << "Operators + and +=: \n";
    cout<< arr_8<<"+ 10 + 15: " << arr_8 + 10 + 15 << endl;
    cout<<arr_8<<"+= 25: ";
    arr_8 += 25;
    cout<<arr_8;
    cout << endl;

    cout << arr_5;
    Array<int>::Iterator it = arr_5.begin();
    cout << "Iterator on begin: " << *it<<endl;
    it = arr_5.end();
    cout << "Iterator on end: " << *(--it) << endl;
    cout << endl;

    it = arr_5.begin();
    index = 10;
    for (int c = 0; c != index; it++, c++);
    el = 125;
    cout << arr_5<<"Insertion element "<<el<<" before the iterator at the position: "<<index<<endl;
    if(!arr_5.Insert(el, it))cout << "There is no such index\n";
    else cout << arr_5<<*it;
    cout << endl;

    cout<<"Deleting an element or a range of elements using iterators:\n" << arr_5;
    index = 3;
    Array<int>::Iterator gap1 = arr_5.begin();
    for (int c = 0; c != index; gap1++, c++);
    index = 6;
    Array<int>::Iterator gap2 = arr_5.begin();
    for (int c = 0; c != index; gap2++, c++);
    arr_5.Remove(gap1, gap2);
    cout << arr_5;
    arr_5.Remove(gap1);
    cout << arr_5;
    cout << endl;

    Array <char> arrsh(5, 'a');
    cout << arrsh;
    return 0;
}
