#include <iostream>
#include <array>
#include <SFML/Graphics.hpp>
#include <vector>
#include <conio.h> 
#include <stdio.h> 



using namespace sf;
using namespace std;




struct for_edges {
    int x;
    int y;
    int number_of_sons;
    int i;
    int j;
    for_edges(int x, int y, int number_of_sons, int i, int j) {
        this->x = x;
        this->y = y;
        this->number_of_sons = number_of_sons;
        this->i = i;
        this->j = j;
    }
    for_edges() {

    }
};

struct edge_pair
{
    Vertex line[2];
};

struct node {
private:
    int size;      
    int key[3];
    node* first;   
    node* second;  
    node* third;   
    node* fourth;  
    node* parent; 

    bool find(int k) { 
        for (int i = 0; i < size; ++i)
            if (key[i] == k) return true;
        return false;
    }

    void swap(int& x, int& y) {
        int r = x;
        x = y;
        y = r;
    }

    void sort2(int& x, int& y) {
        if (x > y) swap(x, y);
    }

    void sort3(int& x, int& y, int& z) {
        if (x > y) swap(x, y);
        if (x > z) swap(x, z);
        if (y > z) swap(y, z);
    }

    void sort() { 
        if (size == 1) return;
        if (size == 2) sort2(key[0], key[1]);
        if (size == 3) sort3(key[0], key[1], key[2]);
    }

    void insert_to_node(int k) {  
        key[size] = k;
        size++;

        sort();

    }

    void remove_from_node(int k) { 
        if (size >= 1 && key[0] == k) {
            key[0] = key[1];
            key[1] = key[2];
            size--;
        }
        else if (size == 2 && key[1] == k) {
            key[1] = key[2];
            size--;
        }
    }

    void become_node2(int k, node* first_, node* second_) {  
        key[0] = k;
        first = first_;
        second = second_;
        third = nullptr;
        fourth = nullptr;
        parent = nullptr;
        size = 1;
    }

    bool is_leaf() { 
        return (first == nullptr) && (second == nullptr) && (third == nullptr);
    }

public:
    
    node(int k) : size(1), key{ k, 0, 0 }, first(nullptr), second(nullptr),
        third(nullptr), fourth(nullptr), parent(nullptr) {}

    node(int k, node* first_, node* second_, node* third_, node* fourth_, node* parent_) :
        size(1), key{ k, 0, 0 }, first(first_), second(second_),
        third(third_), fourth(fourth_), parent(parent_) {}

    friend node* split(node* item); 
    friend node* insert(node* p, int k); 
    friend node* search(node* p, int k); 
    friend node* search_min(node* p); 
    friend node* merge(node* leaf); 
    friend node* redistribute(node* leaf); 
    friend node* fix(node* leaf); 
    friend node* remove(node* p, int k); 
    friend int main();
    friend vector < vector < vector <int> > > treeprint(node* tree, int level);
    friend void print(node* root);
   
};



node* split(node* item) {
    if (item->size < 3) return item;

    node* x = new node(item->key[0], item->first, item->second, nullptr, nullptr, item->parent); 
    node* y = new node(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);  
    if (x->first)  x->first->parent = x;    
    if (x->second) x->second->parent = x;   
    if (y->first)  y->first->parent = y;    
    if (y->second) y->second->parent = y;

    if (item->parent) {
        item->parent->insert_to_node(item->key[1]);

        if (item->parent->first == item) item->parent->first = nullptr;
        else if (item->parent->second == item) item->parent->second = nullptr;
        else if (item->parent->third == item) item->parent->third = nullptr;

        
        if (item->parent->first == nullptr) {
            item->parent->fourth = item->parent->third;
            item->parent->third = item->parent->second;
            item->parent->second = y;
            item->parent->first = x;
        }
        else if (item->parent->second == nullptr) {
            item->parent->fourth = item->parent->third;
            item->parent->third = y;
            item->parent->second = x;
        }
        else {
            item->parent->fourth = y;
            item->parent->third = x;
        }

        node* tmp = item->parent;
        delete item;
        return tmp;
    }
    else {
        x->parent = item;   
        y->parent = item;   
        item->become_node2(item->key[1], x, y);
        return item;
    }
}








node* insert(node* p, int k) { 
    if (!p) return new node(k); 

    if (p->is_leaf()) p->insert_to_node(k);
    else if (k <= p->key[0]) insert(p->first, k);
    else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1])) insert(p->second, k);
    else insert(p->third, k);

    return split(p);
}

node* search(node* p, int k) { 
    if (!p) return nullptr;

    if (p->find(k)) return p;
    else if (k < p->key[0]) return search(p->first, k);
    else if ((p->size == 2) && (k < p->key[1]) || (p->size == 1)) return search(p->second, k);
    else if (p->size == 2) return search(p->third, k);
}

node* search_min(node* p) {
    if (!p) return p;
    if (!(p->first)) return p;
    else return search_min(p->first);
}
node* merge(node* leaf) {
    node* parent = leaf->parent;

    if (parent->first == leaf) {
        parent->second->insert_to_node(parent->key[0]);
        parent->second->third = parent->second->second;
        parent->second->second = parent->second->first;

        if (leaf->first != nullptr) parent->second->first = leaf->first;
        else if (leaf->second != nullptr) parent->second->first = leaf->second;

        if (parent->second->first != nullptr) parent->second->first->parent = parent->second;

        parent->remove_from_node(parent->key[0]);
        delete parent->first;
        parent->first = nullptr;
    }
    else if (parent->second == leaf) {
        parent->first->insert_to_node(parent->key[0]);

        if (leaf->first != nullptr) parent->first->third = leaf->first;
        else if (leaf->second != nullptr) parent->first->third = leaf->second;

        if (parent->first->third != nullptr) parent->first->third->parent = parent->first;

        parent->remove_from_node(parent->key[0]);
        delete parent->second;
        parent->second = nullptr;
    }

    if (parent->parent == nullptr) {
        node* tmp = nullptr;
        if (parent->first != nullptr) tmp = parent->first;
        else tmp = parent->second;
        tmp->parent = nullptr;
        delete parent;
        return tmp;
    }
    return parent;
}

node* redistribute(node* leaf) {
    node* parent = leaf->parent;
    node* first = parent->first;
    node* second = parent->second;
    node* third = parent->third;

    if ((parent->size == 2) && (first->size < 2) && (second->size < 2) && (third->size < 2)) {
        if (first == leaf) {
            parent->first = parent->second;
            parent->second = parent->third;
            parent->third = nullptr;
            parent->first->insert_to_node(parent->key[0]);
            parent->first->third = parent->first->second;
            parent->first->second = parent->first->first;

            if (leaf->first != nullptr) parent->first->first = leaf->first;
            else if (leaf->second != nullptr) parent->first->first = leaf->second;

            if (parent->first->first != nullptr) parent->first->first->parent = parent->first;

            parent->remove_from_node(parent->key[0]);
            delete first;
        }
        else if (second == leaf) {
            first->insert_to_node(parent->key[0]);
            parent->remove_from_node(parent->key[0]);
            if (leaf->first != nullptr) first->third = leaf->first;
            else if (leaf->second != nullptr) first->third = leaf->second;

            if (first->third != nullptr) first->third->parent = first;

            parent->second = parent->third;
            parent->third = nullptr;

            delete second;
        }
        else if (third == leaf) {
            second->insert_to_node(parent->key[1]);
            parent->third = nullptr;
            parent->remove_from_node(parent->key[1]);
            if (leaf->first != nullptr) second->third = leaf->first;
            else if (leaf->second != nullptr) second->third = leaf->second;

            if (second->third != nullptr)  second->third->parent = second;

            delete third;
        }
    }
    else if ((parent->size == 2) && ((first->size == 2) || (second->size == 2) || (third->size == 2))) {
        if (third == leaf) {
            if (leaf->first != nullptr) {
                leaf->second = leaf->first;
                leaf->first = nullptr;
            }

            leaf->insert_to_node(parent->key[1]);
            if (second->size == 2) {
                parent->key[1] = second->key[1];
                second->remove_from_node(second->key[1]);
                leaf->first = second->third;
                second->third = nullptr;
                if (leaf->first != nullptr) leaf->first->parent = leaf;
            }
            else if (first->size == 2) {
                parent->key[1] = second->key[0];
                leaf->first = second->second;
                second->second = second->first;
                if (leaf->first != nullptr) leaf->first->parent = leaf;

                second->key[0] = parent->key[0];
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr) second->first->parent = second;
                first->third = nullptr;
            }
        }
        else if (second == leaf) {
            if (third->size == 2) {
                if (leaf->first == nullptr) {
                    leaf->first = leaf->second;
                    leaf->second = nullptr;
                }
                second->insert_to_node(parent->key[1]);
                parent->key[1] = third->key[0];
                third->remove_from_node(third->key[0]);
                second->second = third->first;
                if (second->second != nullptr) second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
            else if (first->size == 2) {
                if (leaf->second == nullptr) {
                    leaf->second = leaf->first;
                    leaf->first = nullptr;
                }
                second->insert_to_node(parent->key[0]);
                parent->key[0] = first->key[1];
                first->remove_from_node(first->key[1]);
                second->first = first->third;
                if (second->first != nullptr) second->first->parent = second;
                first->third = nullptr;
            }
        }
        else if (first == leaf) {
            if (leaf->first == nullptr) {
                leaf->first = leaf->second;
                leaf->second = nullptr;
            }
            first->insert_to_node(parent->key[0]);
            if (second->size == 2) {
                parent->key[0] = second->key[0];
                second->remove_from_node(second->key[0]);
                first->second = second->first;
                if (first->second != nullptr) first->second->parent = first;
                second->first = second->second;
                second->second = second->third;
                second->third = nullptr;
            }
            else if (third->size == 2) {
                parent->key[0] = second->key[0];
                second->key[0] = parent->key[1];
                parent->key[1] = third->key[0];
                third->remove_from_node(third->key[0]);
                first->second = second->first;
                if (first->second != nullptr) first->second->parent = first;
                second->first = second->second;
                second->second = third->first;
                if (second->second != nullptr) second->second->parent = second;
                third->first = third->second;
                third->second = third->third;
                third->third = nullptr;
            }
        }
    }
    else if (parent->size == 1) {
        leaf->insert_to_node(parent->key[0]);

        if (first == leaf && second->size == 2) {
            parent->key[0] = second->key[0];
            second->remove_from_node(second->key[0]);

            if (leaf->first == nullptr) leaf->first = leaf->second;

            leaf->second = second->first;
            second->first = second->second;
            second->second = second->third;
            second->third = nullptr;
            if (leaf->second != nullptr) leaf->second->parent = leaf;
        }
        else if (second == leaf && first->size == 2) {
            parent->key[0] = first->key[1];
            first->remove_from_node(first->key[1]);

            if (leaf->second == nullptr) leaf->second = leaf->first;

            leaf->first = first->third;
            first->third = nullptr;
            if (leaf->first != nullptr) leaf->first->parent = leaf;
        }
    }
    return parent;
}

node* fix(node* leaf) {
    if (leaf->size == 0 && leaf->parent == nullptr) { 
        delete leaf;
        return nullptr;
    }
    if (leaf->size != 0) { 
        if (leaf->parent) return fix(leaf->parent);
        else return leaf;
    }

    node* parent = leaf->parent;
    if (parent->first->size == 2 || parent->second->size == 2 || parent->size == 2) leaf = redistribute(leaf); 
    else if (parent->size == 2 && parent->third->size == 2) leaf = redistribute(leaf); 
    else leaf = merge(leaf); 

    return fix(leaf);
}

node* remove(node* p, int k) { 
    node* item = search(p, k); 

    if (!item) return p;

    node* min = nullptr;
    if (item->key[0] == k) min = search_min(item->second); 
    else min = search_min(item->third);

    if (min) { 
        int& z = (k == item->key[0] ? item->key[0] : item->key[1]);
        item->swap(z, min->key[0]);
        item = min; 
    }

    item->remove_from_node(k); 
    return fix(item); 
}
vector < vector < vector <int> > > v;
vector < vector < vector <int> > > treeprint(node* tree, int level) {

    if (tree != NULL) { 
        if (v.size() <= level) {
            v.push_back({});
        }
        if (tree->size == 1)
        {
            vector < int > v1 = { tree->key[0], 0 };
                vector <int>  n = {  };
                n.push_back({ tree->key[0] });
                n.push_back({ 0 });
                    v[level].push_back(n);
            treeprint(tree->first, level + 1); 
            treeprint(tree->second, level + 1); 
        }
        else if (tree->size == 2)
        {
            vector < int > v2 = { tree->key[0], tree->key[1] };   
                vector <int>  n = {  };
                n.push_back({ tree->key[0] });
                n.push_back({ tree->key[1] });
                    v[level].push_back(n);
            treeprint(tree->first, level + 1);
            treeprint(tree->second, level + 1);
            treeprint(tree->third, level + 1);
        }
    }
  
     
    return v;
}




void print(node* root) {
    if (root != NULL) { 
        if (root->size == 1)
        {
            cout << root->key[0] << " "; 
            print(root->first); 
            print(root->second); 

        }
        else if (root->size == 2)
        {
            cout << root->key[0] << "," << root->key[1] << " ";
            print(root->first);
            print(root->second);
            print(root->third);

        }
    }
}

void  draw(int length, vector < vector < vector <int> > > end) {
     Font font; 
    font.loadFromFile("vag-world-bold.ttf");
    Text text("", font, 20);
    int xw, yw;
    if (length<=15)
    {
       
        xw = 2000;
        yw = 1000;
        
    }
    else {
        xw = 2500;
        yw = 1300;

     }   

        RenderWindow window(VideoMode(xw, yw), "2-3 tree");
       
    if (window.isOpen())
    {
        
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)             
                window.close();
        }

        
        window.clear(Color(40, 40, 47, 0));
        Texture texture1;
        Texture texture2;

        texture1.loadFromFile("D:\\Programming\\Visual Studio\\repos\\laba3(2)\\Ellipse 204.png");
        texture2.loadFromFile("D:\\Programming\\Visual Studio\\repos\\laba3(2)\\Subtract.png");

        int SS1 = 0;
        int SS2 = 0;
        
           vector < Sprite > Sprites1;
           vector < Sprite > Sprites2;
           vector < for_edges > For_edges;
        for (int i = 0; i < end.size(); i++)
        {
            for (int j = 0; j < end[i].size(); j++)
            {
                if (end[i][j][1] != 0) {

                    for_edges for_edges1;
                    for_edges1.x = 2000 / (end[i].size() + 1) * (j + 1);
                    for_edges1.y = 200 * (i + 1);
                    for_edges1.number_of_sons = 3;
                    for_edges1.i = i;
                    for_edges1.j = j;
                    For_edges.push_back(for_edges1);

                    Sprite sprite2(texture2);
                    Sprites2.push_back(sprite2);
                   
                    Sprites2[SS2].move(for_edges1.x, for_edges1.y);
                    window.draw(Sprites2[SS2]);
                    SS2++;

                }
                else
                {
                  
                    for_edges for_edges1;
                    for_edges1.x = 2000 / (end[i].size() + 1) * (j + 1);
                    for_edges1.y = 200 * (i + 1);
                    for_edges1.number_of_sons = 2;
                    for_edges1.i = i;
                    for_edges1.j = j;
                    For_edges.push_back(for_edges1);

                    Sprite sprite1(texture1);
                    Sprites1.push_back(sprite1);
                    Sprites1[SS1].setPosition(for_edges1.x, for_edges1.y);
                    window.draw(Sprites1[SS1]);
                    SS1++;

                    
                }
            }
        }
      
        for (int i = 0; i < For_edges.size(); i++)
        {
            for_edges temp = For_edges[i];
            
        }
       
        vector <edge_pair > Lines = {};
        vector <int> count;
        int s_count2 = 0;
        int struct_count = 0;
        for (int i = 0; i < end.size()+2; i++)
        {
            count.push_back(0);

        }
        window.clear();
        for (int i = 0; i < end.size()-1; i++)
        {
            for (int j = 0; j < end[i].size(); j++)
            {
                for_edges edge = For_edges[struct_count];

                if (edge.number_of_sons == 2)
                {
                    s_count2 = 0;
                    for (int k = 0; k < i+1; k++)
                    {
                        
                        s_count2 += end[k].size();
                      
                    }
                    if (s_count2 + count[i + 1]>= length)
                    {
                        break;
                    }
                    for_edges edge_1 = For_edges[s_count2+count[i+1]];
                    for_edges edge_2 = For_edges[s_count2+count[i + 1]+1];
                    edge_pair l1;
                    l1.line[0] = Vertex(Vector2f(edge.x+50, edge.y+50));
                    l1.line[1] = Vertex(Vector2f(edge_1.x+50, edge_1.y + 50));
                    edge_pair l2;
                    l2.line[0] = Vertex(Vector2f(edge.x + 50, edge.y + 50));
                    l2.line[1] = Vertex(Vector2f(edge_2.x + 50, edge_2.y + 50));
                    Lines.push_back(l1);
                    Lines.push_back(l2);
                    count[i+1]+=2;                                    

                }
                else if (edge.number_of_sons == 3)
                {
                    s_count2 = 0;
                    for (int k = 0; k < i + 1; k++)
                    {
                        s_count2 += end[k].size();
                        
                    }
                    if (s_count2 + count[i + 1] >= length)
                    {
                        break;
                    }
                   
                    for_edges edge_1 = For_edges[s_count2+count[i + 1]];
                    for_edges edge_2 = For_edges[s_count2+count[i + 1] + 1];
                    for_edges edge_3 = For_edges[s_count2+count[i + 1] + 2];


                    edge_pair l1;
                    l1.line[0] = Vertex(Vector2f(edge.x + 50, edge.y + 50));
                    l1.line[1] = Vertex(Vector2f(edge_1.x + 50, edge_1.y + 50));
                    
                    edge_pair l2;
                    l2.line[0] = Vertex(Vector2f(edge.x + 50, edge.y + 50));
                    l2.line[1] = Vertex(Vector2f(edge_2.x + 50, edge_2.y + 50));


                    
                    edge_pair l3;
                    l3.line[0] = Vertex(Vector2f(edge.x+50, edge.y + 50));
                    l3.line[1] = Vertex(Vector2f(edge_3.x + 50, edge_3.y + 50));
                    Lines.push_back(l1);
                    Lines.push_back(l2);
                    Lines.push_back(l3);
                    count[i + 1] += 3;


                }
                struct_count++;


            }

        }

      
      
        for (int i = 0; i < Lines.size(); i++)
        {
            
            window.draw(Lines[i].line, 2, sf::Lines);

        }
       
       SS1 = 0;
         SS2 = 0;

        vector < Sprite > Sprites01;
        vector < Sprite > Sprites02;
      
        for (int i = 0; i < end.size(); i++)
        {
            for (int j = 0; j < end[i].size(); j++)
            {
               
                if (end[i][j][1] != 0) {

                    for_edges for_edges1;
                    for_edges1.x = 2000 / (end[i].size() + 1) * (j + 1);
                    for_edges1.y = 200 * (i + 1);
                    for_edges1.number_of_sons = 3;
                    for_edges1.i = i;
                    for_edges1.j = j;
                    For_edges.push_back(for_edges1);

                    Sprite sprite2(texture2);
                    Sprites02.push_back(sprite2);                   
                    Sprites02[SS2].move(for_edges1.x, for_edges1.y);
                    window.draw(Sprites02[SS2]);
                    SS2++;

                }
                else
                {
                    
                    for_edges for_edges1;
                    for_edges1.x = 2000 / (end[i].size() + 1) * (j + 1);
                    for_edges1.y = 200 * (i + 1);
                    for_edges1.number_of_sons = 2;
                    for_edges1.i = i;
                    for_edges1.j = j;
                    For_edges.push_back(for_edges1);

                    Sprite sprite1(texture1);
                    Sprites01.push_back(sprite1);
                    Sprites01[SS1].setPosition(for_edges1.x, for_edges1.y);
                    window.draw(Sprites01[SS1]);
                    SS1++;


                }
            }
        }                
       
            window.display();
            system("pause");
          
       
    }

}

int main()
{
    setlocale(LC_ALL, "");
    node* root = nullptr;
    int keys[40] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40 };
    int length;
    cout << "Введите количество вершин дерева: ";
    cin >> length;
    for (int i = 0; i < length; i++)
    {
        root = insert(root, keys[i]);

    }
    print(root);
    cout << endl;
    node* a = search(root, 5);     
    vector < vector < vector <int> > > end;
    end = treeprint(root, 0);   
    draw(length, end);
    while (true)
    {  
    cout << endl;
    cout << "Что вы хотите сделать?"<<endl;
    cout << "Введите 'R' для удаления вершины."<<endl;
    cout << "Введите 'I' для вставки вершины." << endl;
    cout << "Введите 'S' для поиска вершины." << endl;
    cout << "Введите 'E' для выхода." << endl;
    char What;
    cin >> What;
     
    if (What=='r' || What == 'R')
    {
        int toR;
        cout << "Введите номер вершины для удаления: ";        
        cin >> toR;
        remove(root, toR);
        end.clear();

        v.clear();
        end = treeprint(root, 0);
        print(root);
        draw(length, end);
    }
    else if (What == 'i' || What == 'I')
    {
        int toI;
        cout << "Введите номер вершины для вставки: ";
        cin >> toI;
        insert(root, toI);
        end.clear();
        v.clear();
        end = treeprint(root, 0);
        print(root);
        draw(length, end);
    }
    else if (What == 's' || What == 'S')
    {
        int toS;
        cout << "Введите номер вершины для поиска: ";
        cin >> toS;
        node* s = search(root, toS);
        cout<< "Размер: " << s->size << endl;
        cout<< "Первый ключ: " << s->key[0] << endl;
        if (s->size == 2)
        {
        cout << "Второй ключ: " << s->key[1] << endl;
        }
            
        
       
    }
    else if (What == 'e' || What == 'E')
    {
        break;
    }
    }
    

    system("pause");

 return 0;
}