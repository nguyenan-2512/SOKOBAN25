#include "TeleportNetwork.h"
#include <iostream>
#include <algorithm>

TeleportNetwork::TeleportNetwork() {
    // Không cần cooldown nữa vì teleport thủ công
}

void TeleportNetwork::addTeleport(const Point& location, int teleportID) {
    locationToID[location] = teleportID;
    idToLocations[teleportID].push_back(location);

    std::cout << "Added teleport at (" << location.getX() << "," << location.getY()
        << ") with ID: " << teleportID << std::endl;
}

void TeleportNetwork::removeTeleport(const Point& location) {
    auto it = locationToID.find(location);
    if (it != locationToID.end()) {
        int id = it->second;
        locationToID.erase(it);

        auto& locs = idToLocations[id];
        locs.erase(std::remove(locs.begin(), locs.end(), location), locs.end());

        if (locs.empty()) {
            idToLocations.erase(id);
        }
    }
}

Point TeleportNetwork::getDestination(const Point& from) {
    // ✅ BỎ HOÀN TOÀN CHECK COOLDOWN

    auto it = locationToID.find(from);
    if (it == locationToID.end()) {
        return from; // Không phải cổng teleport
    }

    int id = it->second;
    auto idIt = idToLocations.find(id);
    if (idIt == idToLocations.end() || idIt->second.size() <= 1) {
        std::cout << "⚠️ Khong co cong dich de teleport!" << std::endl;
        return from; // Chỉ có 1 cổng, không teleport
    }

    // Lấy danh sách các cổng cùng ID
    const std::vector<Point>& destinations = idIt->second;

    // Tìm cổng đích (không phải cổng hiện tại)
    for (const Point& dest : destinations) {
        if (dest != from) {
            std::cout << "🌀 Teleporting from (" << from.getX() << "," << from.getY()
                << ") to (" << dest.getX() << "," << dest.getY() << ")" << std::endl;

            // ✅ KHÔNG SET COOLDOWN NỮA
            return dest;
        }
    }

    return from;
}

bool TeleportNetwork::isTeleport(const Point& location) const {
    return locationToID.find(location) != locationToID.end();
}

int TeleportNetwork::getTeleportID(const Point& location) const {
    auto it = locationToID.find(location);
    if (it != locationToID.end()) {
        return it->second;
    }
    return -1;
}

std::vector<Point> TeleportNetwork::getLinkedTeleports(int teleportID) const {
    auto it = idToLocations.find(teleportID);
    if (it != idToLocations.end()) {
        return it->second;
    }
    return std::vector<Point>();
}

void TeleportNetwork::update(float deltaTime) {
    // ✅ KHÔNG CẦN UPDATE COOLDOWN NỮA
    // Giữ hàm này để tránh lỗi compile
}

bool TeleportNetwork::canTeleport(const Point& location) const {
    // ✅ LUÔN TRẢ VỀ TRUE
    return true;
}

void TeleportNetwork::setCooldown(const Point& location) {
    // ✅ KHÔNG LÀM GÌ
}

void TeleportNetwork::clear() {
    locationToID.clear();
    idToLocations.clear();
    cooldowns.clear();
}

void TeleportNetwork::printNetwork() const {
    std::cout << "\n=== Teleport Network ===" << std::endl;
    for (const auto& pair : idToLocations) {
        std::cout << "ID " << pair.first << ": ";
        for (const Point& p : pair.second) {
            std::cout << "(" << p.getX() << "," << p.getY() << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << "======================\n" << std::endl;
}