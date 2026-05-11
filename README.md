# Hash Function Drag Race

## 50MB Chunked into pieces ranging from 6 to 15 bytes
### Bottom row is the column average
| SHA256 (ms) | SHA1 (ms) | MD5 (ms) | CRC32C Intel ISA-L (ms) | XXHASH (ms) | DJB2 (ms) | std::hash (ms) |
| --- | --- | --- | --- | --- | --- | --- |
| 900 | 893 | 985 | 52 | 22 | 41 | 40 |
| 855 | 852 | 948 | 52 | 22 | 42 | 40 |
| 857 | 851 | 946 | 53 | 22 | 41 | 40 |
| 859 | 851 | 948 | 53 | 26 | 42 | 40 |
| 867.75 | 861.75 | 956.75 | 52.5 | 23 | 41.5 | 40 |

## 500MB Chunked into pieces ranging from 6 to 15 bytes
### Bottom row is the column average
| SHA256 (ms) | SHA1 (ms) | MD5 (ms) | CRC32C Intel ISA-L (ms) | XXHASH (ms) | DJB2 (ms) | std::hash (ms) |
| --- | --- | --- | --- | --- | --- | --- |
| 8511 | 8517 | 9482 | 531 | 266 | 414 | 405 |
| 8526 | 8524 | 9476 | 531 | 228 | 417 | 407 |
| 8498 | 8519 | 9473 | 529 | 228 | 414 | 407 |
| 8687 | 8652 | 9642 | 533 | 228 | 414 | 407 |
| 8555.5 | 8553 | 9518.25 | 531 | 237.5 | 414.75 | 406.5 |

## 1GB Chunked into pieces ranging from 6 to 15 bytes
### Bottom row is the column average
| SHA256 (ms) | SHA1 (ms) | MD5 (ms) | CRC32C Intel ISA-L (ms) | XXHASH (ms) | DJB2 (ms) | std::hash (ms) |
| --- | --- | --- | --- | --- | --- | --- |
| 16939 | 17020 | 18979 | 1066 | 533 | 829 | 810 |
| 16996 | 17044 | 18977 | 1064 | 456 | 835 | 814 |
| 17086 | 17035 | 19022 | 1110 | 456 | 833 | 813 |
| 17014 | 17037 | 18983 | 1068 | 533 | 831 | 811 |
| 17008.75 | 17034 | 18990.25 | 1077 | 494.5 | 832 | 812 |

## Notes
Compiled with CXXFLAGS set to: -O2 -march=alderlake -mtune=alderlake -pipe via GCC 14.2.0 for the above results.
Tests were executed on a 12600K with minor OC (5000Mhz All P-Core, 4000Mhz All E-Core).
The bytes were sourced from /dev/urandom.
