#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED

#include <iostream>
#include<string>

/// DEFINICION CLASE NAME

class Name {
  private:
    std::string last;
    std::string first;

  public:
    Name();
    Name(const Name&);

    std::string getLast() const;
    std::string getFirst() const;

    std::string toString() const;

    void setLast(const std::string&) ;
    void setFirst(const std::string&) ;

    Name& operator = (const Name&);

    bool operator == (const Name&) const;
    bool operator != (const Name&) const;
    bool operator < (const Name&) const;
    bool operator <= (const Name&) const;
    bool operator > (const Name&) const;
    bool operator >= (const Name&) const;

    friend std::ostream& operator << (std::ostream&,const Name&);
    friend std::istream& operator >> (std::istream&, Name&);
};

#endif // NAME_H_INCLUDED
