#include <iostream>
#define maxSize 20
using namespace std;

int insertElem(int sqList[], int &length, int p, int e)
{
    if (p < 0 || p > length || length == maxSize)
    {
        return 0;
    }
    for (int i = length - 1; i >= p; i--)
    {
        sqList[i + 1] = sqList[i];
    }
    sqList[p] = e;
    length++;
    return 1;
}
int deleteElem(int sqList[], int &length, int p, int &e)
{
    if (p < 0 || p > length - 1)
    {
        return 0;
    }
    e = sqList[p];
    for (int i = p; i < length - 1; i++)
    {
        sqList[i] = sqList[i + 1];
    }
    length--;
    return 1;
}

int main()
{
    int sqList[maxSize] = {33, 34, 35, 36, 37, 38, 39, 40};
    int length = 8;
    insertElem(sqList, length, 3, 9);
    for (int i = 0; i <= length - 1; i++)
    {
        cout << sqList[i] << "\t";
    }
    cout << "length" <<length <<endl;
    cout << endl;
    int e = 0;
    deleteElem(sqList, length, 3, e);
    for (int i = 0; i <= length - 1; i++)
    {
        cout << sqList[i] << "\t";
    }
    cout << endl;
    cout << e << endl;
    getchar();
    return 0;
}