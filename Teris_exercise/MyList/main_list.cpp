#include<string>
#include<iostream>
#include<iterator>
#include<vector>
#include<list>
#include"my_list.h"
using namespace std;
int main() {
    // initialize with a initializer_list
    my_list<int> m = { 1,5,8 };
    // push back and front some values
    m.push_back(1);
    m.push_back(2);
    m.push_front(100);

    // test the normal loop using iterator
    cout << "for loop using const_iterator:" << endl;
    for (auto it = m.begin(); it != m.end(); it++)
        cout << *it << " ";
    cout << endl;

    // test the for-each loop can work 
    cout << "for-each loop result:" << endl;
    for (int a : m)
        cout << a << " ";
    cout << endl;

    // test modifying values in the list
    cout << "modify the first value:" << endl;
    my_list<int>::iterator it = m.begin();
    *it = -3;
    copy(m.begin(), m.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    // test erasing values in the list
    cout << "delete the first value through post-inc (iter++):" << endl;
    m.erase(m.begin()++);
    copy(m.begin(), m.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    // test erasing values in the list
    cout << "delete the second value through pre-inc (++iter):" << endl;
    m.erase(++m.begin());
    copy(m.begin(), m.end(), ostream_iterator<int>(cout, ","));
    cout << endl;
    // test copying values to a vector
    cout << "copy values to a vector, the content in the vector:" << endl;
    vector<int> v(m.size(), 0);
    copy(m.begin(), m.end(), v.begin());
    copy(v.begin(), v.end(), ostream_iterator<int>(cout, "--"));
    cout << endl;

    // misc test
    cout << "list size: " << m.size() << endl;
    cout << "back value: " << m.back() << endl;
    cout << "front value: " << m.front() << endl;
    cout << "is empty: " << m.empty() << endl;

    // test copy constructor
    my_list<int> m2(m);
    cout << "copy constructor testing. element in m2:" << endl;
    copy(m2.begin(), m2.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    // test copy assignment
    my_list<int> m3;
    m3 = m2;
    cout << "copy assignment testing. element in m3:" << endl;
    copy(m3.begin(), m3.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    // test clearing a list
    m.clear();
    cout << "after deleting m, eles in m2:" << endl;
    copy(m2.begin(), m2.end(), ostream_iterator<int>(cout, ","));
    cout << endl;

    // test == operator
    cout << "initially, m2==m3: " << (m2 == m3) << endl;
    m2.front() += 1;
    cout << "after modifying one ele in m2, m2==m3 is: " << (m2 == m3) << endl;
    m2.pop_front();
    cout << "after deleting on ele in m2, m2==m3 is: " << (m2 == m3) << endl;

    cout << "after clearing all values, the size: " << m.size() << endl;
    cout << "after clearing all values, is empty: " << m.empty() << endl;

    // before exiting main, the ~my_list<int> will be executed.
}