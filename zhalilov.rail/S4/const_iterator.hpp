#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

#include "node.hpp"

namespace zhalilov
{
  template < class Key, class T, class Compare >
  class TwoThreeTree < Key, T, Compare >;

  template < class T >
  class ConstTwoThreeIterator: public std::iterator < std::bidirectional_iterator_tag, const T >
  {
  public:
    ~ConstTwoThreeIterator() = default;

    ConstTwoThreeIterator &operator=(const ConstTwoThreeIterator &) = default;

    ConstTwoThreeIterator &operator++();
    ConstTwoThreeIterator &operator--();
    ConstTwoThreeIterator operator++(int);
    ConstTwoThreeIterator operator--(int);

    const T &operator*() const;
    const T *operator->() const;

    bool operator==(const ConstTwoThreeIterator < T > &) const;
    bool operator!=(const ConstTwoThreeIterator < T > &) const;

    template < class Key, class T, class Compare >
    friend TwoThreeTree < Key, T, Compare >;

  private:
    detail::Node < T > node_;
    bool isPtrToLeft_;

    explicit ConstTwoThreeIterator(detail::Node < T > *node, bool isPtrToLeft = true);
    detail::Node < T > *findMin(const detail::Node < T > *);
    detail::Node < T > *findMax(const detail::Node < T > *);
  };

  template < class T >
  ConstTwoThreeIterator < T > &ConstTwoThreeIterator < T >::operator++()
  {
    if (node_.type == detail::NodeType::Three)
    {
      if (isPtrToLeft_)
      {
        detail::Node < T > *minMid = findMin(node_.childs[1]);
        if (minMid == node_)
        {
          isPtrToLeft_ = false;
        }
        return *this;
      }
    }

    detail::Node < T > *minRight = findMin(node_.childs[2]);
    if (minRight == node_)
    {
      while (node_.parent->childs[2] == node_)
      {
        node_ = node_.parent;
      }
      isPtrToLeft_ = true;
    }
    else
    {
      node_ = minRight;
    }
    return *this;
  }

  template < class T >
  ConstTwoThreeIterator < T > &ConstTwoThreeIterator < T >::operator--()
  {
    if (node_.type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        detail::Node < T > *maxMid = findMax(node_.childs[1]);
        if (maxMid == node_)
        {
          isPtrToLeft_ = false;
        }
        return *this;
      }
    }

    detail::Node < T > *maxLeft = findMax(node_.childs[0]);
    if (maxLeft == node_)
    {
      while (node_.parent->childs[0] == node_)
      {
        node_ = node_.parent;
      }
      isPtrToLeft_ = false;
    }
    else
    {
      node_ = maxLeft;
    }
    return *this;
  }

  template < class T >
  ConstTwoThreeIterator < T > ConstTwoThreeIterator < T >::operator++(int)
  {
    ConstTwoThreeIterator temp(*this);
    operator++();
    return temp;
  }

  template < class T >
  ConstTwoThreeIterator < T > ConstTwoThreeIterator < T >::operator--(int)
  {
    ConstTwoThreeIterator temp(*this);
    operator--();
    return temp;
  }

  template < class T >
  const T &ConstTwoThreeIterator < T >::operator*() const
  {
    if (node_.type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        return node_.values[1];
      }
    }
    return node_.values[0];
  }

  template < class T >
  const T *ConstTwoThreeIterator < T >::operator->() const
  {
    if (node_.type == detail::NodeType::Three)
    {
      if (!isPtrToLeft_)
      {
        return node_.values[1];
      }
    }
    return *node_.values[0];
  }

  template < class T >
  bool ConstTwoThreeIterator < T >::operator==(const ConstTwoThreeIterator < T > &ait) const
  {
    bool isEqualValue = true;
    if (node_.type == detail::NodeType::Three)
    {
      isEqualValue = ait.isPtrToLeft_ == isPtrToLeft_;
    }
    return ait.node_ == node_ && isEqualValue;
  }

  template < class T >
  bool ConstTwoThreeIterator < T >::operator!=(const ConstTwoThreeIterator < T > &ait) const
  {
    return !operator==(ait);
  }

  template < class T >
  ConstTwoThreeIterator < T >::ConstTwoThreeIterator(detail::Node < T > *node, bool isPtrToLeft):
    node_(node),
    isPtrToLeft_(isPtrToLeft)
  {}

  template < class T >
  detail::Node < T > *ConstTwoThreeIterator < T >::findMin(const detail::Node < T > *nodeFrom)
  {
    detail::Node < T > *minNode = nodeFrom;
    while (minNode->childs[0])
    {
      minNode = minNode->childs[0];
    }
    return minNode;
  }

  template < class T >
  detail::Node < T > *ConstTwoThreeIterator < T >::findMax(const detail::Node < T > *nodeFrom)
  {
    detail::Node < T > *maxNode = nodeFrom;
    while (maxNode->childs[2])
    {
      maxNode = maxNode->childs[2];
    }
    return maxNode;
  }
}

#endif

#endif