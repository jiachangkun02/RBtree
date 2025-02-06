//
// Created by jiachangkun on 25-2-3.
//

#ifndef SET_H
#define SET_H

#endif //SET_H

#include "RBTree.h"
#pragma once
namespace jia
{
    template<class K>
    class set
    {
    public:
        struct SetofT
        {
            const K& operator()(const K& k)
            {
                return k;
            }
        };
        void _insert(const K& k)
        {
            return _t.insert(k);
        }
        void inoder()
        {
            _t.inorder();
        }
    private:
        RBtree<K,K,SetofT> _t;
    };

    void test_set()
    {
        jia::set<int> s;
        s._insert(4);
        s._insert(8);
        s._insert(9);
        s._insert(3);
        s._insert(6);
        s.inoder();
    }
}