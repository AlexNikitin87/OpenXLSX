/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXLSX_ALL_XLDOCUMENT_H
#define OPENXLSX_ALL_XLDOCUMENT_H

#include "../implementation/headers/XLDocument.h"
#include "XLWorkbook.h"
#include "XLDocumentProperties.h"

namespace OpenXLSX {
    /**
     * @brief
     */
    class XLDocument {
    public:

        /**
         * @brief
         */
        explicit XLDocument()
                : m_document(std::make_shared<Impl::XLDocument>()) {}

        /**
         * @brief
         * @param name
         */
        explicit XLDocument(const std::string &name)
                : m_document(std::make_shared<Impl::XLDocument>(name)) {}

        /**
         * @brief
         * @param other
         */
        XLDocument(const XLDocument &other) = default;

        /**
         * @brief
         * @param other
         */
        XLDocument(const XLDocument &&other) = default;

        /**
         * @brief Destructor
         */
        virtual ~XLDocument() = default;

        /**
         * @brief Open the .xlsx file with the given path
         * @param fileName The path of the .xlsx file to open
         * @todo Consider opening the zipped files as streams, instead of unpacking to a temporary folder
         */
        void OpenDocument(const std::string &fileName) {
            m_document->OpenDocument(fileName);
        }

        /**
         * @brief Create a new .xlsx file with the given name.
         * @param fileName The path of the new .xlsx file.
         */
        void CreateDocument(const std::string &fileName) {
            m_document->CreateDocument(fileName);
        }

        /**
         * @brief Close the current document
         */
        void CloseDocument() {
            m_document->CloseDocument();
            m_document = nullptr;
        }

        /**
         * @brief Save the current document using the current filename, overwriting the existing file.
         * @return true if successful; otherwise false.
         */
        bool SaveDocument() {
            return m_document->SaveDocument();
        }

        /**
         * @brief Save the document with a new name. If a file exists with that name, it will be overwritten.
         * @param fileName The path of the file
         * @return true if successful; otherwise false.
         */
        bool SaveDocumentAs(const std::string &fileName) {
            return m_document->SaveDocumentAs(fileName);
        }

        /**
         * @brief Get the filename of the current document, e.g. "spreadsheet.xlsx".
         * @return A std::string with the filename.
         */
        std::string DocumentName() const {
            return m_document->DocumentName();
        }

        /**
         * @brief Get the full path of the current document, e.g. "drive/blah/spreadsheet.xlsx"
         * @return A std::string with the path.
         */
        std::string DocumentPath() const {
            return m_document->DocumentPath();
        }

        /**
         * @brief Get the underlying workbook object.
         * @return A pointer to the XLWorkbook object
         */
        XLWorkbook Workbook() {
            return XLWorkbook(*m_document->Workbook());
        }

        /**
         * @brief Get the underlying workbook object, as a const object.
         * @return A const pointer to the XLWorkbook object.
         */
        const XLWorkbook Workbook() const {
            return XLWorkbook(*m_document->Workbook());
        }

        /**
         * @brief Get the requested document property.
         * @param theProperty The name of the property to get.
         * @return The property as a string
         */
        std::string GetProperty(XLDocumentProperties theProperty) const {
            return m_document->GetProperty(theProperty);
        }

        /**
         * @brief Set a property
         * @param theProperty The property to set.
         * @param value The value of the property, as a string
         */
        void SetProperty(XLDocumentProperties theProperty,
                         const std::string &value) {
            m_document->SetProperty(theProperty, value);
        }

        /**
         * @brief Delete the property from the document
         * @param propertyName The property to delete from the document
         */
        void DeleteProperty(const std::string &propertyName) {
            m_document->DeleteProperty(propertyName);
        }

    private:
        std::shared_ptr<Impl::XLDocument> m_document;

    };

}

#endif //OPENXLSX_ALL_XLDOCUMENT_H
