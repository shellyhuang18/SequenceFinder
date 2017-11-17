// Shelly Huang
// Main file for Part2(a) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace {

// @db_filename: an input filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.

//takes in file and skips to line line
fstream &GoToLine(fstream &file, int line){
  for(int i = 0; i < line-1; ++i){
    file.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return file;
}

template <typename TreeType>
void QueryTree(const string &db_filename, TreeType &a_tree) {
  // Code for running Part2(a)
  fstream f(db_filename);
  
  //skips all the stuff in the beginning of the text file(credits and junk)
  GoToLine(f, 11);
  string db_line;

  //FIRST PART(populate tree)
  while(f >> db_line){
    stringstream ss;
    ss << db_line;
    string an_enz_acro, a_reco_seq;
    getline(ss, an_enz_acro, '/');

    while(getline(ss, a_reco_seq, '/')){
      SequenceMap new_map(a_reco_seq, an_enz_acro);
      a_tree.insert(new_map);
    }
  }

  //SECOND PART
  string temp;
  while(cin >> temp){
    SequenceMap k;
    //returns bool but alters SequenceMap k to insert found element
    if(a_tree.containsString(temp, &k)) cout << k << endl;
    else cout << "Not Found" << endl;
  }

  f.close();
}

}  // namespace

int main(int argc, char **argv) {
  if (argc != 3) {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
