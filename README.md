# Ternary tree
Ternary search tree is atype of trie(sometimes called prefix tree) where nodes are arranged in similar manner as in binary search. 
It has 3 child nodes. Each node has 3 pointers left, right and equal. Each node has a character variable data andBoolean variable. char variable stores characters of word which we inserted. Boolean variable shows weatherthe character in the node is end of any word that we have inserted in the ternary search.
 
# Spell checker using ternary tree
We have made a spell checker application using ternary search tree data structure.
To make a spell checkere we need a dictionary through which words can be checked if its correct or not. We will insert all the words of the dictionary into a ternary tree and ask the user to input a sentence. If there is any word in the sentence that is not present in ternary tree (by using search function) we will tell that spelling is incorrect. We also incorporated a suggestion function which will suggest a word that should be written whenthe spelling of the word is wrong. The suggestion string which our program outputs will contain the prefix as the wrong string. If there is no word that has prefix as the wrong string inputed, then program wont give any suggestion

## Getting started
* First you need to install c compiler of your choice
* clone the project
* compile and run the .c file
* You will write words/ sentence in terminal
* After you press enter the program will scan your sentence and search the word in wordlist
* It will print your word/paragraph and underlined the words which are not in our word list file (dictonary)
* To exit the program write **exit** in terminal

### Input
Any sentence / paragraph
* Eg: hi this is a spelling checking progr

### Output
hi this is a spelling checking progr(underlined) (did you mean: program)
* If type "exit" the program will terminate

## Example

![sample](https://user-images.githubusercontent.com/83273672/142764964-16c04f2f-20ab-4027-9c7c-d7e717f357d2.png)

