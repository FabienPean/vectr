# VECTR

## Example

```cpp
#include "vectr.h"
#include <iostream>
#include <unordered_map>
int main()
{
    using namespace vectr;
    std::unordered_map<int,vecter> map;
    map[0] = vecter::create<double>();
    map[1] = vecter::create<size_t>();
    map[0].vector<double>().push_back(3.14);
    map[1].vector<size_t>().push_back(42);
    map[0].vector<double>().push_back(1.44);
    for(auto& v: map[0].vector<double>()) std::cout << v << " ";// prints "3.14 1.44"
    for(auto& v: map[1].vector<size_t>()) std::cout << v << " ";// prints "42"
}
```

## What?

This repository provides an experimental container which is attempts to be a generalized sequential container. Each `vecter` can store any type and can be safely rebind to store other types.

## Why?

For fun and education primarily.

A more concrete application is to reduce the amount of indirections for _data frame_ kind of containers. In general, they rely on data structure with a minimum of two indirections. Given in term of (simplified) C++, as a `map<type_index,unique_ptr<void>>`. This container leads to a single indirection by replacing the `unique_ptr` by the type-erased content of a `std::vector`

## How?

`vecter` is inherited by `vecter_impl<T>`. The former contains 32 bytes of information which describes its content, while the latter type provides the methods to interpret correctly its content.

* a pointer to a structure containing general information and methods on the actual type stored (size, alignment, destructor, etc)
* a pointer to the beginning of the buffer
* a pointer to the end of the existing content within the buffer
* a pointer to the end of the whole allocated buffer

The user is responsible to know what type is stored in a `vecter` to be able to use it. However, the basic operations such as destruction/copy/move are safely done.