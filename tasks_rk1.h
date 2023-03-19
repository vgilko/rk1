#include <map> // заголовочный файл с реализацией словаря
#include <vector>
#include <string>
#include <list>

using namespace std;


class WorkWithFile {
private :
    char *dataOfFile;
    int dataSize;

    map<char, int> symbolsFrequency;  // словать для подсчета частотности символов. ключ символ, значение - его частотность

    void readFromFile(const char *fileName);    //функция чтения из файла
    void prepareTestFile(const char *fileName);    //функция для создания тестового файла

    void countSymbolFrequency();

public :
    WorkWithFile();

    ~WorkWithFile();

    void writeStatInfoToFile(const char *outFile);
};

char *convertDecToBin(int number);

char *convertBinToHex(const char *binNum);

void writeToFile(const char* fileName, int writeAppend, const char* hexNum, const char* binNum);

void writeToFile(const char *fileName, const char *strNum);

void buildTree(int height);

std::vector<std::pair<int/*номер строки*/, float /*среднее значение*/>>
averStr2DArray(float **ar, int colCount, int rowCount);

void randFill(float **arr, int colCount, int rowCount);

struct Node {
    Node *next;
    Node *prev;
    int nameNode;
    static int countNodes;
};

class LinkedList {
private :
    Node *Head;
    Node *Tail;

    int nodesAmount;
public :
    LinkedList();

    ~LinkedList();

    void push_back(int nameNode);

    void insert(int nameNode, int position);

    void writeToFileFromTail();

    void writeToFileFromHead();
};

class StudentInfo {
private :
    std::tuple<string /*фамилия*/, string /*имя*/, char * /*№ студ билета*/> info;
    std::map<string/*название предмета*/, std::pair<std::list<int> /*список оценок*/, float /*средняя оценка*/>> subjMark;

    string buildMessageString();

public :
    StudentInfo(string fullName, string name, char *studentId) {
        info = {fullName, name, studentId};
    }

    /*	desription	:	добавления отметки по выбранному предмету
        input		:	subjName - название предмета, mark -- оценка
        output		:	0 - оценка добавлена, 1 - нет такого предмета
        author		:
        date		:
    */
    int addMark(const string &subjName, int mark);

    /*	desription	:	добавления отметки по выбранному предмету
        input		:	subjName - название предмета
        output		:	0 - предмет добавлен, 1 - такой предмет уже есть
        author		:
        date		:

    */
    int addSubj(const string &subjName);

    /*	desription	:	добавления нового предмета
        input		:	subjName - название предмета
        output		:	среднее значение оценки
        author		:
        date		:
    */
    float getAverMark(const string &subjName);

    /*	desription	:	вычисления средней оценки по предметам
        input		:	subjName - название предмета
        output		:	среднее значение оценки
        author		:
        date		:
    */
    void printInfoStudent();

    /*	desription	:	запись данных в файл формат файла
                            [Фамилия] [имя] : [номер билета]
                                [предмет 1]	:	[оценка 1], [оценка 2],... [оценка N] -- [среднее значение]
                                [предмет 2]	:	[оценка 1], [оценка 2],... [оценка N] -- [среднее значение]
        input		:	subjName - название предмета
        output		:	среднее значение оценки
        author		:
        date		:
    */
    void writeAllInfoToFile();
};
