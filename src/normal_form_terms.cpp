#include "lofmi/normal_form_terms.h"

namespace Lofmi
{
FullFormTerm::FullFormTerm(Bitset bits, std::string div) :
    bitset{ std::move(bits) },
    divider{ div } {}

std::ostream& operator<<(std::ostream& os, const FullFormTerm& t)
{
    return os << t.toString();
}

std::string FullFormTerm::toString() const
{
    std::ostringstream os;

    os << '(';

    for (size_t i = 0; i < bitset.size(); i++)
    {
        os << (i == 0 ? "" : divider)
            << (bitset[i] ? "" : "~")
            << 'x' << i;
    }
    os << ')';

    auto result = os.str();
    return os.str();
}


MinFormTerm::MinFormTerm(Bitset bits, std::string div, std::vector<int> nums) :
    FullFormTerm(std::move(bits), div), bit_numbers{ nums }
{
    if (bit_numbers.size() != bits.size())
    {
        throw std::invalid_argument("Bitset size doesn't match labels size");
    }
}

std::string MinFormTerm::toString() const
{
    std::ostringstream os("(");

    for (size_t i = 0; i < bitset.size(); i++)
    {
        os << (i == 0 ? "" : divider)
            << (bitset[i] ? "" : "~")
            << 'x' << bit_numbers[i];
    }
    os << ')';

    return os.str();
}

FullFormMinterm::FullFormMinterm(Bitset bits) : 
    FullFormTerm(std::move(bits), " & ") {}

FullFormMaxterm::FullFormMaxterm(Bitset bits) :
    FullFormTerm(std::move(bits.flip()), " V ") {}

MinFormMinterm::MinFormMinterm(Bitset bits, std::vector<int> nums) :
    MinFormTerm(std::move(bits), " & ", std::move(nums)) {}

MinFormMaxterm::MinFormMaxterm(Bitset bits, std::vector<int> nums) :
    MinFormTerm(std::move(bits), " V ", std::move(nums)) {}

} // namespace Lofmi
