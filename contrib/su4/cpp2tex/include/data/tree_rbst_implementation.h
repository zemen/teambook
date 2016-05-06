/*
 * This file [data/tree_rbst_implementation.h] is part of the “libtamias” library
 * Copyright (c) 2007-2010 Oleg Davydov, Yury Petrov
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


// template RBSTreeNode

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>::RBSTreeNode( KeyType const &newKey ) : key(newKey), left(NULL), right(NULL), parent(NULL), size(1)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>::RBSTreeNode( RBSTreeNode const &node ) : key(node.key), left(node.left), right(node.right), parent(node.parent), size(node.size)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>& tamias::hidden::RBSTreeNode<KeyType>::operator = ( RBSTreeNode<KeyType> const &node )
  {
    key = node.key;
    left = node.left;
    right = node.rigth;
    parent = node.parent;
    size = node.size;
    return *this;
  }

template <typename KeyType>
  tamias::hidden::RBSTreeNode<KeyType>::~RBSTreeNode()
  {
  }


// template RBSTree

template <typename KeyType>
  tamias::RBSTree<KeyType>::RBSTree() : root(NULL), random()
  {
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>::RBSTree( RBSTree <KeyType> const &tree ) : root(NULL), random()
  {
    for (ConstIterator it = tree.begin(); it != tree.end(); it++)
      insert(*it);
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>& tamias::RBSTree<KeyType>::operator = ( RBSTree <KeyType> const &tree )
  {
    clear();
    for (ConstIterator it = tree.begin(); it != tree.end(); it++)
      insert(*it);
    return *this;
  }

template <typename KeyType>
  tamias::RBSTree<KeyType>::~RBSTree()
  {
    clear();
  }

template <typename KeyType>
  tamias::sizetype tamias::RBSTree<KeyType>::size() const
  {
    return root == NULL ? 0 : root->size;
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::insert( KeyType const &key )
  {
    return addKey(root, key);
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::erase( KeyType const &key )
  {
    TreeReference index = findKey(root, key);
    if (index == NULL)
      return false;
    TreeReference result = merge(index->left, index->right);
    if (index->parent != NULL) {
      (index->parent->left == index ? index->parent->left : index->parent->right) = result;
      result = result->parent = index->parent;
      while (result != NULL)
        recalc(result), result = result->parent;
    }
    else if (index == root) {
      root = result;
      if (result != NULL)
        result->parent = NULL;
    }
    else
      throw CommonException("RBSTree: internal error");
    delete index;
    return true;
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::find( KeyType const &key )
  {
    return findIterator(root, key);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::find( KeyType const &key ) const
  {
    return findIterator(root, key);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::findKth( sizetype k )
  {
    if (root->size <= k)
      return Iterator(NULL); // TODO: end-iterator is NOT null-iterator. it-- should work
    TreeReference vertex = root;
    while (true) {
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
    while (true) {
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
  tamias::sizetype tamias::RBSTree<KeyType>::count( KeyType const &key ) const
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
    TreeReference vertex = root, next;
    while (vertex != NULL) {
      if (vertex->left != NULL)
        next = vertex->left, vertex->left = NULL;
      else if (vertex->right != NULL)
        next = vertex->right, vertex->right = NULL;
      else {
        next = vertex->parent;
        delete vertex;
      }
      vertex = next;
    }
    root = NULL;
  }

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
  typename tamias::RBSTree<KeyType>::TreeReference tamias::RBSTree<KeyType>::merge( TreeReference left, TreeReference right )
  {
    if (left == NULL || right == NULL)
      return left != NULL ? left : right;
    if (random.next() % (left->size + right->size) < left->size) {
      left->right = merge(left->right, right);
      recalc(left);
      return left;
    } else {
      right->left = merge(left, right->left);
      recalc(right);
      return right;
    }
  }

template <typename KeyType>
  bool tamias::RBSTree<KeyType>::split( TreeReference vertex, TreeReference &left, TreeReference &right, KeyType const &value )
  {
    if (vertex == NULL) {
      left = right = NULL;
      return true;
    }
    if (value < vertex->key) {
      TreeReference tmpLeft, tmpRight;
      if (!split(vertex->left, tmpLeft, tmpRight, value))
        return false;
      left = tmpLeft;
      right = vertex;
      right->left = tmpRight;
      right->parent = NULL;
      recalc(right);
    }
    else if (vertex->key < value) {
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
  bool tamias::RBSTree<KeyType>::addKey( TreeReference &vertex, KeyType const &key )
  {
    bool result;
    if (vertex == NULL || random.next() % (vertex->size + 1) == 0u) {
      TreeReference tmpLeft, tmpRight;
      if (!split(vertex, tmpLeft, tmpRight, key))
        return false;
      vertex = new hidden::RBSTreeNode<KeyType>(key);
      vertex->left = tmpLeft;
      vertex->right = tmpRight;
      recalc(vertex);
      result = true;
    } else {
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
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::findIterator( TreeReference root, KeyType const &key )
  {
    while (root != NULL) {
      if (key < root->key)
        root = root->left;
      else if (root->key < key)
        root = root->right;
      else
        break;
    }
    return Iterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::Iterator tamias::RBSTree<KeyType>::beginIterator( TreeReference root )
  {
    while (root != NULL && root->left != NULL)
      root = root->left;
    return Iterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::findIterator( TreeReference root, KeyType const &key ) const
  {
    while (root != NULL) {
      if (key < root->key)
        root = root->left;
      else if (root->key < key)
        root = root->right;
      else
        break;
    }
    return ConstIterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::ConstIterator tamias::RBSTree<KeyType>::beginIterator( TreeReference root ) const
  {
    while (root != NULL && root->left != NULL)
      root = root->left;
    return ConstIterator(root);
  }

template <typename KeyType>
  typename tamias::RBSTree<KeyType>::TreeReference tamias::RBSTree<KeyType>::findKey( TreeReference vertex, KeyType const &key )
  {
    while (vertex != NULL) {
      if (key < vertex->key)
        vertex = vertex->left;
      else if (vertex->key < key)
        vertex = vertex->right;
      else
        break;
    }
    return vertex;
  }


// template RBSTreeIterator

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::RBSTreeIterator() : mNode(NULL)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::RBSTreeIterator( RBSTreeNode <KeyType> *node ) : mNode(node)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::RBSTreeIterator( RBSTreeIterator const &iterator ) : mNode(iterator.mNode)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>& tamias::hidden::RBSTreeIterator<KeyType>::operator = ( RBSTreeIterator const &iterator )
  {
    mNode = iterator.mNode;
    return *this;
  }

template <typename KeyType>
  tamias::hidden::RBSTreeIterator<KeyType>::~RBSTreeIterator()
  {
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeIterator<KeyType>::Reference tamias::hidden::RBSTreeIterator<KeyType>::operator * ()
  {
    // TODO: ? if (node == NULL) throw Exception ?
    return mNode->key;
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeIterator<KeyType>::Pointer tamias::hidden::RBSTreeIterator<KeyType>::operator -> ()
  {
    return mNode == NULL ? NULL : &(mNode->key);
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeIterator<KeyType> tamias::hidden::RBSTreeIterator<KeyType>::operator ++ ( int )
  {
    RBSTreeIterator result(*this);
    if (mNode == NULL)
      return result;
    if (mNode->right != NULL) {
      mNode = mNode->right;
      while (mNode->left != NULL)
        mNode = mNode->left;
    }
    else
      while (mNode != NULL) {
        RBSTreeNode<KeyType> *oldNode = mNode;
        mNode = mNode->parent;
        if (mNode == NULL || mNode->right != oldNode)
          break;
      }
    return result;
  }

template <typename KeyType>
  bool tamias::hidden::RBSTreeIterator<KeyType>::operator == ( RBSTreeIterator const &iterator ) const
  {
    return mNode == iterator.mNode;
  }

template <typename KeyType>
  bool tamias::hidden::RBSTreeIterator<KeyType>::operator != ( RBSTreeIterator const &iterator ) const
  {
    return mNode != iterator.mNode;
  }


// template RBSTreeConstIterator

template <typename KeyType>
  tamias::hidden::RBSTreeConstIterator<KeyType>::RBSTreeConstIterator() : mNode(NULL)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeConstIterator<KeyType>::RBSTreeConstIterator ( RBSTreeNode <KeyType> const *node ) : mNode(node)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeConstIterator<KeyType>::RBSTreeConstIterator( RBSTreeConstIterator const &iterator ) : mNode(iterator.mNode)
  {
  }

template <typename KeyType>
  tamias::hidden::RBSTreeConstIterator<KeyType>& tamias::hidden::RBSTreeConstIterator<KeyType>::operator = ( RBSTreeConstIterator const &iterator )
  {
    mNode = iterator.mNode;
    return *this;
  }

template <typename KeyType>
  tamias::hidden::RBSTreeConstIterator<KeyType>::~RBSTreeConstIterator()
  {
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeConstIterator<KeyType>::Reference tamias::hidden::RBSTreeConstIterator<KeyType>::operator * ()
  {
    // TODO: ? if (node == NULL) throw Exception ?
    return mNode->key;
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeConstIterator<KeyType>::Pointer tamias::hidden::RBSTreeConstIterator<KeyType>::operator -> ()
  {
    return mNode == NULL ? NULL : &(mNode->key);
  }

template <typename KeyType>
  typename tamias::hidden::RBSTreeConstIterator<KeyType> tamias::hidden::RBSTreeConstIterator<KeyType>::operator ++ ( int )
  {
    RBSTreeConstIterator result(*this);
    if (mNode == NULL)
      return result;
    if (mNode->right != NULL) {
      mNode = mNode->right;
      while (mNode->left != NULL)
        mNode = mNode->left;
    }
    else
      while (mNode != NULL) {
        const RBSTreeNode<KeyType> *oldNode = mNode;
        mNode = mNode->parent;
        if (mNode == NULL || mNode->right != oldNode)
          break;
      }
    return result;
  }

template <typename KeyType>
  bool tamias::hidden::RBSTreeConstIterator<KeyType>::operator == ( RBSTreeConstIterator const &iterator ) const
  {
    return mNode == iterator.mNode;
  }

template <typename KeyType>
  bool tamias::hidden::RBSTreeConstIterator<KeyType>::operator != ( RBSTreeConstIterator const &iterator ) const
  {
    return mNode != iterator.mNode;
  }

