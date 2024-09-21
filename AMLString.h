/*!
*   @file AMLString.h
*   This file is interface for definition static stringtable with import functions from <b>.mo</b> files.
*
*   @author Zdeněk Skulínek  &lt;<a href="mailto:zdenek.skulinek@seznam.cz">me@zdenekskulinek.cz</a>&gt;
*/
#ifndef AMLSTRING_H
#define AMLSTRING_H

#include <utility>
#include "AMBasicCString.h"
#include "AMCEFNV1a.h"

/**
 *  @ingroup Strings
 *  @{
 */

namespace AMCore {

    class _T_AM_StringItemBase;

    class _T_AM_StringList
    {
        _T_AM_StringList*         _M_next;
        static _T_AM_StringList*  _M_root;
        const uint64_t            _M_name_hash;
        _T_AM_StringList*         _M_next_chunk;
/*
         virtual bool SaveContent(void* vpnode)=0;
         virtual int  LoadContent(void* vpdoc, void* vpnode)=0;*/
    public:
        _T_AM_StringItemBase* _M_first_item;
    //    int                       _M_length;
    public:
        _T_AM_StringList(const uint64_t tableHash);
        ~_T_AM_StringList();
        static _T_AM_StringList* GetStringTable(const uint64_t nameHash);
        static _T_AM_StringList* GetStringTable(const char* name);
        _T_AM_StringList& registerItem(_T_AM_StringItemBase* item);
        void Add(_T_AM_StringList& second);
        /*
           bool Save(const char* name);
           int  Load(const char* name);
        */
    };

    template<uint64_t tableHash>
    class _T_AM_StringListHolder
    {
        static _T_AM_StringList _M_list;
    public:
        _T_AM_StringList& list() {return _M_list;}
        static _T_AM_StringList& registerItem(_T_AM_StringItemBase* item)
        {
            return _M_list.registerItem(item);
        }
    };
    template<uint64_t tableHash>
    _T_AM_StringList _T_AM_StringListHolder<tableHash>::_M_list(tableHash);

    class _T_AM_String;

    class AMLStringProvider
    {
        const _T_AM_StringItemBase* _M_string_item;

        constexpr
        AMLStringProvider(const _T_AM_StringItemBase* stringItem) :
            _M_string_item(stringItem)
        {}

        friend class AMLString;
        friend class _T_AM_String;
        friend class _T_AM_StringItemBase;
    public:
        constexpr const char* c_str() const noexcept;
        constexpr size_t length() const noexcept;
    };

    using AMLStringBase = AMBasicConstString<char, std::char_traits<char>, AMLStringProvider>;
    class _T_AM_String;
    class _T_AM_StringItemBase;


    /**
     *  @ingroup Strings
     *  @brief Object returned by "_" (add to localized table) function
     */
    class AMLString: public AMLStringBase
    {
        constexpr
        AMLString(const AMLStringProvider& provider) noexcept:
            AMLStringBase(provider) {}
        friend class _T_AM_String;
        friend class _T_AM_StringItemBase;
    public:

        /**
         * @return original (parameter of _ function) string (const char*)
         */
        constexpr
        const char* getOriginalString() const noexcept;

        /**
         * @return original (parameter of _ function) string length
         */
        constexpr
        size_t getOriginalLength() const noexcept;

        /**
         * @return original (parameter of _ function) string (string_view)
         */
        constexpr
        std::string_view getOriginalStringView() const noexcept;
    };

    struct _T_AM_StringItemBase
    {
        const char* _M_str;
        int         _M_length;
        const char* _M_original_str;
        int         _M_original_length;
        _T_AM_StringItemBase* _M_next;
    public:
        constexpr static int ceLength(const char* src)
        {
            int len = 0;
            while(src[len] != '\0') len++;
            return len + 1;
        }

        constexpr
        _T_AM_StringItemBase(const char* str) :
            _M_str(str),
            _M_length(_T_AM_StringItemBase::ceLength(str)),
            _M_original_length(_M_length),
            _M_original_str(str),
            _M_next(nullptr)
        {}

        constexpr
        _T_AM_StringItemBase() :
            _M_str(nullptr),
            _M_length(0),
            _M_original_str(nullptr),
            _M_original_length(0),
            _M_next(nullptr)
        {}

        constexpr
        const char* getTranslatedString() const noexcept
        {
            return _M_str;
        }

        constexpr
        void setTranslatedString(const char* str) noexcept
        {
            _M_str = str;
            _M_length = _T_AM_StringItemBase::ceLength(str);
        }

        constexpr
        const char* getOriginalString() const noexcept
        {
            return _M_original_str;
        }

        constexpr
        size_t getOriginalLength() const noexcept
        {
            return _M_original_length == 0 ? 0 : _M_original_length - 1;
        }

        AMLString getAMLString() const
        {
            AMLStringProvider prov(this);
            AMLString amls(prov);
            return amls;
        }

        constexpr
        int getTranslatedLength() const noexcept
        {
            return _M_length == 0 ? 0 : _M_length - 1;
        }

        constexpr
        _T_AM_StringItemBase* getNextItem() const noexcept
        {
            return _M_next;
        }
    };

    constexpr
    const char* AMLStringProvider::c_str() const noexcept
    {
        return _M_string_item->getTranslatedString();
    }

    constexpr
    size_t AMLStringProvider::length() const noexcept
    {
        return _M_string_item->getTranslatedLength();
    }

    constexpr
    const char* AMLString::getOriginalString() const noexcept
    {
        return _M_provider._M_string_item->getOriginalString();
    }

    constexpr
    size_t AMLString::getOriginalLength() const noexcept
    {
        return _M_provider._M_string_item->getOriginalLength();
    }

    constexpr
    std::string_view AMLString::getOriginalStringView() const noexcept
    {
        return std::string_view(_M_provider._M_string_item->getOriginalString(), _M_provider._M_string_item->getOriginalLength());
    }

    template<uint64_t tableHash, const char... chars>
    struct _T_AM_StringItemStatic: public _T_AM_StringItemBase
    {
        static constexpr const char _M_original_str_data[sizeof...(chars)] = {chars...};
    public:
        constexpr
        _T_AM_StringItemStatic() :
            _T_AM_StringItemBase(_T_AM_StringItemStatic::_M_original_str_data)
        {}
    };

    template<uint64_t tableHash, const char... chars>
    class _T_AM_StringItemWrapper
    {
        static _T_AM_StringItemStatic<tableHash, chars...> _M_static_item;
        static _T_AM_StringList& _M_table;
    public:
        static constexpr _T_AM_StringItemBase* getTranslationObject()
        {
            return static_cast<_T_AM_StringItemBase*>(&_M_static_item);
            _T_AM_StringList& tab = _M_table;
        }
    };
    template<uint64_t tableHash, const char... chars>
    _T_AM_StringItemStatic<tableHash, chars...> _T_AM_StringItemWrapper<tableHash, chars...>::_M_static_item =
                                                    _T_AM_StringItemStatic<tableHash, chars...>();
    template<uint64_t tableHash, const char... chars>
    _T_AM_StringList& _T_AM_StringItemWrapper<tableHash, chars...>::_M_table =
        _T_AM_StringListHolder<tableHash>::registerItem(static_cast<_T_AM_StringItemBase*>(&_M_static_item));

    /*
     *  @ingroup Strings
     */
    class _T_AM_String
    {
        template<uint64_t tableHash, typename T, std::size_t... ints>
        constexpr inline _T_AM_StringItemBase* getTextImpl(T data, std::index_sequence<ints...> int_seq)
        {
            constexpr const char* src = data();
            return _T_AM_StringItemWrapper<tableHash, (src[ints])...>::getTranslationObject();
        }
    public:

        template<typename T>
        constexpr inline AMLString getTextImpl(T data)
        {
            _T_AM_StringItemBase* stringItem = getTextImpl< AMCEFNV1aAlgorithm::fnv1a64("default")>
                                                   (data, std::make_index_sequence<_T_AM_StringItemBase::ceLength(data())>{});
            AMLStringProvider provider(stringItem);
            return AMLString(provider);
        }
    };

    template<typename T>
    constexpr inline AMLString _T_AM_String_getTextImpl(T data)
    {
        _T_AM_String s;
        return s.getTextImpl(data);
    }


}//namespace


/**
 *  @ingroup Strings
 *  @brief Adds string to localization stringtable
 *  @param string string
 *  @returns translated string
 */
#define _(string) AMCore::_T_AM_String_getTextImpl([]()constexpr{ return string;})
#define _L(string) AMCore::_T_AM_String<wchar_t>::getTextImpl([]()constexpr{ return string;})

/** @} */

#endif /* AMLSTRING_H */
