#pragma once

#include "lofmi/common.h"
#include "lofmi/normal_form_terms.h"

namespace Lofmi
{
class FullNormalForm
{
public:
    using Terms = std::vector<std::unique_ptr<FullFormTerm>>;
    friend std::ostream& operator<<(std::ostream& os, const FullNormalForm& f);

protected:
    FullNormalForm(std::vector<Bitset> x, Bitset y, std::string divider);
    Terms terms;
    const std::string divider;
};

class FullDisjunctiveNormalForm : public FullNormalForm
{
public:
    FullDisjunctiveNormalForm(std::vector<Bitset> x, Bitset y);
};

class FullConjunctiveNormalForm : public FullNormalForm
{
public:
    FullConjunctiveNormalForm(std::vector<Bitset> x, Bitset y);
};

class MinDisjunctiveForm : public FullNormalForm
{
public:
    MinDisjunctiveForm(
        std::vector<Bitset> x,
        Bitset y,
        std::vector<std::vector<int>> bit_numbers
    );
};

class MinConjunctiveForm : public FullNormalForm
{
public:
    MinConjunctiveForm(
        std::vector<Bitset> x,
        Bitset y,
        std::vector<std::vector<int>> bit_numbers
    );
};

} // namespace Lofmi
