#include "page.hpp"
#include <iostream>

Page::Page(json::Value* posts) {
  // Looping through all elements of the json Array "posts".
  // Each element/object in the array constitutes the
  // contents and data of one post
  int i = 0;
  while (posts->index(i) != 0x0) {
  	Post tempPost;
  	json::Value* userPostData = posts->index(i)->findKey("data");
    std::string tempStr;

    // Use tempStr to use the substr method on it and remove
    // the quotation marks off the begginning and end of the string
  	tempStr = userPostData->findKey("title")->getString();
    // The following line of code removes the quotes 
    tempStr = tempStr.substr(1, tempStr.length() - 2);
    tempPost.title = tempStr;
  	tempStr = userPostData->findKey("author")->getString();
    // Here it is again
    tempStr = tempStr.substr(1, tempStr.length() - 2);
    tempPost.author = tempStr;

    // Force the numbers to be ints. The function actually returns a double
  	tempPost.upvotes = (int)userPostData->findKey("ups")->getNumber();
  	tempPost.downvotes = (int)userPostData->findKey("downs")->getNumber();
  	tempPost.numComments = (int)userPostData->findKey("num_comments")->getNumber();
  	contents.push_back(tempPost);
    ++i;
  }
}

void Page::printPage() {
  for (int i = 0; i < contents.size(); ++i) {
    std::cout << "AUTHOR: " << contents[i].author << '\n';
    std::cout << "TITLE: " << contents[i].title << '\n';
    std::cout << "▲" << contents[i].downvotes << " ";
    std::cout << "▼" << contents[i].upvotes << " ";
    std::cout << "COMMENTS: " << contents[i].numComments << '\n';
    std::cout << '\n' << '\n';
  }
}