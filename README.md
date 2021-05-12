# ONLY_HEADER_STL_LOADER

It is easy to use, only header, *.stl file loader.

***USAGE***

* `#define STL_SHOW_ERRORS` before include, if you don't want to check the error.

```c++
#include "stl_loader.h"

STL_HEADER stl_header;
STL_TRIANGLE* triangles;

if(!stl_load_from_file("../files/DeLorean.STL", stl_header, triangles))
{
    /*check error*/
}

/*...*/

/*free memory*/
stl_free(triangles);

```
