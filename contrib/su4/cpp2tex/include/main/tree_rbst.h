/*
 * This file [main/tree_rbst.h] is part of the “libtamias” library
 * Copyright (c) 2007-2009 Oleg Davydov, Yury Petrov
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Our contacts:
 *   mailto: burunduk3@gmail.com (Oleg Davydov)
 *   mailto: jpsbur@gmail.com (Yury Petrov)
 */

#pragma once

#include <cstdlib>
#include "../basic/iterator.h"

namespace tamias
{
  /* http://en.wikipedia.org/wiki/Randomized_binary_search_tree */
  template <typename KeyType>
    class RBSTree;

  namespace hidden
  {
    template <typename KeyType>
      struct RBSTreeNode
      {
        KeyType key;
        RBSTreeNode *left, *right, *parent;
        sizetype size;
        RBSTreeNode( const KeyType &newKey = KeyType() );
        RBSTreeNode( const RBSTreeNode& node );
        ~RBSTreeNode();
        RBSTreeNode& operator = ( const RBSTreeNode &node );
      };

    template <typename KeyType>
      class RBSTreeIterator
      {
        public:
          typedef KeyType* Pointer;
          typedef KeyType& Reference;
        private:
          RBSTreeNode<KeyType> *node;
        public:
          RBSTreeIterator();
          RBSTreeIterator( RBSTreeNode<KeyType> *node );
          RBSTreeIterator( const RBSTreeIterator &iterator );
          ~RBSTreeIterator();
          RBSTreeIterator& operator = ( const RBSTreeIterator &iterator );

          Reference operator * ();
          Pointer operator -> ();
          // TODO: all operators

          RBSTreeIterator& operator ++ ();
          RBSTreeIterator operator ++ ( int );
          RBSTreeIterator& operator -- ();
          RBSTreeIterator operator -- ( int );
          bool operator == ( const RBSTreeIterator &iterator ) const;
          bool operator != ( const RBSTreeIterator &iterator ) const;
      };

    template <typename KeyType>
      class ConstRBSTreeIterator
      {
        public:
          typedef const KeyType* Pointer;
          typedef const KeyType& Reference;
        private:
          const RBSTreeNode<KeyType> *node;
        public:
          ConstRBSTreeIterator();
          ConstRBSTreeIterator( const RBSTreeNode<KeyType> *node );
          ConstRBSTreeIterator( const ConstRBSTreeIterator &iterator );
          ~ConstRBSTreeIterator();
          ConstRBSTreeIterator& operator = ( const ConstRBSTreeIterator &iterator );

          Reference operator * ();
          Pointer operator -> ();

          ConstRBSTreeIterator& operator ++ ();
          ConstRBSTreeIterator operator ++ ( int );
          ConstRBSTreeIterator& operator -- ();
          ConstRBSTreeIterator operator -- ( int );
          bool operator == ( const ConstRBSTreeIterator &iterator ) const;
          bool operator != ( const ConstRBSTreeIterator &iterator ) const;
      };
  }

  template <typename KeyType>
    class RBSTree
    {
      public:
        typedef hidden::RBSTreeIterator<KeyType> Iterator;
        typedef hidden::ConstRBSTreeIterator<KeyType> ConstIterator;
      private:
        typedef hidden::RBSTreeNode<KeyType> *TreeReference;
        TreeReference root;

        void recalc( TreeReference node );
        TreeReference merge( TreeReference first, TreeReference second );
        bool split( TreeReference root, TreeReference &left, TreeReference &right , const KeyType &splitter );
        bool addKey( TreeReference &root, const KeyType &value );
        Iterator beginIterator( TreeReference root );
        Iterator findIterator( TreeReference root, const KeyType &value );
        ConstIterator beginIterator( TreeReference root ) const;
        ConstIterator findIterator( TreeReference root, const KeyType &value ) const;
        TreeReference findKey( TreeReference root, const KeyType &value );
      public:
        RBSTree();
        RBSTree( const RBSTree &tree );
        ~RBSTree();
        RBSTree& operator = ( const RBSTree &tree );

        sizetype size() const;
        bool add( const KeyType &value ); // [TODO] ? insert
        bool erase( const KeyType &value );
        Iterator find( const KeyType &value );
        ConstIterator find( const KeyType &value ) const;
        Iterator findKth( sizetype k );
        ConstIterator findKth( sizetype k ) const;
        sizetype count( const KeyType &value ) const;
        Iterator begin();
        Iterator end();
        ConstIterator begin() const;
        ConstIterator end() const;

        void clear();
    };
}

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>::RBSTreeNode( const KeyType &newKey )
                : key(newKey), left(NULL), right(NULL), parent(NULL), size(1)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>::RBSTreeNode( const RBSTreeNode &node )
                : key(node.key), left(node.left), right(node.right), parent(node.parent), size(node.size)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>::~RBSTreeNode()
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>&
  tamias::hidden::RBSTreeNode<KeyType>::operator = ( const RBSTreeNode<KeyType> &node )
  {
    key = node.key;
    left = node.left;
    right = node.rigth;
    parent = node.parent;
    size = node.size;
    return *this;
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::RBSTreeIterator() : node(NULL)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::RBSTreeIterator( RBSTreeNode<KeyType> *newNode ) : node(newNode)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::RBSTreeIterator( const RBSTreeIterator &iterator )
                : node(iterator.node)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::~RBSTreeIterator()
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>&
  tamias::hidden::RBSTreeIterator<KeyType>::operator = ( const RBSTreeIterator &iterator )
  {
    node = iterator.node;
    return *this;
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeIterator<KeyType>::Reference
           tamias::hidden::RBSTreeIterator<KeyType>::operator * ()
  {
    // TODO: ? if (node == NULL) throw Exception ?
    return node->key;
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeIterator<KeyType>::Pointer
           tamias::hidden::RBSTreeIterator<KeyType>::operator -> ()
  {
    return node == NULL ? NULL : &(node->key);
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeIterator<KeyType>
           tamias::hidden::RBSTreeIterator<KeyType>::operator ++ ( int )
  {
    RBSTreeIterator result(*this);
    if (node == NULL)
      return result;
    if (node->right != NULL)
    {
      node = node->right;
      while (node->left != NULL)
        node = node->left;
    }
    else
      while (node != NULL)
      {
        RBSTreeNode<KeyType> *oldNode = node;
        node = node->parent;
        if (node == NULL || node->right != oldNode)
          break;
      }
    return result;
  }

template <typename KeyType>
  bool tamias::hidden::RBSTreeIterator<KeyType>::operator == ( const RBSTreeIterator &iterator ) const
  {
    return node == iterator.node;
  }

template <typename KeyType>
  bool tamias::hidden::RBSTreeIterator<KeyType>::operator != ( const RBSTreeIterator &iterator ) const
  {
    return node != iterator.node;
  }

template <typename KeyType>
  tamias::hidden::ConstRBSTreeIterator<KeyType>::ConstRBSTreeIterator() : node(NULL)
  {
  }

template <typename KeyType>
  tamias::hidden::ConstRBSTreeIterator<KeyType>::ConstRBSTreeIterator ( const RBSTreeNode<KeyType> *newNode )
                : node(newNode)
  {
  }

template <typename KeyType>
  tamias::hidden::ConstRBSTreeIterator<KeyType>::ConstRBSTreeIterator( const ConstRBSTreeIterator &iterator )
                                               : node(iterator.node)
  {
  }

template <typename KeyType>
  tamias::hidden::ConstRBSTreeIterator<KeyType>::~ConstRBSTreeIterator()
  {
  }

template <typename KeyType>
  tamias::hidden::ConstRBSTreeIterator<KeyType>&
  tamias::hidden::ConstRBSTreeIterator<KeyType>::operator = ( const ConstRBSTreeIterator &iterator )
  {
    node = iterator.node;
    return *this;
  }

template <typename KeyType>
  typename tamias::hidden::ConstRBSTreeIterator<KeyType>::Reference
           tamias::hidden::ConstRBSTreeIterator<KeyType>::operator * ()
  {
    // TODO: ? if (node == NULL) throw Exception ?
    return node->key;
  }

template <typename KeyType>
  typename tamias::hidden::ConstRBSTreeIterator<KeyType>::Pointer
           tamias::hidden::ConstRBSTreeIterator<KeyType>::operator -> ()
  {
    return node == NULL ? NULL : &(node->key);
  }

template <typename KeyType>
  typename tamias::hidden::ConstRBSTreeIterator<KeyType>
           tamias::hidden::ConstRBSTreeIterator<KeyType>::operator ++ ( int )
  {
    ConstRBSTreeIterator result(*this);
    if (node == NULL)
      return result;
    if (node->right != NULL)
    {
      node = node->right;
      while (node->left != NULL)
        node = node->left;
    }
    else
      while (node != NULL)
      {
        const RBSTreeNode<KeyType> *oldNode = node;
        node = node->parent;
        if (node == NULL || node->right != oldNode)
          break;
      }
    return result;
  }

template <typename KeyType>
  bool tamias::hidden::ConstRBSTreeIterator<KeyType>::operator == ( const ConstRBSTreeIterator &iterator ) const
  {
    return node == iterator.node;
  }

template <typename KeyType>
  bool tamias::hidden::ConstRBSTreeIterator<KeyType>::operator != ( const ConstRBSTreeIterator &iterator ) const
  {
    return node != iterator.node;
  }

/* template RBSTree */
template <typename KeyType>
  void tamias::RBSTree<KeyType>::recalc( TreeReference vertex )
  {
    if (vertex == NULL)
      return;
    sizetype size = 1;
    if (vertex->left != NULL)
    {
      size += vertex->left->size;
      vertex->left->parent = vertex;
    }
    if (vertex->right != NULL)
    {
      size += vertex->right->size;
      vertex->right->parent = vertex;
    }
    vertex->size = size;
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::TreeReference
           tamias::RBSTree<KeyType>::merge( TreeReference left, TreeReference right )
  {
    if (left == NULL || right == NULL)
      return left != NULL ? left : right;
    if (rand() % (left->size + right->size) < left->size)
    {
      left->right = merge(left->right, right);
      recalc(left);
      return left;
    }
    else
    {
      right->left = merge(left, right->left);
      recalc(right);
      return right;
    }
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::split( TreeReference vertex, TreeReference &left, TreeReference &right,
                                        const KeyType &value )
  {
    if (vertex == NULL)
    {
      left = right = NULL;
      return true;
    }
    if (value < vertex->key)
    {
      TreeReference tmpLeft, tmpRight;
      if (!split(vertex->left, tmpLeft, tmpRight, value))
        return false;
      left = tmpLeft;
      right = vertex;
      right->left = tmpRight;
      right->parent = NULL;
      recalc(right);
    }
    else if (vertex->key < value)
    {
      TreeReference tmpLeft, tmpRight;
      if (!split(vertex->right, tmpLeft, tmpRight, value))
        return false;
      left = vertex;
      right = tmpRight;
      left->right = tmpLeft;
      left->parent = NULL;
      recalc(left);
    }
    else
      return false;
    return true;
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::addKey( TreeReference &vertex, const KeyType &key )
  {
    bool result;
    if (vertex == NULL || rand() % (vertex->size + 1) == 0u)
    {
      TreeReference tmpLeft, tmpRight;
      if (!split(vertex, tmpLeft, tmpRight, key))
        return false;
      vertex = new tamias::hidden::RBSTreeNode<KeyType>(key);
      vertex->left = tmpLeft;
      vertex->right = tmpRight;
      recalc(vertex);
      result = true;
    }
    else
    {
      if (key < vertex->key)
        result = addKey(vertex->left, key);
      else if (vertex->key < key)
        result = addKey(vertex->right, key);
      else
        result = false;
      if (result)
        recalc(vertex);
    }
    return result;
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator
           tamias::RBSTree<KeyType>::findIterator( TreeReference root, const KeyType &key )
  {
    if (root == NULL)
      return Iterator(NULL);
    if (key < root->key)
      return findIterator(root->left, key);
    if (root->key < key)
      return findIterator(root->right, key);
    return Iterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::beginIterator( TreeReference root )
  {
    if (root == NULL)
      return Iterator(NULL);
    if (root->left != NULL)
      return beginIterator(root->left);
    return Iterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator
           tamias::RBSTree<KeyType>::findIterator( TreeReference root, const KeyType &key ) const
  {
    if (root == NULL)
      return ConstIterator(NULL);
    if (key < root->key)
      return findIterator(root->left, key);
    if (root->key < key)
      return findIterator(root->right, key);
    return ConstIterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::beginIterator( TreeReference root ) const
  {
    if (root == NULL)
      return ConstIterator(NULL);
    if (root->left != NULL)
      return beginIterator(root->left);
    return ConstIterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::TreeReference
           tamias::RBSTree<KeyType>::findKey( TreeReference vertex, const KeyType &key )
  {
    if (vertex == NULL)
      return NULL;
    if (key < vertex->key)
      return findKey(vertex->left, key);
    if (vertex->key < key)
      return findKey(vertex->right, key);
    return vertex;
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>::RBSTree() : root(NULL)
  {
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>::RBSTree( const RBSTree &tree ) : root(tree.root)
  {
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>::~RBSTree()
  {
    // !!!TODO!!! : free memory!
//     printf("---\n");
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>& tamias::RBSTree<KeyType>::operator = ( const RBSTree &tree )
  {
    root = tree.root; // TODO: это что за приколы?
    return *this;
  }

template <typename KeyType>
  tamias::sizetype tamias::RBSTree<KeyType>::size() const
  {
    return root == NULL ? 0 : root->size;
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::add( const KeyType &key )
  {
    return addKey(root, key);
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::erase( const KeyType &key )
  {
    TreeReference index = findKey(root, key);
    if (index == NULL)
      return false;
    TreeReference result = merge(index->left, index->right);
    if (index->parent != NULL)
    {
      (index->parent->left == index ? index->parent->left : index->parent->right) = result;
      result = index->parent;
      while (result != NULL)
        recalc(result), result = result->parent;
    }
    else if (index == root)
    {
      root = result;
      if (result != NULL)
        result->parent = NULL;
    }
    else
    {
      // TODO maybe an assert?
    }
    delete index;
    return true;
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::find( const KeyType& key )
  {
    return findIterator(root, key);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::find( const KeyType& key ) const
  {
    return findIterator(root, key);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::findKth( sizetype k )
  {
    if (root->size <= k)
      return Iterator(NULL); // TODO: end-iterator is NOT null-iterator
    TreeReference vertex = root;
    while (true)
    {
      sizetype cntLeft = vertex->left == NULL ? 0 : vertex->left->size;
      if (k < cntLeft)
        vertex = vertex->left;
      else if (k > cntLeft)
        vertex = vertex->right, k -= cntLeft + 1;
      else
        return Iterator(vertex);
    }
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::findKth( sizetype k ) const
  {
    if (root->size >= k)
      return ConstIterator(NULL); // TODO: end-iterator is NOT null-iterator
    TreeReference vertex = root;
    while (true)
    {
      sizetype cntLeft = vertex->left == NULL ? 0 : vertex->left->size;
      if (k < cntLeft)
        vertex = vertex->left;
      else if (k > cntLeft)
        vertex = vertex->right, k -= cntLeft + 1;
      else
        return ConstIterator(vertex);
    }
  }

template <typename KeyType>
  tamias::sizetype tamias::RBSTree<KeyType>::count( const KeyType& key ) const
  {
    return findIterator(root, key) == ConstIterator(NULL) ? 0 : 1;
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::begin()
  {
    return beginIterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::end()
  {
    return Iterator(NULL);
    // TODO ^^ This is wrong.
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::begin() const
  {
    return beginIterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::end() const
  {
    return ConstIterator(NULL);
  }

template <typename KeyType>
  void tamias::RBSTree<KeyType>::clear()
  {
    // !!!TODO!!! free memory
    root = NULL;
  }

