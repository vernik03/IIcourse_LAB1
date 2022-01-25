#include <iostream>
#include <windows.h>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>


using namespace std;

struct level_of_character {
    
    unsigned int character_id;
    unsigned int level;
    //1 - main
    //2 - secondary
    //3 - episodic

};

struct character_info
{
    unsigned int id;
    char name[256];
  
};

struct book_info
{
    unsigned int id;
    char title[256]; 
    char description[1024];
    int pages;
    char authors_name[50];
    char authors_surname[50];
    char date[11];
    vector<level_of_character> characters;
    
    
};

void add_character(character_info character)
{
   
    ifstream in;
    int id_in_int_2=0;
    in.open("../character.txt");
    bool flag = false;
    char id_in[20];
    char name_in[256];
    in.getline(id_in, 20);
    int id_in_int = atoi(id_in);
    in.getline(name_in, 256);
    while (!in.eof())
    {
        
        if (name_in == character.name)
        {
            flag = true;
           

        }
        id_in_int_2 = id_in_int;
        in.getline(id_in, 20);
        id_in_int = atoi(id_in);
        in.getline(name_in, 256);
      
    }
    in.close();
    ofstream out;
  
    if (!flag)
    {
        
        id_in_int_2++;
        character.id = id_in_int_2;
       
        
        ofstream out;
        out.open("../character.txt", std::ios::app);
       
            out << character.id << endl;
            out << character.name << endl;
            out.close();
      
    }

  
}


int character_id(character_info character)
{
    ifstream in;
    in.open("../character.txt");
   
    char id_in[20];
    char name_in[256];
    in.getline(id_in, 20);
    int id_in_int = atoi(id_in);
    in.getline(name_in, 256);
  
    while (!in.eof())
    {
        
        if (string(name_in) == string(character.name))
        {
           
            in.close();
           
            return id_in_int;
        }
       
        in.getline(id_in, 20);
        id_in_int = atoi(id_in);
        in.getline(name_in, 256);
    }
}

void add_book()
{
    unsigned int id = 0;
    ifstream book_temp;    
    book_temp.open("../book.txt");
    char chars[1024];
    book_temp.getline(chars, 1024);
    
    while (!book_temp.eof())
    {
        if (chars[0] == '@')
        {
            id++;
        }
        book_temp.getline(chars, 1024);
    }
    book_temp.close();
   
    book_info elem;
    ofstream out;
    out.open("../book.txt", std::ios::app);
   
    while (true)
    {
        elem.id = id;
        cout << "Enter book title: ";
        gets_s(elem.title);
        gets_s(elem.title);
        cout << "Enter author`s name: ";
        
        gets_s(elem.authors_name);
        cout << "Enter author`s surname: ";
        
        gets_s(elem.authors_surname);
        cout << "Enter date of publication: ";
            
        cin >> elem.date; 
        regex rx(R"(\d\d(.)\d\d(.)\d\d\d\d)");
       while (!regex_match(elem.date, rx))
        {
            cout << "Invalod date input. Try again: ";
            cin >> elem.date;
            
        } 
        cout << "Enter book description: ";
        gets_s(elem.description);
        gets_s(elem.description);
        cout << "Enter number of pages: ";
        cin >> elem.pages;
        while (!int(elem.pages))
        {
            cout << "Invalod number of pages input. Try again: ";
            cin >> elem.pages;
           
        } 


        character_info character;
        cout << "Enter name of main character: ";
        gets_s(character.name);
        gets_s(character.name);

        add_character(character);
        level_of_character new_ch;
        new_ch.character_id = character_id(character);
        new_ch.level = 1;
        vector<level_of_character> characters;
        characters.push_back(new_ch);

        char add_flag;
        cout << "Add more characters?" << endl;
        cout << "'Y' or 'N'" << endl;
        cin >> add_flag;
       
        while (add_flag == 'Y' || add_flag == 'y')
        {
            
          
            character_info character;
            cout << "Enter name of character: ";
            gets_s(character.name);
            gets_s(character.name);
            add_character(character);
            level_of_character new_ch;
            new_ch.character_id = character_id(character);
            cout << character_id(character) << endl;
            cout << new_ch.character_id<<endl;
            cout << "Enter the level of character in this book: ";
            cin >> new_ch.level;
            characters.push_back(new_ch);
            cout << "Add more characters?" << endl;
            cout << "'Y' or 'N'" << endl;
            cin >> add_flag;
        } 
        elem.characters = characters;
        out << elem.id << endl;
        out << elem.title << endl;
        out << elem.authors_name << endl;
        out << elem.authors_surname << endl;
        out << elem.description << endl;
        out << elem.date << endl;
        out << elem.pages << endl;
        for (int i = 0; i < elem.characters.size(); i++)
        {
            out << elem.characters[i].character_id << endl;
            out << elem.characters[i].level << endl;
        }
        out << "@" << endl;;
        out.close();
        break;
        
    }
    
}


void write_book(book_info input_book) {
    unsigned int id = 0;
    ifstream book_temp;
    book_temp.open("../book.txt");
    char chars[1024];
    book_temp.getline(chars, 1024);

    while (!book_temp.eof())
    {
        if (chars[0] == '@')
        {
            id++;
        }
        book_temp.getline(chars, 1024);
    }
    book_temp.close();

    book_info elem = input_book;
    ofstream out;
    out.open("../book.txt", std::ios::app);
      
        out << elem.id << endl;
        out << elem.title << endl;
        out << elem.authors_name << endl;
        out << elem.authors_surname << endl;
        out << elem.description << endl;
        out << elem.date << endl;
        out << elem.pages << endl;
        for (int i = 0; i < elem.characters.size(); i++)
        {
            out << elem.characters[i].character_id << endl;
            out << elem.characters[i].level << endl;
        }
        out << "@" << endl;;
        out.close();

}


bool book_by_character_for_delete(int character_id) {

    bool flag = 0;
    vector<book_info> books;
    ifstream in;
    in.open("../book.txt");
    char chars[50];
    in.getline(chars, 50);
    while (!in.eof())
    {
        book_info elem;


        elem.id = atoi(chars);
        in.getline(elem.title, 256);
        in.getline(elem.authors_name, 50);
        in.getline(elem.authors_surname, 50);
        in.getline(elem.description, 1024);
        in.getline(elem.date, 11);
        in.getline(chars, 50);
        elem.pages = atoi(chars);
        char check[50];
        level_of_character temp;
        in.getline(chars, 50);
        temp.character_id = atoi(chars);
        in.getline(chars, 50);
        temp.level = atoi(chars);
        elem.characters.push_back(temp);
        in.getline(chars, 50);

        while (chars[0] != '@')
        {


            temp.character_id = atoi(chars);

            in.getline(chars, 50);
            temp.level = atoi(chars);
            elem.characters.push_back(temp);
            in.getline(chars, 50);
        }


        for (int i = 0; i < elem.characters.size(); i++)
        {
            if (elem.characters[i].character_id == character_id)
            {
                books.push_back(elem);
                flag = 1;
                break;
            }

        }

        in.getline(chars, 50);
        if (chars[0] == NULL)
        {
            break;
        }
    }
    in.close();
    if (flag)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void delete_character() {

    ifstream in;
    in.open("../character.txt");
    char chars[256];
    vector<character_info> characters;
    while (!in.eof()) {
        character_info elem;
        in.getline(chars, 256);
        elem.id = atoi(chars);
        in.getline(elem.name, 256);




        if (!book_by_character_for_delete(elem.id))
        {
            characters.push_back(elem);
        }




    }
    in.close();
    std::ofstream ofs;
    ofs.open("../character.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    for (int i = 0; i < characters.size(); i++)
    {
        add_character(characters[i]);
    }




}

bool delete_book(char input[256]) {

    vector<book_info> books;
    bool flag=0;
    ifstream in;
    in.open("../book.txt");
    char chars[50];
    in.getline(chars, 50);
    while (!in.eof())
    {
        book_info elem;


        elem.id = atoi(chars);
        in.getline(elem.title, 256);
        in.getline(elem.authors_name, 50);
        in.getline(elem.authors_surname, 50);
        in.getline(elem.description, 1024);
        in.getline(elem.date, 11);
        in.getline(chars, 50);
        elem.pages = atoi(chars);
        char check[50];
        level_of_character temp;
        in.getline(chars, 50);
        temp.character_id = atoi(chars);
        in.getline(chars, 50);
        temp.level = atoi(chars);
        elem.characters.push_back(temp);
        in.getline(chars, 50);

        while (chars[0] != '@')
        {


            temp.character_id = atoi(chars);

            in.getline(chars, 50);
            temp.level = atoi(chars);
            elem.characters.push_back(temp);
            in.getline(chars, 50);
        }


        if (!( string(input).find(string(elem.title)) != string::npos) || !(string(elem.title).find(string(input)) != string::npos))
        {
            books.push_back(elem);
        }
        if (string(input).find(string(elem.title)) != string::npos || string(elem.title).find(string(input)) != string::npos)
        {
            flag = 1;
        }
        
        in.getline(chars, 50);
        if (chars[0] == NULL)
        {
            break;
        }
    }
    in.close();
    std::ofstream ofs;
    ofs.open("../book.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    for (int i = 0; i < books.size(); i++)
    {
        write_book(books[i]);
    }
    if (flag)
    {
        delete_character();
        return 0;
    }
    else
    {
        return 1;
    }
}




bool update_book(char book_title[256], int item, char input[1024]) {

    vector<book_info> books;
    bool flag = 0;
    ifstream in;
    in.open("../book.txt");
    char chars[50];
    in.getline(chars, 50);
    while (!in.eof())
    {
        book_info elem;


        elem.id = atoi(chars);
        in.getline(elem.title, 256);
        in.getline(elem.authors_name, 50);
        in.getline(elem.authors_surname, 50);
        in.getline(elem.description, 1024);
        in.getline(elem.date, 11);
        in.getline(chars, 50);
        elem.pages = atoi(chars);
        char check[50];
        level_of_character temp;
        in.getline(chars, 50);
        temp.character_id = atoi(chars);
        in.getline(chars, 50);
        temp.level = atoi(chars);
        elem.characters.push_back(temp);
        in.getline(chars, 50);

        while (chars[0] != '@')
        {


            temp.character_id = atoi(chars);

            in.getline(chars, 50);
            temp.level = atoi(chars);
            elem.characters.push_back(temp);
            in.getline(chars, 50);
        }


        if (!(string(book_title).find(string(elem.title)) != string::npos) || !(string(elem.title).find(string(book_title)) != string::npos))
        {
            books.push_back(elem);
        }
        if (string(book_title).find(string(elem.title)) != string::npos || string(elem.title).find(string(book_title)) != string::npos)
        {
            switch (item)
            {
            case 0:
                cout << "Autor`s name "<<string(elem.authors_name)<<" changed to ";
                for (int i = 0; i < sizeof(elem.authors_name); i++)
                {
                    elem.authors_name[i] = input[i];
                }
                cout << string(elem.authors_name) << endl;
                break;
            case 1:
                cout << "Autor`s surname " << string(elem.authors_surname) << " changed to ";
                for (int i = 0; i < sizeof(elem.authors_surname); i++)
                {
                    elem.authors_surname[i] = input[i];
                }
                cout << string(elem.authors_surname) << endl;
                break;
            case 2:
                cout << "Book description changed to ";
                for (int i = 0; i < sizeof(elem.description); i++)
                {
                    elem.description[i] = input[i];
                }
                cout << string(elem.description) << endl;
                break;
            case 3:
                cout << "Number of pages changed from "<< elem.pages;                
                    elem.pages = atoi(input);                
                cout <<" to " <<elem.pages << endl;
                break;
            case 4:
                cout << "Date of publiching changed from "<< string(elem.date);
                for (int i = 0; i < sizeof(elem.date); i++)
                {
                    elem.date[i] = input[i];
                }
                cout <<" to "<< string(elem.date) << endl;
                break;
            default:
                break;
            }



            books.push_back(elem);
            flag = 1;
        }

        in.getline(chars, 50);
        if (chars[0] == NULL)
        {
            break;
        }
    }
    in.close();
    std::ofstream ofs;
    ofs.open("../book.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    for (int i = 0; i < books.size(); i++)
    {
        write_book(books[i]);
    }
    if (flag)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}




void read_all_books()
{

    ifstream in;
    in.open("../book.txt");
    char chars[50];
    in.getline(chars, 50);
    while (!in.eof())
    {
        book_info elem;


        elem.id = atoi(chars);
        in.getline(elem.title, 256);
        in.getline(elem.authors_name, 50);
        in.getline(elem.authors_surname, 50);
        in.getline(elem.description, 1024);
        in.getline(elem.date, 11);
        in.getline(chars, 50);
        elem.pages = atoi(chars);
        char check[50];
        level_of_character temp;
        in.getline(chars, 50);
        temp.character_id = atoi(chars);
        in.getline(chars, 50);
        temp.level = atoi(chars);
        elem.characters.push_back(temp);
        in.getline(chars, 50);

        while (chars[0] != '@')
        {


            temp.character_id = atoi(chars);

            in.getline(chars, 50);
            temp.level = atoi(chars);
            elem.characters.push_back(temp);
            in.getline(chars, 50);
        }

        cout << elem.title << "    " << elem.authors_name << " " << elem.authors_surname << "    " << elem.date << "    " << elem.pages << " pages" << endl;
        cout << endl;
        cout << elem.description << endl;
        cout << endl;


        for (int i = 0; i < elem.characters.size(); i++)
        {
            ifstream in_ch;
            in_ch.open("../character.txt");
            char id_in[20];
            char name_in[256];

            while (!in_ch.eof())
            {
                in_ch.getline(id_in, 20);
                int id_in_int = atoi(id_in);
                in_ch.getline(name_in, 256);

                if (id_in_int == elem.characters[i].character_id)
                {
                    cout << name_in << endl;


                }

            }
            in_ch.close();

        }

        cout << endl;

        in.getline(chars, 50);
        if (chars[0] == NULL)
        {
            break;
        }
    }
    in.close();


}

bool comp(pair <int, int> a, pair <int, int> b) {
    return a.second < b.second;
}


void book_by_character(int character_id) {

    vector<book_info> books;
    ifstream in;
    in.open("../book.txt");
    char chars[50];
    in.getline(chars, 50);
    while (!in.eof())
    {
        book_info elem;


        elem.id = atoi(chars);
        in.getline(elem.title, 256);
        in.getline(elem.authors_name, 50);
        in.getline(elem.authors_surname, 50);
        in.getline(elem.description, 1024);
        in.getline(elem.date, 11);
        in.getline(chars, 50);
        elem.pages = atoi(chars);
        char check[50];
        level_of_character temp;
        in.getline(chars, 50);
        temp.character_id = atoi(chars);
        in.getline(chars, 50);
        temp.level = atoi(chars);
        elem.characters.push_back(temp);
        in.getline(chars, 50);

        while (chars[0] != '@')
        {


            temp.character_id = atoi(chars);

            in.getline(chars, 50);
            temp.level = atoi(chars);
            elem.characters.push_back(temp);
            in.getline(chars, 50);
        }


        for (int i = 0; i < elem.characters.size(); i++)
        {
            if (elem.characters[i].character_id == character_id)
            {
                books.push_back(elem);
                
                break;
            }

        }

        in.getline(chars, 50);
        if (chars[0] == NULL)
        {
            break;
        }
    }
    in.close();

    vector<pair<int, int>> books_id;

    for (int i = 0; i < books.size(); i++)
    {
        char chars_date[5];
        int int_date;
        vector<int> date;
        chars_date[0] = books[i].date[0];
        chars_date[1] = books[i].date[1];
        int_date = atoi(chars_date);
        date.push_back(int_date);

        chars_date[0] = books[i].date[3];
        chars_date[1] = books[i].date[4];
        int_date = atoi(chars_date);
        date.push_back(int_date);

        chars_date[0] = books[i].date[6];
        chars_date[1] = books[i].date[7];
        chars_date[2] = books[i].date[8];
        chars_date[3] = books[i].date[9];
        int_date = atoi(chars_date);
        
        date.push_back(int_date);

        int_date = date[2] * 10000 + date[1] * 100 + date[0];
        books_id.push_back(make_pair(books[i].id, int_date));
    }

    sort(books_id.begin(), books_id.end(), comp);

    for (int i = 0; i < books_id.size(); i++)
    {
        for (int j = 0; j < books.size(); j++)
        {
            if (books_id[i].first==books[j].id)
            {
                cout << endl;
                
                cout << books[j].title << "    " << books[j].authors_name << " " << books[j].authors_surname <<  endl;
               
                
            }
        }
    }
    cout << endl;
}

int find_by_character(char input[256]) {

    ifstream in;
    in.open("../character.txt");
    char chars[256];
    
    while (!in.eof()) {
        character_info elem;
        in.getline(chars, 256);
        elem.id = atoi(chars);
        in.getline(elem.name, 256);
       
        if (string(input).find(string(elem.name)) != string::npos || string(elem.name).find(string(input)) != string::npos)
        {

            book_by_character(elem.id);


            in.close();
            return 0;
        }


    }
    in.close();
    return 1;



}


int find(char input[256])
{

    ifstream in;
    in.open("../book.txt");
    char chars[50];
    in.getline(chars, 50);
    while (!in.eof())
    {        
        book_info elem;
          
        
        elem.id = atoi(chars);
        in.getline(elem.title, 256);
        in.getline(elem.authors_name, 50);
        in.getline(elem.authors_surname, 50);
        in.getline(elem.description, 1024);
        in.getline(elem.date, 11);
        in.getline(chars, 50);
        elem.pages= atoi(chars);
        char check[50];
        level_of_character temp;
        in.getline(chars, 50);
        temp.character_id = atoi(chars);
        in.getline(chars, 50);
        temp.level = atoi(chars);
        elem.characters.push_back(temp);
        in.getline(chars, 50);
        
        while (chars[0]!= '@')
        {            
           
           
            temp.character_id = atoi(chars);

            in.getline(chars, 50);
            temp.level = atoi(chars);
            elem.characters.push_back(temp);
            in.getline(chars, 50);
        }


        if (string(input).find(string(elem.authors_name)) != string::npos || string(input).find(string(elem.authors_surname)) != string::npos || string(input).find(string(elem.title)) != string::npos||
            string(elem.authors_name).find(string(input)) != string::npos || string(elem.authors_surname).find(string(input)) != string::npos || string(elem.title).find(string(input)) != string::npos)
        {

            cout << endl;
            cout << elem.title << "    " << elem.authors_name << " " << elem.authors_surname << "    " << elem.date << "    " << elem.pages << " pages" << endl;
            cout << endl;
            cout << elem.description << endl;
            cout << endl;


          //  in.close();
            //return 0;

        }
        in.getline(chars, 50);
        if (chars[0]==NULL)
        {
            break;
        }
    }
    in.close();
    return 1;
}






int main() {
    //read_all_books();
    char input_letter;
    cout << "Welcome to our library!" << endl;
    unsigned int id = 0;
    book_info elem;

    while (true) {
        cout << "Press press 'F' to find a book or press 'E' to edit library: ";
        cin >> input_letter;
        if (input_letter == 'F' || input_letter == 'f'|| input_letter == 'E' || input_letter == 'e')
        {
            break;
        }
        else {
            cout << "Invalid syntax. Try again" << endl;
        }
        
    }
    while (input_letter == 'F' || input_letter == 'f' || input_letter == 'E' || input_letter == 'e')
    {

   

        while (input_letter == 'E' || input_letter == 'e')
        {
            cout << "Press press 'A' to add a book, press 'D' to delete, press 'U' to update or press 'B' to turn back: ";
            cin >> input_letter;
            if (input_letter == 'A' || input_letter == 'a')
            {
                add_book();
                break;
            }
            else if (input_letter == 'D' || input_letter == 'd')
            {
                while (true)
                {

                
                    char input[256];
                    cout << "Enter a title of a book: ";
                    gets_s(input);
                    gets_s(input);
                    bool success = delete_book(input);
                    if (!success)
                    {

                        break;
                    }
                    cout << "Invalid syntax. Try again" << endl;
                }
            }
            else if (input_letter == 'U' || input_letter == 'u')
            {
                while (true)
                {


                    char book_title[256];
                    int item;
                    char input[1024];
                    cout << "Enter a title of a book: ";
                    gets_s(book_title);
                    gets_s(book_title);
                    cout << "What item you want to update: "<<endl;
                    cout << "0 - autor`s name" << endl;
                    cout << "1 - autor`s surname" << endl;
                    cout << "2 - book description" << endl;
                    cout << "3 - number of pages" << endl;
                    cout << "4 - date of publishing" << endl;                  
                    cin>>item;
                    cout << "Enter new value: ";
                    gets_s(input);
                    gets_s(input);

                    cout << string(book_title)<<" "<<item<<" "<<string(input) << endl;
                    bool success = update_book(book_title, item, input);
                    if (!success)
                    {
                        break;
                    }
                    cout << "Invalid syntax. Try again" << endl;
                }
            }
            else if (input_letter == 'B' || input_letter == 'b')
            {
                break;
            }
            else {
                input_letter = 'E';
                cout << "Invalid syntax. Try again" << endl;
            }

        }
        if (input_letter == 'F' || input_letter == 'f')
        {
            char input[256];
            cout << "Enter a title of a book, an author's name or a name of a character: ";
            gets_s(input);
            gets_s(input);
            bool finder;
            finder = find(input);
            if (finder)
            {
                finder = find_by_character(input);

            }
            while (finder)
            {
                cout << "Search error. Try again?"<<endl;
                cout << "Press press 'Y' or 'N'" << endl;
                cin >> input_letter;

                if (input_letter == 'Y' || input_letter == 'n' || input_letter == 'y' || input_letter == 'N')
                {
                    if (input_letter == 'Y' || input_letter == 'y')
                    {
                        cout << "Enter a title of a book, an author's name or a name of a character: ";
                        gets_s(input);
                        gets_s(input);                    
                        finder = find(input);
                        if (finder)
                        {
                            finder = find_by_character(input);

                        }

                    }
                    else
                    {
                        break;
                    };
                }
                else {
                    cout << "Invalid syntax. Try again" << endl;
                }

            }
        }

        while (true) {
            cout << "Press press 'F' to find a book, press 'E' to edit library or press 'C' to close the program: ";
            cin >> input_letter;
            if (input_letter == 'F' || input_letter == 'f' || input_letter == 'E' || input_letter == 'e')
            {
                break;
            }
            else if (input_letter == 'C' || input_letter == 'c')
            {
                return 0;
            }
            else {
                cout << "Invalid syntax. Try again" << endl;
            }

        }

    }
    return 0;
}