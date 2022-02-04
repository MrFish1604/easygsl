# easygsl
A library to make as simple as possible the use of [gsl](https://www.gnu.org/software/gsl/).

Only **Vector** and **Matrix** with elements of type double are implemented yet.

### How to install
```sh
git clone https://github.com/MrFish1604/easygsl.git
cd easy_gsl/
sudo make install
```

### How to use
In your source:
```cpp
#include <easy_gsl/easy_gsl.h>
```
Compile with:
```sh
g++ [src.cpp] /usr/lib/easy_gsl/easy_gsl.a -lgsl
```
