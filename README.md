BenchMark
=========

<img src="images/logo_BenchMark_468x300.png" style="width:300px; float: left; margin: 0 10px 10px 0;" alt="BenchMark Logo"/>

### Links
The project's home page:  https://github.com/marknelsonengineer/BenchMark  (hosted by GitHub)

The source code is documented at:  https://www2.hawaii.edu/~marknels/BenchMark  (hosted by The University of Hawaiʻi at Mānoa)

### Documentation
BenchMark is a toolset for analysing the relative performance of various things
that I'm interested in.

### Results
First, I'm shocked and thrilled at the performance of Release-mode `memcpy()`
and `memset()` functions from glibc.  Look at these results:

Results of `memcpy()` in CPU ticks using different compilers & options
|     n | Release | MinSizeRel | Clang |
|------:|--------:|-----------:|------:|
|     8 |       1 |         13 |    11 |
|    16 |       2 |         13 |     9 |
|    32 |       2 |         13 |    12 |
|    64 |       6 |         13 |    12 |
|   128 |       4 |         19 |    10 |
|   256 |       4 |         22 |    15 |
|   512 |      12 |         27 |    28 |
|  1024 |      20 |         38 |    31 |
|  2048 |      38 |         67 |    56 |
|  4096 |      86 |        141 |    94 |
|  8192 |     172 |        485 |   179 |
| 16384 |     744 |        719 |   840 |
| 32768 |    1836 |       1957 |  1698 |
| 65536 |    3264 |       4240 |  3386 |

#### Observations
- Notice how the speeds are about the same when `n` < 256
- Notice how much more efficient the Release build over Clang or MinSizeRel, 
  especially at low `n`.
- The results of `memcpy()` are so good, it makes me doubt whether I can
  improve the speed with hand-coded assembly.
- Results for `memset()` are very similar to `memcpy()` (Not shown)

#### Key
| Build          | Compiler                            | Options                                                                                  |
|----------------|-------------------------------------|------------------------------------------------------------------------------------------|
| **Release**    | Statically linked gcc executable    | `-lstdc++ -fuse-ld=gold -march=native -mtune=native -Ofast -funroll-loops -static -mfma` |
| **MinSizeRel** | Dynamically linked gcc executable   | `-lstdc++ -fuse-ld=gold -march=native -mtune=native -Oz -mfma`                           |
| **Clang**      | Dynamically linked Clang executable | `-march=native`                                                                          |

The tests were performed on a MacBook Pro:
- Architecture: Coffee Lake – 9th Generation Intel Core
- Cache line size: 64 bytes
