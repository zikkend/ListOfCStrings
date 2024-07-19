#include "ListOfStrings.h"

const size_t DEFAULT_CAPASITY = 2;
const size_t SIZE_OF_META_STRING = 100;

inline static void GetSizeAndCapacity(const char* meta_string, size_t& size, size_t& capacity)
{
    sscanf_s(meta_string, "%d %d", &size, &capacity);
}

inline static void UpdateMetaString(char** list, size_t size, size_t capacity)
{
    char meta_string[SIZE_OF_META_STRING];
    sprintf_s(meta_string, SIZE_OF_META_STRING, "%d %d", size, capacity);
    strcpy_s(list[0], SIZE_OF_META_STRING, meta_string);
}

void PrintStringList(const char** list)
{
    if (list == nullptr)
    {
        std::cout << "list = nullptr";
        return;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    std::cout << "Size: " << size << " Capacity: " << capacity << std::endl;

    for (size_t i = 1; i < size + 1; ++i)
    {
        std::cout << list[i] << std::endl;
    }
    std::cout << std::endl;
}

void StringListInit(char**& list)
{
    if (list != nullptr)
    {
        std::cout << "list must be nullptr" << std::endl;
        return;
    }

    list = (char**)malloc((DEFAULT_CAPASITY + 1) * sizeof(char*));
    if (list == nullptr)
    {
        std::cout <<  "Failed to allocate memory for the list" << std::endl;
        return;
    }

    // Setting meta string sush as "0 2" wher 0 is size and 2 - capacity(not including meta string)
    list[0] = (char*)malloc(SIZE_OF_META_STRING * sizeof(char));
    sprintf_s(list[0], SIZE_OF_META_STRING, "%d %d", 0, DEFAULT_CAPASITY);
}

void StringListDestroy(char**& list)
{
    if (list == nullptr)
    {
        return;
    }
 
    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    for (size_t i = 0; i < size + 1; i++)
    {
        free(list[i]);
    }
    free(list);
    list = nullptr;

}

void StringListAdd(char**& list, char* str)
{
    if (list == nullptr || str == nullptr)
    {
        std::cout << "list and str mustn't be nullptr" << std::endl;
        return;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    if (size == capacity)
    {
        capacity *= 2;
        char** new_list = (char**)realloc(list, (capacity + 1) * sizeof(char*));

        if (new_list == nullptr)
        {
            std::cout << "Failed to allocate memory for the list when adding" << std::endl;
            return;
        }

        list = new_list;
    }

    size_t new_string_size = (strlen(str) + 1);
    list[size + 1] = (char*)malloc(new_string_size * sizeof(char));
    strcpy_s(list[size + 1], new_string_size, str);

    UpdateMetaString(list, size + 1, capacity);
}

void StringListRemove(char** list, char* str)
{
    if (list == nullptr || str == nullptr)
    {
        return;
    }
   
    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    for (size_t i = 1; i < size + 1; ++i)
    {
        if (strcmp(list[i], str) == 0)
        {
            free(list[i]);

            // Shift elements to the left
            for (size_t j = i; j < size; ++j)
                list[j] = list[j + 1];

            size--;
            i--;
        }
    }
    
    UpdateMetaString(list, size, capacity);
}

int StringListSize(char** list)
{
    if (list == nullptr)
    {
        return 0;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);
    return size;

}

int StringListIndexOf(char** list, char* str)
{
    if (list == nullptr || str == nullptr)
    {
        return -1;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    for (size_t i = 1; i < size + 1; ++i)
    {
        if (strcmp(list[i], str) == 0)
        {
            return i;
        }
    }
    return -1;
}

void StringListRemoveDuplicates(char**& list)
{
    if (list == nullptr)
    {
        return;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    for (size_t i = 1; i < size; ++i) {
        for (size_t j = i + 1; j < size + 1; ++j) {
            if (strcmp(list[i], list[j]) == 0) {
                free(list[j]);

                // Shift elements to the left
                for (size_t k = j; k < size; ++k)
                    list[k] = list[k + 1];
                size--;
                j--;
            }
        }
    }

    UpdateMetaString(list, size, capacity);
}

inline static size_t CalculateReplacementsCount(const char* str, const char* before, const char* after)
{
    size_t count = 0, len_before = strlen(before);
    char* current_position = (char*)str,* before_position;
    for (; before_position = strstr(current_position, before); ++count)
    {
        current_position = before_position + len_before;
    }
    return count;
}

char* ReplaceSubstring(const char* str, const char* before, const char* after)
{
    if (before == nullptr || after == nullptr)
    {
        return nullptr;
    }

    size_t len_before = strlen(before);
    if (len_before == 0)
    {
        return nullptr;
    }
    size_t len_after = strlen(after);
    

    size_t count = CalculateReplacementsCount(str, before, after);
    if (count == 0)
    {
        return nullptr;
    }

    size_t new_string_len = strlen(str) + (len_after - len_before) * count + 1;
    char* result = (char*)malloc(new_string_len);
    if (!result)
    {
        return nullptr;
    }
    result[0] = '\0';

    // Replace all occurrences of 'before' with 'after'
    size_t len_front;
    char* current_position;
    while (count--) {
        current_position = strstr((char*)str, before);
        len_front = current_position - str;
        strncat_s(result, new_string_len, str, len_front);
        strcat_s(result, new_string_len, after);
        str += len_front + len_before;
    }
    strcat_s(result, new_string_len, str);
    return result;
}

void StringListReplaceInStrings(char** list, const char* before, const char* after)
{
    if (list == nullptr || before == nullptr || after == nullptr)
    {
        return;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    for (size_t i = 1; i < size + 1; ++i)
    {
        char* new_string = ReplaceSubstring(list[i], before, after);
        if (new_string != nullptr)
        {
            free(list[i]);
            list[i] = new_string;
        }
    }
}

inline static int CompareStrings(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}

void StringListSort(char** list)
{
    if (list == nullptr)
    {
        return;
    }

    size_t size, capacity;
    GetSizeAndCapacity(list[0], size, capacity);

    qsort(list + 1, size, sizeof(char*), CompareStrings);
}