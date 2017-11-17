// <Your name>
// Main file for Part2(b) of Homework 2.

#include "AvlTree.h"
#include "BinarySearchTree.h"
#include "SequenceMap.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <math.h>
using namespace std;

namespace {

// @db_filename: an input database filename.
// @seq_filename: an input sequences filename.
// @a_tree: an input tree of the type TreeType. It is assumed to be
//  empty.



fstream &GoToLine(fstream &file, int line){
  for(int i = 0; i < line-1; ++i){
    file.ignore(numeric_limits<streamsize>::max(), '\n');
  }
  return file;
}

template <typename TreeType>
int find(const string file, TreeType &a_tree, int *calls){
  int count = 0;
  fstream f(file);
  string sequence;
  while(f >> sequence){
    if(a_tree.containsString(sequence)) count++;
    *calls += a_tree.findCalls(sequence);
  }

  f.close();
  return count;
}

template <typename TreeType>
int removeSequences(const string file, TreeType &a_tree){
  int counter= 0, calls = 0;
  string seq;
  fstream f(file);

  while(f >> seq){
    if(counter % 2 == 0){
      SequenceMap temp;
      a_tree.containsString(seq, &temp);
      calls += a_tree.removeCalls(temp);
    }
    counter++;
  }

  f.close();
  return calls;
}

template <typename TreeType>
void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree) {
  // Code for running Part2(b)  
  fstream rebase(db_filename);
  //skips all the stuff in the beginning of the text file(credits and junk)
  GoToLine(rebase, 11);
  string db_line;

  //Populates tree 
  while(rebase >> db_line){
    db_line = db_line.substr(0, db_line.length()-2);
    stringstream ss;
    ss << db_line;
    string an_enz_acro, a_reco_seq;
    getline(ss, an_enz_acro, '/');

    while(getline(ss, a_reco_seq, '/')){
      SequenceMap new_map(a_reco_seq, an_enz_acro);
      a_tree.insert(new_map);
    }
  }

  //(2) Prints	the	number	of	nodes	in	your	tree	n.
  int node_count = a_tree.nodeCount();
  cout << "(2) Node count: " << node_count << endl;

  //(3)Computes the	average	depth of	your	search	tree,	i.e.	the	internal	path	length	
  //divided by n.

  //(3a) Printns the average depth.
  float average_depth = a_tree.internalPath()/a_tree.nodeCount();
  cout << "(3a) Average depth: " << average_depth << endl;

  //(3b)Prints	the	ratio	of	the	average	depth	to	log2𝑛.
  cout << "(3b) average depth/log2n: " << (average_depth/log2(node_count)) << endl;

  //(4) Searches (find())	the	tree	for	each	string	in	the	sequences.txt	file.	Also
  // counts	the	total	number	of recursive	calls	for	all	executions	of	find()
 
  //(4a) Prints	the	total	number	of	successful	queries	(number	of	strings	found).	
  int calls = 0;
  int success_queries = find(seq_filename, a_tree, &calls);
  cout << "(4a) Strings found: " << success_queries << endl;

  //(4b) Prints the	average	number	of	recursion	calls,	i.e.	#total	number	of	
  //recursion	calls	/	number	of	queries.
  float average_find_calls = (float)calls/(float)success_queries;
  cout << "(4b) Recursive calls: "  << average_find_calls << endl;
  

  //(5) Removes every	other	sequence in	sequences.txt from	the	tree.	Also	counts	the	
  //total	number	of	recursion	calls	for	all	executions	of	remove().
  
  cout << "\n Removed every other sequence in sequences.txt from the tree \n \n"; 

  //(5a) Prints	the	total	number	successful	removes.
  int remove_calls = removeSequences(seq_filename, a_tree);
  cout <<"(5a) Removes: " << a_tree.getRemoves() << endl;
  cout << "rmeove calls: " << remove_calls;
  //(5b) Prints the	average	number	of	recursion	calls,	i.e.	#total	number	of	
  //recursion	calls	/	number	of	remove	calls.
  float average_removes = (float)remove_calls/210;
  cout << "(5b) Average: " << average_removes << endl;


  //(6) Redo	steps	2 and	3:
  
  //(6a) Prints	number	of	nodes	in	your	tree
  node_count = a_tree.nodeCount();
  cout << "(6a) Node count: " << node_count << endl;

  //(6b) Prints	the	average	depth.
  average_depth = a_tree.internalPath()/a_tree.nodeCount();
  cout << "(6b) Average depth: " << average_depth << endl;

  //(6c) Prints	the ratio	of	the	average	depth	to	log2n
  cout << "(6c) average depth/log2n: " << (average_depth/log2(node_count)) << endl;
}


}  // namespace

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }

  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST") {
    // Note that you will replace BinarySearchTree<int> with BinarySearchTree<SequenceMap>
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else if (param_tree == "AVL") {
    // Note that you will replace AvlTree<int> with AvlTree<SequenceMap>
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  } else {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
