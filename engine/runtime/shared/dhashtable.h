
// This module implements a helpful hash table structure that will
// map keys to void pointers.

// Note: currently, it treats keys as CASE-INSENSITIVE strings!

#ifndef __DHASHTABLE_H__
#define __DHASHTABLE_H__

// Hash types.
#define HASH_2BYTENUMBER    0   // Treats keys as 2 byte numbers.
#define HASH_STRING_NOCASE  1   // Treats keys as case-insensitive strings.
#define HASH_RAW            2   // Keys are raw data (like case-sensitive strings).
#define HASH_FILENAME       3   // Keys are case-insensitive and / maps to \.
#define NUM_HASH_TYPES      4


// Handle types.   Got rid of the structure types.  Good idea in principle,
//but had a serious downside of creating bad header dependencies.
class HHashTable;
class HHashElement;
class HHashIterator;


// Create and destroy hash tables.  mapSize controls how large the
// internal table is.  The larger it is, the less collisions are likely,
// but larger numbers means more memory usage.
HHashTable *hs_CreateHashTable(uint32 mapSize, int hashType);
void hs_DestroyHashTable(HHashTable *hTable);

// Just a helper to see how many key collisions have happened.
uint32 hs_GetNumCollisions(HHashTable *hTable);

// Add an element to the hash table.
HHashElement *hs_AddElement(HHashTable *hTable, const void *pKey, uint32 keyLen);

// Remove an element.
void hs_RemoveElement(HHashTable *hTable, HHashElement *hElement);

// Looks for the element you specify.  Returns NULL if it can't find one.
HHashElement *hs_FindElement(HHashTable *hTable, const void *pKey, uint32 keyLen);

// If there are more than one elements with the same key, you can call this (after hs_FindElement)
// to find the rest of them.
HHashElement *hs_FindNextElement(HHashTable *hTable, HHashElement *hInElement, const void *pKey, uint32 keyLen);

// The hash table will store the key for you so you don't have to store
// an extra copy of it.  If you set pKeyLen to NULL, it'll be ignored.
void* hs_GetElementKey(HHashElement *hElement, uint32 *pKeyLen);

// Get/Set user data for a hash element.
void* hs_GetElementUserData(HHashElement *hElement);
void hs_SetElementUserData(HHashElement *hElement, void *pUser);


// Iterate over the hash table.  Each function returns NULL
// when you are done iterating.

// A loop should look like this.
// hIterator = hs_GetFirstElement(hTable);
// while (hIterator)
// {
//     hElement = hs_GetNextElement(hIterator);
//     process hElement...
// }
// Note: it is safe to remove hElement while iterating.

HHashIterator *hs_GetFirstElement(HHashTable *hTable);
HHashElement *hs_GetNextElement(HHashIterator *&pIterator);


#endif  // __DHASHTABLE_H__

