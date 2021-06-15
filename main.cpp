#include <iostream>
#include <cmath>
#include <vector>

template <typename T, typename K>
struct Tree_element
{
	T value;
	K key;
	unsigned int height;
	Tree_element* tree_next_right;
	Tree_element* tree_next_left;
	Tree_element* tree_prev;
};

template <typename T, typename K>
struct Tree
{
	Tree_element<T, K>* tree_root;
};

template <typename T, typename K>
void Constructor(Tree<T, K>* tree) //1
{
	tree->tree_root = nullptr;
}

template <typename T, typename K>
void Fix_height(Tree_element<T, K>* tree_element)
{
	tree_element->height = tree_element->tree_prev->height + 1;
	while (tree_element->tree_next_left != nullptr)
	{
		Fix_height(tree_element->tree_next_left);
	}
	while (tree_element->tree_next_left != nullptr)
	{
		Fix_height(tree_element->tree_next_right);
	}
}

template <typename T, typename K>
void Little_left_spin(Tree<T, K>* tree, Tree_element<T, K>* tree_element) 
{
	if (tree_element->tree_prev == nullptr)
	{
		tree->tree_root = tree_element->tree_next_right;
		Tree_element<T, K>* tree_time = tree_element->tree_next_right->tree_next_left;
		tree_element->tree_next_right->tree_next_left = tree_element;
		tree_element->tree_next_right->tree_prev = nullptr;
		tree_element->tree_prev = tree_element->tree_next_right;
		tree_element->tree_next_right = tree_time;
		tree_time->tree_prev = tree_element;
	}
	else
	{
		if (tree_element->tree_prev->tree_next_right == tree_element)
		{
			tree_element->tree_prev->tree_next_right = tree_element->tree_next_right;
		}
		else 
		{
			tree_element->tree_prev->tree_next_left == tree_element->tree_next_right;
		}
		Tree_element<T, K>* tree_time = tree_element->tree_next_right->tree_next_left;
		tree_element->tree_next_right->tree_next_left = tree_element;
		tree_element->tree_next_right->tree_prev = tree_element->tree_prev;
		tree_element->tree_prev = tree_element->tree_next_right;
		tree_element->tree_next_right = tree_time;
		tree_time->tree_prev = tree_element;
	}
	Fix_height(tree_element->tree_prev);
}

template <typename T, typename K>
void Little_right_spin(Tree<T, K>* tree, Tree_element<T, K>* tree_element)
{
	if (tree_element->tree_prev == nullptr)
	{
		tree->tree_root = tree_element->tree_next_left;
		Tree_element<T, K>* tree_time = tree_element->tree_next_left->tree_next_right;
		tree_element->tree_next_left->tree_next_right = tree_element;
		tree_element->tree_next_left->tree_prev = nullptr;
		tree_element->tree_prev = tree_element->tree_next_left;
		tree_element->tree_next_left = tree_time;
		tree_time->tree_prev = tree_element;
	}
	else
	{
		if (tree_element->tree_prev->tree_next_right == tree_element)
		{
			tree_element->tree_prev->tree_next_right = tree_element->tree_next_left;
		}
		else
		{
			tree_element->tree_prev->tree_next_left == tree_element->tree_next_left;
		}
		Tree_element<T, K>* tree_time = tree_element->tree_next_left->tree_next_right;
		tree_element->tree_next_left->tree_next_right = tree_element;
		tree_element->tree_next_left->tree_prev = tree_element->tree_prev;
		tree_element->tree_prev = tree_element->tree_next_left;
		tree_element->tree_next_left = tree_time;
		tree_time->tree_prev = tree_element;
	}
	Fix_height(tree_element->tree_prev);
}

template <typename T, typename K>
int Find_max_height(Tree_element<T, K>* tree_element)
{
	int max_height = 0;
	if ((tree_element->tree_next_right == nullptr) && (tree_element->tree_next_left == nullptr))
	{
		max_height = tree_element->height;
	}
	else
	{
		int height_left = 0;
		int height_right = 0;
		if (tree_element->tree_next_right != nullptr)
		{
			height_right = Find_max_height(tree_element->tree_next_right);
		}
		if (tree_element->tree_next_left != nullptr)
		{
			height_left = Find_max_height(tree_element->tree_next_left);
		}
		if (height_left > height_right)
		{
			max_height = height_left;
		}
		else
		{
			max_height = height_right;
		}
	}
	return max_height;
}

template <typename T, typename K>
void Big_left_spin(Tree<T, K>* tree, Tree_element<T, K>* tree_element)
{
	Little_left_spin(tree, tree_element->tree_next_left);
	Little_right_spin(tree, tree_element);
}

template <typename T, typename K>
void Big_right_spin(Tree<T, K>* tree, Tree_element<T, K>* tree_element)
{
	Little_right_spin(tree, tree_element->tree_next_right);
	Little_left_spin(tree, tree_element);
}

template <typename T, typename K>
void Balance(Tree<T, K>* tree, Tree_element<T, K>* tree_element)
{
	if ((Find_max_height(tree->tree_root) > 2) && (tree_element->tree_next_left != nullptr) && (tree_element->tree_next_left->tree_next_left != nullptr) && 
		(tree_element->tree_next_left->tree_next_right != nullptr) && (tree_element->tree_next_right != nullptr) && 
		(tree_element->tree_next_left->tree_next_right != nullptr) && (tree_element->tree_next_right->tree_next_right != nullptr))
	{
		if (((Find_max_height(tree_element->tree_next_right) - Find_max_height(tree_element->tree_next_left)) == 2) &&
				((Find_max_height(tree_element->tree_next_right->tree_next_left) == Find_max_height(tree_element->tree_next_right->tree_next_right)) ||
					(Find_max_height(tree_element->tree_next_right->tree_next_right) - Find_max_height(tree_element->tree_next_right->tree_next_left) == 1)))
		{
			Little_left_spin(tree, tree_element);
		}
		else if (((Find_max_height(tree_element->tree_next_left) - Find_max_height(tree_element->tree_next_right)) == 2) &&
			((Find_max_height(tree_element->tree_next_left->tree_next_left) == Find_max_height(tree_element->tree_next_left->tree_next_right)) ||
				(Find_max_height(tree_element->tree_next_left->tree_next_left) - Find_max_height(tree_element->tree_next_left->tree_next_right) == 1)))
		{
			Little_right_spin(tree, tree_element);
		}
		else if (((Find_max_height(tree_element->tree_next_right) - Find_max_height(tree_element->tree_next_left)) == 2) &&
			(Find_max_height(tree_element->tree_next_right->tree_next_left) > Find_max_height(tree_element->tree_next_right->tree_next_right)))
		{
			Big_left_spin(tree, tree_element);
		}
		else if (((Find_max_height(tree_element->tree_next_left) - Find_max_height(tree_element->tree_next_right)) == 2) &&
			(Find_max_height(tree_element->tree_next_left->tree_next_right) > Find_max_height(tree_element->tree_next_left->tree_next_left)))
		{
			Big_right_spin(tree, tree_element);
		}
		while (tree_element->tree_next_left != nullptr)
		{
			Balance(tree, tree_element->tree_next_left);
		}
		while (tree_element->tree_next_left != nullptr)
		{
			Balance(tree, tree_element->tree_next_right);
		}
	}
}

template <typename T, typename K>
void Push(Tree<T, K>* tree, Tree_element<T, K>* tree_element, T value, K key)
{
	if (tree->tree_root == nullptr)
	{
		tree->tree_root = new Tree_element<T, K>;
		tree->tree_root->key = key;
		tree->tree_root->value = value;
		tree->tree_root->height = 1;
		tree->tree_root->tree_next_right = nullptr;
		tree->tree_root->tree_next_left = nullptr;
		tree->tree_root->tree_prev = nullptr;
	}
	else
	{
		if (tree->tree_root->key < key)
		{
			if (tree->tree_root->tree_next_right == nullptr)
			{
				Push_help(tree->tree_root, value, key);
			}
			else
			{
				Push_help(tree->tree_root->tree_next_right, value, key);
			}
		}
		else
		{
			if (tree->tree_root->tree_next_left == nullptr)
			{
				Push_help(tree->tree_root, value, key);
			}
			else
			{
				Push_help(tree->tree_root->tree_next_left, value, key);;
			}
		}
	}
	Balance(tree, tree->tree_root);
}

template <typename T, typename K>
void Push_help(Tree_element<T, K>* tree_element, T value, K key)
{
	if (tree_element->key < key)
	{
		if (tree_element->tree_next_right == nullptr)
		{
			Tree_element<T, K>* tree_push = new Tree_element<T, K>;
			tree_push->key = key;
			tree_push->value = value;
			tree_push->tree_next_right = nullptr;
			tree_push->tree_next_left = nullptr;
			tree_push->tree_prev = tree_element;
			tree_element->tree_next_right = tree_push;
			tree_push->height = tree_element->height + 1;
		}
		else
		{
			Push_help(tree_element->tree_next_right, value, key);
		}
	}
	else
	{
		if (tree_element->tree_next_left == nullptr)
		{
			Tree_element<T, K>* tree_push = new Tree_element<T, K>;
			tree_push->key = key;
			tree_push->value = value;
			tree_push->tree_next_right = nullptr;
			tree_push->tree_next_left = nullptr;
			tree_push->tree_prev = tree_element;
			tree_element->tree_next_left = tree_push;
			tree_push->height = tree_element->height + 1;
		}
		else
		{
			Push_help(tree_element->tree_next_left, value, key);
		}
	}
}

template <typename T, typename K>
 void Pop(Tree<T, K>* tree, Tree_element<T, K>* tree_element, K key)
{
	 if (tree->tree_root == nullptr)
	 {
		 std::cout << "The tree is clear.\n";
	 }
	 else
	 {
		 if (tree->tree_root->key > key)
		 {
			 Pop_help(tree->tree_root->tree_next_left, key);
		 }
		 else 
		 {
			 Pop_help(tree->tree_root->tree_next_right, key);
		 }
	 }
	 Balance(tree, tree->tree_root);
}

 template <typename T, typename K>
 Tree_element<T, K>* Find_min_key(Tree_element<T, K>* tree_element)
 {
	 if (tree_element->tree_next_left == nullptr)
	 {
		 return tree_element;
	 }
	 else
	 {
		 Find_min_key(tree_element->tree_next_left);
	 }
 }

 template <typename T, typename K>
 void Pop_help(Tree_element<T, K>* tree_element, K key)
 {
	 if (tree_element->key == key)
	 {
		 if ((tree_element->tree_next_right == nullptr) && (tree_element->tree_next_left == nullptr))
		 {
			 std::cout << "Your element is " << tree_element->value << "\n";
			 if (tree_element->tree_prev->tree_next_right = tree_element)
			 {
				 tree_element->tree_prev->tree_next_right = nullptr;
			 }
			 else
			 {
				 tree_element->tree_prev->tree_next_left = nullptr;
			 }
			 delete tree_element;
		 }
		 else
		 {
			 Tree_element<T, K>* tree_time = Find_min_key(tree_element->tree_next_right);
			 if (Find_min_key(tree_element->tree_next_right)->tree_prev->tree_next_right = tree_element)
			 {
				 Find_min_key(tree_element->tree_next_right)->tree_prev->tree_next_right = nullptr;
			 }
			 else
			 {
				 Find_min_key(tree_element->tree_next_right)->tree_prev->tree_next_left = nullptr;
			 }
			 delete Find_min_key(tree_element->tree_next_right);
			 std::cout << "Your element is " << tree_element->value << "\n";
			 if (tree_element->tree_prev->tree_next_right = tree_element)
			 {
				 tree_element->tree_prev->tree_next_right = tree_time;
			 }
			 else
			 {
				 tree_element->tree_prev->tree_next_left = tree_time;
			 }
			 tree_time->tree_prev = tree_element->tree_prev;
			 tree_time->tree_next_left = tree_element->tree_next_left;
			 if (tree_time->tree_next_right == nullptr)
			 {
				 tree_time->tree_next_right = tree_element->tree_next_right;
			 }
			 else
			 {
				 tree_time->tree_next_right->tree_next_right = tree_element->tree_next_right;
			 }
			 delete tree_element;
		 }
	 }
	 else if ((tree_element->tree_next_right == nullptr) && (tree_element->tree_next_left == nullptr))
	 {
		 std::cout << "There isn't your element.";
	 }
	 else if (tree_element->key > key)
	 {
		 if (tree_element->tree_next_left == nullptr)
		 {
			 std::cout << "There isn't your element.";
		 }
		 else
		 {
			 Pop_help(tree_element->tree_next_left, key);
		 }
	 }
	 else if (tree_element->key < key)
	 {
		 if (tree_element->tree_next_right == nullptr)
		 {
			 std::cout << "There isn't your element.";
		 }
		 else
		 {
			 Pop_help(tree_element->tree_next_right, key);
		 }
	 }
 }

 template <typename T, typename K>
 void Destructor(Tree<T, K>* tree)
 {
	 if (tree->tree_root == nullptr)
	 {
		 std::cout << "Your tree is clear.";
	 }
	 else if ((tree->tree_root->tree_next_right == nullptr) && (tree->tree_root->tree_next_left == nullptr))
	 {
		 delete tree->tree_root;
	 }
	 else
	 {
		 if (tree->tree_root->tree_next_right != nullptr)
		 {
			 Destructor_help(tree->tree_root->tree_next_right);
		 }
		 if (tree->tree_root->tree_next_left != nullptr)
		 {
			 Destructor_help(tree->tree_root->tree_next_left);
		 }
	 }
 }

 template <typename T, typename K>
 void Destructor_help(Tree_element<T, K>* tree_element)
 {
	 if ((tree_element->tree_next_right == nullptr) && (tree_element->tree_next_left == nullptr))
	 {
		 delete tree_element;
	 }
	 else
	 {
		 if (tree_element->tree_next_right != nullptr)
		 {
			 Destructor_help(tree_element->tree_next_right);
		 }
		 if (tree_element->tree_next_left != nullptr)
		 {
			 Destructor_help(tree_element->tree_next_left);
		 }
	 }
 }

 template <typename T, typename K>
 void Print(Tree<T, K>* tree)
 {
	 int max_height = Find_max_height(tree->tree_root);
	 int print_size = 2 * pow(2, max_height) - 1;
	 std::vector <Tree_element<T, K>*> Vec;
	 for (int h = 1; h <= max_height; h++)
	 {
		 Print_help(Vec, h, tree->tree_root);
		 double tabs_time = (print_size - pow(2, (h - 1))) / (pow(2, (h - 1)) + 1);
		 int tabs = static_cast<int>(tabs_time);
		 int extra_tab = 0;
		 if (tabs_time != static_cast<int>(tabs_time))
		 {
			 extra_tab += 1;
		 }
		 for (int x = 0; x < pow(2, (h - 1)); x++)
		 {
			 for (int i = 0; i < tabs; i++)
			 {
				 std::cout << "\t";
			 }
			 if (Vec[x]->height != 0)
			 {
				 std::cout << Vec[x]->key << ": " << Vec[x]->value << "\t";
			 }
			 else
			 {
				 std::cout << "\t";
			 }
			 if ((x == ((pow(2, (h - 1)) / 2)) - 1) && (extra_tab != 0))
			 {
				 std::cout << "\t";
			 }
		 }
		 std::cout << "\n";
		 Vec.clear();
	 }
 }

 template <typename T, typename K>
 void Print_help(std::vector <Tree_element<T, K>*>& Vec, int h, Tree_element<T, K>* tree_element)
 {
	 if (tree_element->height == h)
	 {
		 Vec.push_back(tree_element);
	 } 
	 else if (tree_element->height < h)
	 {
		 if (tree_element->tree_next_left == nullptr)
		 {
			 Tree_element<T, K>* tree_print = new Tree_element<T, K>;
			 tree_print->height = 0;
			 Vec.push_back(tree_print);
		 }
		 else
		 {
			 Print_help(Vec, h, tree_element->tree_next_left);
		 }
		 if (tree_element->tree_next_right == nullptr)
		 {
			 Tree_element<T, K>* tree_print = new Tree_element<T, K>;
			 tree_print->height = 0;
			 Vec.push_back(tree_print);
		 }
		 else
		 {
			 Print_help(Vec, h, tree_element->tree_next_right);
		 }
	 }
 }

int main()
{
	Tree<int, int>* My_tree = new Tree<int, int>;
	Constructor(My_tree);
	Tree_element <int, int>* My_tree_element = new Tree_element <int, int>;
	My_tree_element->key = 5;
	My_tree_element->value = 17;
	My_tree_element->height = 1;
	My_tree_element->tree_next_left = nullptr;
	My_tree_element->tree_next_right = nullptr;
	My_tree_element->tree_prev = nullptr;
	My_tree->tree_root = My_tree_element;
	Push(My_tree, My_tree->tree_root, 25, 3);
	Push(My_tree, My_tree->tree_root, 35, 6);
	Push(My_tree, My_tree->tree_root, 57, 7);
	Pop(My_tree, My_tree->tree_root, 7);
	Print(My_tree);
	Destructor(My_tree);
	return 0;
}
