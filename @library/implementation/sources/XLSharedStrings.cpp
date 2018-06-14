//
// Created by Troldal on 01/09/16.
//

#include "../headers/XLSharedStrings.h"
#include "../headers/XLDocument.h"

using namespace std;
using namespace OpenXLSX::Impl;

/**
 * @details Constructs a new XLSharedStrings object. Only one (common) object is allowed per XLDocument instance.
 * A filepath to the underlying XML file must be provided.
 */
XLSharedStrings::XLSharedStrings(XLDocument &parent,
                                 const std::string &filePath)
    : XLAbstractXMLFile(parent, filePath),
      XLSpreadsheetElement(parent),
      m_sharedStringNodes(),
      m_emptyString("")
{
    ParseXMLData();
}

/**
 * @details Saves the XML file (if modified) and destroys the object.
 */
XLSharedStrings::~XLSharedStrings()
{
    //CommitXMLData();
}

/**
 * @details Overrides the method in XLAbstractXMLFile. Clears the internal datastructure and fills it with the strings
 * in the XML file.
 * @todo Consider making the return value void.
 */
bool XLSharedStrings::ParseXMLData()
{
    // Clear the datastructure
    m_sharedStringNodes.clear();

    // Find the first node and iterate through the XML file, storing all string nodes in the internal datastructure
    for (auto &node : XmlDocument()->first_child().children()) m_sharedStringNodes.push_back(node.first_child());
    return true;
}

/**
 * @details Look up a shared string by index and return a pointer to the corresponding node in the underlying XML file.
 * If the index is larger than the number of shared strings a nullptr will be returned.
 * The resulting string is returned as pointer-to-const, as the client is not supposed to modify the shared strings
 * directly.
 */
const XMLNode XLSharedStrings::GetStringNode(unsigned long index) const
{
    if (index > m_sharedStringNodes.size() - 1)
        throw std::range_error("Node does not exist");
    else
        return m_sharedStringNodes.at(index);
}

/**
 * @details Look up a shared string node by string and return a pointer to the corresponding node in the underlying XML file.
 * If the index is larger than the number of shared strings a nullptr will be returned.
 * The resulting string is returned as pointer-to-const, as the client is not supposed to modify the shared strings
 * directly.
 */
const XMLNode XLSharedStrings::GetStringNode(string_view str) const
{
    for (const auto &s : m_sharedStringNodes) {
        if (string_view(s.text().get()) == str) return s;
    }

    throw std::range_error("Node does not exist");
}

/**
 * @details Look up a string index by the string content. If the string does not exist, the returned index is -1.
 */
long XLSharedStrings::GetStringIndex(string_view str) const
{

    long result = -1;
    long counter = 0;
    for (const auto &s : m_sharedStringNodes) {
        if (string_view(s.text().get()) == str) {
            result = counter;
            break;
        }
        counter++;
    }

    return result;
}

/**
 * @details
 */
bool XLSharedStrings::StringExists(string_view str) const
{

    if (GetStringIndex(str) < 0)
        return false;
    else
        return true;
}

/**
 * @details
 */
bool XLSharedStrings::StringExists(unsigned long index) const
{
    if (index > m_sharedStringNodes.size() - 1)
        throw false;
    else
        return true;
}

/**
 * @details Append a string by creating a new node in the XML file and adding the string to it. The index to the
 * shared string is returned
 */
long XLSharedStrings::AppendString(string_view str)
{

    // Create the required nodes
    auto node = XmlDocument()->append_child("si");
    auto value = node.append_child("t");
    value.text().set(string(str).c_str());

    // Add the node pointer to the internal datastructure.
    m_sharedStringNodes.push_back(value);
    SetModified();

    // Return the Index of the new string.
    return m_sharedStringNodes.size() - 1;
}

/**
 * @details Clear the string at the given index. This will affect the entire spreadsheet; everywhere the shared string
 * is used, it will be erased.
 */
void XLSharedStrings::ClearString(int index)
{
    m_sharedStringNodes.at(index).set_value("");
    SetModified();
}
