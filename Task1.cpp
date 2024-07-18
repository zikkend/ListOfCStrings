#include <iostream>

#include "ListOfStrings.h"

int main()
{
    char** list = nullptr;
    {
        StringListInit(list);

        StringListAdd(list, (char*)"a");
        StringListAdd(list, (char*)"c");
        StringListAdd(list, (char*)"d");
        StringListAdd(list, (char*)"b");
        StringListAdd(list, (char*)"a");
        StringListAdd(list, (char*)"f");
        StringListAdd(list, (char*)"b");
        StringListAdd(list, (char*)"m");

        PrintStringList((const char**)list);

        std::cout << "Remove all duplicates" << std::endl;

        StringListRemoveDuplicates(list);
        PrintStringList((const char**)list);

        StringListDestroy(list);
    }
    //{
    //    StringListInit(list);

    //    StringListAdd(list, (char*)"11");
    //    StringListAdd(list, (char*)"5");
    //    StringListAdd(list, (char*)"3");
    //    PrintStringList((const char**)list);

    //    StringListAdd(list, (char*)"41");
    //    StringListAdd(list, (char*)"3");
    //    StringListAdd(list, (char*)"2112");
    //    StringListAdd(list, (char*)"5");
    //    StringListAdd(list, (char*)"3");
    //    PrintStringList((const char**)list);

    //    std::cout << "Indexes:" << StringListIndexOf(list, (char*)"1") << " "
    //        << StringListIndexOf(list, (char*)"4") << std::endl;

    //    //StringListRemove(list, (char*)"1");
    //    //StringListRemove(list, (char*)"3");
    //    //PrintStringList((const char**)list);

    //    StringListRemoveDuplicates(list);
    //    PrintStringList((const char**)list);

    //    StringListReplaceInStrings(list, "1", "abc");
    //    PrintStringList((const char**)list);
    //}
    //
    //{
    //    StringListDestroy(list);

    //    StringListInit(list);
    //    StringListAdd(list, (char*)"1");
    //    StringListAdd(list, (char*)"5");
    //    StringListAdd(list, (char*)"3");
    //    StringListAdd(list, (char*)"8");
    //    StringListAdd(list, (char*)"3");
    //    StringListAdd(list, (char*)"20");
    //    StringListAdd(list, (char*)"2");
    //    StringListAdd(list, (char*)"9");
    //    PrintStringList((const char**)list);

    //    StringListSort(list);
    //    PrintStringList((const char**)list);


    //    StringListDestroy(list);
    //}
    
}

