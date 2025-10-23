#pragma once
#include "Point.h"
#include "Teleport.h"
#include <unordered_map>
#include <vector>
#include <memory>

// Hash function cho Point để dùng trong unordered_map
struct PointHash {
    std::size_t operator()(const Point& p) const {
        return std::hash<int>()(p.getX()) ^ (std::hash<int>()(p.getY()) << 1);
    }
};

class TeleportNetwork {
private:
    // Map từ vị trí -> Teleport ID
    std::unordered_map<Point, int, PointHash> locationToID;

    // Map từ ID -> danh sách các vị trí cùng ID (cổng liên kết)
    std::unordered_map<int, std::vector<Point>> idToLocations;

    // Cooldown để tránh teleport liên tục vô hạn
    std::unordered_map<Point, float, PointHash> cooldowns;
    float cooldownTime = 0.5f; // 0.5 giây

public:
    TeleportNetwork();

    // Thêm cổng teleport
    void addTeleport(const Point& location, int teleportID);

    // Xóa cổng teleport
    void removeTeleport(const Point& location);

    // Lấy điểm đến khi đi vào cổng (trả về điểm đến, nếu không có trả về vị trí hiện tại)
    Point getDestination(const Point& from);

    // Kiểm tra xem vị trí có phải cổng teleport không
    bool isTeleport(const Point& location) const;

    // Lấy ID của cổng tại vị trí
    int getTeleportID(const Point& location) const;

    // Lấy tất cả cổng cùng ID
    std::vector<Point> getLinkedTeleports(int teleportID) const;

    // Update cooldowns
    void update(float deltaTime);

    // Kiểm tra cooldown
    bool canTeleport(const Point& location) const;

    // Set cooldown
    void setCooldown(const Point& location);

    // Clear all
    void clear();

    // Debug: in thông tin mạng
    void printNetwork() const;
};