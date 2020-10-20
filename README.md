# Recover
The program recovers deleted JPEG files from a memory card by iterating over a copy of the memory card, identifying the signature pattern of bytes that distinguish JPEGs from other file formats (0xff, 0xd8, 0xff and 0xe1 - 0xef) and writing them to a file.
