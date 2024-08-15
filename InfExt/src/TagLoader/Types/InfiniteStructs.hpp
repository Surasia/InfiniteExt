#ifndef INFINITESTRUCT_HPP
#define INFINITESTRUCT_HPP



/* File From libinfinite by Coarforge */


#include <stdint.h>
#pragma pack(push,1)

// saved in the typeInfo field, but not always (in externalResource)
// wether or not that tag has been loaded
#define STATUS_LOADED (1 << 0)


// Source: https://github.com/Z-15/Halo-Infinite-Tag-Editor/blob/master/Halo-Infinite-Tag-Editor/InfiniteModuleEditor/Slipspace/Tag.cs

// Pointers are assumed to be 64 bits. If they aren't, this could cause problems

typedef uint32_t string_id;

typedef struct tagblock tagblock;

template<typename t>
struct tagBlock {
    void* Elements;
    t* block;    // CAUTION: this value gets overwritten by the loader to point to the struct holding the data of this block
    //          I don't think it's used anywhere for other things, but this could cause problems
    uint32_t count;
};

// _42
// to assign the data, just use the next entry in the data table (iterating over all that are used)
// looks like they are in region 1 as well, or at least they can be
struct dataReference {
    void* data;
    uint64_t TypeInfo;
    uint32_t unknown;
    uint32_t size;
};

// _41
struct tagReference {
    void* TypeInfo;  // CAUTION: the loader puts the pointer to the root struct of the referenced tag here
    uint32_t globalId;
    uint64_t assetId;
    union {
        uint32_t tagClass;
        char tagClassc[4];
    };
    uint32_t localHandle;

};

// _43
// these don't get loaded by default
template<typename t>
struct externalResource {
    t* block;     /*
                                 * Points to the struct that holds more info about the resource
                                 * The actual resource data has to be requested from the moduleItem(s) for it
                                 */
    uint32_t Handle;    // Index of the CTE (it's not really needed once the tag has been loaded, no there's no point in keeping a pointer to it here
    // when ther isn't really enough space without overwriting unknown, which could turn out to be important)
    uint32_t unknown;
};

// _10
struct shortPoint2D {
    uint16_t x;
    uint16_t y;
};

// _12 (maybe? maybe also mmr3hash)
typedef struct rgbColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;	// unused I guess
} rgbColor;

typedef rgbColor argbColor;	// same thing

// _16
struct point2D {
    float x;
    float y;
};

// _18
struct vector2D {
    float x;
    float y;
};

// _17
struct point3D {
    float x;
    float y;
    float z;
};

// _19
struct vector3D {
    float x;
    float y;
    float z;
};

// _20

typedef struct realARGBColor realARGBColor;

struct realARGBColor {
    float a;
    float r;
    float g;
    float b;
};

//_1F
typedef struct realRGBColor realRGBColor;

struct realRGBColor {
    float r;
    float g;
    float b;
};


// _1A
typedef struct realQuaternion realQuaternion;

struct realQuaternion {
    float x;
    float y;
    float z;
    float w;
};

// _1B
typedef struct realEulerAngle2D {
    float x;
    float y;
} realEulerAngles2D;

// _1C
typedef struct realEulerAngle3D realEulerAngle3D;

struct realEulerAngle3D {
    float x;
    float y;
    float z;
};

// _1D
typedef struct realPlane2D realPlane2D;
struct realPlane2D {
    float x;
    float y;
    float d;
};

// _1E
typedef struct realPlane3D realPlane3D;

struct realPlane3D {
    float x;
    float y;
    float z;
    float d;
};

// _23
typedef struct shortBounds {
    uint16_t min;
    uint16_t max;
} shortBounds;

// _25
typedef struct realBounds realBounds;

struct realBounds {
    float min;
    float max;
};

// _26
// probably not really right
typedef struct realBounds realFractionBounds;

// _8
typedef float angle;

// _2E
typedef uint16_t shortBlockIndex;

// _2F
typedef uint16_t customShortBlockIndex;

// _30
typedef uint32_t longBlockIndex;

#pragma pack(pop)

#endif
