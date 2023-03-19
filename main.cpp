#include <iostream>
#include "tasks_rk1.h"

using namespace std;

void task_1() {
    WorkWithFile workWithFile = WorkWithFile();

    workWithFile.writeStatInfoToFile("result_sourceFile_task1.txt");
}

void task_2() {
    char *binary = convertDecToBin(-454432);

    writeToFile("result_task2", binary);
}

void task_3() {
    char *binary = convertDecToBin(123421321);

    char *toHex = convertBinToHex(binary);

    writeToFile("binToHex.txt", 0, toHex, binary);
}

void task_4() {
    buildTree(10);
}

void task_5() {
    int columnAmount = 2;
    int rowAmount = 2;

    auto **arr = new float *[rowAmount];
    for (int i = 0; i < rowAmount; i++) {
        arr[i] = new float[columnAmount];
    }

    randFill(arr, columnAmount, rowAmount);

    for (int i = 0; i < rowAmount; ++i) {
        for (int j = 0; j < columnAmount; ++j) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    auto result = averStr2DArray(arr, columnAmount, rowAmount);

    for (auto &value: result) {
        cout << value.first << " = " << value.second << endl;
    }
}

void task_6() {
    LinkedList list = LinkedList();

    list.push_back(0);
    list.push_back(1);

    list.writeToFileFromHead();
    list.writeToFileFromTail();
}

void task_7() {
    LinkedList list = LinkedList();

    list.insert(0, 0);
    list.insert(1, 1);
    list.insert(1, 2);

    list.writeToFileFromHead();
    list.writeToFileFromTail();
}

void task_8() {
    char id[] = "23421d";
    StudentInfo info = StudentInfo("FullName", "Name", id);

    cout << info.addSubj("Russian") << endl;
    cout << info.addSubj("Russian") << endl;
    cout << info.addMark("Russian", 4) << endl;
    cout << info.addMark("Russian", 3) << endl;
    cout << info.addMark("Russian", 4) << endl;

    cout << info.addSubj("Math") << endl;
    cout << info.addMark("Math", 5) << endl;

    cout << info.getAverMark("Russian") << endl;
    cout << info.getAverMark("Math") << endl;
    cout << info.getAverMark("Uknown") << endl;

    info.printInfoStudent();
    info.writeAllInfoToFile();
}

int main() {
    task_2();
}
