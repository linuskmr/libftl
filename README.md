# libftl

Test implementation of the standard library of [FTL](https://github.com/linuskmr/forty-two-lang).

Here are collected thoughts about the implementation of the standard library of FTL. I know that this code here is 
not idiomatic C++ code. C++ was just chosen as prototype language for FTL's standard library, and so this code 
is developed with FTL's anticipated available features in mind.

## Naming conventions

Whether CamelCase or sneak_case is not yet decided.

Rules for variable and method names:

| Prefix                 | Variable          | Method           |
| ---------------------  | ----------------- | -----------------|
| _ (single underscore)  | private/read-only | private          |
| __ (double underscore) | internal/builtin  | internal/builtin |

> Note: All member variables and methods of classes are public and follow these rules. This is to mimic the behavior 
> of FTL as well as possible.

## Usage of the c++ standard library

Because FTL only has access to the libc, try to avoid using the c++ standard library and go with the libc.