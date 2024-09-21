/**
 * @file: AMBasicCString.h
 * Constant string
 *
 * @author Robotea technologies s.r.o.
 */

#ifndef AMBASICCSTRING_H
#define AMBASICCSTRING_H

#include <bits/functexcept.h>
#include <assert.h>
#include <cstddef>
#include <string> // char_traits

#define D_INLINE constexpr
#define D_NOEXCEPTION noexcept(true)

/**
 *  @ingroup Strings
 *  @{
 */

namespace AMCore {

/**
 *  @ingroup Strings
 *  @class AMCStringProvider
 *  @brief AMCore::AMCStringProvider is a trivial implementation of string provider.
 *  It is used by AMBasicConstString if provider is not explicitly specified.
 */
template<class TChar> class AMCStringProvider
{
public:
    typedef TChar        value_type;
    typedef const TChar* const_pointer;

    /**
     *  @brief AMCStringProvider default constructor.
     *  @throw This function will not throw an exception.
     */
    D_INLINE AMCStringProvider() D_NOEXCEPTION :
        data_(nullptr),
        len_(0)
    {}

    /**
     *  @brief AMCStringProvider constructor that initializes members.
     *  @param d - pointer to constant string.
     *  @param len - length of the string.
     *  @throw This function will not throw an exception.
     */
    D_INLINE AMCStringProvider(const_pointer d, size_t len) D_NOEXCEPTION :
        data_(d),
        len_(len)
    {}

    /**
     *  @brief access stored pointer.
     *  @return stored pointer to constant string.
     *  @throw This function will not throw an exception.
     */
    const_pointer c_str() const D_NOEXCEPTION { return data_; };

    /**
     *  @brief access string length.
     *  @return length of constant string.
     *  @throw This function will not throw an exception.
     */
    size_t length() const D_NOEXCEPTION { return len_; };

private:
    const TChar* data_;
    size_t len_;
};

static D_INLINE size_t
__sv_check(size_t __size, size_t __pos, const char* __s)
{
    if (__pos > __size)
        std::__throw_out_of_range_fmt(__N("%s: __pos (which is %zu) > __size "
                                          "(which is %zu)"), __s, __pos, __size);
    return __pos;
}

static D_INLINE size_t
__sv_limit(size_t __size, size_t __pos, size_t __off) D_NOEXCEPTION
{
    const bool __testoff = __off < __size - __pos;
    return __testoff ? __off : __size - __pos;
}

/**
 *  @ingroup Strings
 *  @class AMBasicConstString
 *  @brief  A non-owning reference to a string.
 *
 *  @ingroup strings
 *  @ingroup sequences
 *
 *  @tparam _AMChar Type of character
 *  @tparam _AMTraits Traits for character type, defaults to
 *                   char_traits<_AMChar>.
 *
 *  A AMBasicConstString looks like this:
 *
 */
template<typename _AMChar, typename _AMTraits = std::char_traits<_AMChar>, class TStringProvider = AMCStringProvider<_AMChar>>
class AMBasicConstString
{
    static_assert(!std::is_array_v<_AMChar>);
    static_assert(std::is_trivial_v<_AMChar> && std::is_standard_layout_v<_AMChar>);
    static_assert(std::is_same_v<_AMChar, typename _AMTraits::char_type>);
    friend class AMLString;

public:

    // types
    using traits_type   = _AMTraits;
    using value_type    = _AMChar;
    using pointer       = value_type*;
    using const_pointer = const value_type*;
    using reference     = value_type&;
    using const_reference = const value_type&;
    using const_iterator  = const value_type*;
    using iterator        = const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = const_reverse_iterator;
    using size_type        = size_t;
    using difference_type  = ptrdiff_t;
    static D_INLINE size_type npos = size_type(-1);

    /**
     *  @brief AMBasicConstString default constructor.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    AMBasicConstString() D_NOEXCEPTION
    {}

    /**
     *  @brief AMBasicConstString constructor with provider
     *         parameter.
     *  @param provider const reference to provider object.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    AMBasicConstString(const TStringProvider& provider) D_NOEXCEPTION:
        _M_provider(provider)
    {}

    /**
     *  @brief AMBasicConstString copy constructor.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    AMBasicConstString(const AMBasicConstString&) D_NOEXCEPTION = default;

    /**
     *  @brief AMBasicConstString constructor with string parameter.
     *         May be used for some compatibility reasons. Does not
     *         make a bin sense in the AMLString scope.
     *  @param __str const pointer to string.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    AMBasicConstString(const _AMChar* __str) D_NOEXCEPTION:
        _M_provider(__str, traits_type::length(__str))
    {}

    /**
     *  @brief AMBasicConstString constructor with string and length
     *         parameters. May be used for some compatibility
     *         reasons. Does not make a big sense in the AMLString
     *         scope.
     *  @param __str const pointer to string.
     *  @param __len string length.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    AMBasicConstString(const _AMChar* __str, size_type __len) D_NOEXCEPTION :
        _M_provider(__str, __len)
    {}

    /**
     *  @brief Default assignment operator.
     *  @return Reference to *this.
     *  @throw This function will not throw an exception.
     */
    D_INLINE AMBasicConstString&
    operator=(const AMBasicConstString&) D_NOEXCEPTION = default;

    /**
     *  @brief Returns an iterator to the beginning.
     *  @return iterator to the first character
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_iterator begin() const D_NOEXCEPTION
    {
        return this->data();
    }

    /**
     *  @brief Returns an iterator to the end.
     *  @return iterator to the character following the last
     *          character
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_iterator end() const D_NOEXCEPTION
    {
        return this->data() + this->length();
    }

    /**
     *  @brief Returns an const_iterator to the beginning.
     *  @return const_iterator to the first character
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_iterator cbegin() const D_NOEXCEPTION
    {
        return this->data();
    }

    /**
     *  @brief Returns an const_iterator to the end.
     *  @return const_iterator to the character following the last
     *          character
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_iterator cend() const D_NOEXCEPTION
    {
        return this->data() + this->length();
    }

    /**
     *  @brief Returns a reverse_iterator to the beginning.
     *  @return reverse_iterator to the first character of the
     *          reversed string. It corresponds to the last
     *          character of the non-reversed string.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reverse_iterator rbegin() const D_NOEXCEPTION
    {
        return const_reverse_iterator(this->end());
    }

    /**
     *  @brief Returns a reverse_iterator to the end.
     *  @return reverse_iterator to the character following the last
     *          character of the reversed string. It corresponds to
     *          the character preceding the first character of the
     *          non-reversed string.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reverse_iterator rend() const D_NOEXCEPTION
    {
        return const_reverse_iterator(this->begin());
    }

    /**
     *  @brief Returns a const_reverse_iterator to the beginning.
     *  @return const_reverse_iterator to the first character of the
     *          reversed string. It corresponds to the last
     *          character of the non-reversed string.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reverse_iterator crbegin() const D_NOEXCEPTION
    {
        return const_reverse_iterator(this->end());
    }

    /**
     *  @brief Returns a const_reverse_iterator to the end.
     *  @return const_reverse_iterator to the character following
     *          the last character of the reversed string. It
     *          corresponds to the character preceding the first
     *          character of the non-reversed string.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reverse_iterator crend() const D_NOEXCEPTION
    {
        return const_reverse_iterator(this->begin());
    }

    /**
     *  @brief Returns the number of characters.
     *  @return number of CharT elements.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type size() const D_NOEXCEPTION
    {
        return _M_provider.length();
    }

    /**
     *  @brief Returns the number of characters.
     *  @return number of CharT elements.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type length() const D_NOEXCEPTION
    {
        return size();
    }

    /**
     *  @brief Returns a pointer to an array that contains a
     *         null-terminated sequence of characters.
     *  @return pointer to the c-string representation of the string
     *          object's value.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const value_type* c_str() const D_NOEXCEPTION
    {
        return data();
    }

    /**
     *  @brief Returns a pointer to an array that contains a
     *         null-terminated sequence of characters.
     *  @return pointer to the c-string representation of the string
     *          object's value.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const value_type* data() const D_NOEXCEPTION
    {
        return _M_provider.c_str();
    }

    /**
     *  @brief Checks whether the string is empty.
     *  @return true if the string is empty, false otherwise.
     *  @throw This function will not throw an exception.
     */
    [[nodiscard]] D_INLINE
    bool empty() const D_NOEXCEPTION
    {
        return this->size() == 0;
    }

    /**
     *  @brief Accesses the specified character.
     *  @return Const reference to the requested character.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reference operator [](size_type __pos) const D_NOEXCEPTION
    {
        assert(__pos < this->size());
        return *(this->data() + __pos);
    }

    /**
     *  @brief Accesses the specified character with bounds
     *         checking.
     *  @return Const reference to the requested character.
     *  @throw std::out_of_range if pos >= size().
     */
    D_INLINE
    const_reference at(size_type __pos) const
    {
        if (__pos >= length())
            std::__throw_out_of_range_fmt(__N("AMBasicConstString::at: __pos "
                                              "(which is %zu) >= this->size() "
                                              "(which is %zu)"), __pos, this->size());
            return *(this->data() + __pos);
    }

    /**
     *  @brief Accesses the first character.
     *  @return const reference to the first character, equivalent
     *          to operator[](0)
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reference front() const D_NOEXCEPTION
    {
        assert(this->size() > 0);
        return *this->data();
    }

    /**
     *  @brief Accesses the last character.
     *  @return const reference to the last character, equivalent to
     *          operator[](size() - 1).
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    const_reference back() const D_NOEXCEPTION
    {
        assert(this->size() > 0);
        return *(this->data() + this->size() - 1);
    }

    /**
     *  @brief swaps the contents.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    void swap(AMBasicConstString& __sv) D_NOEXCEPTION
    {
        auto __tmp = *this;
        *this = __sv;
        __sv = __tmp;
    }

    /**
     *  @brief Copies the substring [__pos, __pos + rcount) to the
     *         character array pointed to by __str, where rcount is
     *         the smaller of __n and size() - __pos.
     *  @param __str - pointer to the destination character string.
     *  @param __n - requested substring length.
     *  @param __pos - position of the first character.
     *  @return Number of characters copied.
     *  @throw std::out_of_range if __pos > size().
     */
    D_INLINE
    size_type copy(_AMChar* __str, size_type __n, size_type __pos = 0) const
    {
        __glibcxx_requires_string_len(__str, __n);
        __pos = std::__sv_check(size(), __pos, "AMBasicConstString::copy");
        const size_type __rlen = std::min(__n, length() - __pos);

        traits_type::copy(__str, data() + __pos, __rlen);

        return __rlen;
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    int compare(AMBasicConstString __str) const D_NOEXCEPTION
    {
        const size_type __rlen = std::min(this->length(), __str.length());
        int __ret = traits_type::compare(this->data(), __str.data(), __rlen);
        if (__ret == 0)
            __ret = _S_compare(this->length(), __str.length());
        return __ret;
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    int compare(std::basic_string_view<_AMChar, _AMTraits> __str) const D_NOEXCEPTION
    {
        const size_type __rlen = std::min(this->length(), __str.length());
        int __ret = traits_type::compare(this->data(), __str.data(), __rlen);
        if (__ret == 0)
            __ret = _S_compare(this->length(), __str.length());
        return __ret;
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @param __pos1 - position of the first character in this
     *         string to compare
     *  @param __n1 - number of characters of this string to compare
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    int compare(size_type __pos1, size_type __n1, AMBasicConstString __str) const
    {
        std::basic_string_view<_AMChar, _AMTraits> tstr(this->data(), this->length());
        return tstr.substr(__pos1, __n1).compare(__str.data());
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @param __pos1 - position of the first character in this
     *         string to compare
     *  @param __n1 - number of characters of this string to compare
     *  @param __pos2 - position of the first character in other
     *         string to compare
     *  @param __n2 - number of characters of other string to
     *              compare
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    int compare(size_type __pos1, size_type __n1,
                AMBasicConstString __str, size_type __pos2, size_type __n2) const
    {
        std::basic_string_view<_AMChar, _AMTraits> tstr(this->data(), this->length());
        std::basic_string_view<_AMChar, _AMTraits> ostr(__str.data(), __str.length());
        return tstr.substr(__pos1, __n1).compare(ostr.substr(__pos2, __n2));
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    int compare(const _AMChar* __str) const D_NOEXCEPTION
    {
        return this->compare(std::basic_string_view<_AMChar, _AMTraits>{__str});
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @param __pos1 - position of the first character in this
     *         string to compare
     *  @param __n1 - number of characters of this string to compare
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    int compare(size_type __pos1, size_type __n1, const _AMChar* __str) const
    {
        std::basic_string_view<_AMChar, _AMTraits> tstr(this->data(), this->length());
        return tstr.substr(__pos1, __n1).compare(__str);
    }

    /**
     *  @brief Compares two strings.
     *  @param __str - string to compare.
     *  @param __pos1 - position of the first character in this
     *         string to compare
     *  @param __n1 - number of characters of this string to compare
     *  @param __n2 - number of characters of other string to
     *              compare
     *  @return negative value if this string is less than the other
     *          one, zero if the both strings are equal, positive
     *          value if this string is greater than the other one.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    int compare(size_type __pos1, size_type __n1,
                const _AMChar* __str, size_type __n2) const D_NOEXCEPTION
    {
        std::basic_string_view<_AMChar, _AMTraits> tstr(this->data(), this->length());
        std::basic_string_view<_AMChar, _AMTraits> ostr(__str, __n2);
        return tstr.substr(__pos1, __n1).compare(ostr);
    }

    /**
     *  @brief Finds the first substring equal to the given
     *         character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character of the found
     *          substring, or npos if no such substring is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find(AMBasicConstString __str, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find(__str.data(), __pos, __str.size());
    }

    /**
     *  @brief Finds the first substring equal to the given
     *         character.
     *  @param __c - character to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character found, or
     *          npos if no such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find(_AMChar __c, size_type __pos = 0) const D_NOEXCEPTION
    {
        size_type __ret = npos;
        if (__pos < this->length())
        {
            const size_type __n = this->length() - __pos;
            const _AMChar* __p = traits_type::find(this->data() + __pos, __n, __c);
            if (__p)
                __ret = __p - this->data();
        }
        return __ret;
    }

    /**
     *  @brief Finds the first substring equal to the given
     *         character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @param __n - length of substring to search for
     *  @return Position of the first character of the found
     *          substring, or npos if no such substring is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION;

    /**
     *  @brief Finds the first substring equal to the given
     *         character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character of the found
     *          substring, or npos if no such substring is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find(const _AMChar* __str, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find(__str, __pos, traits_type::length(__str));
    }

    /**
     *  @brief Finds the last substring equal to the given
     *         character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character of the found
     *          substring, or npos if no such substring is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type rfind(AMBasicConstString __str, size_type __pos = npos) const D_NOEXCEPTION
    {
        return this->rfind(__str.data(), __pos, __str.size());
    }

    /**
     *  @brief Finds the last substring equal to the given
     *         character.
     *  @param __c - character to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the last character found, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type rfind(_AMChar __c, size_type __pos = npos) const D_NOEXCEPTION
    {
        size_type __size = this->length();
        if (__size > 0)
        {
            if (--__size > __pos)
                __size = __pos;
            for (++__size; __size-- > 0; )
                if (traits_type::eq(this->data()[__size], __c))
                    return __size;
        }
        return npos;
    }

    /**
     *  @brief Finds the last substring equal to the given
     *         character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @param __n - length of substring to search for
     *  @return Position of the first character of the found
     *          substring, or npos if no such substring is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type rfind(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION;

    /**
     *  @brief Finds the last substring equal to the given
     *         character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character of the found
     *          substring, or npos if no such substring is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type rfind(const _AMChar* __str, size_type __pos = npos) const D_NOEXCEPTION
    {
        return this->rfind(__str, __pos, traits_type::length(__str));
    }

    /**
     *  @brief Finds the first character equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first occurrence of any character of
     *          the substring, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_first_of(AMBasicConstString __str, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find_first_of(__str.data(), __pos, __str.size());
    }

    /**
     *  @brief Finds the first character equal to the given character.
     *  @param __c - character to search for
     *  @param __pos - position at which to start the search
     *  @return Position of the first occurrence the character, or
     *          npos if no such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_first_of(_AMChar __c, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find(__c, __pos);
    }

    /**
     *  @brief Finds the first character equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @param __n - length of the string of characters to search
     *             for
     *  @return Position of the first occurrence of any character of
     *          the substring, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_first_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION;

    /**
     *  @brief Finds the first character equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first occurrence of any character of
     *          the substring, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_first_of(const _AMChar* __str, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find_first_of(__str, __pos, traits_type::length(__str));
    }

    /**
     *  @brief Finds the last character equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which the search is to finish
     *  @return Position of the last occurrence of any character of
     *          the substring, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_last_of(AMBasicConstString __str, size_type __pos = npos) const D_NOEXCEPTION
    {
        return this->find_last_of(__str.data(), __pos, __str.size());
    }

    /**
     *  @brief Finds the last character equal the given character.
     *  @param __c - character to search for.
     *  @param __pos - position at which the search is to finish
     *  @return Position of the last occurrence of the character, or
     *          npos if no such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_last_of(_AMChar __c, size_type __pos=npos) const D_NOEXCEPTION
    {
        return this->rfind(__c, __pos);
    }

    /**
     *  @brief Finds the last character equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which the search is to finish
     *  @param __n - length of the string of characters to search
     *             for
     *  @return Position of the last occurrence of any character of
     *          the substring, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_last_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION;

    /**
     *  @brief Finds the last character equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which the search is to finish
     *  @return Position of the last occurrence of any character of
     *          the substring, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_last_of(const _AMChar* __str, size_type __pos = npos) const D_NOEXCEPTION
    {
        return this->find_last_of(__str, __pos, traits_type::length(__str));
    }

    /**
     *  @brief Finds the first character not equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character not equal to any of
     *          the characters in the given string, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_first_not_of(AMBasicConstString __str, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find_first_not_of(__str.data(), __pos, __str.size());
    }

    /**
     *  @brief Finds the first character not equal to the given
     *         character.
     *  @param __c - character to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character not equal to the
     *          given character, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_first_not_of(_AMChar __c, size_type __pos = 0) const D_NOEXCEPTION
    {
        for (; __pos < this->length(); ++__pos)
            if (!traits_type::eq(this->data()[__pos], __c))
                return __pos;
        return npos;
    }

    /**
     *  @brief Finds the first character not equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @param __n - length of the string of characters to compare
     *  @return Position of the first character not equal to any of
     *          the characters in the given string, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_first_not_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION;

    /**
     *  @brief Finds the first character not equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the first character not equal to any of
     *          the characters in the given string, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_first_not_of(const _AMChar* __str, size_type __pos = 0) const D_NOEXCEPTION
    {
        return this->find_first_not_of(__str, __pos, traits_type::length(__str));
    }

    /**
     *  @brief Finds the last character not equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the last character not equal to any of
     *          the characters in the given string, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_last_not_of(AMBasicConstString __str, size_type __pos = npos) const D_NOEXCEPTION
    {
        return this->find_last_not_of(__str.data(), __pos, __str.size());
    }

    /**
     *  @brief Finds the last character not equal to the given
     *         character.
     *  @param __c - character to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the last character not equal to the
     *          given character, or npos if no such character is
     *          found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_last_not_of(_AMChar __c, size_type __pos = npos) const D_NOEXCEPTION
    {
        size_type __size = this->length();
        if (__size)
        {
            if (--__size > __pos)
                __size = __pos;
            do
            {
                if (!traits_type::eq(this->data()[__size], __c))
                    return __size;
            }
            while (__size--);
        }
        return npos;
    }

    /**
     *  @brief Finds the last character not equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @param __n - length of the string of characters to compare
     *  @return Position of the last character not equal to any of
     *          the characters in the given string, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    D_INLINE
    size_type find_last_not_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION;

    /**
     *  @brief Finds the last character not equal to any of the
     *         characters in the given character sequence.
     *  @param __str - string to search for.
     *  @param __pos - position at which to start the search
     *  @return Position of the last character not equal to any of
     *          the characters in the given string, or npos if no
     *          such character is found.
     *  @throw This function will not throw an exception.
     */
    __attribute__((__nonnull__)) D_INLINE
    size_type find_last_not_of(const _AMChar* __str, size_type __pos = npos) const D_NOEXCEPTION
    {
        return this->find_last_not_of(__str, __pos, traits_type::length(__str));
    }

private:

    static D_INLINE
    int _S_compare(size_type __n1, size_type __n2) D_NOEXCEPTION
    {
        const difference_type __diff = __n1 - __n2;
        if (__diff > __gnu_cxx::__int_traits<int>::__max)
            return __gnu_cxx::__int_traits<int>::__max;
        if (__diff < __gnu_cxx::__int_traits<int>::__min)
            return __gnu_cxx::__int_traits<int>::__min;
        return static_cast<int>(__diff);
    }

    TStringProvider _M_provider;
};


// non-member AMBasicConstString comparison function

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the strings are equal, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator==(AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    const _AMChar* __y) D_NOEXCEPTION
    {
        return __x.compare(__y) == 0;
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the strings are equal, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator==(const _AMChar* __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return __y.compare(__x) == 0;
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the strings are equal, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator==(AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return __x.size() == __y.size() && __x.compare(__y) == 0;
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the strings are not equal, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator!=(AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return !(__x == __y);
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the first string is lesser than the second
     *          one, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator< (AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return __x.compare(__y) < 0;
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the first string is greater tan the second
     *          one, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator> (AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return __x.compare(__y) > 0;
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the first string is lesser than or equal to
     *          the second one, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator<=(AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return __x.compare(__y) <= 0;
    }

    /**
     *  @brief Compares two strings.
     *  @param __x - first string.
     *  @param __y - second string.
     *  @return true if the first string is greater than or equal to
     *          the second one, false otherwise.
     *  @throw This function will not throw an exception.
     */
    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    D_INLINE
    bool operator>=(AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __x,
                    AMBasicConstString<_AMChar, _AMTraits, TStringProvider> __y) D_NOEXCEPTION
    {
        return __x.compare(__y) >= 0;
    }

    template<typename _AMChar, typename _AMTraits, typename TStringProvider>
    inline std::basic_ostream<_AMChar, _AMTraits>&
    operator<<(std::basic_ostream<_AMChar, _AMTraits>& __os,
               AMBasicConstString<_AMChar,_AMTraits, TStringProvider> __str)
    {
        return __ostream_insert(__os, __str.data(), __str.size());
    }

    inline namespace literals
    {
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wliteral-suffix"
#endif
    inline D_INLINE AMBasicConstString<char>
    operator""_c(const char* __str, size_t __len) D_NOEXCEPTION
    {
        return AMBasicConstString<char>{__str, __len};
    }

#ifdef _GLIBCXX_USE_WCHAR_T
    inline D_INLINE AMBasicConstString<wchar_t>
    operator""_c(const wchar_t* __str, size_t __len) D_NOEXCEPTION
    {
        return AMBasicConstString<wchar_t>{__str, __len};
    }
#endif

#ifdef _GLIBCXX_USE_CHAR8_T
    inline D_INLINE AMBasicConstString<char8_t>
    operator""_c(const char8_t* __str, size_t __len) D_NOEXCEPTION
    {
        return AMBasicConstString<char8_t>{__str, __len};
    }
#endif

    inline D_INLINE AMBasicConstString<char16_t>
    operator""_c(const char16_t* __str, size_t __len) D_NOEXCEPTION
    {
        return AMBasicConstString<char16_t>{__str, __len};
    }

    inline D_INLINE AMBasicConstString<char32_t>
    operator""_c(const char32_t* __str, size_t __len) D_NOEXCEPTION
    {
        return AMBasicConstString<char32_t>{__str, __len};
    }
#if defined(__GNUC__) && !defined(__clang__)
#pragma GCC diagnostic pop
#endif
  } // namespace literals

    template<typename _AMChar, typename _AMTraits, typename _Provider>
    D_INLINE typename AMBasicConstString<_AMChar, _AMTraits, _Provider>::size_type
    AMBasicConstString<_AMChar, _AMTraits, _Provider>::
        find(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION
    {
        __glibcxx_requires_string_len(__str, __n);

        if (__n == 0)
            return __pos <= length() ? __pos : npos;
        if (__pos >= length())
            return npos;

        const _AMChar __elem0 = __str[0];
        const _AMChar* __first = data() + __pos;
        const _AMChar* const __last = data() + length();
        size_type __len = length() - __pos;

        while (__len >= __n)
        {
            // Find the first occurrence of __elem0:
            __first = traits_type::find(__first, __len - __n + 1, __elem0);
            if (!__first)
                return npos;
            // Compare the full strings from the first occurrence of __elem0.
            // We already know that __first[0] == __s[0] but compare them again
            // anyway because __s is probably aligned, which helps memcmp.
            if (traits_type::compare(__first, __str, __n) == 0)
                return __first - data();
            __len = __last - ++__first;
        }
        return npos;
    }

    template<typename _AMChar, typename _AMTraits, typename _Provider>
    D_INLINE typename AMBasicConstString<_AMChar, _AMTraits, _Provider>::size_type
    AMBasicConstString<_AMChar, _AMTraits, _Provider>::
        rfind(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION
    {
        __glibcxx_requires_string_len(__str, __n);

        if (__n <= this->length())
        {
            __pos = std::min(size_type(this->length() - __n), __pos);
            do
            {
                if (traits_type::compare(this->data() + __pos, __str, __n) == 0)
                    return __pos;
            }
            while (__pos-- > 0);
        }
        return npos;
    }

    template<typename _AMChar, typename _AMTraits, typename _Provider>
    D_INLINE typename AMBasicConstString<_AMChar, _AMTraits, _Provider>::size_type
    AMBasicConstString<_AMChar, _AMTraits, _Provider>::
        find_first_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION
    {
        __glibcxx_requires_string_len(__str, __n);

        for (; __n && __pos < this->length(); ++__pos)
        {
            const _AMChar* __p = traits_type::find(__str, __n, this->data()[__pos]);
            if (__p)
                return __pos;
        }
        return npos;
    }

    template<typename _AMChar, typename _AMTraits, typename _Provider>
    D_INLINE typename AMBasicConstString<_AMChar, _AMTraits, _Provider>::size_type
    AMBasicConstString<_AMChar, _AMTraits, _Provider>::
        find_last_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION
    {
        __glibcxx_requires_string_len(__str, __n);
        size_type __size = this->size();
        if (__size && __n)
        {
            if (--__size > __pos)
                __size = __pos;
            do
            {
                if (traits_type::find(__str, __n, this->data()[__size]))
                    return __size;
            }
            while (__size-- != 0);
        }
        return npos;
    }

    template<typename _AMChar, typename _AMTraits, typename _Provider>
    D_INLINE typename AMBasicConstString<_AMChar, _AMTraits, _Provider>::size_type
    AMBasicConstString<_AMChar, _AMTraits, _Provider>::
        find_first_not_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION
    {
        __glibcxx_requires_string_len(__str, __n);
        for (; __pos < this->length(); ++__pos)
            if (!traits_type::find(__str, __n, this->data()[__pos]))
                return __pos;
        return npos;
    }

    template<typename _AMChar, typename _AMTraits, typename _Provider>
    D_INLINE typename AMBasicConstString<_AMChar, _AMTraits, _Provider>::size_type
    AMBasicConstString<_AMChar, _AMTraits, _Provider>::
        find_last_not_of(const _AMChar* __str, size_type __pos, size_type __n) const D_NOEXCEPTION
    {
        __glibcxx_requires_string_len(__str, __n);
        size_type __size = this->length();
        if (__size)
        {
            if (--__size > __pos)
                __size = __pos;
            do
            {
                if (!traits_type::find(__str, __n, this->data()[__size]))
                    return __size;
            }
            while (__size--);
        }
        return npos;
    }

} //namespace AMCore

/** @} */

#endif  // AMBASICCSTRING_H
