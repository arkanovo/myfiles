#include <iostream>	 //Библиотека с работой в консоли
#include <string>	//Библиотека для работы со строками	
#include <cstdlib>	//Библиотека функций, в данном коде используется только функция stoi() – преобразование из string в integer


using namespace std;

class XO
{
    char** ptr;
    int** numberarr;
    int sizeField;
    public:
        XO(int sizeField1);                                                     //Главный двигатель программы - создание двух двумерных массива ptr и numberarr
        ~XO();                                                                  //Освобождение выделенной памяти под массивы
        void printfield(void);                                                  //Рисовка поля крестики-нолики под заданный параметр sizeField
        int playingX(int x, int y);                                             //Крестики ходят
        int playingO(int x, int y);                                             //Нолики ходят
        int FindCross(int startX, int startY, int endX, int endY);              //Нахождение расположения крестиков, является под-функцией функции WinCross
        bool WinCross(void);                                                    //Нахождение выигрышной ситуации крестиков
        int FindNull(int startX, int startY, int endX, int endY);               //Нахождение расположения ноликов, является под-функцией функции WinNull
        bool WinNull(void);                                                     //Нахождение выигрышной ситуации ноликов
        void botMove(int sizeField);                                            //Алгоритм хода бота
};

bool is_number(const string& s)                                                 //Проверка на правильность ввода координаты
{
    string::const_iterator it = s.begin();
    while (it != s.end() && isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void XO::printfield(void)                                                   
{
    for (int i = 0, g = 0; i < (sizeField * 2 + 1); i++)
        {
        if (i % 2 == 0)
        {
            cout<< "+";
            for(int h = 0; h < sizeField; h++)
                cout<< "---+";
            cout<<endl;
        }
        else{
            cout <<"| ";
            for (int j = 0; j < sizeField; j++)
                cout << ptr[g][j] << " | ";

            cout << endl;
            g++;
        }
    }
}
void XO::botMove(int sizeField)                                             
{
    bool flag = true;
    int row, column;
    row = column = -1;

    for (int i = 0; i < sizeField; i++)
    {
        for (int j = 0; j < sizeField; j++)
        {
            if (numberarr[i][j] == 0)
            {
                ptr[i][j] = 'X';           //Присваиваем ячейке значение "X" и "1" в массивах и проверяем, выигрышная ли эта ячейка для человека.
                numberarr[i][j] = 1;
                if (XO::WinCross())
                {
                    row = i;
                    column = j;
                    flag = false;   // В интернете искал много способов, многие рекомендовали через goto останавливать вложенные циклы
                    break;          //Я придумал такой способ. Как только находим нужные нам координаты, прекращаем поиск по циклу.
                }
                else
                    numberarr[i][j] = 0;
                    ptr[i][j] = ' ';
            }
        }
    if(!flag) break;
    }
    flag = true;
    if ((row == -1) && (column == -1))          //Если не находим нужные координаты, присваиваем свободные первые попавшиеся
    {
        for (int i = 0; i < sizeField; i++)
        {
            for (int j = 0; j < sizeField; j++)
            {
                if (numberarr[i][j] == 0)
                {
                    row = i;
                    column = j;
                }
            }
        }
    }
    XO::playingO(row, column);
    XO::printfield();

}
int XO::playingX(int x, int y)                                              
{
    do
    {
        if(numberarr[x - 1][y - 1] == 0)
            ptr[x - 1][y - 1] = 'X';

        else
        {
            cout<< "\n\n\n ERROR!!!" <<endl;
            cout<< "This cell is occupied. Please select free cell." <<endl;
            cout<< "x, y: "; cin>> x >> y;
            if(numberarr[x - 1][y - 1] == 0)
                ptr[x - 1][y - 1] = 'X';
        }
    } while(numberarr[x - 1][y - 1] != 0);
    numberarr[x - 1][y - 1] = 1;
    return 0;
}
int XO::playingO(int x, int y)                                              
{
    ptr[x][y] = 'O';
    numberarr[x][y] = 2;
    return 0;
}
int XO::FindCross(int startX, int startY, int endX, int endY)               
{
    int k = 0;
    if(startX != endX)
    {
        for(int i = 0; i < endX; i++)
        {
            if(numberarr[endY][i] == 1)
                k++;
            else
                return k;
        }
    }
    else if(startY != endY)
    {
        for(int i = 0; i < endY; i++)
        {
            if(numberarr[i][endX] == 1)
                k++;
            else
                return k;
        }
    }
    else
    {
        if(startX == sizeField)
        {
            for(int i = 0, j = (startX - 1); i<startX; i++, j--)
            {
                if(numberarr[j][i] == 1)
                    k += 1;
                else
                    return k;
            }
        }
        if(startY == sizeField)
        {
            for(int i = 0; i<sizeField; i++)
            {
                if(numberarr[i][i] == 1)
                    k += 1;
                else
                    return k;
            }
        }
    }
    return k;
}

int XO::FindNull(int startX, int startY, int endX, int endY)                
{
    int k = 0;
    if(startX != endX)
    {
        for(int i = 0; i < endX; i++)
        {
            if(numberarr[endY][i] == 2)
                k++;
            else
                return k;
        }
    }
    else if(startY != endY)
    {
        for(int i = 0; i < endY; i++)
        {
            if(numberarr[i][endX] == 2)
                k++;
            else
                return k;
        }
    }
    else
    {
        if(startX == sizeField)
        {
            for(int i = 0, j = (startX - 1); i < startX; i++, j--)
            {
                if(numberarr[j][i] == 2)
                    k += 1;
                else
                    return k;
            }
        }
        if(startY == sizeField)
        {
            for(int i = 0; i < sizeField; i++)
            {
                if(numberarr[i][i] == 2)
                    k += 1;
                else
                    return k;
            }
        }
    }
    return k;
}
bool XO::WinCross(void)                                                     
{
    int rows = 0, columns = 0, diagonal1 = 0, diagonal2 = 0;
    for(int i = 0; i < sizeField; i++)
    {
        for(int j = 0; j < sizeField; j++)
        {
            rows = FindCross(j, i, sizeField, i);
            if(rows == sizeField)
                return true;
            columns = FindCross(i, j, i, sizeField);
            if(columns == sizeField)
                return true;
            diagonal1 = FindCross(sizeField, j, sizeField, j);
            if(diagonal1 == sizeField)
                return true;
            diagonal2 = FindCross(0, sizeField, 0, sizeField);
            if(diagonal2 == sizeField)
                return true;
        }
    }
    return false;
}
bool XO::WinNull(void)                                                      
{
    int rows, columns, diagonal1, diagonal2;
    for(int i = 0; i < sizeField; i++)
    {
        for(int j = 0; j < sizeField; j++)
        {
            rows = FindNull(j, i, sizeField, i);
            if(rows == sizeField)
                return true;
            columns = FindNull(i, j, i, sizeField);
            if(columns == sizeField)
                return true;
            diagonal1 = FindNull(sizeField, j, sizeField, j);
            if(diagonal1 == sizeField)
                return true;
            diagonal2 = FindNull(0, sizeField, 0, sizeField);
            if(diagonal2 == sizeField)
                return true;
        }
    }
    return false;
}
XO::XO(int sizeField1)                                                      
{
    sizeField = sizeField1;
    ptr = new char* [sizeField];
    numberarr = new int* [sizeField1];
    for (int h = 0; h < sizeField; h++)
    {
        ptr[h] = new char [sizeField];
        numberarr[h] = new int [sizeField1];
    }
    for (int row = 0; row < sizeField; row++)
    {
        for (int column = 0; column < sizeField; column++)
        {
            ptr[row][column] = ' ';
            numberarr[row][column] = 0;
        }
    }
}
XO::~XO()                                                                   
{
    for(int h = 0; h < sizeField; h++)
    {
        delete [] ptr[h];
        delete [] numberarr[h];
    }
}
int main()                                                                  //Основная функция
{
    int sIzefield, int_x, int_y;
    string x,y;
    bool checkX, checkO;
    char answer;
    char f_player[15];
    cout<< "Please, print in the name of the player: "; cin>>f_player;
    cout<<endl;
    do
    {
        cout<< " New Game!" <<endl;
        cout<< "Enter the number of crosses: "; cin>>sIzefield;
        if(sIzefield < 3)
        {
            cout<< "\n Error! Wrong size of field, the field is default 3x3" <<endl;
            sIzefield = 3;
        }
        XO game(sIzefield);
        game.printfield();
        for(int step = 0; step < sIzefield*sIzefield; step++)
        {
            if((step % 2) == 0)
            {
                cout<< " " <<f_player<< " move..." <<endl;
                cout<< " Enter the row and the column: "; cin>> x >> y;
                if(is_number(x) && is_number(y))
                {
                    int_x = stoi(x);
                    int_y = stoi(y);
                }
                else
                {
                    while ((!(is_number(x))) || (!(is_number(y))))
                    {
                        TestValue:
                        cout<< "\n Error in coordinates! Correct values in the interval (1,"<< sIzefield << ").";
                        cin.clear();
                        cout<< "\n Enter the correct values: "; cin>> x >> y;

                        int_x = stoi(x);
                        int_y = stoi(y);

                        if ((int_x > sIzefield) || (int_y > sIzefield))
                        {
                            goto TestValue;
                        }
                        else break;
                    }
                }

                game.playingX(int_x, int_y);
                game.printfield();
                checkX = game.WinCross();
                if(checkX == true)
                {
                    cout<<f_player<<" WIN!!!" <<endl;
                    break;
                }
            }
            else
            {
                cout<< " " << "Bot" << " move..." <<endl;
                game.botMove(sIzefield);
                checkO = game.WinNull();
                if (checkO)
                {
                    cout<<" " << "Bot" << " WIN!!!" <<endl;
                    break;
                }
            }
            if (step == (sIzefield*sIzefield - 1))
                if ((!checkX) && (!checkO))
                    cout<< "Draw!" <<endl;
        }
        cout<< "\n\n\n Game over!" <<endl;
        cout<< "Do you want to play again? (input 'y' or anything to exit) "; cin>> answer;
    } while(answer == 'y');
    return 0;
}
