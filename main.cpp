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
	size_t String_size = 2 * pow (2, key_max) - 1;
	for (unsigned int key_time = 0; key_time <= key_max; key_time++)
	{
		unsigned int tabs = String_size / 2;
		std::vector<T> Vec;
		Print_help (Tree, key_time, Vec);
		if (key_time != key_max)
		{
			for (unsigned int h = 0; h <= tabs; h++)
			{
				std::cout << "\t";
			{ 
			for (int h: Vec)
			{
				std::cout << h;
				while ((key_max - key_time) != 0)
					{
						std::cout << '\t";
						
					}
			}
			std::cout << "\n";
			}
		}
		else //тогда это последний уровень дерева, что следует из его балансировки
		{
			Print_help_max (Tree, key_time, Vec);
			for (int h: Vec)
			{
				std::cout << h << "\t";
			}
		}
		tabs -= 1;
	}
}

template <typename T> //5 - для систематизации печати - заполнение вектора значениями дерева
Tree_element<T>* Print_help (Tree_element<T>* Tree, unsigned int key_time, std::vector<T>& Vec)
{
	if (Tree -> key == key_time)
	{	
		Vec.push_back(Tree);
	}
	Print_help (Tree -> tree_next_left , key_time, Vec);	
	Print_help (Tree -> tree_next_right , key_time, Vec);	
	return Vec;
}

template <typename T> //5 - для систематизации печати - заполнение вектора значениями последнего уровня дерева
Tree_element<T>* Print_help_max (Tree_element<T>* Tree, unsigned int key_max, std::vector<T>& Vec)
{
	if (Tree -> key == key_max - 1)
	{	
		if (Tree -> tree_next_left != 0)
		{
			Vec.push_back(Tree -> tree_next_left)
		}
		else
		{
			Vec.push_back(0);
		}
		if (Tree -> tree_next_right != 0)
		{
			Vec.push_back(Tree -> tree_next_right)
		}
		else
		{
			Vec.push_back(0);
		}
	}
	Print_help_max (Tree -> tree_next_left , key_max, Vec);	
	Print_help_max (Tree -> tree_next_right , key_max, Vec);
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
