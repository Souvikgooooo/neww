// Spell checking program in c using ternert search tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Node of ternary search tree
struct node 
{
	char ch; //character to enter
	int end; //determine if word is ended here or not
	//3 children of tst
	struct node *left;
	struct node *right;
	struct node *equal;
};

struct Node
{
	struct node *first;
	char second[100];
	int third;
};

struct qnode
{
	struct Node *newnode;
	struct qnode *next;
};

// Function to create a new tst node
struct node *newnode(char ch)
{
	//initializing values
	struct node *newnode = (struct node *)malloc(sizeof(struct node));
	newnode->ch = ch;
	newnode->end = 0;
	newnode->left = newnode->equal = newnode->right = NULL;
	return newnode;
}

//This function will insert word in tst
void insert(struct node **root, char *word)
{
	//If tree is empty create a new node
	if (*root == NULL)
	{
		*root = newnode(*word);
	}

	//If current word character is smaller than root's character
	if ((*word) < (*root)->ch)
	{
		insert(&((*root)->left), word); // inserting word in left sub tree
	}
	//If current word character is grester than root's character
	else if ((*word) > (*root)->ch)
	{
		insert(&((*root)->right), word); // inserting word in Right sub tree
	}
	//If current word character is same as that of root's character
	else
	{
		if (*(word + 1))
		{
			insert(&((*root)->equal), word + 1); // inserting word in equal sub tree
		}
		else
		{
			(*root)->end = 1;
		}
	}
}

// Function to search word in tst
int search(struct node *root, char *word)
{
	if (root == NULL) // if tree is empty
	{
		return 0;
	}
	//If current word's character is smaller than root's character
	if (*word < (root)->ch) 
	{
		return search(root->left, word); // search the word in left sub tree
	}
	//If current word's character is smaller than root's character
	else if (*word > (root)->ch)
	{
		return search(root->right, word); // search the word in right sub tree
	}
	else
	{
		if (*(word + 1) == '\0') // If word ends return end
		{
			return root->end;
		}
		else // if not end then call function recursively
		{
			return search(root->equal, word + 1);
		}
	}
}

//This function iterates from the node where the last character of the "wrong" string was found 
//it goes to equal child pointer of the root and keeps adding its character to the "wrong string"
//this goes until we found that string is present in TST
void final(struct node *root, char *str, char *ret, struct node *temp)
{
	int add = 0;

	while (search(temp, ret) != 1)
	{
		strncat(ret, &(root->ch), 1);
		if (search(temp, ret))
		{
			return;
		}
		add = 1;
		root = root->equal;
	}
}

//suggest a word corrosponding to inputed word's preffix 
//If corrosponding word prefix not in our dictonary then doesn't return anything
void suggest(struct node *root, char *str, char *ret, struct node *temp)
{
	char **substr = malloc(100 * sizeof(char *)); 
	for (int i = 0; i < 100; i++) // 100 is max charecter size of word
	{
		substr[i] = malloc(100 * sizeof(char));
		substr[i] = "";
	}
	struct node *prev = NULL;
	int n = strlen(str); // check word size of word
	int i = 0;
	// Traversing whole word character by charecter
	while (i < n)
	{
		if (root == NULL) // if tree is empty return
			return;
		if (root->ch == str[i]) //if charecter matches with root's child
		{
			prev = root;
			root = root->equal; // make equal our new root
			i++;
			continue;
		}
		if (root->ch < str[i]) //if current charecter is greater then charecter corresponding to current word
			root = root->right; // make right sub tree of root to new root
		else //if current charecter is less then charecter corresponding to current word
			root = root->left; // make left sub tree of root to new root
	}
	strncpy(ret, str, strlen(str));
	final(root, str, ret, temp);
}

int main()
{
	FILE *fptr = fopen("./words.txt", "r"); // reading dictonary file
	if (fptr == NULL)
	{
		printf("Error openeing the file"); // print Error if not able to open the file
		exit(1);
	}
	
	struct node *root = NULL; // root node
	char a; // character to take word from user character by character
	char real[100] = ""; 
	char word[100] = ""; // user input

	// Insert wordlist file in tst
	while ((a = fgetc(fptr)) != EOF) 
	{
		if (a == '\n') // if word ends insert it
		{
			insert(&root, word);
			memset(word, 0, strlen(word)); // empty word after insertion in tst 
		}
		else
		{
			strncat(word, &a, 1); // Appends 1 character from a to word
		}
	}

	char s[100] = "";
	char c; // user input
	char cha;
	struct node *temp = root;
	while (c = getchar()) // Taking input from user
	{
		char **substr;
		c = tolower(c); 

		// if word terminates search word tst
		if (c == ' ' || c == '\n' || c == ',' || c == '.' || c == '!' || c == '?' || c == ';' || c == ':')
		{
			//if found return that word
			if (search(root, s))
			{
				printf("%s ", s);
			}
			// If not found print word with an underline
			else
			{
				suggest(root, s, real, temp); // Suggest word accoding to word prefix
				root = temp;
				printf(" \e[4m%s\e[0m ", s); // print word with underline
				// if we find a word to suggest print suggested word is not then no suggestion
				if (strlen(real) != 0) 
				{
					printf("(did you mean: ");
					printf("%s", real);
					printf(")");
				}
				memset(real, 0, strlen(real)); // empty real variable
			}
			memset(s, 0, strlen(s)); // empty s
		}
		else
		{
			strncat(s, &c, 1); // append 1 character from c pointer to s
		}
		int val = strcmp(s, "exit"); // if we type exit then exit the program
		if (val == 0)
			return 0;
	}
	printf("\n");
}