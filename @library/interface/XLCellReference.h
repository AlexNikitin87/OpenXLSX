//
// Created by KBA012 on 27-06-2018.
//

#ifndef OPENXLSX_ALL_XLCELLREFERENCE_H
#define OPENXLSX_ALL_XLCELLREFERENCE_H

#include "../implementation/headers/XLCellReference.h"

namespace OpenXLSX
{

    class XLCellReference
    {
    public:
        explicit XLCellReference(const std::string &cellAddress = "") : m_cellReference(Impl::XLCellReference(cellAddress)) {}

        XLCellReference (unsigned long row,
                         unsigned int column) : m_cellReference(Impl::XLCellReference(row, column)) {}



    private:
        Impl::XLCellReference m_cellReference;

    };

}


#endif //OPENXLSX_ALL_XLCELLREFERENCE_H
