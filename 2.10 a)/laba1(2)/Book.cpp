#include "Book.h"


Book::Book(string new_id, string new_title, string new_description, string new_num_of_pages, string new_authors_name, string new_authors_surname, string new_date){
    SetId(new_id);
    SetTitle(new_title);
    SetDescription(new_description);
    SetName(new_authors_name);
    SetSurname(new_authors_surname);
    SetNumOfPages(new_num_of_pages);
    SetDate(new_date);
}

unsigned int Book::GetId() {
    return id;
}

string Book::GetTitle() {
    return title;
}

string Book::GetDescription() {
    return description;
}

string Book::GetName() {
    return authors_name;
}

string Book::GetSurname() {
    return authors_surname;
}

int Book::GetNumOfPages() {
    return num_of_pages;
}

string Book::GetDate() {
    return to_string(date.day) + '.' + to_string(date.month) + '.' + to_string(date.year);
}

void Book::GetDateStream(ofstream& out)
{
    out << setfill('0');
    out << setw(2) << date.day << "." << setw(2) << date.month << "." << setw(4) << date.year;
}

Date Book::GetDateStruct() {
    return date;
}

/*template <typename ch_id>
string Book::GetCharacterLevel(typename ch_id) {
    int int_id;
    if (!is_arithmetic_v<ch_id>)
    {
        int_id = stoi(ch_id);
    }
    else
    {
        int_id = ch_id;
    }
    switch (characters.at(int_id))
    {
    case Level::MAIN:
        return "Main";
    case Level::SECONDARY:
        return "Secondary";
    case Level::EPISODIC:
        return "Episodic";
    default:
        break;
    }
}*/

string Book::GetCharacterLevel(string ch_id) {
    switch (characters.at(stoi(ch_id)))
    {
    case Level::MAIN:
        return "Main";
    case Level::SECONDARY:
        return "Secondary";
    case Level::EPISODIC:
        return "Episodic";
    default:
        break;
    }
}

string Book::GetCharacterLevel(int ch_id) {
    switch (characters.at(ch_id))
    {
    case Level::MAIN:
        return "Main";
    case Level::SECONDARY:
        return "Secondary";
    case Level::EPISODIC:
        return "Episodic";
    default:
        break;
    }
}

int Book::GetCharacterLevelInt(string ch_id) {
    return static_cast<int>(characters.at(stoi(ch_id)));
}

int Book::GetCharacterLevelInt(int ch_id) {
    return static_cast<int>(characters.at(ch_id));
}


int Book::GetNumOfCharacters() {
    return characters.size();
}

map<int, Level> Book::GetAllCharacters() {
    return characters;
}

void Book::SetId(string str) {
    id = stoi(str);
}

void Book::SetTitle(string str) {
    title = str;
}

void Book::SetDescription(string str) {
    description = str;
}

void Book::SetName(string str) {
    authors_name = str;
}

void Book::SetSurname(string str) {
    authors_surname = str;
}

void Book::SetNumOfPages(string str) {
    num_of_pages = stoi(str);
}

void Book::SetDate(string str) {
    if (str.size() != 10)
    {
        throw invalid_argument("Wrong DATE input.");
    }
    date.day = stoi(str.substr(0, 2));
    date.month = stoi(str.substr(3, 2));
    date.year = stoi(str.substr(6));
    if (!CheckDay())
    {
        throw invalid_argument("Wrong DATE values.");
    }
}

bool Book::CheckDay() {
    return (date.day > 0 && date.day <= 31 && (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12))
        || (date.day > 0 && date.day <= 30 && (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11))
        || (date.day > 0 && date.day <= 29 && date.month == 2 && date.year % 4 == 0)
        || (date.day > 0 && date.day <= 28 && date.month == 2);
}

void Book::SetCharacter(string id_str, string lvl_str) {
    characters[stoi(id_str)] = Level(stoi(lvl_str));
}
