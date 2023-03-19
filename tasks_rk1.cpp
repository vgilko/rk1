#include "tasks_rk1.h"

#include <fstream> // заголовочный файл для работы с файлами
#include <iostream>
#include <sstream>

using namespace std;

WorkWithFile::WorkWithFile() { // конструктор по умолчанию
    dataOfFile = nullptr;
}

WorkWithFile::~WorkWithFile() { // деструктор
    if (dataOfFile != nullptr) {
        delete[] dataOfFile;
    }
}

void WorkWithFile::readFromFile(const char *fileName) {
    ifstream in(fileName, ios::in);

    if (in.is_open()) { // если файловый поток открылся корректно
        // определение размера файла
        in.seekg(0, in.end); // устанавливаем указатель в конец файла
        int fileSize = in.tellg(); // получаем значение текущей позиции
        in.seekg(0, in.beg); // возвращаем указатель в начало файла

        // выделение памяти под содержимое файла
        dataSize = fileSize;
        dataOfFile = new char[dataSize + 1];

        // чтение содержимого файла
        in.read(dataOfFile, fileSize);

        in.close(); // закрываем файловый поток
    }
}

void WorkWithFile::prepareTestFile(
        const char *fileName) { // не понял, для чего нужна эта функция, поэтому просто скопируем из файла с данными в новый файл
    ofstream out(fileName, ios::out);

    if (out) { // если файловый поток открылся корректно
        out.write(dataOfFile, dataSize);
        out.close();
    }
}

void WorkWithFile::countSymbolFrequency() {
    if (dataOfFile != nullptr) {
        char currentChar;

        for (int i = 0; i < dataSize; i++) { // итерируемся, пока не встретим нуль-терминал
            currentChar = dataOfFile[i];
            if (symbolsFrequency.find(currentChar) ==
                symbolsFrequency.end()) { // если не нашли. symbolsFrequency.find возвращает end(),
                // если такое значение не найдено
                symbolsFrequency[currentChar] = 1;
            } else {
                symbolsFrequency[currentChar]++; //  если такой символ нашли, то обращаемся к нему в словаре и инкрементируем его значение
            }
        }
    }

}


void WorkWithFile::writeStatInfoToFile(const char *outFile) {
    readFromFile("sourceFile_task1.txt"); // считываем данные из файла

    countSymbolFrequency(); // подсчитываем частотность для каждого символа

    ofstream out(outFile, ios::out); //  открываем файловый поток
    if (out) { // если файловый поток открылся нормально
        for (auto it = symbolsFrequency.begin();
             it != symbolsFrequency.end(); it++) { // итерируемся по словарю с частотностью символов
            out << it->first << "\t" << it->second << "\n"; // выводим данные по требуемому формату
        }
        out.close();
    }
}

char *convertDecToBin(int number) {
    bool isNegative = false; // флаг для отрицательных чисел
    if (number < 0) {
        isNegative = true;
        number = -number;
    } else if (number == 0) { // отдельно обрабатываем случай, когда входное значение равно нулю
        // просто создаем массив и помещаем в него 0. длина массива 2, т.к. в строке помимо нуля должен быть и нуль-терминал "\0"
        char *res = new char[2];
        res[0] = '0';
        return res;
    }

    int binaryArray[32]; // массив для хранения двоичной записи числа
    int i = 0;

    // перевод числа в двоичную систему
    while (number > 0) {
        binaryArray[i] = number % 2; //записываем в соответствующую позицию остаток от деления на 2
        number /= 2;
        i++;
    }

    if (isNegative) { // если исходное число меньше нуля
        for (int j = 0; j < i; j++) {
            binaryArray[j] = !binaryArray[j]; // инвертируем биты 0 => 1, 1 => 0
        }

        // получаем двоичное представление отрицательного числа
        int carry = 1;
        int k = 0;
        while (carry && k < 32) {
            int temp = binaryArray[k] + carry;
            binaryArray[k] = temp % 2;
            carry = temp / 2;
            k++;
        }
    }

    // записываем биты в обратном порядке
    char *reversedBinaryArray = new char[32];
    int indexReversedArray = 0;
    for (int j = i - 1; j >= 0; j--) {
        reversedBinaryArray[indexReversedArray] = binaryArray[j] == 1 ? '1' : '0';
        ++indexReversedArray;
    }

    return reversedBinaryArray;
}

char *convertBinToHex(const char *binNum) {
    string binary = string(binNum);

    int len = binary.length();
    string hex;
    int i = 0;

    // Если длина бинарного числа не кратна 4, дополняем его слева нулями до кратности 4.
    if (len % 4 != 0) {
        while (i < (4 - len % 4)) {
            binary = "0" + binary;
            i++;
        }
    }

    len = binary.length();
    i = 0;

    // Проходим по бинарному числу по 4 символа и конвертируем их в шестнадцатеричное представление.
    while (i < len) {
        string nibble = binary.substr(i,
                                      4); // берем подстроку 4 символа, максимальное значение 1111 в двоичной, что равняется 15 в десятичной
        int decimal = stoi(nibble, nullptr, 2); // конвертируем из двоичного числа в десятичное

        if (decimal <= 9) {
            hex += to_string(decimal);
        } else {
            hex += (char) (decimal - 10 +
                           'A'); // если число двузначное, то вычисляем его смещение относительно символа А.
            // в ascii символы расположены последовательно, что позволяет производить оперции с числовыми кодами символов
        }

        i += 4; // 4 т.к. взяли подстроку размера 4
    }

    char *result = new char[hex.size()]; // копируем в си строку, потому что string.c_str() возвращает константную строку,
    // что не подходит под тип возвращаемого значения функции
    for (int i = 0; i < hex.size(); ++i) {
        result[i] = hex[i];
    }

    return result;
}

void writeToFile(const char *fileName, int writeAppend, const char *hexNum, const char *binNum) {
    ofstream out_file(fileName); // открываем файловый поток на запись

    if (out_file) {
        out_file << binNum << "\t" << hexNum << endl;

        out_file.close();
    }
}

// Функция записи строки в файл
void writeToFile(const char *fileName, const char *strNum) {
    ofstream outFile(fileName); // открываем файл для записи

    if (outFile.is_open()) { // если файл успешно открыт
        outFile << strNum; // записываем строку в файл
        outFile.close(); // закрываем файл
        cout << "Результат записан в файл " << fileName << endl;
    } else { // если произошла ошибка при открытии файла
        cout << "Не удалось открыть файл " << fileName << " для записи" << endl;
    }
}

void buildTree(int height) {
    for (int layer = height; layer > 0; --layer) { /* суть в том, что нам надо выставить пробелы на каждом шаге как (текущая_высота_ёлки - 1)
 *    таким образом, строим ёлку с ее макушки и до основания
        */
        for (int i = 0; i < layer; ++i) { // выставляем нужное количество пробелов
            cout << " ";
        }

        for (int i = 0; i < (height - layer) * 2 + 1; i++) { // необходимо выставить (height - layer) * 2 + 1 звёздочек
            // выставляем звёздочки
            cout << "*";
        }

        // перенос строки после каждого слоя
        cout << endl;
    }
}

std::vector<std::pair<int, float>> averStr2DArray(float **arr, int colCount, int rowCount) {
    vector<pair<int, float>> result; // вектор, в который будем запиывать среднее значение элементов каждой строки

    for (int row = 0; row < rowCount; ++row) { // цикл по строкам
        float row_sum = 0; // переменная для подсчета суммы элементов строки

        for (int column = 0; column < colCount; ++column) { // цикл по столбцам
            row_sum += arr[row][column];
        }

        result.push_back(pair<int, float>(row, row_sum /
                                               (float) colCount)); // вставляем пару "строка"-"значение" в вектор. Используем эту функцию,потому что не создается доп копия
    }

    return result;
}

void randFill(float **arr, int colCount, int rowCount) {
    if (colCount == 0 || rowCount == 0) { // обрабатываем неверно введенные данные
        cout << "Columns count and rows count must be greater than zero" << endl;
        return; // return пустой, потому что функция имеет тип возвращаемого параметра - void
    }

    // обрабатываем случай, когда под массив не была выделена память. Как альтернатива - самим выделить память
    if (arr == nullptr) {
        cout << "Invalid array" << endl;
        return; // return пустой, потому что функция имеет тип возвращаемого параметра - void
    }

    // проходимся по массиву, инициализируем рандомными значениями от 1 до 10
    for (int row = 0; row < rowCount; ++row) { // цикл по строкам
        for (int column = 0; column < colCount; ++column) { // цикл по столбцам
            arr[row][column] = rand() % 10 + 1;
        }
    }
}

LinkedList::LinkedList() {
    Head = Tail = nullptr;
    nodesAmount = 0;
}

LinkedList::~LinkedList() {
    Node *iter = Head;
    while (iter) {
        Node *temp = iter;
        iter = iter->next;

        delete temp;
    }
}

void LinkedList::push_back(int nameNode) {
    if (!Head) {
        Tail = Head = new Node{nullptr, nullptr, ++nameNode};
    } else if (Head == Tail) {
        Tail = new Node{nullptr, Head, ++nameNode};
        Head->next = Tail;
    } else {
        Tail = new Node{nullptr, Tail, ++nameNode};
        Tail->prev->next = Tail;
    }

    ++nodesAmount;
}

void LinkedList::writeToFileFromHead() {
    ofstream out_file("fromHead.txt");

    if (out_file) {
        Node *iter = Head;
        while (iter) {
            out_file << iter->nameNode;

            if (iter->next) {
                out_file << ";";
            }

            iter = iter->next;
        }

        out_file.close();
    }
}

void LinkedList::writeToFileFromTail() {
    ofstream out_file("fromTail.txt");

    if (out_file) {
        Node *iter = Tail;

        while (iter) {
            out_file << iter->nameNode;

            if (iter->prev) {
                out_file << ";";
            }

            iter = iter->prev;
        }

        out_file.close();
    }
}

void LinkedList::insert(int nameNode, int position) {
    if (position >= 0 && position <= nodesAmount) {
        Node *newNode = new Node{nullptr, nullptr, nameNode};

        if (position == 0) { // добавление в начало списка
            newNode->next = Head;

            if (Head) {
                Head->prev = newNode;
            }

            Head = newNode;
            if (!Tail) {
                Tail = newNode;
            }
        } else if (position == nodesAmount) { // добавление в конец списка
            Tail->next = newNode;
            newNode->prev = Tail;
            Tail = newNode;
        } else { // добавление в середину списка
            int index = 0;
            Node *iter = Head;

            while (iter && index < position) {
                iter = iter->next;
                index++;
            }

            newNode->prev = iter->prev;
            newNode->next = iter;
            iter->prev->next = newNode;
            iter->prev = newNode;
        }

        ++nodesAmount;
    }
}

/*	desription	:	добавления отметки по выбранному предмету
    input		:	subjName - название предмета, mark -- оценка
    output		:	0 - оценка добавлена, 1 - нет такого предмета
    author		:
    date		:
*/
int StudentInfo::addMark(const string &subjName, int mark) {
    if (subjMark.find(subjName) != subjMark.end()) { // если такой предмет существует
        pair<list<int>, float> &pair = subjMark.at(subjName); // получаем ссылку на пару "список оценок" - "средняя оценка"

        pair.first.push_back(mark); // добавляем новую оценку в список оценок

        // пересчёт оценок
        int sum = 0;
        for (auto &val: pair.first) {
            sum += val;
        }

        pair.second = (float) sum / (float) pair.first.size();

        return 1;
    }

    return 0;
}

/*	desription	:	добавления отметки по выбранному предмету
    input		:	subjName - название предмета
    output		:	0 - предмет добавлен, 1 - такой предмет уже есть
    author		:
    date		:

*/
int StudentInfo::addSubj(const string &subjName) {
    if (subjMark.find(subjName) == subjMark.end()) { // если такого предмета НЕТ
        subjMark.insert({subjName, {{}, 0}}); // создаем пару "название предмета" - "пара "пустой список оценок" - "средняя оценка""

        return 1;
    }

    return 0;
}

/*	desription	:	добавления нового предмета
    input		:	subjName - название предмета
    output		:	среднее значение оценки
    author		:
    date		:
*/
float StudentInfo::getAverMark(const string &subjName) {
    if (subjMark.find(subjName) != subjMark.end()) { // если нашли такой предмет
        return subjMark.at(subjName).second; // возвращаем среднее значение оценок
    }

    return 0;
}

string StudentInfo::buildMessageString() { // отдельная функция, чтобы переиспользовать и в printInfoStudent и в writeAllInfoToFile
    // формирует сообщение по нашему шаблону
    stringstream sstream; // поток для составления строки

    sstream << '[' << get<0>(info) << "] [" << get<1>(info) << "] : " << get<2>(info) << "\n"; // получаем значения из тапла (фамилия, имя, зачётка)

    for (auto iter = subjMark.begin(); iter != subjMark.end(); ++iter) { // итерируемся по словарю
        sstream << "\t" << iter->first << " : "; // название предмета является ключом в словаре

        list<int> &marks = iter->second.first; // создаем переменную - ссылку на список оценок, для удобства
        for (auto marksIter = marks.begin(); marksIter != marks.end(); ++marksIter) { // пробегаемся по списку оценок
            sstream << *marksIter;

            if (next(marksIter) != marks.end()) { // условие, чтобы после последней оценки не было запятой
                sstream << ", ";
            } else {
                sstream << " -- "; // условие, чтобы после последней оценки поставить разделительные символы "--" (как в задании)
            }
        }

        sstream << iter->second.second << endl; // записываем среднюю оценку по предмету и перевод на новую строку
    }

    return sstream.str(); // возвращаем строку
}

/*	desription	:	вычисления средней оценки по предметам
    input		:	subjName - название предмета
    output		:	среднее значение оценки
    author		:
    date		:
*/
void StudentInfo::printInfoStudent() {
    cout << buildMessageString();
}


/*	desription	:	запись данных в файл формат файла
                        [Фамилия] [имя] : [номер билета]
                            [предмет 1]	:	[оценка 1], [оценка 2],... [оценка N] -- [среднее значение]
                            [предмет 2]	:	[оценка 1], [оценка 2],... [оценка N] -- [среднее значение]
    input		:	subjName - название предмета
    output		:	среднее значение оценки
    author		:
    date		:
*/
void StudentInfo::writeAllInfoToFile() {
    ofstream out_file("student_data.txt");

    if (out_file) {
        out_file << buildMessageString();

        out_file.close();
    }
}


