#pragma once
#include <string>
#include "json.hpp"

struct Post {
    std::string author;
    std::string title;
    int upvotes;
    int downvotes;
    int numComments;
};