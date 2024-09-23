/**
 * @mainpage Andromeda String localization library
 * @brief This library is essential for develop quality multilanguage applications.
 *
 * Typical localizing library needs to search in any data structure for localized string. This library not.
 * At runtime, it only takes a pointer, so it may cost only one or two CPU instructions.

 * Usage is as usual with gettext. Parser finds all occurences of function "_" an store it to file with **po** suffix.
 * This file is merged into global a take to translator. Result of this is process is **mo** file, that can be included
 * back into project. Loading of **mo** files is not accomplished at this time.
 *
 * How it works
 * ============
 *
 * Look! AMLString tooks only one mov instruction!
 *
 * \image html AMLStringSpeed.png "AMLString disassembly"
 *
 * Sources
 * =======
 *
 * Download at [GitHUB](https://github.com/robotea/amlstring)
 *
 * Building AMLString
 * ==================
 *
 * Getting sources
 * ---------------
 *
 * \code
 * git submodule update
 * \endcode
 *
 * Compiling
 * ---------
 *
 * \code
 * mkdir cmake-build-debug
 *
 * cd cmake-build-debug
 *
 * cmake ..
 *
 * make
 * \endcode
 *
 * Output Library
 * --------------
 *
 * \code
 * /lib/libAMLString.so
 * \endcode
 *
 * Single test (not necessary)
 * ---------------------------
 *
 * \code
 * ./TEST_AMLString
 * \endcode
 *
 * License
 * =========
 *
 * This library is under GNU GPL v3 license. If you need business license, don't hesitate to contact [me](mailto:zdenek.skulinek@robotea.com?subject=License for AMException).
 *
 * Contribute
 * ==========
 *
 * Please contact [me](mailto:zdenek.skulinek@robotea.com?subject=License for AMException).
 *
 * Dependencies
 * ============
 *
 * - [Google test](https://github.com/google/googletest.git)
 * - [FNV1a hash algorithm](https://github.com/robotea/amfnv1a.git)
 */
