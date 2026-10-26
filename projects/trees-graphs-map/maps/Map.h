#pragma once

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <vector>

template<typename T, std::size_t BucketCount = 10>
class Map {
public:
    std::array<std::vector<T>, BucketCount> buckets {};

    std::size_t badHash(const T& key) const {
        const auto* bytes = reinterpret_cast<const unsigned char*>(&key);
        std::uint64_t weightedSum = 0;

        for (std::size_t i = 0; i < sizeof(T); ++i) {
            weightedSum += static_cast<std::uint64_t>(bytes[i]) * static_cast<std::uint64_t>(i + 1U);
        }

        return static_cast<std::size_t>(weightedSum);
    }

    std::size_t bucketIndex(const T& key) const {
        return badHash(key) % BucketCount;
    }

    void insert(const T& key) {
        auto& bucket = buckets[bucketIndex(key)];
        if (std::find(bucket.begin(), bucket.end(), key) == bucket.end()) {
            bucket.push_back(key);
        }
    }

    void remove(const T& key) {
        auto& bucket = buckets[bucketIndex(key)];
        bucket.erase(std::remove(bucket.begin(), bucket.end(), key), bucket.end());
    }

    bool search(const T& key) const {
        const auto& bucket = buckets[bucketIndex(key)];
        return std::find(bucket.begin(), bucket.end(), key) != bucket.end();
    }
};
