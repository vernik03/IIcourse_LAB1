#include <iostream>
#include <windows.h>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include "Character.h"
#include "Book.h"

using namespace std;

class Library {
public:
    Library(string file_books = "../book.txt", string file_characters = "../character.txt") {
        ReadBooks(file_books);
        ReadCharacters(file_characters);
    }
    void ReadBooks(string file) {
        ifstream in(file);
        string temp;
        if (in)
        {
            while (!in.eof())
            {
                Book new_book;
                getline(in, temp);
                if (temp == "")
                {
                    break;
                }
                new_book.SetId(temp);
                getline(in, temp);
                new_book.SetTitle(temp);  
                getline(in, temp);
                new_book.SetName(temp);
                getline(in, temp);
                new_book.SetSurname(temp);
                getline(in, temp);
                new_book.SetDescription(temp);
                getline(in, temp);                
                new_book.SetDate(temp);
                getline(in, temp);
                new_book.SetNumOfPages(temp);
                getline(in, temp);
                while (temp[0] != '@')
                {
                    string ch_id = temp;
                    getline(in, temp);
                    new_book.SetCharacter(ch_id, temp);
                    getline(in, temp);
                }
                SetBook(new_book);
            }
        }
        else
        {
            throw invalid_argument("Wrong filename.");
        }
    }

    void ReadCharacters(string file) {
        ifstream in(file);
        string temp;
        if (in)
        {
            while (!in.eof())
            {
                Character new_character;
                getline(in, temp);
                if (temp == "")
                {
                    break;
                }
                new_character.SetId(temp);
                getline(in, temp);
                new_character.SetName(temp);
                SetCharacter(new_character);
            }
        }
        else
        {
            throw invalid_argument("Wrong filename.");
        }
    }

    void WriteBooks(string file = "../book.txt") {
        ofstream out(file);
        if (out)
        {
            for (int i = 0; i < books.size(); i++)
            {
                out << books[i].GetId()             << endl;
                out << books[i].GetTitle()          << endl;                
                out << books[i].GetName()           << endl;
                out << books[i].GetSurname()        << endl;
                out << books[i].GetDescription()    << endl;             
                books[i].GetDateStream(out); out    << endl;
                out << books[i].GetNumOfPages()     << endl;
                for (auto [ch_id, level] : books[i].GetAllCharacters()) {
                    out << ch_id << endl;
                    out << books[i].GetCharacterLevelInt(ch_id) << endl;
                }
                out << '@' << endl;
            }
        }
        else
        {
            throw invalid_argument("Wrong filename.");
        }
    }

    void WriteCharacters(string file = "../character.txt") {
        ofstream out(file);
        if (out)
        {
            for (int i = 0; i < characters.size(); i++)
            {
                out << characters[i].GetId() << endl;
                out << characters[i].GetName() << endl;
            }
        }
        else
        {
            throw invalid_argument("Wrong filename.");
        }
    }

    void SetBook(Book new_book) {
        books.push_back(new_book);
    }
    void SetCharacter(Character new_character) {
        characters.push_back(new_character);
    }
private:
    vector<Book> books;
    vector<Character> characters;
};


int main() {
    Library lib;

    lib.WriteBooks();
    lib.WriteCharacters();
    //read_all_books();
  /*  char input_letter;
    cout << "Welcome to our library!" << endl;
    unsigned int id = 0;
    Book new_book();

    while (true) {
        cout << "Press press 'F' to find a book or press 'E' to edit library: ";
        cin >> input_letter;
        if (input_letter == 'F' || input_letter == 'f' || input_letter == 'E' || input_letter == 'e')
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
                add_book("../book.txt");
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
                    cout << "What item you want to update: " << endl;
                    cout << "0 - autor`s name" << endl;
                    cout << "1 - autor`s surname" << endl;
                    cout << "2 - book description" << endl;
                    cout << "3 - number of pages" << endl;
                    cout << "4 - date of publishing" << endl;
                    cin >> item;
                    cout << "Enter new value: ";
                    gets_s(input);
                    gets_s(input);

                    cout << string(book_title) << " " << item << " " << string(input) << endl;
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
                cout << "Search error. Try again?" << endl;
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
    return 0;*/
    
}