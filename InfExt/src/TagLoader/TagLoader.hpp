#ifndef TAGLOADER_HPP
#define TAGLOADER_HPP

#include <map>
#include <shared_mutex>

/* Layout of TagStruct in Memory */
struct TagStruct {
    uint32_t Datum = 0;
    uint32_t ObjectId = 0;
    std::string TagGroup = "";
    uint64_t TagData = 0;
    std::string TagTypeDesc = "";
};


class TagLoader {
public:
    /* Public Functions */
    static void PrintTagInfo();
    static void TagAddressPrinter(uintptr_t ModuleBase);
    static std::string ReadString(uintptr_t address);
    static void LoadTags(uint32_t TagCount, uint64_t TagStart);
    static std::map<std::string, std::map<uint32_t, TagStruct>> GetTagsList();
    static void ReadTags(uintptr_t ModuleBase);

private:
    /* Private Variables */
    static std::map<std::string, std::map<uint32_t, TagStruct>> TagsList;
    static std::shared_mutex tagsListMutex;
    static std::atomic<uint64_t> baseAddress;
};

#endif
