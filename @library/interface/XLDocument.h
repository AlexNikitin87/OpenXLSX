//
// Created by Kenneth Balslev on 14/06/2018.
//

#ifndef OPENXLSX_ALL_XLDOCUMENT_H
#define OPENXLSX_ALL_XLDOCUMENT_H

#include "../implementation/headers/XLDocument.h"
#include "XLWorkbook.h"
#include "XLDocumentProperties.h"

namespace OpenXLSX
{
    class XLDocument
    {
    public:
        explicit XLDocument()
            : m_document(std::make_shared<Impl::XLDocument>()) {}

        explicit XLDocument(const std::string& name)
            : m_document(std::make_shared<Impl::XLDocument>(name)) {}

        XLDocument(const XLDocument &other) = default;

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
        void CreateDocument(const std::string &fileName){
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
