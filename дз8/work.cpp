
#include <windows.h>

//в задании было назвать файлы с пробелом
//но задание старое и было задано до
//того как мы научились работать с файлами с пробелом в имени
#include <fstream>
#include <iostream>

void fill(std::string file_name, std::string &container)
{
    static std::ifstream cin_from;
    static std::string memory_string;
    cin_from.open(file_name);
    //старое дз
    while (!cin_from.eof())
    {
        getline(cin_from, memory_string);
        container += memory_string + '\n';
    }
    cin_from.close();
}

void sort_and_print(std::string names)
{
    static int new_biggest_1;
    static int new_biggest_2 = 1073741824;
    static int copy = -1;
    static bool start = true;
    while (start)
    {
        copy = new_biggest_1;
        new_biggest_1 = 0;
        for (int this_element = 0, this_name_value = 0; names[this_element]; ++this_element)
        {
            if (names[this_element] == '\n')
            {

                if ((this_name_value > new_biggest_1) && (this_name_value < new_biggest_2))
                {
                    new_biggest_1 = this_name_value;
                }
                this_name_value = 0;
            }
            else
            {
                this_name_value += names[this_element];
            }
        }
        for (int this_element = 0, this_name_value = 0; names[this_element]; ++this_element)
        {
            if (names[this_element] == '\n')
            {
                if (this_name_value == new_biggest_1)
                {
                    for (int this_element_2 = this_element - 1; names[this_element_2] != '\n' && this_element_2 != -1; --this_element_2)
                    {
                        if (names[this_element_2 - 1] == '\n' || !this_element_2)
                        {
                            for (int this_element = this_element_2; names[this_element] != '\n' && names[this_element]; ++this_element)
                            {
                                std::cout << names[this_element];
                            }
                            std::cout << '\n';
                        }
                    }
                }
                this_name_value = 0;
            }
            else
            {
                this_name_value += names[this_element];
            }
        }
        if (copy == new_biggest_1)
        {
            start = false;
        }
        new_biggest_2 = new_biggest_1;
        new_biggest_1 = 0;
    }
    new_biggest_2 = 1073741824;
    start = true;
}

void add_from_file_to_file(std::string file_name_1, std::string file_name_2)
{
    static std::ofstream cout_in;

    static std::ifstream cin_from_1;
    static std::string memory_string_1;

    static std::ifstream cin_from_2;
    static std::string memory_string_2;

    bool work;

    cin_from_1.open(file_name_1);
    while (!cin_from_1.eof())
    {
        //Sleep(1000);

        work = true;

        getline(cin_from_1, memory_string_1);

        cin_from_2.open(file_name_2);
        while (!cin_from_2.eof())
        {
            getline(cin_from_2, memory_string_2);
            if (memory_string_1 == memory_string_2)
            {
                work = false;
            }
        }
        cin_from_2.close();

        if (work)
        {
            cout_in.open(file_name_2, std::ios::app);
            cout_in << memory_string_1 << '\n';
            cout_in.close();
        }
    }
    cin_from_1.close();
    cout_in.close();
}

int main()
{
    std::string mat_friends;
    std::string pat_friends;
    //контейнеры

    fill("mat.dat", mat_friends);
    fill("pat.dat", pat_friends);
    //заполнение контейнеров

    sort_and_print(mat_friends);
    std::cout << "#############################################\n"; //разделитель
    sort_and_print(pat_friends);
    //проверка сортировки

    add_from_file_to_file("mat.dat", "matnpat.dat");
    add_from_file_to_file("pat.dat", "matnpat.dat");
}