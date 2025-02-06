//
// Created by jiachangkun on 25-2-3.
//

#ifndef MAP_H
#define MAP_H

#endif //MAP_H

#include"RBTree.h"
#pragma once

namespace jia
{
    template<class K,class V>
    class map
    {
    public:
        struct MapofT
        {
            const K& operator()(const pair<K,V>& kv)
            {
                return kv.first;
            }
        };
        void _insert(const pair<K,V>&  kv)
        {
            return _t.insert(kv);
        }

    private:
        RBtree<K,pair<K,V>,MapofT> _t;
    };

    void test_map()
    {
        jia::map<int,int> m;
        m._insert(make_pair(4,5));
        m._insert(make_pair(8,7));
        m._insert(make_pair(6,1));
        m._insert(make_pair(4,3));


    }
}