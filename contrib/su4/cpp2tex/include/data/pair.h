/*
 * This file [main/pair.h] is part of the “libtamias” library
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

namespace tamias
{
  template <typename TypeA, typename TypeB>
    class Pair
    {
      public:
        TypeA first;
        TypeB second;
        Pair();
        Pair( const TypeA &newFirst , const TypeB &newSecond );
        template <typename newTypeA, typename newTypeB>
          Pair( const Pair <newTypeA, newTypeB> &source );
        Pair <TypeA, TypeB>& operator = ( const Pair <TypeA, TypeB> &source);
        ~Pair();
        bool operator < ( const Pair &pair ) const;
    };

  template <typename TypeA, typename TypeB>
    Pair <TypeA, TypeB> makePair( const TypeA &first, const TypeB &second );
}

template <typename TypeA, typename TypeB>
  tamias::Pair<TypeA, TypeB>::Pair() : first(), second()
  {
  }

template <typename TypeA, typename TypeB>
  tamias::Pair <TypeA, TypeB> ::Pair( const TypeA &newFirst, const TypeB &newSecond ) : first(newFirst), second(newSecond)
  {
  }

template <typename TypeA, typename TypeB>
  template <typename newTypeA, typename newTypeB>
    tamias::Pair <TypeA, TypeB> ::Pair( const Pair <newTypeA, newTypeB> &source )
                                : first(source.first), second(source.second)
    {
    }

template <typename TypeA, typename TypeB>
  tamias::Pair <TypeA, TypeB>& tamias::Pair <TypeA, TypeB> ::operator = ( const Pair <TypeA, TypeB> &source )
  {
    first = source.first;
    second = source.second;
    return *this;
  }

template <typename TypeA, typename TypeB>
  tamias::Pair <TypeA, TypeB> ::~Pair()
  {
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair <TypeA, TypeB> ::operator < ( const Pair &pair ) const
  {
    if (first < pair.first)
      return true;
    if (pair.first < first)
      return false;
    return second < pair.second;
  }

template <typename TypeA, typename TypeB>
  tamias::Pair <TypeA, TypeB> tamias::makePair( const TypeA &first, const TypeB &second )
  {
    return Pair <TypeA, TypeB> (first, second);
  }

