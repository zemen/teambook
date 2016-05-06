/*
 * This file [data/pair_implementation.h] is part of the “libtamias” library
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

template <typename TypeA, typename TypeB>
  tamias::Pair<TypeA, TypeB>::Pair() : first(), second()
  {
  }

template <typename TypeA, typename TypeB>
  tamias::Pair<TypeA, TypeB>::Pair( TypeA const &newFirst, TypeB const &newSecond ) : first(newFirst), second(newSecond)
  {
  }

template <typename TypeA, typename TypeB>
  template <typename newTypeA, typename newTypeB>
    tamias::Pair<TypeA, TypeB>::Pair( Pair <newTypeA, newTypeB> const &pair ) : first(pair.first), second(pair.second)
    {
    }

template <typename TypeA, typename TypeB>
  tamias::Pair <TypeA, TypeB>& tamias::Pair<TypeA, TypeB>::operator = ( Pair <TypeA, TypeB> const &pair )
  {
    first = pair.first;
    second = pair.second;
    return *this;
  }

template <typename TypeA, typename TypeB>
  tamias::Pair<TypeA, TypeB>::~Pair()
  {
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair<TypeA, TypeB>::operator < ( Pair const &pair ) const
  {
    if (first < pair.first)
      return true;
    if (pair.first < first)
      return false;
    return second < pair.second;
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair<TypeA, TypeB>::operator <= ( Pair const &pair ) const
  {
    if (first < pair.first)
      return true;
    if (pair.first < first)
      return false;
    return !(pair.second < second);
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair<TypeA, TypeB>::operator > ( Pair const &pair ) const
  {
    if (first < pair.first)
      return false;
    if (pair.first < first)
      return true;
    return pair.second < second;
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair<TypeA, TypeB>::operator >= ( Pair const &pair ) const
  {
    if (first < pair.first)
      return false;
    if (pair.first < first)
      return true;
    return !(second < pair.second);
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair<TypeA, TypeB>::operator == ( Pair const &pair ) const
  {
    if (first < pair.first || pair.first < first)
      return false;
    if (second < pair.second || pair.second < second)
      return false;
    return true;
  }

template <typename TypeA, typename TypeB>
  bool tamias::Pair<TypeA, TypeB>::operator != ( Pair const &pair ) const
  {
    if (first < pair.first || pair.first < first)
      return true;
    if (second < pair.second || pair.second < second)
      return true;
    return false;
  }

template <typename TypeA, typename TypeB>
  tamias::Pair <TypeA, TypeB> tamias::makePair( TypeA const &first, TypeB const &second )
  {
    return Pair<TypeA, TypeB>(first, second);
  }

