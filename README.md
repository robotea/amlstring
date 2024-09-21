# AMLString - localizable strings

Typical localizing library needs to search in any data structure for localized string. This library not. At runtime, it only takes a pointer, so it may cost only one or two CPU instructions.

Usage is as usual with gettext. Parser finds all occurences of function "_" an store it to file with **po** suffix. This file is merged into global a take to translator. Result of this is
process is **mo** file, that can be included back into project. Loading of **mo** files is not accomplished at this time.

Result of "_" call id object of AMBasicCString class. It has similar interface as std::string, thus can be used for searching, substringing... etc. Except modification od this object. 

## Usage

Typical usage is very simple...

    AMLString texts[] = {_("quick"), _("brown"), _("fox")};

    std::stringstream stream;
    stream << texts[1];

## Building AMLString

### Getting sources

```bash
git submodule update
```

### Compiling

```bash

mkdir cmake-build-debug

cd cmake-build-debug

cmake ..

make
```

### Output Library

```bash
/lib/libAMLString.so
```

### Single test (not necessary)

```bash
./TEST_AMFNV1a

./TEST_AMLString
```

## Licencing

This library is under GNU GPL v3 licence. If you need business licence, don't hesitate to contact [me](mailto:zdenek.skulinek@robotea.com?subject=Lincence for AMException).

## Contribute

Please contact [me](mailto:zdenek.skulinek@robotea.com?subject=Lincence for AMException).

## Dependencies

1. [Google test](https://github.com/google/googletest.git)