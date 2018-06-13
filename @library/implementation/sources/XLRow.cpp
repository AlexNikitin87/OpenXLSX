//
// Created by KBA012 on 02/06/2017.
//

#include <algorithm>
#include "../headers/XLRow.h"
#include "../headers/XLWorksheet.h"
#include "../headers/XLCell.h"
#include "../headers/XLCellValue.h"
#include "../headers/XLException.h"

using namespace std;
using namespace OpenXLSX;


/**
 * @details Constructs a new XLRow object from information in the underlying XML file. A pointer to the corresponding
 * node in the underlying XML file must be provided.
 */
XLRow::XLRow(XLWorksheet &parent,
             XMLNode rowNode)
    : m_parentWorksheet(parent),
      m_parentDocument(*parent.ParentDocument()),
      m_rowNode(rowNode),
      m_height(15),
      m_descent(0.25),
      m_hidden(false),
      m_rowNumber(0),
      m_cells()
{
    // Read the Row number attribute
    auto rowAtt = m_rowNode.attribute("r");
    if (rowAtt) m_rowNumber = stoul(rowAtt.value());

    // Read the Descent attribute
    auto descentAtt = m_rowNode.attribute("x14ac:dyDescent");
    if (descentAtt) SetDescent(stof(descentAtt.value()));

    // Read the Row Height attribute
    auto heightAtt = m_rowNode.attribute("ht");
    if (heightAtt) SetHeight(stof(heightAtt.value()));

    // Read the hidden attribute
    auto hiddenAtt = m_rowNode.attribute("hidden");
    if (hiddenAtt) {
        if (string(hiddenAtt.value()) == "1") SetHidden(true);
        else SetHidden(false);
    }

    // Iterate throught the Cell nodes and add cells to the m_cells vector
    auto spansAtt = m_rowNode.attribute("spans");
    if (spansAtt) {
        for (auto &currentCell : rowNode.children()) {
            XLCellReference cellRef(currentCell.attribute("r").value());
            Resize(cellRef.Column());
            m_cells.emplace(cellRef.Column() - 1, XLCell::CreateCell(m_parentWorksheet, currentCell));
        }
    }
}

/**
 * @details Resizes the m_cells vector holding the cells and updates the 'spans' attribure in the row node.
 */
void XLRow::Resize(unsigned int cellCount)
{
    //m_cells.resize(cellCount);
    m_rowNode.attribute("spans") = string("1:" + to_string(cellCount)).c_str();
}

/**
 * @details Returns the m_height member by value.
 */
float XLRow::Height() const
{
    return m_height;
}

/**
 * @details Set the height of the row. This is done by setting the value of the 'ht' attribute and setting the
 * 'customHeight' attribute to true.
 */
void XLRow::SetHeight(float height)
{
    m_height = height;

    // Set the 'ht' attribute for the Cell. If it does not exist, create it.
    auto heightAtt = m_rowNode.attribute("ht");
    if (!heightAtt) m_rowNode.append_attribute("ht") = m_height;
    else heightAtt.set_value(height);

    // Set the 'customHeight' attribute. If it does not exist, create it.
    auto customAtt = m_rowNode.attribute("customHeight");
    if (!customAtt) m_rowNode.append_attribute("customHeight") = 1;
    else customAtt.set_value(1);
}

/**
 * @details Return the m_descent member by value.
 */
float XLRow::Descent() const
{
    return m_descent;
}

/**
 * @details Set the descent by setting the 'x14ac:dyDescent' attribute in the XML file
 */
void XLRow::SetDescent(float descent)
{
    m_descent = descent;

    // Set the 'x14ac:dyDescent' attribute. If it does not exist, create it.
    auto descentAtt = m_rowNode.attribute("x14ac:dyDescent");
    if (!descentAtt) m_rowNode.append_attribute("x14ac:dyDescent") = m_descent;
    else descentAtt = descent;
}

/**
 * @details Determine if the row is hidden or not.
 */
bool XLRow::Ishidden() const
{
    return m_hidden;
}

/**
 * @details Set the hidden state by setting the 'hidden' attribute to true or false.
 */
void XLRow::SetHidden(bool state)
{
    m_hidden = state;

    std::string hiddenstate;
    if (m_hidden) hiddenstate = "1";
    else hiddenstate = "0";

    // Set the 'hidden' attribute. If it does not exist, create it.
    auto hiddenAtt = m_rowNode.attribute("hidden");
    if (!hiddenAtt) m_rowNode.append_attribute("hidden") = hiddenstate.c_str();
    else hiddenAtt.set_value(hiddenstate.c_str());
}

/**
 * @details Get the pointer to the row node in the underlying XML file but returning the m_rowNode member.
 */
XMLNode XLRow::RowNode() const
{
    return m_rowNode;
}

/**
 * @details Return a pointer to the XLCell object at the given column number. If the cell does not exist, it will be
 * created.
 */
XLCell *XLRow::Cell(unsigned int column)
{
    // If the requested Column number is higher than the number of Columns in the current Row,
    // create a new Cell node, append it to the Row node, resize the m_cells vector, and insert the new node.
    if (auto result = m_cells.lower_bound(column - 1); result == m_cells.end()) {
        // Create the new Cell node
        auto cellNode = m_rowNode.append_child("c");
        cellNode.append_attribute("r").set_value(XLCellReference(m_rowNumber, column).Address().c_str());

        // Append the Cell node to the Row node, and create a new XLCell node and insert it in the m_cells vector.
        m_rowNode.attribute("spans") = string("1:" + to_string(column)).c_str();
        m_cells.emplace(column - 1, XLCell::CreateCell(m_parentWorksheet, cellNode));

        // If the requested Column number is lower than the number of Columns in the current Row,
        // but the Cell does not exist, create a new node and insert it at the rigth position.
    } else if ((*result).second->CellReference()->Column() != column){

        // Find the next Cell node and insert the new node at that position.
        auto cellNode = m_rowNode.insert_child_before("c", (*result).second->CellNode());
        cellNode.append_attribute("r") = XLCellReference(m_rowNumber, column).Address().c_str();
        m_cells.emplace(column - 1, XLCell::CreateCell(m_parentWorksheet, cellNode));
    }

    return m_cells.at(column - 1).get();
}

/**
 * @details
 */
const XLCell *XLRow::Cell(unsigned int column) const
{

    if (column > CellCount()) {
        throw XLException("Cell does not exist!");
    }
    else {
        return m_cells.at(column - 1).get();
    }
}

/**
 * @details Get the number of cells in the row, by returning the size of the m_cells vector.
 */
unsigned int XLRow::CellCount() const
{
    return static_cast<unsigned int>(m_cells.size());
}

/**
 * @details Create an entirely new XLRow object (no existing node in the underlying XML file. The row and the first cell
 * in the row are created and inserted in the XML tree. A std::unique_ptr to the new XLRow object is returned
 * @todo What happens if the object is not caught and gets destroyed? The XML data still exists...
 */
void XLRow::CreateRow(XLWorksheet &worksheet,
                      unsigned long rowNumber)
{
    // Create the node
    XMLNode nodeRow;

    // Insert the newly created Row and Cell in the right place in the XML structure.
    if (!worksheet.SheetDataNode().first_child() || rowNumber >= worksheet.RowCount()) {
        // If there are no Row nodes, or the requested Row number exceed the current maximum, append the the node
        // after the existing rownodes.
        nodeRow = worksheet.SheetDataNode().append_child("row");
    }
    else {
        // Otherwise, search the Row nodes vector for the next node and insert there.
        // Vector is 0-based, Excel is 1-based; therefore rowNumber-1.
        XLRows::iterator iter = worksheet.Rows()->lower_bound(rowNumber - 1);
        if (iter != worksheet.Rows()->end() && iter->second.RowNode().attribute("r").as_ullong() != rowNumber)
            nodeRow = worksheet.SheetDataNode().insert_child_before("row", iter->second.RowNode());
    }

    nodeRow.append_attribute("r") = rowNumber;
    nodeRow.append_attribute("x14ac:dyDescent") = 0.2;
    nodeRow.append_attribute("spans") = "1:1";
    nodeRow.append_child("c").append_attribute("r") = XLCellReference(rowNumber, 1).Address().c_str();

    worksheet.Rows()->emplace(rowNumber - 1, XLRow(worksheet, nodeRow));
}
