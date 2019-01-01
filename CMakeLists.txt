cmake_minimum_required(VERSION 3.12)
project(YourSQL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(./googletest)
include_directories(./googletest/include)
link_directories(./googltest)

SET(SOURCE
        src/PF/bufmanager/BufPageManager.h
        src/PF/bufmanager/FindReplace.h
        src/PF/fileio/FileManager.h
        src/PF/fileio/FileTable.h
        src/PF/utils/compare.h
        src/PF/utils/MyBitMap.h
        src/PF/utils/MyHashMap.h
        src/PF/utils/MyLinkList.h
        src/PF/utils/pagedef.h
        src/PF/pf.h
        src/RM/RID.cpp
        src/RM/rm.h
        src/RM/rm_internal.h
        src/RM/RM_FileHandle.cpp
        src/RM/RM_FileScan.cpp
        src/RM/RM_Manager.cpp
        src/RM/RM_Record.cpp
        src/IX/IX_Manager.cpp
        src/IX/IX_Manager.h
        src/IX/IX_IndexHandle.cpp
        src/IX/IX_IndexHandle.h
        src/IX/IX_IndexScan.cpp
        src/IX/IX_IndexScan.h
        src/IX/IX_PUBLIC.h
        src/IX/IX_PRIVATE.h
        src/IX/BPlusTreeNode.cpp
        src/IX/BPlusTreeNode.h
        src/RM_Test/rmtest.h
        src/RM_Test/test_basic1.cpp
        src/RM_Test/test_massive1.cpp
        src/PF_Test/pftest.h
        src/PF_Test/test.cpp
        src/RM_Test/test_error.cpp
        src/RM/RM_Error.cpp
        src/RM/RM_Error.h
        src/IX_Test/ixtest.h
        src/IX_Test/test.cpp
        src/SM/SM_PUBLIC.h
        src/SM/SM_PRIVATE.h
        src/SM/SM_Manager.cpp
        src/SM/SM_Manager.h
        src/Parser/parser.h
        src/Parser/lex.yy.cpp
        src/Parser/yacc.tab.h
        src/Parser/astree.cpp
        src/Parser/astree.h
        src/QL/QL_PRIVATE.h
        src/QL/QL_PUBLIC.h
        src/QL/QL_Manager.h
        src/QL/QL_Manager.cpp
        src/Printer/Printer.cpp
        src/Printer/Printer.h
        src/Printer/StdoutPrinter.cpp
        src/Printer/StdoutPrinter.h src/QL/Selector.cpp src/QL/Selector.h src/utilities.cpp src/QL/SelectResult.cpp src/QL/SelectResult.h src/Regex/Regex.cpp src/Regex/Regex.h)


SET(GTEST 1)

IF(GTEST)
    SET(SOURCE ${SOURCE}
            src/gtestcase/IX1.cpp
            src/gtestcase/QL1.cpp
            src/gtestcase/RM1.cpp
            src/gtestcase/SM1.cpp
            src/gtestcase/Regex1.cpp
            )
    set(LIBRARIES gtest_main)
    # for QL print control
    add_compile_definitions(GTEST=OPEN)
else()
    SET(SOURCE ${SOURCE}
            src/RM_Test/test_scan.cpp
            src/testmain.cpp
            )
endif()

add_executable(YourSQL
#        src/Parser/yacc.tab.cpp
#        src/Parser/yacc.tab.h
        ${SOURCE})

#set(LIBRARIES test)
set(LIBRARIES ${LIBRARIES}
#        gtest
#        gtest_main
        pthread)


target_link_libraries(YourSQL ${LIBRARIES})
