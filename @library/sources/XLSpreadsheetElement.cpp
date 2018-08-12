//
// Created by KBA012 on 18-12-2017.
//

#include "../headers/XLSpreadsheetElement.h"
#include "../headers/XLDocument.h"

namespace OpenXLSX
{
    /**
     * @details
     */
    XLSpreadsheetElement::XLSpreadsheetElement(XLDocumentImpl &parent)
        : m_document(&parent),
          m_workbook(&parent.Workbook())
    {

    }

    /**
     * @details
     */
    XLWorkbook *XLSpreadsheetElement::ParentWorkbook()
    {
        return const_cast<XLWorkbook *>(static_cast<const XLSpreadsheetElement *>(this)->ParentWorkbook());
    }

    /**
     * @details
     */
    const XLWorkbook * XLSpreadsheetElement::ParentWorkbook() const
    {
        return m_workbook;
    }

    /**
     * @details
     */
    XLDocumentImpl * XLSpreadsheetElement::ParentDocument()
    {
        return const_cast<XLDocumentImpl *>(static_cast<const XLSpreadsheetElement *>(this)->ParentDocument());
    }

    /**
     * @details
     */
    const XLDocumentImpl * XLSpreadsheetElement::ParentDocument() const
    {
        return m_document;
    }
}