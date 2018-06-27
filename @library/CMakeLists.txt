cmake_minimum_required(VERSION 3.5)
project(OpenXLSX.Library VERSION 0.5)

#=======================================================================================================================
# Determine C++ compiler vendor
#=======================================================================================================================
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(IS_CLANG TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(IS_GCC TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(IS_INTEL TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(IS_MSVC TRUE)
endif()

add_subdirectory(implementation/@zip)
add_subdirectory(implementation/@xml)

#=======================================================================================================================
# Set C/C++ compiler version
#=======================================================================================================================
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#=======================================================================================================================
# Set compiler flags
#=======================================================================================================================
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-value")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++")
    #set(CMAKE_VERBOSE_MAKEFILE ON)
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
    IF (MINGW)
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-use-linker-plugin")
        #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fwhole-program")
    ENDIF(MINGW)
ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")


#=======================================================================================================================
# Set project metadata
#=======================================================================================================================
set(PROJECT_VENDOR "Kenneth Troldal Balslev")
set(PROJECT_CONTACT "kenneth.balslev@gmail.com")
set(PROJECT_URL "https://github.com/troldal/OpenXLSX")
set(PROJECT_DESCRIPTION "A library for reading, writing and modifying Excel spreadsheets for C++17")

#=======================================================================================================================
# Find project files
#=======================================================================================================================
set(OPENXLSX_HEADERS
        implementation/headers/XLAbstractXMLFile.h
        implementation/headers/XLAppProperties.h
        implementation/headers/XLColor.h
        implementation/headers/XLContentTypes.h
        implementation/headers/XLCoreProperties.h
        implementation/headers/XLDocument.h
        implementation/headers/XLException.h
        implementation/headers/XLFont.h
        implementation/headers/XLRelationships.h
        implementation/headers/XLSharedStrings.h
        implementation/headers/XLSpreadsheetElement.h
        implementation/headers/XLStyles.h
        implementation/headers/XLTokenizer.h
        implementation/headers/XLWorkbook.h
        implementation/headers/XLChartsheet.h
        implementation/headers/XLColumn.h
        implementation/headers/XLRow.h
        implementation/headers/XLSheet.h
        implementation/headers/XLTemplate.h
        implementation/headers/XLWorksheet.h
        implementation/headers/XLCell.h
        implementation/headers/XLCellFormats.h
        implementation/headers/XLCellFormula.h
        implementation/headers/XLCellIterator.h
        implementation/headers/XLCellRange.h
        implementation/headers/XLCellReference.h
        implementation/headers/XLCellType.h
        implementation/headers/XLCellValue.h
        implementation/headers/XLDocumentProperties.h
        implementation/headers/XLSheetProperties.h
        interface/XLDocumentProperties.h
        interface/XLSheet.h
        interface/XLSheetProperties.h
        interface/XLWorkbook.h
        interface/XLDocument.h
        interface/XLCellReference.h
        interface/XLChartsheet.h
        interface/XLWorksheet.h interface/XLCell.h)

set(OPENXLSX_SOURCES
        implementation/sources/XLAbstractXMLFile.cpp
        implementation/sources/XLAppProperties.cpp
        implementation/sources/XLColor.cpp
        implementation/sources/XLContentTypes.cpp
        implementation/sources/XLCoreProperties.cpp
        implementation/sources/XLDocument.cpp
        implementation/sources/XLFont.cpp
        implementation/sources/XLRelationships.cpp
        implementation/sources/XLSharedStrings.cpp
        implementation/sources/XLSpreadsheetElement.cpp
        implementation/sources/XLStyles.cpp
        implementation/sources/XLTokenizer.cpp
        implementation/sources/XLWorkbook.cpp
        implementation/sources/XLChartsheet.cpp
        implementation/sources/XLColumn.cpp
        implementation/sources/XLRow.cpp
        implementation/sources/XLSheet.cpp
        implementation/sources/XLWorksheet.cpp
        implementation/sources/XLCell.cpp
        implementation/sources/XLCellFormats.cpp
        implementation/sources/XLCellFormula.cpp
        implementation/sources/XLCellIterator.cpp
        implementation/sources/XLCellRange.cpp
        implementation/sources/XLCellReference.cpp
        implementation/sources/XLCellValue.cpp)

#=======================================================================================================================
# Build OpenXLSX library
#=======================================================================================================================
add_library(OpenXLSXDepend STATIC $<TARGET_OBJECTS:xml> $<TARGET_OBJECTS:zlibstatic> $<TARGET_OBJECTS:zip> $<TARGET_OBJECTS:zip++>)
add_library(OpenXLSX STATIC ${OPENXLSX_HEADERS} ${OPENXLSX_SOURCES})
target_link_libraries(OpenXLSX PRIVATE OpenXLSXDepend)

#=======================================================================================================================
# Install OpenXLSX Library
#=======================================================================================================================
install (TARGETS OpenXLSX DESTINATION lib)
install (FILES ${WORKBOOK_HEADERS} ${SHEET_HEADERS} DESTINATION include/OpenXLSX)

