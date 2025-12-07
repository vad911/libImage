// versionInfo.cpp
// #include <imageReader/versionInfo.h>
#include "imageReader/versionInfo.h"
#include <iostream>

VersionInfo::VersionInfo() {}

std::string VersionInfo::getCommitHash() {
    return GIT_COMMIT_HASH;
}

std::string VersionInfo::getBranch() {
    return GIT_BRANCH;
}

std::string VersionInfo::getCommitDate() {
    return GIT_COMMIT_DATE;
}

std::string VersionInfo::getTag() {
    return GIT_TAG;
}

std::string VersionInfo::getBuildDate() {
    return BUILD_DATE;
}

void VersionInfo::printVersionInfo() {
    std::cout << "=== Version Info ===" << std::endl;
    std::cout << "Commit: " << getCommitHash() << std::endl;
    std::cout << "Branch: " << getBranch() << std::endl;
    std::cout << "Commit Date: " << getCommitDate() << std::endl;
    std::cout << "Tag: " << getTag() << std::endl;
    std::cout << "Build Date: " << getBuildDate() << std::endl;
    std::cout << "===================" << std::endl;
}