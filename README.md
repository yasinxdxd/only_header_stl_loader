# ONLY_HEADER_STL_LOADER
It is easy to use, only header, *.stl file loader.

***USAGE***

* `#define STL_SHOW_ERRORS` before include, if you don't want to check the error. *

```c++
#include "stl_loader.h"

STL_HEADER stl_header;
STL_TRIANGLE* triangles;
attribute_byte_count* attributes;

if(stl_load_from_file("../files/DeLorean.STL", stl_header, triangles, attributes))
{
    /*check error*/
}

/*...*/

/*free memory*/
stl_free<STL_TRIANGLE>(triangles);
stl_free<attribute_byte_count>(attributes);

```