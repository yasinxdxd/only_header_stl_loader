/**
 *
 * MIT License
 * 
 * Copyright (c) 2021 Muhammed Yasinhan Yaşar
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or substantial 
 * portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
 * LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *  
**/

/* #define STL_SHOW_ERRORS before include if you don't want to check error. */

/***USAGE***/
//    
//    STL_HEADER stl_header;
//    STL_TRIANGLE* triangles;
//    attribute_byte_count* attributes;
//
//    if(stl_load_from_file("../files/DeLorean.STL", stl_header, triangles, attributes))
//    {
//        /*check error*/
//    }
//
//    /*...*/
//
//    /*free memory*/
//
//    stl_free<STL_TRIANGLE>(triangles);
//    stl_free<attribute_byte_count>(attributes);
//
/********************/

#ifndef STL_LOADER_ONLY_HEADER
#define STL_LOADER_ONLY_HEADER

#include <fstream>

typedef struct _stl_triangle
{
    float normal_vector[3];               //12 bytes  x, y, z
    float vertex1[3];                     //12 bytes  x, y, z
    float vertex2[3];                     //12 bytes  x, y, z
    float vertex3[3];                     //12 bytes  x, y, z

} STL_TRIANGLE; //48 bytes

typedef unsigned short int attribute_byte_count;      //2 bytes

typedef struct _stl_header
{
    unsigned char header[80];       //80 bytes
    unsigned int triangles_number;  //4 bytes
    
} STL_HEADER; //84 bytes

//

bool stl_load_from_file(const char* path, STL_HEADER& stl_header, STL_TRIANGLE*& triangles, attribute_byte_count*& attributes)
{
    std::ifstream file;

    file.open(path, std::ios::in | std::ios::binary);
    
    if(file.is_open())
    {
        file.read(reinterpret_cast<char*>(&stl_header), sizeof(stl_header));
        
        triangles = new STL_TRIANGLE[stl_header.triangles_number];
        attributes = new attribute_byte_count[stl_header.triangles_number];
        
        for(unsigned int i = 0; i < stl_header.triangles_number; i++)
        {
            file.read(reinterpret_cast<char*>(&triangles[i]), sizeof(STL_TRIANGLE));
            file.read(reinterpret_cast<char*>(&attributes[i]), sizeof(attribute_byte_count));
        }

        file.close();

        return true;
    }
    
    file.close();

#ifdef STL_SHOW_ERRORS
    printf("file cannot opened! [load_stl_header_from_file]");
#endif

    return false;
}

template<typename _Type>
void stl_free(_Type*& pointer_array)
{
    delete[] pointer_array;
    pointer_array = nullptr;
}

#endif //STL_LOADER_ONLY_HEADER