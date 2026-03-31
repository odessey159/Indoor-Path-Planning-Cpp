#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include "testcases.h"
#include "util.h"
#include "reference.h"

int main() {
    using namespace testcases;

    for (int i = 0; i < 20; ++i) {
        const auto& tc = testcases::testcases[i];

        int* w[4] = {
            const_cast<int*>(tc.w[0].data()),
            const_cast<int*>(tc.w[1].data()),
            const_cast<int*>(tc.w[2].data()),
            const_cast<int*>(tc.w[3].data())
        };

        std::vector<std::string> path;
        int dist = reference::FindShortestPath(tc.start, tc.end, path, w);  // ← your logic

        std::cout << "=== Test Case #" << i << " ===\n";
        std::cout << "Start: " << tc.start << ", End: " << tc.end << "\n";
        std::cout << "Distance: " << dist << "\n";
        std::cout << "Path: ";
        for (const auto& p : path) std::cout << p << " ";
        std::cout << "\n";

        auto [valid, reason] = check_path(path);
        if (!valid) {
            std::cout << "❌ Invalid path: " << reason << "\n";
        } else {
            std::cout << "✅ Path is valid.\n";
        }

        std::cout << "\n";
    }

    return 0;
}
