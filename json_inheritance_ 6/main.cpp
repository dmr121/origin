#include "json.hpp"
#include "page.hpp"
#include <iostream>
#include <vector>
#include <typeinfo>

int
main()
{
  std::istreambuf_iterator<char> first(std::cin);
  std::istreambuf_iterator<char> last;
  std::string s(first, last);  

  json::Value* subreddit = json::parse(s);

  // Finding the array called "children".
  // This array contains the post contents/details
  json::Value* posts = subreddit->findKey("data")->findKey("children");

  // Initialize a new Page object which contains a vector
  // of Post objects.
  // A Post object contains the important contents of a post.
  // These are stored as json::Value objects
  Page page(posts);

  // Print all of the posts in the content vector in Page class
  page.printPage();
}