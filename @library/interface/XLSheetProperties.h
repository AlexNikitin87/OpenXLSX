//
// Created by Kenneth Balslev on 14/06/2018.
//

#ifndef OPENXLSX_XLSHEETPROPERTIES_H
#define OPENXLSX_XLSHEETPROPERTIES_H

namespace OpenXLSX {

//======================================================================================================================
//========== XLSheetType Enum ==========================================================================================
//======================================================================================================================

    /**
     * @brief The XLSheetType class is an enumeration of the available sheet types, e.g. Worksheet (ordinary
     * spreadsheets), and Chartsheet (sheets with only a chart).
     */
    enum class XLSheetType
    {
        WorkSheet, ChartSheet, DialogSheet, MacroSheet
    };


//======================================================================================================================
//========== XLSheetState Enum =========================================================================================
//======================================================================================================================

    /**
     * @brief The XLSheetState is an enumeration of the possible (visibility) states, e.g. Visible or Hidden.
     */
    enum class XLSheetState
    {
        Visible, Hidden, VeryHidden
    };
}

#endif //OPENXLSX_XLSHEETPROPERTIES_H
