#pragma once
#include "post.hpp"
#include "json.hpp"
#include <vector>

struct Page {
	std::vector<Post> contents;

	Page(json::Value* posts);
	void printPage();
};