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

#ifndef OPENXLSX_ALL_XLCELLRANGE_H
#define OPENXLSX_ALL_XLCELLRANGE_H

#include "../implementation/headers/XLCellRange.h"
#include "XLCell.h"
namespace OpenXLSX {

    class XLCellRange
    {
    public:
        explicit XLCellRange(Impl::XLCellRange &range) : m_range(&range) {}

        /**
         * @brief Copy constructor [default].
         * @param other The range object to be copied.
         * @note This implements the default copy constructor, i.e. memberwise copying.
         */
        XLCellRange(const XLCellRange &other) = default;

        /**
         * @brief Move constructor [default].
         * @param other The range object to be moved.
         * @note This implements the default move constructor, i.e. memberwise move.
         */
        XLCellRange(XLCellRange &&other) = default;

        /**
         * @brief Destructor [default]
         * @note This implements the default destructor.
         */
        ~XLCellRange() = default;

        /**
         * @brief The copy assignment operator [default]
         * @param other The range object to be copied and assigned.
         * @return A reference to the new object.
         * @throws A std::range_error if the source range and destination range are of different size and shape.
         * @note This implements the default copy assignment operator.
         */
        XLCellRange &operator=(const XLCellRange &other) = default;

        /**
         * @brief The move assignment operator [default].
         * @param other The range object to be moved and assigned.
         * @return A reference to the new object.
         * @note This implements the default move assignment operator.
         */
        XLCellRange &operator=(XLCellRange &&other) = default;

        /**
         * @brief Get a pointer to the cell at the given coordinates.
         * @param row The row number, relative to the first row of the range (index base 1).
         * @param column The column number, relative to the first column of the range (index base 1).
         * @return A pointer to the cell at the given range coordinates.
         */
        XLCell Cell(unsigned long row,
                    unsigned int column) {return XLCell(*m_range->Cell(row, column)); }

        /**
         * @brief Get a const pointer to the cell at the given coordinates.
         * @param row The row number, relative to the first row of the range (index base 1).
         * @param column The column number, relative to the first column of the range (index base 1).
         * @return A const pointer to the cell at the given range coordinates.
         */
        const XLCell Cell(unsigned long row,
                          unsigned int column) const {return XLCell(*m_range->Cell(row, column)); }

        /**
         * @brief Get the number of rows in the range.
         * @return The number of rows.
         */
        unsigned long NumRows() const { return m_range->NumRows(); }

        /**
         * @brief Get the number of columns in the range.
         * @return The number of columns.
         */
        unsigned int NumColumns() const { return m_range->NumColumns(); }

        /**
         * @brief Transpose the range.
         */
        void Transpose(bool state) const { m_range->Transpose(state); }

        /**
         * @brief Get an iterator pointing to the first cell in the range.
         * @return The iterator pointing to the first cell in the range.
         */
        XLCellIterator begin();

        /**
         * @brief
         * @return
         */
        XLCellIteratorConst begin() const;

        /**
         * @brief Get an iterator pointing to the end of the grid (nullptr)
         * @return The iterator pointing to the end of the range.
         */
        XLCellIterator end();

        /**
         * @brief
         * @return
         */
        XLCellIteratorConst end() const;

        /**
         * @brief
         */
        void Clear();

    private:
        Impl::XLCellRange* m_range;
    };

}


#endif //OPENXLSX_ALL_XLCELLRANGE_H
