#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include "SequenceMap.h"
#include <fstream>
#include <string>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )         --> Insert x
// void remove( x )         --> Remove x
// int removeCalls( x )     --> Remove x and count how many recursive calls were made
// int getRemoves( )        --> Return number of removes made 
// bool contains( x )       --> Return true if x is present
// bool containsString(x,c) --> Return if recognition string is contained within tree and returns object
// bool containsString(x)   --> Return if recognition string is contained within tree
// int findCalls( x )       --> Return number of recursive calls made to find a reco sequence in the tree
// Comparable findMin( )    --> Return smallest item
// Comparable findMax( )    --> Return largest item
// boolean isEmpty( )       --> Return true if empty; else false
// void makeEmpty( )        --> Remove all items
// void printTree( )        --> Print tree in sorted order
// int nodeCount( )         --> Return number of nodes in the tree
// int internalPath (       --> Return internal path (all node paths added up)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
    int removes = 0;
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {   
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    //when object is needed
    bool containsString( const string x, Comparable *c){
         return containsString(x, root, c);
    }
    //just check if reco sequence is contained within tree
    bool containsString( const string x){
        Comparable c;
        bool value = containsString(x, root, &c);
        //Comparable *temp = &c;
        //delete temp;
        return value;
    }

    int findCalls(const string x){
        return findCalls(x, root, 0);
    }

    
    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }
    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    int nodeCount(){
        return nodeCount(root);
    }

    float internalPath(){
        return internalPath(root, 0);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    int removeCalls( const Comparable & x){
        return removeCalls( x, root, 1);
    }
    
    int getRemoves(){
        return removes;
    }

  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    BinaryNode *root;

    int nodeCount(BinaryNode *t){
        if(t == NULL) return 0;
        return (nodeCount(t->left) + nodeCount(t->right)) + 1;
    }

    float internalPath(BinaryNode *t, int total){
        if(t == NULL) return 0;
        if(t->left == NULL && t->right == NULL){
            return total + 1;
        }
        return total + (internalPath(t->left, total + 1) + internalPath(t->right, total + 1));
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else{
            t->element.Merge(x); // Duplicate
        }
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else{
            t->element.Merge(x);  // Duplicate
        }
             
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    int removeCalls( const Comparable & x, BinaryNode * & t, int calls )
    {
        calls++;
        if( t == nullptr )
            return calls;   // Item not found; do nothing
        if( x < t->element )
            return removeCalls( x, t->left, calls );
        else if( t->element < x )
            return removeCalls( x, t->right, calls );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            return removeCalls( t->element, t->right, calls );
        }
        else
        {
            removes++;
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }

        return calls;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */

    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */

    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }

    //dont need object, just checking if string is present
    // bool containsString( const string x, BinaryNode *t){
    //     if( t == nullptr )
    //         return false;
    //     else if( x < t->element.GetReco() ){
    //         find_calls++;
    //         return containsString( x, t->left );
    //     }   
    //     else if( t->element.GetReco() < x ){
    //         find_calls++;
    //         return containsString( x, t->right );
    //     }        
    //     else
    //         return true;    // Match

    // }

    
    //for returning object
    bool containsString( const string x, BinaryNode *t, Comparable *c){
        if( t == nullptr )
            return false;
        else if( x < t->element.GetReco() )
            return containsString( x, t->left, c );
        else if( t->element.GetReco() < x )
            return containsString( x, t->right, c );
        else{
            *c = t->element;
            return true;    // Match
        }
    }

    int findCalls( const string x, BinaryNode *t, int calls){
        calls++;
        if( t == nullptr )
            return 0;
        else if( x < t->element.GetReco() )
            return findCalls( x, t->left, calls );
        else if( t->element.GetReco() < x )
            return findCalls( x, t->right, calls );
        else{
            return calls;    // Match
        }
    }

    //Non-recursive version
    // while( t != nullptr ){
    //     if( x < t->element.GetReco() )
    //         t = t->left;
    //     else if( t->element.GetReco() < x )
    //         t = t->right;
    //     else{
    //         *c = t->element;
    //         return true;    // Match
    //     }
    // }
    // return false;
    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }

};

#endif
