//
// Created by Kenneth Balslev on 14/06/2018.
//

#ifndef OPENXLSX_ALL_XLDOCUMENTPROPERTIES_H
#define OPENXLSX_ALL_XLDOCUMENTPROPERTIES_H


namespace OpenXLSX {

//======================================================================================================================
//========== XLDocumentProperties Enum =================================================================================
//======================================================================================================================

    /**
     * @brief The XLDocumentProperties class is an enumeration of the possible properties (metadata) that can be set
     * for a XLDocument object (and .xlsx file)
     */
    enum class XLDocumentProperties
    {
        Title,
        Subject,
        Creator,
        Keywords,
        Description,
        LastModifiedBy,
        LastPrinted,
        CreationDate,
        ModificationDate,
        Category,
        Application,
        DocSecurity,
        ScaleCrop,
        Manager,
        Company,
        LinksUpToDate,
        SharedDoc,
        HyperlinkBase,
        HyperlinksChanged,
        AppVersion
    };
}


#endif //OPENXLSX_ALL_XLDOCUMENTPROPERTIES_H
