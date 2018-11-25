cmake_minimum_required(VERSION 3.12)
project(YourSQL)

set(CMAKE_CXX_STANDARD 14)

add_executable(YourSQL
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
        src/testmain.cpp
        src/RM_Test/rmtest.h
        src/RM_Test/test_basic1.cpp
        src/RM_Test/test_massive1.cpp
        src/PF_Test/pftest.h
        src/PF_Test/test.cpp src/RM_Test/test_error.cpp src/RM/RM_Error.cpp src/RM/RM_Error.h)
