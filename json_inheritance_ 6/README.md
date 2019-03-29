# David Rozmajzl

## How to use:

./json < "reddit.com/r/subReddit.json"

You will need to download the json file of course

## Cmake

Because I have a newer version of cmake, I used the line ***set(CMAKE_CXX_STANDARD 14)*** to set the C++ version as opposed to the way you originally had in your CMakeLists.txt file.

## Short Summary

I used your code pretty much as is. I wasn't sure of any way to use the parser
you made without pretty much directly copying the code you wrote. Instead, I just
used your original code. I created a Post class which contains basic info about each post, like the title, author, upvotes, downvotes, and number of comments. I added some virtual functions to json.hpp in the Value class. 

## findKey(string s)
One called findKey() allows me to return a pointer to the value in the key/value pair of an object. I can simply type in a string and get the pointer to the object that is "unlocked" by that string. 

## index (int n)
Another function index(int n) allows me to get a pointer to the nth element in an Array object inherited from Value. This was especially useful in accessing the content of the posts as it is all mostly stored in a giant array.

## getString() & getNumber()
These are self explanatory. They were necessary in accesing the value of a String and Number of object respectively through a Value* pointer.
