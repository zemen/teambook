/*
 * This file [data/tree_rbst.h] is part of the “libtamias” library
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

#pragma once

namespace tamias {
  namespace hidden {
    template <typename KeyType> struct RBSTreeNode;
  }
  template <typename KeyType> class RBSTree; // http://en.wikipedia.org/wiki/Randomized_binary_search_tree
  namespace hidden {
    template <typename KeyType> class RBSTreeIterator;
    template <typename KeyType> class RBSTreeConstIterator;
  }
}

#include "../basic/exception.h"
#include "../basic/types.h"
#include "../main/random_lcg.h" // TODO: setup random and do not make cross-links between sections

template <typename KeyType>
  struct tamias::hidden::RBSTreeNode {
    KeyType key;
    RBSTreeNode *left, *right, *parent;
    sizetype size;

    RBSTreeNode( KeyType const &newKey = KeyType() );
    RBSTreeNode( RBSTreeNode const &node );
    RBSTreeNode& operator = ( RBSTreeNode const &node );
    ~RBSTreeNode();
  };

template <typename KeyType>
  class tamias::RBSTree {
    public:
      typedef KeyType* Pointer;
      typedef KeyType& Reference;
      typedef KeyType const* ConstPointer;
      typedef KeyType const& ConstReference;
      typedef hidden::RBSTreeIterator<KeyType> Iterator;
      typedef hidden::RBSTreeConstIterator<KeyType> ConstIterator;

    public:
      RBSTree();
      RBSTree( RBSTree const &tree );
      RBSTree& operator = ( RBSTree const &tree );
      ~RBSTree();

      sizetype size() const;
      bool insert( KeyType const &value );
      bool erase( KeyType const &value );

      Iterator find( KeyType const &value );
      ConstIterator find( KeyType const &value ) const;
      Iterator findKth( sizetype k );
      ConstIterator findKth( sizetype k ) const;
      sizetype count( const KeyType &value ) const;

      Iterator begin();
      Iterator end();
      ConstIterator begin() const;
      ConstIterator end() const;

      void clear();

    private:
      typedef hidden::RBSTreeNode<KeyType>* TreeReference;
      TreeReference root;
      LCGRandom random;

      void recalc( TreeReference node );
      TreeReference merge( TreeReference first, TreeReference second );
      bool split( TreeReference root, TreeReference &left, TreeReference &right , KeyType const &splitter );
      bool addKey( TreeReference &root, KeyType const &value );
      Iterator beginIterator( TreeReference root );
      ConstIterator beginIterator( TreeReference root ) const;
      Iterator findIterator( TreeReference root, KeyType const &value );
      ConstIterator findIterator( TreeReference root, KeyType const &value ) const;
      TreeReference findKey( TreeReference root, KeyType const &value );
  };

template <typename KeyType>
  class tamias::hidden::RBSTreeIterator {
    public:
      typedef typename RBSTree<KeyType>::Pointer Pointer;
      typedef typename RBSTree<KeyType>::Reference Reference;

    public:
      RBSTreeIterator();
      RBSTreeIterator( RBSTreeNode <KeyType> *node );
      RBSTreeIterator( RBSTreeIterator const &iterator );
      RBSTreeIterator& operator = ( RBSTreeIterator const &iterator );
      ~RBSTreeIterator();

      Reference operator * ();
      Pointer operator -> ();
      // TODO: all operators

      RBSTreeIterator& operator ++ ();
      RBSTreeIterator operator ++ ( int );
      RBSTreeIterator& operator -- ();
      RBSTreeIterator operator -- ( int );
      bool operator == ( RBSTreeIterator const &iterator ) const;
      bool operator != ( RBSTreeIterator const &iterator ) const;

    private:
      RBSTreeNode<KeyType> *mNode;
  };

template <typename KeyType>
  class tamias::hidden::RBSTreeConstIterator {
    public:
      typedef typename RBSTree<KeyType>::ConstPointer Pointer;
      typedef typename RBSTree<KeyType>::ConstReference Reference;

    public:
      RBSTreeConstIterator();
      RBSTreeConstIterator( RBSTreeNode <KeyType> const *node );
      RBSTreeConstIterator( RBSTreeConstIterator const &iterator );
      RBSTreeConstIterator& operator = ( RBSTreeConstIterator const &iterator );
      ~RBSTreeConstIterator();

      Reference operator * ();
      Pointer operator -> ();

      RBSTreeConstIterator& operator ++ ();
      RBSTreeConstIterator operator ++ ( int );
      RBSTreeConstIterator& operator -- ();
      RBSTreeConstIterator operator -- ( int );
      bool operator == ( const RBSTreeConstIterator &iterator ) const;
      bool operator != ( const RBSTreeConstIterator &iterator ) const;

    private:
      RBSTreeNode<KeyType> const *mNode;
  };

#include "tree_rbst_implementation.h"

