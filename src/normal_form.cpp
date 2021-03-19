#include "lofmi/normal_form.h"

namespace Lofmi
{
std::ostream& operator<<(std::ostream& os, const FullNormalForm& f)
{
    for (size_t i = 0; i < f.terms.size(); i++)
    {
        os << (i == 0 ? "" : f.divider) << *(f.terms[i]);
    }
    
    return os;
}

FullNormalForm::FullNormalForm(
    std::vector<Bitset> x, Bitset y, std::string div
) : divider{ div }
{
    if (y.size() != x.size())
    {
        throw std::invalid_argument("x size doesn't match y size");
    }

    if (x.size())
    {
        size_t bitset_size = x[0].size();

        for (const Bitset& bitset : x)
        {
            if (bitset.size() != bitset_size)
            {
                throw std::invalid_argument("x bitsets have different sizes");
            }
        }
    }
}

FullDisjunctiveNormalForm::FullDisjunctiveNormalForm(
    std::vector<Bitset> x, Bitset y
) : FullNormalForm(x, y, " V ")
{
    for (size_t i = 0; i < y.size(); i++)
    {
        if (y[i])
        {
            terms.push_back(std::make_unique<FullFormMinterm>(x[i]));
        }
    }
}

FullConjunctiveNormalForm::FullConjunctiveNormalForm(
    std::vector<Bitset> x, Bitset y
) : FullNormalForm(x, y, " & ")
{
    for (size_t i = 0; i < y.size(); i++)
    {
        if (!y[i])
        {
            terms.push_back(std::make_unique<FullFormMaxterm>(x[i]));
        }
    }
}

MinDisjunctiveForm::MinDisjunctiveForm(
    std::vector<Bitset> x,
    Bitset y,
    std::vector<std::vector<int>> bit_numbers
) : FullNormalForm(x, y, " V ")
{
    for (size_t i = 0; i < y.size(); i++)
    {
        if (y[i])
        {
            terms.push_back(
                std::make_unique<MinFormMinterm>(x[i], bit_numbers[i])
            );
        }
    }
}

MinConjunctiveForm::MinConjunctiveForm(
    std::vector<Bitset> x,
    Bitset y,
    std::vector<std::vector<int>> bit_numbers
) : FullNormalForm(x, y, " & ")
{
    for (size_t i = 0; i < y.size(); i++)
    {
        if (!y[i])
        {
            terms.push_back(
                std::make_unique<MinFormMaxterm>(x[i], bit_numbers[i])
            );
        }
    }
}

} // namespace Lofmi
