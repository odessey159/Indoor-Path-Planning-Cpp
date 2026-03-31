#pragma once
#include <string>
#include <vector>

std::tuple<bool, std::string> check_path(const std::vector<std::string>& path);
std::vector<int> partial_length(const std::vector<std::string> &path, int** w);
bool goes_up(const std::vector<std::string> &path, std::string start, std::string end);
