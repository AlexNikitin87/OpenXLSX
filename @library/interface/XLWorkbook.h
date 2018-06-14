//
// Created by KBA012 on 14-06-2018.
//

#ifndef OPENXLSX_ALL_XLWORKBOOK_H
#define OPENXLSX_ALL_XLWORKBOOK_H

#include "../implementation/headers/XLDocument.h"
#include "../implementation/headers/XLWorkbook.h"

namespace OpenXLSX
{
    class XLWorkbook
    {
    public:
        explicit XLWorkbook() : m_document(nullptr),
                                m_workbook(nullptr) {}

        explicit XLWorkbook(const std::string& name)


    private:
        Impl::XLDocument* m_document;
        Impl::XLWorkbook* m_workbook;
    };

}

#endif //OPENXLSX_ALL_XLWORKBOOK_H
