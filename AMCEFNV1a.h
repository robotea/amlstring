/**
 * @file: AMCEFNV1a.h
 * Constant expression implementation of FNV1a Algorithm
 *
 * @author Zdeněk Skulínek  &lt;<a href="mailto:zdenek.skulinek@seznam.cz">me@zdenekskulinek.cz</a>&gt;
 */

#ifndef AMCEFNV1a_H
#define AMCEFNV1a_H

#include <cstdint>

/**
 *  @ingroup Crypto
 *  @{
 */

namespace AMCore {

	/**
	 *  @ingroup Crypto
	 *  @brief Constant expression implementation of FNV1a Algorithm
	 *
	 *  Example:
	 *	@code{.cpp}
	 *  #include <AMCore/AMCEFNV1a.h>
	 *  #include <iostream>
	 *
	 *  using namespace AMCore;
	 *  using namespace std;
	 *
	 *  int main() {
	 *    	cout<<"Enter password (color of blood): ";
	 *    	char pass[1024];
	 *    	cin>>pass;
	 *    	uint64_t hash = AMFNV1aAlgorithm::fnv1a64(pass);
	 *
	 *    	switch (hash)
	 *    	{
	 *        	case AMCEFNV1aAlgorithm::fnv1a64("blue"): cout<<"Fail"<<endl;break;
	 *        	case AMCEFNV1aAlgorithm::fnv1a64("green"): cout<<"Fail"<<endl;break;
	 *        	case AMCEFNV1aAlgorithm::fnv1a64("red"): cout<<"Hooray!"<<endl;break;
	 *        	case AMCEFNV1aAlgorithm::fnv1a64("yellow"): cout<<"Fail"<<endl;break;
	 *        	default: cout<<"Fail"<<endl;
	 *    	}
	 *    	return 0;
	 *	}
	 *  @endcode
	 */
	class AMCEFNV1aAlgorithm
	{
	    static const std::uint64_t basis64 = 0xcbf29ce484222325ULL;
	    static const std::uint64_t prime64 = 0x100000001b3ULL;
	    static const std::uint32_t basis32 = 0x811c9dc5UL;
	    static const std::uint32_t prime32 = 0x01000193UL;
	public:
		/**
		 *  @brief 64bit variant of FNV1a Algorithm
		 *  @param input any null-terminated string
		 *  @returns 64bit hash
		 */
	    static constexpr std::uint64_t fnv1a64(const char* input)
	    {
	        std::uint64_t hash = basis64;
	        const char* str = input;
	        while(*str) {
	            hash = (hash ^ (std::uint64_t)(*str)) * prime64;
	            str++;
	        }
	        return hash;
	    }
		/**
		 *  @brief 32bit variant of FNV1a Algorithm
		 *  @param input any null-terminated string
		 *  @returns 32bit hash
		 */
	    static constexpr std::uint32_t fnv1a32(const char* input)
	    {
	        std::uint32_t hash = basis32;
	        const char* str = input;
	        while(*str) {
	            hash = (hash ^ (std::uint32_t)(*str)) * prime32;
	            str++;
	        }
	        return hash;
	    }
	};

}//namespace

/** @} */

#endif //AMCEFNV1a_H
