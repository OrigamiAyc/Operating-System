# OS homework week 12

<p align="right">by PB18000227 艾语晨</p>

### Question 1

> Q :
>
> Explain the following terms：
>
> Fragmentation fault, TLB, Page fault, Demand paging, Thrashing

> A :

- Fragmentation fault (Segmentation fault)
	- When you are accessing a piece of memory that is not allowed to be accessed, then the OS returns you an error called – segmentation fault
	- Or concisely, segmentation fault is triggered when visiting a segment in an illegal way
- TLB
	- TLB is short for 'Translation Lookaside Buffer', and it uses the idea of caching
	- Its purpose is to improve memory access performance when page table look incurs large overhead
	- Its traits are fast (since it's part of the pipeline) and small
- Page fault
	- When the MMU finds that a virtual page involved in an instruction demand is invalid (not in the memory), the CPU then generates an interrupt called page fault
- Demand paging
	- The allocation is done in an lazy way, that is the system only *says* that the memory is allocated, yet actually it's *not* until you really access it
- Thrashing
	- Thrashing is a condition that more time is spent on paging than executing, probably since a process does not have enough frames to support pages in active use, therefore resulting in frequent page fault, replacing a page that will be needed again right away

### Question 2

> Q :
>
> Consider a paging system with the page table stored in memory.
>
> a. If a memory reference takes 50 nanoseconds, how long does a paged memory reference take?
>
> b. If we add TLBs, and 75 percent of all page-table references are found in the TLBs, what is the effective memory reference time? (Assume that finding a page-table entry in the TLBs takes 2 nanoseconds, if the entry is present.)

> A :

**a.**

$50+50=100ns$（visit page table & use the address to visit statistics)

**b.**

$75\%*(2+50)+25\%*(50+50)=64.5ns$

> Note :
>
> The accessing of TLB and page table (in memory) are simultaneous, thus the loading of page table has already begun even if TLB missed

### Question 3

> Q :
>
> Assume a program has just referenced an address in virtual memory. Describe a scenario how each of the following can occur: (If a scenario cannot occur, explain why.)
>
> • TLB miss with no page fault
>
> • TLB miss and page fault
>
> • TLB hit and no page fault
>
> • TLB hit and page fault

> A :

- TLB miss with no page fault
	- The demanded page is not in the TLB (映射关系没有存进去) , yet it's allocated (maybe in swap area)
- TLB miss and page fault
	- The demanded page is not in the TLB, and not allocated
- TLB hit and no page fault
	- The demanded page is in the TLB, and allocated
- TLB hit and page fault
	- This condition won't occur, since the TLB includes information of frame number, which shows the mapping from virtual page to physical page, thus won't cause page fault

### Question 4

> Q :
>
> Assume we have a demand-paged memory. The page table is held in registers. It takes 8 milliseconds to service a page fault if an empty page is available or the replaced page is not modified, and 20 milliseconds if the replaced page is modified. Memory access time is 100 nanoseconds. Assume that the page to be replaced is modified 70 percent of the time. What is the maximum acceptable page-fault rate for an effective access time of no more than 200 nanoseconds?

> A :
>
> Analyse : If page-fault happens, it's needed to be serviced by replacing pages, using 8 or 20 ms according to page condition; else it only takes 100 ns

We assume that the page-fault rate is $p$ , then we have :

$100ns*(1-p)+(0.3*8ms+0.7*20ms)*p<200ns$

Therefore, $p<6\cdot 10^{-6}$

### Question 5

> Q :
>
> Consider the following page reference string: 7, 2, 3, 1, 2, 5, 3, 4, 6, 7, 7, 1, 0, 5, 4, 6, 2, 3, 0, 1. Assuming demand paging with three frames, how many page faults would occur for the following replacement algorithms?
>
> • LRU replacement
>
> • FIFO replacement
>
> • Optimal replacement

> A :
>
> The first row is the page reference string, the last row is whether page faults would occur (t for true)

LRU : 18 times

|7|2|3|1|2|5|3|4|6|7|7|1|0|5|4|6|2|3|0|1|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|7|2|3|1|2|5|3|4|6|7|7|1|0|5|4|6|2|3|0|1|
| |7|2|3|1|2|5|3|4|6|6|7|1|0|5|4|6|2|3|0|
| | |7|2|3|1|2|5|3|4|4|6|7|1|0|5|4|6|2|3|
|t|t|t|t| |t|t|t|t|t| |t|t|t|t|t|t|t|t|t|

FIFO : 17 times

|7|2|3|1|2|5|3|4|6|7|7|1|0|5|4|6|2|3|0|1|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|7|2|3|1|1|5|5|4|6|7|7|1|0|5|4|6|2|3|0|1|
| |7|2|3|3|1|1|5|4|6|6|7|1|0|5|4|6|2|3|0|
| | |7|2|2|3|3|1|5|4|4|6|7|1|0|5|4|6|2|3|
|t|t|t|t| |t| |t|t|t| |t|t|t|t|t|t|t|t|t|

Optimal : 13 times

|7|2|3|1|2|5|3|4|6|7|7|1|0|5|4|6|2|3|0|1|
|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|-|
|7|7|7|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|
| |2|2|2|2|5|5|5|5|5|5|5|5|5|4|6|2|3|3|3|
| | |3|3|3|3|3|4|6|7|7|7|0|0|0|0|0|0|0|0|
|t|t|t|t| |t| |t|t|t| | |t| |t|t|t|t| | |

### Question 6

> Q :
>
> Suppose that a disk drive has 5,000 cylinders, numbered 0 to 4999. The drive is currently serving a request at cylinder 2150, and the previous request was at cylinder 1805. The queue of pending requests, in FIFO order, is: 2069, 1212, 2296, 2800, 544, 1618, 356, 1523, 4965, 3681 Starting from the current head position, what is the total distance (in cylinders) that the disk armmoves to satisfy all the pending requests for each of the following disk-scheduling algorithms?
>
> a. FCFS
>
> b. SSTF
>
> c. SCAN
>
> d. LOOK
>
> e. C-SCAN
>
> f. C-LOOK

> A :
>
> From the fact that *the previous request was at cylinder 1805*, we can infer that the scanning is from 0 to 4999 at the beginning

##### FCFS

|1805|2150|2069|1212|2296|2800|544|1618|356|1523|4965|3681|
|-|-|-|-|-|-|-|-|-|-|-|-|
| | |2069|1212|2296|2800|544|1618|356|1523|4965|3681|

$distance = (2150-1212)+(2800-1212)+(2800-544)+(1618-544)+\\(1618-356)+(4965-356)+(4965-3681)=13011$

##### SSTF

|1805|2150|2069|1212|2296|2800|544|1618|356|1523|4965|3681|
|-|-|-|-|-|-|-|-|-|-|-|-|
| | |2069|2296|2800|3681|4965|1618|1523|1212|544|356|

$distance=(2150-2069)+(4965-2069)+(4965-356)=7586$

##### SCAN (4965 -> 4999 -> 2069)

|1805|2150|2069|1212|2296|2800|544|1618|356|1523|4965|3681|
|-|-|-|-|-|-|-|-|-|-|-|-|
| | |2296|2800|3681|4965|2069|1618|1523|1212|544|356|

$distance=(4999-2150)+(4999-356)=7492$

##### LOOK (4965 -> 2069)

|1805|2150|2069|1212|2296|2800|544|1618|356|1523|4965|3681|
|-|-|-|-|-|-|-|-|-|-|-|-|
| | |2296|2800|3681|4965|2069|1618|1523|1212|544|356|

$distance=(4965-2150)+(4965-356)=7424$

##### C-SCAN (4965 -> 4999 -> 0 ->356)

|1805|2150|2069|1212|2296|2800|544|1618|356|1523|4965|3681|
|-|-|-|-|-|-|-|-|-|-|-|-|
| | |2296|2800|3681|4965|356|544|1212|1523|1618|2069|

$distance=(4999-2150)+4999+2069=9917$

##### C-LOOK (4965 -> 356)

|1805|2150|2069|1212|2296|2800|544|1618|356|1523|4965|3681|
|-|-|-|-|-|-|-|-|-|-|-|-|
| | |2296|2800|3681|4965|356|544|1212|1523|1618|2069|

$distance=(4965-2150)+(4965-356)+(2069-356)=9137$
