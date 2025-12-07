#ifndef VERSIONINFO_H
#define VERSIONINFO_H

// versionInfo.h - должен находиться в libs/libImageReader/include/imageReader/
#pragma once

#include <string>

class VersionInfo {
public:
    VersionInfo();
    
    static std::string getCommitHash();
    static std::string getBranch();
    static std::string getCommitDate();
    static std::string getTag();
    static std::string getBuildDate();
    
    static void printVersionInfo();
};

#endif // VERSIONINFO_H
