#include <iostream>
#include <cstring>

#include "../AMLString.h"

namespace AMCore {

_T_AM_StringList* _T_AM_StringList::_M_root = nullptr;

_T_AM_StringList::_T_AM_StringList(const uint64_t tableHash) :
    _M_name_hash(tableHash)
{
    if (!_M_root) {
        _M_root=this;
        _M_next=0;
    }
    else {
        _T_AM_StringList* pp = _M_root;
        _T_AM_StringList** plast = &_M_root;
        while (pp && pp->_M_name_hash < tableHash) {
            plast = &(pp->_M_next);
            pp = pp->_M_next;
        }
        *plast = this;
        _M_next = pp;
    }
    _M_next_chunk = this;
}

_T_AM_StringList::~_T_AM_StringList() {}

_T_AM_StringList* _T_AM_StringList::GetStringTable(const uint64_t nameHash)
{
    _T_AM_StringList* pp = _M_root;
    while (pp)
    {
        if (pp->_M_name_hash == nameHash)
            return pp;
        pp = pp->_M_next;
    }
    return nullptr;
}

_T_AM_StringList* _T_AM_StringList::GetStringTable(const char* name)
{
    return _T_AM_StringList::GetStringTable(AMCEFNV1aAlgorithm::fnv1a64(name));
}

void _T_AM_StringList::Add(_T_AM_StringList& second)
{
    if (&second == this)
        return;
    _T_AM_StringList* pp = this;
    while (pp->_M_next_chunk != this)
    {
        if (pp->_M_next_chunk == &second)
            return;
        pp = pp->_M_next_chunk;
    }
    pp->_M_next_chunk = &second;
    second._M_next_chunk = this;
}


_T_AM_StringList& _T_AM_StringList::registerItem(_T_AM_StringItemBase* item)
{
    _T_AM_StringItemBase* p = _M_first_item;
    _T_AM_StringItemBase* pLast = nullptr;
    while( p ) {
        if (strcmp(item->_M_original_str, p->_M_original_str) < 0) {
            if (pLast) {
                item->_M_next = pLast->_M_next;
                pLast->_M_next = item;
            }
            else {
                item->_M_next = _M_first_item;
                _M_first_item = item;
            }
            return *this;
        }
        pLast = p;
        p = p->_M_next;
    }
    if (pLast) {
        pLast->_M_next = item;
        item->_M_next = nullptr;
    }
    else {
        _M_first_item = item;
        item->_M_next = nullptr;
    }
    return *this;
};

}//namespace
