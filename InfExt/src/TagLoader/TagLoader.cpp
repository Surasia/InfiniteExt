#include "TagLoader.hpp"
#include "../Logger/Logger.hpp"

std::map<std::string, std::map<uint32_t, TagStruct>> TagLoader::TagsList;
std::atomic<uint64_t> TagLoader::baseAddress(0);

void TagLoader::PrintTagInfo()
{
    Logger& logger = Logger::GetInstance(false);
    logger.Log(Logger::INFO, "Base Tag Address: {:x}", baseAddress.load());

    uint32_t tagCount = *reinterpret_cast<uint32_t*>(baseAddress + 0x6c);
    uint64_t tagStart = *reinterpret_cast<uint64_t*>(baseAddress + 0x78);

    logger.Log(Logger::INFO, "Tag Count: {}", tagCount);
    logger.Log(Logger::INFO, "Tag Start: {:x}", tagStart);

    LoadTags(tagCount, tagStart);
}


void TagLoader::TagAddressPrinter(uintptr_t ModuleBase) 
{
    while (baseAddress.load() == 0) {
        std::memcpy(&baseAddress, reinterpret_cast<void*>(ModuleBase + 0x48A10D8), sizeof(baseAddress));
        if (baseAddress.load() != 0) {
            PrintTagInfo();
            return;
        }
        else {
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }
    PrintTagInfo();
}

std::string TagLoader::ReadString(uintptr_t address) 
{
    std::string result;
    char* str = reinterpret_cast<char*>(address);
    while (*str != '\0') {
        result += *str++;
    }
    return result;
}

void TagLoader::LoadTags(uint32_t TagCount, uint64_t TagStart) 
{
    Logger& logger = Logger::GetInstance(false);

    for (uint32_t tagIndex = 0; tagIndex < TagCount; ++tagIndex) {
        TagStruct currentStruct;
        uintptr_t tagAddress = TagStart + (tagIndex * 52);

        currentStruct.Datum = *reinterpret_cast<uint32_t*>(tagAddress);
        currentStruct.ObjectId = *reinterpret_cast<uint32_t*>(tagAddress + 4);
        uintptr_t tagGroupPointer = *reinterpret_cast<uintptr_t*>(tagAddress + 8);
        uintptr_t tagGroupStringPointer = *reinterpret_cast<uintptr_t*>(tagGroupPointer);
        currentStruct.TagGroup = ReadString(tagGroupStringPointer);
        currentStruct.TagData = *reinterpret_cast<uintptr_t*>(tagAddress + 0x10);
        uintptr_t tagDescPointer = *reinterpret_cast<uintptr_t*>(tagAddress + 0x18);
        uintptr_t tagDescStringPointer = *reinterpret_cast<uintptr_t*>(tagDescPointer);
        currentStruct.TagTypeDesc = ReadString(tagDescStringPointer);

        TagsList[currentStruct.TagGroup][currentStruct.Datum] = currentStruct;
    }
}

std::map<std::string, std::map<uint32_t, TagStruct>> TagLoader::GetTagsList()
{
	return TagsList;
}

void TagLoader::ReadTags(uintptr_t ModuleBase)
{
	Logger& logger = Logger::GetInstance(false);
	logger.Log(Logger::INFO, "Tag Instances Address: {:x}", ModuleBase + 0x48A10D8);
	TagAddressPrinter(ModuleBase);
}
