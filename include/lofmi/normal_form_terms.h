#pragma once

#include "lofmi/common.h"

namespace Lofmi
{
class FullFormTerm
{
public:
    friend std::ostream& operator<<(std::ostream& os, const FullFormTerm& t);

protected:
    FullFormTerm(Bitset bitset, std::string divider);
    virtual std::string toString() const;
    const std::string divider;
    const Bitset bitset;
};

class MinFormTerm : public FullFormTerm
{
protected:
    MinFormTerm(Bitset bitset, std::string div, std::vector<int> bit_numbers);
    std::string toString() const override;
    const std::vector<int> bit_numbers;
};

class FullFormMinterm : public FullFormTerm
{
public:
    FullFormMinterm(Bitset bitset);
};

class FullFormMaxterm : public FullFormTerm
{
public:
    FullFormMaxterm(Bitset bitset);
};

class MinFormMinterm : public MinFormTerm
{
public:
    MinFormMinterm(Bitset bitset, std::vector<int> bit_numbers);
};

class MinFormMaxterm : public MinFormTerm
{
public:
    MinFormMaxterm(Bitset bitset, std::vector<int> bit_numbers);
};    
} // namespace Lofmi
