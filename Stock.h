//****************************************************************************************************************************************
//
//     File:			    Stock.h
//     Student:				Cyrus Bajracharya
//     Assignment:		    Assignment 9
//     Course:				COSC 3100 01 Data Structures II
//     Due:				    11/12/2021
//     Descrpition:         This code creates a structure node that stores template value and frequency for a huffmans stock.
//                          Additionally, this also contains a stock class for storing name, price and symbol.
//
//****************************************************************************************************************************************
#ifndef STOCK_H
#define STOCK_H
#include<string>
//****************************************************************************************************************************************
template<typename T>
struct Node {
    T value;
    double frequency;
    Node<T>* left;
    Node<T>* right;
    Node(){
        left = nullptr;
        right = nullptr;
    }
};
//****************************************************************************************************************************************
class Stock {
private:
    std::string companyName, sym;
    double stockPrice;
public:
    Stock(const std::string& name = "", const std::string& symbol = "", double price = 0);
    Stock(const Stock& s);

    int hash(int size) const;
    void display() const;
    friend std::ostream& operator << (std::ostream& out, const Stock& c);
    
    inline void setName(std::string name);
    inline void setSymbol(std::string symbol);
    inline void setPrice(double price);
    inline std::string getName() const;
    inline std::string getSymbol() const;
    inline double getPrice() const;
    inline bool operator == (const Stock& rhs) const;
    inline bool operator != (const Stock& rhs) const;
    inline bool operator > (const Stock& rhs) const;
    inline bool operator < (const Stock& rhs) const;
};
//****************************************************************************************************************************************
inline void Stock::setName(std::string name)
{
    companyName = name;
}
//****************************************************************************************************************************************
inline void Stock::setSymbol(std::string symbol)
{
    sym = symbol;
}
//****************************************************************************************************************************************
inline void Stock::setPrice(double price)
{
    stockPrice = price;
}
//****************************************************************************************************************************************
inline std::string Stock::getName() const
{
    return companyName;
}
//****************************************************************************************************************************************
inline std::string Stock::getSymbol() const
{
    return sym;
}
//****************************************************************************************************************************************
inline double Stock::getPrice() const
{
    return stockPrice;
}
//****************************************************************************************************************************************
inline bool Stock::operator == (const Stock& rhs) const
{
    return (this->stockPrice == rhs.stockPrice);
}
//****************************************************************************************************************************************
inline bool Stock::operator != (const Stock& rhs) const
{
    return (this->stockPrice != rhs.stockPrice);
}
//****************************************************************************************************************************************
inline bool Stock::operator > (const Stock& rhs) const
{
    return (this->stockPrice > rhs.stockPrice);
}
//****************************************************************************************************************************************
inline bool Stock::operator < (const Stock& rhs) const
{
    return (this->stockPrice < rhs.stockPrice);
}
//****************************************************************************************************************************************
#endif