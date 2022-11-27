// Huffman Coding using Greedy Algorithm
// Author : mufasa159
// Email  : ma4590@rit.edu
// Date   : Nov 27, 2022

#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;


// node for creating tree
struct node {
  char data;
  int frequency;
  node *leftChild, *rightChild;
};


// for comparing two nodes and choosing the
// item with lowest frequency first
struct compareNodes {
  bool operator()(node *left, node *right) {
    return left->frequency > right->frequency;
  };
};


// for getting a tree node
node* getNode(char data, int frequency, node *leftChild, node *rightChild) {
  node *newNode = new node();
  newNode->data = data;
  newNode->frequency = frequency;
  newNode->leftChild = leftChild;
  newNode->rightChild = rightChild;
  return newNode;
};


// for generating huffman code strings (ex. 1011)
void toHuffmanCode(node *root, string huffmanCode, map<char, string> &codePairs) {
  // do nothing if node is empty
  if (root == nullptr) {
		return;
  };
  
  // check if leaf node exist in root node
  if (!root->leftChild && !root->rightChild) {
    codePairs[root->data] = huffmanCode;
  };
  
  toHuffmanCode(root->leftChild, huffmanCode + "0", codePairs);
  toHuffmanCode(root->rightChild, huffmanCode + "1", codePairs);
};


// generate and traverse tree to return Huffman 
// Codes for each character in user input
map<char, string> HuffmanCodes(map<char, int> data) {
  // initialize node pointers
  struct node *left, *right, *top;
  
  // stores tree nodes
  priority_queue<node*, vector<node*>, compareNodes> tree;

  // add nodes to tree
  for (auto pair: data) {
    tree.push(getNode(pair.first, pair.second, nullptr, nullptr));
  };

  // while node exist in tree, keep running
  while (tree.size() != 1) {
    // remove low frequency items from queue
    left = tree.top();
    tree.pop();
    right = tree.top();
    tree.pop();

    // create a new node with added frequency of two 
    // previous nodes then add it to the queue
		tree.push(getNode('\0', left->frequency + right->frequency, left, right));
	};

  // stores character and encoded value
  map<char, string> codePairs;

  // stores generated Huffman Codes for each character in codePairs map
  toHuffmanCode(tree.top(), "", codePairs);

  return codePairs;
};


// main funciton of the program
int main() {
  string userInput;                       // store user input
  cout << "Enter a string: " << endl;     // display prompt on terminal
  getline(cin, userInput);                // get user input line

  // store character and calculated frequency data in a map
  map<char, int> data;
	for (char ch: userInput) {
		data[ch]++;
	};

  // generate huffman Codes for all characters in user input string
  map<char, string> huffmanCodes = HuffmanCodes(data);

  // display encoded character values on terminal
  cout << endl << "Huffman Codes: " << endl;
  for (auto pair: huffmanCodes) {
		cout << pair.first << "   " << pair.second << endl;
	};
};
