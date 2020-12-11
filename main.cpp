#include <iostream>
#include <cmath>
#include <vector>

template <class T>
struct Tree_element
{
    T value;
    unsigned int key;
    Tree_element* tree_next_left;
    Tree_element* tree_next_right;
};

template <typename T> //6 - поиск нужного элемента
Tree_element<T>* Find_element (Tree_element<T>* Tree, T n)
{
    if (Tree -> value == n)
    {
        return Tree;
    }
    if (Tree -> value > n)
    {
        if (Tree -> tree_next_left == nullptr)
        {
            return -1; //данного елемента нет
        }
        else
        {
            Find_element(Tree -> tree_next_left);
        }
    }
    if (Tree -> value < n)
    {
        if (Tree -> tree_next_right == nullptr)
        {
            return -1; //данного елемента нет
        }
        else
        {
            Find_element(Tree -> tree_next_right);
        }
    }
}

template <typename T> //6 - поиск максимального элемента
Tree_element<T>* Find_max_element (Tree_element<T>* Tree)
{
    if (Tree -> tree_next_right == nullptr)
    {
        return Tree;
    }
    else
    {
        Find_max_element (Tree -> tree_next_right);
    }
}

template <typename T> //6 - поиск минимального элемента
Tree_element<T>* Find_min_element (Tree_element<T>* Tree)
{
    if (Tree -> tree_next_left == nullptr)
    {
        return Tree;
    }
    else
    {
        Find_min_element (Tree -> tree_left_right);
    }
}

template <typename T> //6 - восстановление уровня узла
void Fix_key (Tree_element<T>* Tree)
{
    unsigned int key1 = Tree -> tree_next_left -> key;
    unsigned int key2 = Tree -> tree_next_right -> key;
    if(key1 > key2)
    {
        Tree -> key = key1 + 1;
    }
    else
    {
        Tree -> key = key2 + 1;
    }
}

template <typename T> //6 - правый поворот
Tree_element<T>* Right_rotation (Tree_element<T>* Tree)
{
    Tree_element<T>& tree_time = Tree -> tree_next_left;
    Tree -> tree_next_left = tree_time -> tree_next_right;
    tree_time -> tree_next_right = Tree;
    Fix_key (Tree);
    Fix_key (tree_time);
    return tree_time;
}

template <typename T> //6 - левый поворот
Tree_element<T>* Left_rotation (Tree_element<T>* Tree)
{
    Tree_element<T>& tree_time = Tree -> tree_next_right;
    Tree -> tree_next_right = tree_time -> tree_next_left;
    tree_time -> tree_next_lift = Tree;
    Fix_key (Tree);
    Fix_key (tree_time);
    return tree_time;
}

template <typename T> //6 - балансировка
Tree_element<T>* Balance (Tree_element<T>* Tree)
{
    Fix_key (Tree);
    if ((Tree -> tree_next_right -> key) - (Tree -> tree_next_left -> key) == 2)
    {
        if ((Tree -> tree_next_right -> trer_next_right -> key) - (Tree -> tree_next_right -> tree_next_left -> key) > 0)
        {
            Tree -> tree_next_right = Right_rotation (Tree -> tree_next_right);
            Tree -> tree_next_right = Left_rotation (Tree -> tree_next_right);

        }
        else
        {
            Tree -> tree_next_right = Left_rotation (Tree -> tree_next_right);
        }
    }
    if ((Tree -> tree_next_right -> key) - (Tree -> tree_next_left -> key) == -2)
    {
        if ((Tree -> tree_next_left -> trer_next_right -> key) - (Tree -> tree_next_left -> tree_next_left -> key) < 0)
        {
            Tree -> tree_next_left = Left_rotation (Tree -> tree_next_left);
            Tree -> tree_next_left = Right_rotation (Tree -> tree_next_left);

        }
        else
        {
            Tree -> tree_next_left = Right_rotation (Tree -> tree_next_left);
        }
    }
    return Tree;
}

template <typename T> //1
void Constructor (Tree_element<T>* Tree)
{
    Tree -> value = 0;
    Tree -> key = 1;
    Tree -> tree_next_left = nullptr;
    Tree -> tree_next_right = nullptr;
}

template <typename T> //3
Tree_element<T>* Push (Tree_element<T>* Tree, T n)
{
    if (Tree -> value > n)
    {
        Tree -> tree_next_left = Push(Tree -> tree_next_left, n);
    }
    else
    {
        Tree -> tree_next_right = Push(Tree -> tree_next_right, n);
    }
    return Balance (Tree);
}

template <typename T> //4
Tree_element<T>* Erase (Tree_element<T>* Tree, T n)
{
    if (Find_element(Tree, n) == -1)
    {
        std::cout << "There isn't a needed element.";
    }
    else
    {
        if ((Find_element(Tree, n) -> tree_next_left == nullptr) && (Find_element(Tree, n) -> tree_next_right == nullptr))
        {
            delete Find_element(Tree, n);
            return Balance(Tree);
        }
        else
        {
            if (Tree -> value > n)
            {
                Find_max_element(Tree -> tree_next_left) -> tree_next_left = Find_element(Tree, n) -> tree_next_left;
                Find_max_element(Tree -> tree_next_left) -> tree_next_right = Find_element(Tree, n) -> tree_next_right;
                delete Find_element(Tree, n);
                return Balance(Tree);
            }
            if (Tree -> value < n)
            {
                Find_min_element(Tree -> tree_next_right) -> tree_next_left = Find_element(Tree, n) -> tree_next_left;
                Find_min_element(Tree -> tree_next_right) -> tree_next_right = Find_element(Tree, n) -> tree_next_right;
                delete Find_element(Tree, n);
                return Balance(Tree);
            }
        }
    }
}

template <typename T> //6 - удаление максимального узла
Tree_element<T>* Delete_right_elements (Tree_element<T>* Tree)
{
    delete Find_max_element(Tree);
    return Balance(Tree);
}

template <typename T> //6 - удаление минимального узла
T* Delete_left_elements (Tree_element<T>* Tree)
{
    delete Find_min_element(Tree);
    return Balance(Tree);
}

template <typename T> //2
void Destructor (Tree_element<T>* Tree)
{
    while (Find_max_element(Tree) != Tree)
    {
        Delete_max_elements(Tree);
    }
    while (Find_min_element(Tree) != Tree)
    {
        Delete_min_elements(Tree);
    }
    delete Tree;
}

template <typename T> //5
void Print (Tree_element<T>* Tree)
{
    Balance(Tree);
    unsigned int key1 = Find_max_element(Tree) -> key;
    unsigned int key2 = Find_min_element(Tree) -> key;
    unsigned int key_max;
    if (key1 >= key2)
    {
        key_max = key1;
    }
    else
    {
        key_max = key2;
    }
    unsigned int tab = static_cast<int>(pow(2, (key_max - 1)));
     if (Tree != nullptr)
     {
         std::vector<T> Vec;
         Print_help(Tree, 200, Vec, 4, key_max);
         T print_string;
         print_string.value = -1;
         for (int i = key_max; i > 0; i--)
         {
             for (int j = 0; j < Vec.size(); j++)
             {
                 if (Vec[j].key == i)
                 {
                     for (int k = 0; k < tab; k++)
                     {
                         std::cout << " ";
                     }
                     if (Vec[j].value == -1)
                     {
                         std::cout << "-";
                     }
                     else
                     {
                         std::cout << Vec[j].value;
                     }
                     for (int k = 0; k < (tab - 1); k++)
                     {
                         std::cout << " ";
                     }
                 }
             }
             tab = tab / 2;
             std::cout << "\n";
         }
     }
}

template <typename T> //5 - для систематизации печати - заполнение вектора значениями дерева
void Print_help (Tree_element<T>* Tree, int k, std::vector<T>& Vec, int n, unsigned int key_max)
{
    if (Tree != nullptr)
    {
        T x;
        if (k == 200)
        {
            x.key = key_max;
            x.value = Tree -> value;
            Vec.push_back(x);
            x.key = key_max - 1;
            if (Tree -> tree_next_left != nullptr)
            {
                x.value = Tree -> tree_next_left -> value;
            }
            else
            {
                x.value = -1;
            }
            Vec.push_back(x);
            n = key_max - 1;
            Print_help(Tree -> tree_next_left, 100, Vec, n - 1, key_max);
            Print_help(Tree -> tree_next_right, 100, Vec, n - 1, key_max);
        }
        if (k == 100)
        {
            if ((Tree -> tree_next_left != nullptr) || (Tree -> tree_next_right != nullptr))
            {
                x.key = n;
                if (Tree -> tree_next_left != nullptr)
                {
                    x.value = Tree -> tree_next_left -> value;
                }
                else
                {
                    x.value = -1;
                }
                Vec.push_back(x);
                if (Tree -> tree_next_right != nullptr)
                {
                    x.value = Tree -> tree_next_right -> value;
                }
                else
                {
                    x.value = -1;
                }
                Vec.push_back(x);
                Print_help(Tree -> tree_next_left, 100, Vec, n - 1, key_max);
                Print_help(Tree -> tree_next_right, 100, Vec, n - 1, key_max);
            }
            else
            {
                x.key = n;
                x.value = -1;
                Vec.push_back(x);
                Vec.push_back(x);
                Print_help(Tree -> tree_next_left, 101, Vec, n - 1, key_max);
                Print_help(Tree -> tree_next_right, 101, Vec, n - 1, key_max);
            }
        }
    }
}

int main()
{
    //проверка для стандартного типа
    Tree_element<std::vector>* tree_time = new Tree_element<std::vector>;
    Constructor (tree_time);
    for (int i = 0; i < 10; ++i)
	{
		tree_time = Push(tree_time, i);
	}
	Print(tree_time);
	std::cout << "\n\n";
	Erase (tree_time, 10);
	Erase (tree_time, 2);
	Erase (tree_time, 4);
	Print(tree_time);
	Destructor(tree_time);
    return 0;
}
