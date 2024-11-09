#include "TagLoader.hpp"

#include "../Logger/Logger.hpp"

std::map<std::string, std::map<uint32_t, TagStruct>> TagLoader::TagsList;
std::atomic<uint64_t> TagLoader::baseAddress(0);

void TagLoader::PrintTagInfo()
{
    Logger &logger = Logger::GetInstance(false);
    logger.Log(Logger::INFO, "Base Tag Address: {:x}", baseAddress.load());

    constexpr uint8_t tagCountOffset = 0x6c;
    constexpr uint8_t tagStartOffset = 0x78;
    uint32_t tagCount = *reinterpret_cast<uint32_t *>(baseAddress + tagCountOffset);
    uint64_t tagStart = *reinterpret_cast<uint64_t *>(baseAddress + tagStartOffset);

    logger.Log(Logger::INFO, "Tag Count: {}", tagCount);
    logger.Log(Logger::INFO, "Tag Start: {:x}", tagStart);

    LoadTags(tagCount, tagStart);
}


void TagLoader::TagAddressPrinter(uintptr_t ModuleBase)
{
    constexpr uintptr_t tagAddressOffset = 0x48BE488;
    while (baseAddress.load() == 0)
    {
        std::memcpy(&baseAddress, reinterpret_cast<void *>(ModuleBase + tagAddressOffset), sizeof(baseAddress));
        if (baseAddress.load() != 0)
        {
            PrintTagInfo();
            return;
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    PrintTagInfo();
}

std::string TagLoader::ReadString(uintptr_t address)
{
    std::string result;
    char *str = reinterpret_cast<char *>(address);
    while (*str != '\0')
    {
        result += *str++;
    }
    return result;
}


void TagLoader::LoadTags(uint32_t tagCount, uint64_t tagStart)
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uint8_t tagStructSize = 52;

    for (uint32_t tagIndex = 0; tagIndex < tagCount; ++tagIndex)
    {
        TagStruct tagStruct;
        uint64_t tagAddress = tagStart + (tagIndex * tagStructSize);

        tagStruct.Datum = *reinterpret_cast<uint32_t *>(tagAddress);
        tagStruct.ObjectId = *reinterpret_cast<uint32_t *>(tagAddress + 4);

        uintptr_t tagGroupPointer = *reinterpret_cast<uintptr_t *>(tagAddress + 8);
        tagStruct.TagGroup = ReadString(*reinterpret_cast<uintptr_t *>(tagGroupPointer));

        tagStruct.TagData = *reinterpret_cast<uintptr_t *>(tagAddress + 0x10);

        uintptr_t tagDescPointer = *reinterpret_cast<uintptr_t *>(tagAddress + 0x18);
        tagStruct.TagTypeDesc = ReadString(*reinterpret_cast<uintptr_t *>(tagDescPointer));

        TagsList[tagStruct.TagGroup][tagStruct.Datum] = tagStruct;
    }
}



std::map<std::string, std::map<uint32_t, TagStruct>> TagLoader::GetTagsList()
{
    return TagsList;
}

void TagLoader::ReadTags(uintptr_t ModuleBase)
{
    Logger &logger = Logger::GetInstance(false);
    // basically in IDA search for "tag instances" and then you'll see a function called with "tag instances" as a parameter for it.
    // the return value (v0) is the address you want.
    constexpr uintptr_t tagInstanceOffset = 0x48BE488;
    logger.Log(Logger::INFO, "Tag Instances Address: {:x}", ModuleBase + tagInstanceOffset);
    TagAddressPrinter(ModuleBase);
}
