/*
 * This file [data/flyweight.h] is part of the “libtamias” library
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

template <typename Type>
  tamias::Flyweight<Type>::Flyweight() : mData(new Data)
  {
    mData->counter = 1;
  }

template <typename Type>
  tamias::Flyweight<Type>::Flyweight( Flyweight const &fly ) : mData(fly.mData)
  {
    mData->counter++;
  }

template <typename Type>
  tamias::Flyweight<Type>& tamias::Flyweight<Type>::operator = ( Flyweight const &fly )
  {
    if (--mData->counter == 0)
      delete mData;
    mData = fly.mData;
    mData->counter++;
    return *this;
  }

template <typename Type>
  tamias::Flyweight<Type>::~Flyweight()
  {
    if (--mData->counter == 0)
      delete mData;
  }

template <typename Type>
  Type& tamias::Flyweight<Type>::data()
  {
    return mData->data;
  }

template <typename Type>
  Type const& tamias::Flyweight<Type>::data() const
  {
    return mData->data;
  }

