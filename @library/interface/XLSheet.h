//
// Created by Kenneth Balslev on 14/06/2018.
//

#ifndef OPENXLSX_ALL_XLSHEET_H
#define OPENXLSX_ALL_XLSHEET_H

#include "../implementation/headers/XLSheet.h"
#include "XLSheetProperties.h"

namespace OpenXLSX {

    /**
     * @brief
     */
    class XLSheet {
    public:

        /**
         * @brief
         * @param sheet
         */
        explicit XLSheet(Impl::XLSheet &sheet)
                : m_sheet(&sheet) {}

        /**
          * @brief The copy constructor.
          * @param other The object to be copied.
          * @note The default copy constructor is used, i.e. only shallow copying of pointer data members.
          * @todo Can this method be deleted?
          */
        XLSheet(const XLSheet &other) = default;

        /**
         * @brief
         * @param other
         */
        XLSheet(XLSheet &&other) = default;

        /**
         * @brief The destructor
         * @note The default destructor is used, since cleanup of pointer data members is not required.
         */
        virtual ~XLSheet() = default;

        /**
         * @brief Assignment operator
         * @return A reference to the new object.
         * @note The default assignment operator is used, i.e. only shallow copying of pointer data members.
         * @todo Can this method be deleted?
         */
        XLSheet &operator=(const XLSheet &other) = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLSheet &operator=(XLSheet &&other) = default;

        /**
         * @brief Method to retrieve the name of the sheet.
         * @return A std::string with the sheet name.
         */
        virtual const std::string &Name() const { return m_sheet->Name(); }

        /**
         * @brief Method for renaming the sheet.
         * @param name A std::string with the new name.
         */
        virtual void SetName(const std::string &name) { m_sheet->SetName(name); }

        /**
         * @brief Method for getting the current visibility state of the sheet.
         * @return An XLSheetState enum object, with the current sheet state.
         */
        virtual const XLSheetState &State() const { return m_sheet->State(); }

        /**
         * @brief Method for setting the state of the sheet.
         * @param state An XLSheetState enum object with the new state.
         */
        virtual void SetState(XLSheetState state) { m_sheet->SetState(state); }

        /**
         * @brief Method to get the type of the sheet.
         * @return An XLSheetType enum object with the sheet type.
         */
        virtual const XLSheetType &Type() const { return m_sheet->Type(); }

        /**
         * @brief Method for cloning the sheet.
         * @param newName A std::string with the name of the clone
         * @return A pointer to the cloned object.
         * @note This is a pure abstract method. I.e. it is implemented in subclasses.
         */
        virtual XLSheet *Clone(const std::string &newName) = 0;

        /**
         * @brief Method for getting the index of the sheet.
         * @return An int with the index of the sheet.
         */
        virtual unsigned int Index() const {
            return m_sheet->Index();
        }

        /**
         * @brief Method for setting the index of the sheet. This effectively moves the sheet to a different position.
         */
        virtual void SetIndex() {
            m_sheet->SetIndex();
        }

    protected:
        Impl::XLSheet *m_sheet;
    };
}

#endif //OPENXLSX_ALL_XLSHEET_H
