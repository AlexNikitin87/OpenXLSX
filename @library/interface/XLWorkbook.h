//
// Created by KBA012 on 14-06-2018.
//

#ifndef OPENXLSX_ALL_XLWORKBOOK_H
#define OPENXLSX_ALL_XLWORKBOOK_H


#include "../implementation/headers/XLWorkbook.h"
#include "XLSheet.h"
#include "XLWorksheet.h"
#include "XLChartsheet.h"

namespace OpenXLSX
{
    /**
     * @brief An interface class to an Impl::XLWorkbook object. This class holds a raw pointer to the underlying
     * Impl::XLWorkbook object. Destruction will be handled by the classes in the Impl namespace.
     */
    class XLWorkbook
    {
    public:
        explicit XLWorkbook(Impl::XLWorkbook& workbook)
            : m_workbook(&workbook) {}

        /**
         * @brief Copy Constructor.
         * @param other The XLWorkbook object to be copied.
         * @note The copy constructor has been explicitly deleted, as XLWorkbook objects should not be copied.
         */
        XLWorkbook(const XLWorkbook &other) = default;

        /**
         * @brief Copy assignment operator.
         * @param other The XLWorkbook object to be assigned to the current.
         * @return A reference to *this
         * @note The copy assignment operator has been explicitly deleted, as XLWorkbook objects should not be copied.
         */
        XLWorkbook &operator=(const XLWorkbook &other) = default;

        /**
         * @brief Move constructor.
         * @param other The XLWorkbook to be moved.
         * @note The move constructor has been explicitly deleted, as XLWorkbook objects should not be moved.
         */
        XLWorkbook(XLWorkbook &&other) = default;

        /**
         * @brief Move assignment operator.
         * @param other The XLWorkbook to be move assigned.
         * @return A reference to *this
         * @note The move assignment operator has been explicitly deleted, as XLWorkbook objects should not be moved.
         */
        XLWorkbook &operator=(XLWorkbook &&other) = default;

        /**
         * @brief Destructor
         * @note Default destructor specified
         */
        virtual ~XLWorkbook() = default;

        /**
         * @brief Get the sheet (worksheet or chartsheet) at the given index.
         * @param index The index et which the desired sheet is located.
         * @return A pointer to an XLAbstractSheet with the sheet at the index.
         * @todo This method is currently unimplemented.
         * @todo What should happen if the index is invalid?
         */
        XLSheet Sheet(unsigned int index) { return XLSheet(*m_workbook->Sheet(index)); }

        /**
         * @brief Get the sheet (worksheet or chartsheet) with the given name.
         * @param sheetName The name at which the desired sheet is located.
         * @return A pointer to an XLAbstractSheet with the sheet at the index.
         * @todo This method is currently unimplemented.
         * @todo What should happen if the name is invalid?
         */
        XLSheet Sheet(const std::string &sheetName) { return XLSheet(*m_workbook->Sheet(sheetName)); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        XLWorksheet Worksheet(const std::string &sheetName) { return XLWorksheet(*m_workbook->Worksheet(sheetName)); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        const XLWorksheet Worksheet(const std::string &sheetName) const { return XLWorksheet(*m_workbook->Worksheet(sheetName)); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        XLChartsheet Chartsheet(const std::string &sheetName) { return XLChartsheet(*m_workbook->Chartsheet(sheetName)); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        const XLChartsheet Chartsheet(const std::string &sheetName) const { return XLChartsheet(*m_workbook->Chartsheet(sheetName)); }

        /**
         * @brief
         * @param sheetName
         */
        void DeleteSheet(const std::string &sheetName) { m_workbook->DeleteSheet(sheetName); }

        /**
         * @brief Add a new worksheet to the workbook, with the given name and index.
         * @param sheetName The name of the worksheet.
         * @param index The index at which the worksheet should be inserted.
         */
        void AddWorksheet(const std::string &sheetName, unsigned int index = 0) { m_workbook->AddWorksheet(sheetName, index); }

        /**
         * @brief Clone an existing worksheet.
         * @param extName The name of the worksheet to clone.
         * @param newName The name of the cloned worksheet.
         * @param index The index at which the worksheet should be inserted.
         * @todo The function works, but Excel reports errors when opening.
         * @todo Is it possible to have a common CloneSheet function?
         */
        void CloneWorksheet(const std::string &extName,
                            const std::string &newName,
                            unsigned int index = 0) { m_workbook->CloneWorksheet(extName, newName, index); }

        /**
         * @brief Add a new chartsheet to the workbook, with the given name and index.
         * @param sheetName The name of the chartsheet.
         * @param index The index at which the chartsheet should be inserted.
         * @todo This method is currently unimplemented.
         */
        void AddChartsheet(const std::string &sheetName, unsigned int index = 0) { m_workbook->AddChartsheet(sheetName, index); }

        /**
         * @brief
         * @param index
         */
        void MoveSheet(unsigned int index) { m_workbook->MoveSheet(index); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        unsigned int IndexOfSheet(const std::string &sheetName) { return m_workbook->IndexOfSheet(sheetName); }

        /**
         * @brief
         * @param sheetName
         * @param index
         */
        void SetIndexOfSheet(const std::string &sheetName, unsigned int index) {m_workbook->SetIndexOfSheet(sheetName, index); }

        /**
         * @brief
         * @return
         */
        unsigned int SheetCount() const { return m_workbook->SheetCount(); }

        /**
         * @brief
         * @return
         */
        unsigned int WorksheetCount() const { return m_workbook->WorksheetCount(); }

        /**
         * @brief
         * @return
         */
        unsigned int ChartsheetCount() const { return m_workbook->ChartsheetCount(); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        bool SheetExists(const std::string &sheetName) const { return m_workbook->SheetExists(sheetName); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        bool WorksheetExists(const std::string &sheetName) const { return m_workbook->WorksheetExists(sheetName); }

        /**
         * @brief
         * @param sheetName
         * @return
         */
        bool ChartsheetExists(const std::string &sheetName) const { return m_workbook->ChartsheetExists(sheetName); }

        /**
         * @brief
         */
        void DeleteNamedRanges() {m_workbook->DeleteNamedRanges(); }


    private:
        Impl::XLWorkbook* m_workbook;
    };

}

#endif //OPENXLSX_ALL_XLWORKBOOK_H
