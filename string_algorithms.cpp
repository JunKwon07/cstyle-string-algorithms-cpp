#include "p_4_header.hpp"

//----------------------#1----------------------------------
std::size_t length (char const *a){
    if (!a){
        return 0;
    }

    int count{};
    for (int i{}; a[i]; ++i){  
        ++count;
    }
    return count; 
}


void testlength(){
    char const* input[]{ nullptr, "s", "BAnana" , "water", "!!!!,,99../32"};
    std::size_t output[]{0, 1, 6, 5, 13};
    for (int i{}; i < 5; ++i){ 
        std::size_t result{length(input[i])};
        std::cout << (result == output[i]) << std::endl;
    }
}

//----------------------#2----------------------------------
int compare (char const* str1, char const* str2){
    assert (str1 && str2);


    if (*str1 == '\0' && *str2 == '\0'){
        return 0;
    }
    if (*str1 == 0 && *str2){
        return -1;
    }
    if (*str1  && *str2 == 0){
        return 1;
    } 
    
    if (*str1 < *str2){
        return -1;
    } 
    if (*str1 > *str2){
        return 1;
    }
    
    return compare(str1 + 1, str2 + 1);
    
}

void testcompare(){
    char const* input1[]{""};
    char const* input2[]{""}; 
    for (int i{}; i < 1; ++i){
        int result(compare(input1[i], input2[i]));
        std::cout << result << std::endl;
    }
    
}

//----------------------#3----------------------------------
void assign (char* str1, char const* str2){
    if (!str1){
        return;
    }
    if (!str2){
        return;
    }

    std::size_t n {length(str2)};
    for (std::size_t i{}; i < n; ++i){
        str1[i] = str2[i];
    }
    str1[n] = '\0';

}

void testassign(){
    const char* str2{"cat"};
    std::size_t n{length(str2)};
    char* input1{new(std::nothrow) char[n]};
    assign(input1, str2);
    std::cout << input1 << std::endl;
    std::cout << str2 << std::endl;
    std::cout << std::endl;
    assign(input1, "car");
    std::cout << input1 << std::endl;
}



//----------------------#4----------------------------------
unsigned int distance( char const *str1, char const *str2 ){
    if(length(str1) == 0 || !str1){
        return (length(str2));
    }
    if(length(str2) == 0 || !str2){
        return (length(str1));
    }

    if (*str1 == *str2){
        return distance(str1 + 1, str2 + 1);
    }
    
    unsigned int min{std::min((1 + distance(str1 + 1, str2)), (1 + distance(str1, str2 +1)))};
    return (std::min (min, (1 + distance(str1 + 1, str2 + 1))));
    
}


void testdistance(){
    char const* word1{""};
    char const* word2{"lllll"}; 
    std::cout << distance(word1, word2) << std::endl;
}


//----------------------#5----------------------------------
std::size_t is_sorted(char *array[], std::size_t capacity ){
    if (!array || capacity == 0){
        return 0;
    }

    for (int i{1}; i < capacity; ++i){
        if (compare(array[i-1], array[i]) == 1){
            
            return i;
        }
    }
    return capacity;
}

void testissorted(){ 
    std::size_t capacity{5};
    char* input[capacity]{"z", "e", "c", "diamond", "e"};
    std::size_t output{is_sorted(input, capacity)};
    std::cout << output << std::endl;
}



//----------------------#6----------------------------------
void insert(char *array[], std::size_t capacity ){
    if (!array || capacity == 0){
        return;
    }
    char* temp{new(std::nothrow) char[length(array[capacity-1])+1]}; 
    assign(temp, array[capacity-1]);
    int i{capacity-1};
    for ( ;i > 0 && (compare (array[i-1], temp) == 1); --i){
        // array[i] = array[i-1];
        assign(array[i], array[i-1]);     
    }
    // array[i] = temp;
    assign(array[i], temp);
    delete [] temp;

}

void testinsert(){
    std::size_t capacity{5};
    char* input[capacity]{"apple", "banana", "carrot", "diamond", "banana"};
    for (int i{}; i < capacity; ++i){
        std::cout << input[i] << std::endl;
    }
    std::cout << std::endl;
    insert(input, capacity);
    std::cout << "test result:" << std::endl << std::endl;
    for (int i{}; i < capacity; ++i){
        std::cout << input[i] << std::endl;
    }
}

//----------------------#7----------------------------------
void insertion_sort( char *array[], std::size_t capacity ){
    if (!array || capacity == 0){
        return;
    }
    for (int k{2}; k <= capacity; ++k){
        insert(array, k);
    } 
}

void testinsertion_sort(){
    std::size_t capacity{6};
    char* input[capacity]{"a", "b", "z", "d", "e", "f"};
    for (int i{}; i < capacity; ++i){
        std::cout << input[i] << std::endl;
    }
    std::cout << std::endl;
    insertion_sort(input, capacity);
    std::cout << "test:" << std::endl << std::endl;
    for (int i{}; i < capacity; ++i){
        std::cout << input[i] << std::endl;
    }
}

//----------------------#8----------------------------------
std::size_t remove_duplicates( char *array[], std::size_t capacity ){
    if (!array || capacity <= 0 ){
        return 0;
    }
    std::size_t i{};
    for (std::size_t j{1}; j < capacity; ++j){
        while (compare(array[i], array[j]) == 0) {
            ++j;
        }
        array[(i++) +1] = array[j];
    }
    for (std::size_t k{i}; k < (capacity-1); ++k){
        array[k+1] = array[k];
    }

    return i+1;
}

void testremove_duplicates(){
    std::size_t capacity {5};
    char* input[capacity]{"apple", "apple", "apple", "banana", "can"};
    for (int i{}; i < capacity; ++i){
        std::cout << input[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << remove_duplicates(input, capacity) << std::endl;
    std::cout << std::endl;
    for (int i{}; i < capacity; ++i){
        std::cout << input[i] << std::endl;
    }
}


//----------------------#9----------------------------------
std::size_t find (char *array[], std::size_t capacity, char const *str){
    assert(str);

    if (!array || capacity <= 0){
        return 0;
    }

    unsigned int IndexOfMinDistance{0};
    unsigned int MinDistance {20};
    for (int i{}; i < capacity; ++i){
        unsigned int d {distance (array [i], str)};
        if (d == 0) {
            return i;
        } 

        if (d < MinDistance){
            IndexOfMinDistance = i;
            MinDistance = d;
        }
    }
    return IndexOfMinDistance;  
}


void testfind(){
    std::size_t capacity{6};
    char* input[capacity]{"apple", "banana", "canada", "donut", "elastic", "fire"};
    char const* word{"lllll"};

    std::cout << find(input, capacity, word) << std::endl;
}

// std::size_t find (char *array[], std::size_t capacity, char const *str){
//     if (!array || capacity <= 0){
//         return 0;
//     }
//     if (!str){
//         return 
//     }

//     unsigned int IndexOfMinDistance{0};
//     unsigned int MinDistance {20};
//     for (int i{}; i < capacity; ++i){
//         if (compare (array[i], str) == 0){
//             return i;
//         }
//         else {
//             unsigned int d {distance (array [i], str)};
//             if (d < MinDistance){
//                 IndexOfMinDistance = i;
//                 MinDistance = d;
//             }
//         }
//     }
//     return IndexOfMinDistance;  
// }




//----------------------#11----------------------------------
void free_word_array( char** word_array ){
    if (!word_array){
        return;
    } 
    if (word_array[0]){
        delete[] word_array[0];
    }
    delete[] word_array;
}







// int main(){
//     //testlength();
//     //testcompare();
//     //testassign();
//     //testdistance();
//     //testissorted();
//     //testinsert();
//     //testinsertion_sort();
//     //testremove_duplicates();
//     testfind();
// }   