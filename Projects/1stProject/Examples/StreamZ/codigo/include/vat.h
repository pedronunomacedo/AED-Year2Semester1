/**
 * @file vat.h
 */

#ifndef VAT_H_INCLUDED
#define VAT_H_INCLUDED

#include "utils.h"

/**
 * @brief %VAT number.
 */
class VAT: public utils::string_regex{
public:
    /**
     * @brief   Regular expression string that describes a valid VAT.
     */
    static const std::string REGEX_STR;
    /**
     * @brief   Empty constructor
     */
    explicit VAT();
    /**
     * @brief   Constructor accepting %VAT as string
     * @param   vat String containing %VAT
     * @exception   VAT::VATTooLong When VAT is longer than the maximum size
     */
    explicit VAT(const std::string &vat);
    /** @brief Overload of operator=. */
    VAT& operator=(const std::string &s);
};

#endif //ADDRESS_H_INCLUDED
