# ![xtensor](http://quantstack.net/assets/images/xtensor.svg)

[![Travis](https://travis-ci.org/QuantStack/xtensor.svg?branch=master)](https://travis-ci.org/QuantStack/xtensor)
[![Appveyor](https://ci.appveyor.com/api/projects/status/quf1hllkedr0rxbk?svg=true)](https://ci.appveyor.com/project/QuantStack/xtensor)
[![Documentation Status](http://readthedocs.org/projects/xtensor/badge/?version=latest)](https://xtensor.readthedocs.io/en/latest/?badge=latest)
[![Binder](https://img.shields.io/badge/launch-binder-brightgreen.svg)](http://mybinder.org/repo/QuantStack/xtensor/notebooks/notebooks/xtensor.ipynb)
[![Join the Gitter Chat](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/QuantStack/Lobby?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

Multi-dimensional arrays with broadcasting and lazy computing.

## Introduction

`xtensor` is a C++ library meant for numerical analysis with multi-dimensional array expressions.

`xtensor` provides

 - an extensible expression system enabling **lazy broadcasting**.
 - an API following the idioms of the **C++ standard library**.
 - tools to manipulate array expressions and build upon `xtensor`.

Containers of `xtensor` are inspired by [NumPy](http://www.numpy.org), the Python array programming library. **Adaptors** for existing data structures to be plugged into our expression system can easily be written. In fact, `xtensor` can be used to **process `numpy` data structures inplace** using Python's [buffer protocol](https://docs.python.org/3/c-api/buffer.html). For more details on the numpy bindings, check out the [xtensor-python](https://github.com/QuantStack/xtensor-python) project.

`xtensor` requires a modern C++ compiler supporting C++14. The following C++ compilers are supported:

 - On Windows platforms, Visual C++ 2015 Update 2, or more recent
 - On Unix platforms, gcc 4.9 or a recent version of Clang

## Installation

`xtensor` is a header-only library. We provide a package for the conda package manager.

```bash
conda install -c conda-forge xtensor
```

Or you can directly install it from the sources:

```bash
cmake -D CMAKE_INSTALL_PREFIX=your_install_prefix
make install
```

## Usage

### Basic Usage

**Initialize a 2-D array and compute the sum of one of its rows and a 1-D array.**

```cpp
#include <iostream>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"

xt::xarray<double> arr1
  {{1.0, 2.0, 3.0},
   {2.0, 5.0, 7.0},
   {2.0, 5.0, 7.0}};

xt::xarray<double> arr2
  {5.0, 6.0, 7.0};

xt::xarray<double> res = xt::view(arr1, 1) + arr2;

std::cout << res;
```

Outputs:

```
{7, 11, 14}
```

**Initialize a 1-D array and reshape it inplace.**

```cpp
#include <iostream>
#include "xtensor/xarray.hpp"
#include "xtensor/xio.hpp"

xt::xarray<int> arr
  {1, 2, 3, 4, 5, 6, 7, 8, 9};

arr.reshape({3, 3});

std::cout << arr;
```

Outputs:

```
{{1, 2, 3},
 {4, 5, 6},
 {7, 8, 9}}
```

## The Numpy to xtensor cheat sheet

If you are familiar with numpy APIs, and you are interested in xtensor, you can check out the [numpy to xtensor cheat sheet](https://xtensor.readthedocs.io/en/latest/numpy.html) provided in the documentation.

## Lazy Broadcasting with `xtensor`

We can operate on arrays of different shapes of dimensions in an elementwise fashion. Broadcasting rules of xtensor are similar to those of [numpy](http://www.numpy.org) and [libdynd](http://libdynd.org).

### Broadcasting rules

In an operation involving two arrays of different dimensions, the array with the lesser dimensions is broadcast across the leading dimensions of the other.

For example, if `A` has shape `(2, 3)`, and `B` has shape `(4, 2, 3)`, the result of a broadcasted operation with `A` and `B` has shape `(4, 2, 3)`. 

```
   (2, 3) # A
(4, 2, 3) # B
---------
(4, 2, 3) # Result
```

The same rule holds for scalars, which are handled as 0-D expressions. If `A` is a scalar, the equation becomes:

```
       () # A
(4, 2, 3) # B
---------
(4, 2, 3) # Result
```

If matched up dimensions of two input arrays are different, and one of them has size `1`, it is broadcast to match the size of the other. Let's say B has the shape `(4, 2, 1)` in the previous example, so the broadcasting happens as follows:

```
   (2, 3) # A
(4, 2, 1) # B
---------
(4, 2, 3) # Result
```

### Universal functions, Laziness and Vectorization

With `xtensor`, if `x`, `y` and `z` are arrays of *broadcastable shapes*, the return type of an expression such as `x + y * sin(z)` is **not an array**. It is an `xexpression` object offering the same interface as an N-dimensional array, which does not hold the result. **Values are only computed upon access or when the expression is assigned to an xarray object**. This allows to operate symbolically on very large arrays and only compute the result for the indices of interest.

We provide utilities to **vectorize any scalar function** (taking multiple scalar arguments) into a function that will perform on `xexpression`s, applying the lazy broadcasting rules which we just described. These functions are called *xfunction*s. They are `xtensor`'s counterpart to numpy's universal functions.

In `xtensor`, arithmetic operations (`+`, `-`, `*`, `/`) and all special functions are *xfunction*s.

### Iterating over `xexpression`s and Broadcasting Iterators

All `xexpression`s offer two sets of functions to retrieve iterator pairs (and their `const` counterpart).

 - `begin()` and `end()` provide instances of `xiterator`s which can be used to iterate over all the elements of the expression. The order in which elements are listed is `row-major` in that the index of last dimension is incremented first.
 - `xbegin(shape)` and `xend(shape)` are similar but take a *broadcasting shape* as an argument. Elements are iterated upon in a row-major way, but certain dimensions are repeated to match the provided shape as per the rules described above. For an expression `e`, `e.xbegin(e.shape())` and `e.begin()` are equivalent.

### Runtime vs Compile-time dimensionality

Two container classes implementing multi-dimensional arrays are provided: `xarray` and `xtensor`.

 - `xarray` can be reshaped dynamically to any number of dimensions. It is the container that is the most similar to numpy arrays.
 - `xtensor` has a dimension set at compilation time, which enables many optimizations. For example, shapes and strides
    of `xtensor` instances are allocated on the stack instead of the heap.

`xarray` and `xtensor` container are both `xexpression`s and can be involved and mixed in universal functions, assigned to each other etc...

Besides, two access operators are provided:

 - The variadic template `operator()` which can take multiple integral arguments or none.
 - And the `operator[]` which takes a single multi-index argument, which can be of size determined at runtime. `operator[]` also supports
   access with braced initializers.

### Performance

The dynamic nature of `xarray` over `xtensor` has a cost. Since the dimension is unknown at build time, the sequences holding shape and strides
of `xarray` instances are heap-allocated, which makes it significantly more expansive than `xtensor`. Shape and strides of `xtensor` are stack
allocated which makes them more efficient.

More generally, the library implement a `promote_shape` mechanism at build time to determine the optimal sequence type to hold the shape of an
expression. The shape type of a broadcasting expression whose members have a dimensionality determined at compile time will have a stack allocated
shape. If a single member of a broadcasting expression has a dynamic dimension (for example an `xarray`), it bubbles up to entire broadcasting expression which will have a heap allocated shape. The same hold for views, broadcast expressions, etc...

Therefore, when building an application with xtensor, we recommend using statically dimensioned containers whenever possible to improve the overall performance of the application.

## Python bindings

The [xtensor-python](https://github.com/QuantStack/xtensor-python) project provides the implementation of two `xtensor` containers, `pyarray` and `pytensor` which
effectively wrap numpy arrays, allowing inplace modification, including reshapes.

## Building and Running the Tests

Building the tests requires the [GTest](https://github.com/google/googletest) testing framework and [cmake](https://cmake.org).

gtest and cmake are available as a packages for most linux distributions. Besides, they can also be installed with the `conda` package manager (even on windows):

```bash
conda install -c conda-forge gtest cmake
```

Once `gtest` and `cmake` are installed, you can build and run the tests:

```bash
mkdir build
cd build
cmake -DBUILD_TESTS=ON ../
make xtest
```

You can also use CMake to download the source of `gtest`, build it, and use the generated libraries:

```bash
mkdir build
cd build
cmake -DBUILD_TESTS=ON -DDOWNLOAD_GTEST=ON ../
make xtest
```

In the context of continuous integration with Travis CI, tests are run in a `conda` environment, which can be activated with

```bash
cd test
conda env create -f ./test-environment.yml
source activate test-xtensor
cd ..
cmake -DBUILD_TESTS=ON .
make xtest
```

## Building the HTML Documentation

xtensor's documentation is built with three tools

 - [doxygen](http://www.doxygen.org)
 - [sphinx](http://www.sphinx-doc.org)
 - [breathe](https://breathe.readthedocs.io)

While doxygen must be installed separately, you can install breathe by typing

```bash
pip install breathe
``` 

Breathe can also be installed with `conda`

```bash
conda install -c conda-forge breathe
```

Finally, build the documentation with

```bash
make html
```

from the `docs` subdirectory.

## License

We use a shared copyright model that enables all contributors to maintain the
copyright on their contributions.

This software is licensed under the BSD-3-Clause license. See the [LICENSE](LICENSE) file for details.
