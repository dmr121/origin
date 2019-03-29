#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace json
{
  // Declare derived classes to make their
  // names available.
  struct Value;
  struct Null;
  struct Bool;
  struct Number;
  struct String;
  struct Array;
  struct Object;


  // A "visitor" defines the "table" used
  // for implementing an algorithm on a
  // data structure defined hierarchically.
  struct Visitor
  {
    // Each "row" in the "table" is a virtual
    // function accepting a reference to an
    // object of some derived class from the
    // hierarchy.
    virtual void visit(Null const& n) { }
    virtual void visit(Bool const& b) { }
    virtual void visit(Number const& n) { }
    virtual void visit(String const& s) { }
    virtual void visit(Array const& a) { }
    virtual void visit(Object const& o) { }
  };

  // Computes the size (number of nodes) in
  // the JSON value v (recursively).
  int size(Value const& v);

  // Returns the height of the tree.
  int height(Value const& v);

  // Abstractly represents the set of JSON
  // values (i.e., one of null, true, false,
  // numbers, strings, arrays, objects.)
  struct Value
  {
    // Ignore this for now.
    virtual ~Value() = default;

    // The "accept" function is responsible
    // for "jumping" to the row in the table
    // that matches the dynamic type of this
    // object.
    virtual void accept(Visitor& vis) const = 0;

    // Returns the pointer to the object at the specified key
    virtual Value* findKey(std::string s) const {
      Value* temp;
      return temp;
    }

    // Returns the pointer to the Array at the specified int index 
    virtual Value* index(int index) {
      Value* temp;
      return temp;
    }

    // Returns a string.
    // This function is meant to be used on a Value* pointer to a String object
    virtual std::string getString() const {
      return "not a string";
    }


    // Returns a double
    // This is meant to be used on a Value* pointer to a Number object
    virtual double getNumber() const {
      return 0; 
    }
  };

  // Represents the string/value "null".
  struct Null : Value
  {
    // The override calls back to the "table"
    // in order to execute a behavior associated
    // with the dynamic type of this object,
    // which is now (also) the static type.
    void accept(Visitor& vis) const {
      return vis.visit(*this);
    }
  };

  // Represents the values "true" and "false".
  struct Bool : Value
  {
    Bool(bool b) : value(b) { }
    
    void accept(Visitor& vis) const {
      return vis.visit(*this);
    }

    // Represents "true" if true and "false"
    // otherwise.
    bool value;
  };

  // Represents numbers.
  struct Number : Value
  {
    Number(double n) : value(n) { }
    
    void accept(Visitor& vis) const {
      return vis.visit(*this);
    }

    double value;

    double getNumber() const {
      return value;
    }
  };

  // Represents strings.
  //
  // Here, we also inherit from std::string
  // in order to reuse its interface and
  // implementation.
  struct String : Value, std::string
  {
    void accept(Visitor& vis) const {
      return vis.visit(*this);
    }

    using std::string::string;

    std::string getString() const {
      return *this;
    }
  };

  // Represents a sequence of values 
  // (recursively).
  //
  // Again, we inherit to reuse the interface
  // of vector (and its implementation).
  //
  // NOTE: std::vector<Value*> is a "polymorphic
  // container" -- a container of polymorphic class
  // objects. The dynamic types of objects in the
  // container can vary at runtime.
  struct Array : Value, std::vector<Value*>
  {
    using std::vector<Value*>::vector;

    void accept(Visitor& vis) const {
      return vis.visit(*this);
    }

    Value* index(int index) {
      std::vector<Value*>::iterator i = begin() + index;
      return *i;
    }

  };

  // Represents objects.
  //
  // We hash on std::string rather than String (for 
  // ease of correct implementation) and definitely
  // not on String* (which would hash on addresses,
  // not string values).
  struct Object : Value, std::unordered_map<std::string, Value*>
  {
    using std::unordered_map<std::string, Value*>::unordered_map;  

    void accept(Visitor& vis) const {
      return vis.visit(*this);
    }

    // Argument: Name of object to find
    // Returns pointer to the object
    Value* findKey(std::string s) const {
      std::string temp = "\"" + s + "\"";
      for (auto itr = begin(); itr != end(); ++itr) {
        if (itr->first == temp) {
          return itr->second;
        }
      }

      std::cout << "Value not found" << '\n';
    }
  };


  // Operations

  Value* parse(std::string const& str);


} // namespace

