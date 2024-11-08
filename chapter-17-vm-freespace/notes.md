# README notes

- What is "alignment"?
  - Round up to the nearest header-space-sized free chunk in size.

# Questions

1. First run with the flags `-n 10 -H 0 -p BEST -s 0` to generate a few random allocations and frees.
   - Can you predict what alloc()/free() will return? Yes!
   - Can you guess the state of the free list after each request? Yes!
   - What do you notice about the free list over time?: the free list increases in size

```
ptr[0] = Alloc(3) returned 1000 (searched 1 element)
Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

Free(ptr[0]) returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

Free(ptr[1]) returned 0
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

Free(ptr[2]) returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1008
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

Free(ptr[3]) returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1000
Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[5] = Alloc(7) returned 1008
Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]
```

2. How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes?
   - Note to self: worst-fit policy means finding the largest possible chunk to use.
   - Overall the number of items in the list is higher.
   - The largest free chunk continuously shrinks and ends up smaller than the best-fit-policy's largest chunk.
   - The algorithm searches for more elements.
   - There are a higher number of small chunks.

```
ptr[0] = Alloc(3) returned 1000
Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]


ptr[3] = Alloc(8) returned 1016
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1024 sz:76 ]

Free(ptr[3])
returned 0
Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ] [ addr:1024 sz:76 ]

ptr[4] = Alloc(2) returned 1024
Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ] [ addr:1026 sz:74 ]

ptr[5] = Alloc(7) returned 1026
Free List [ Size 5 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:8 ] [ addr:1033 sz:67 ]

```

3. What about using FIRST fit (-p FIRST)? What speeds up when you use first fit?
   - It does not need to search as many elements to allocate the memory chunk.
   - More clutter at the beginning of the list. Could benefit from coalescing.

```
ptr[0] = Alloc(3) returned 1000, searched 1 elements
Free List [ Size 1 ]:  [ addr:1003 sz:97 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003, searched 1 elements
Free List [ Size 2 ]:  [ addr:1000 sz:3 ] [ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008, searched 3 elements
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1008, searched 3 elements
Free List [ Size 3 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1016 sz:84 ]

Free(ptr[3])
returned 0
Free List [ Size 4 ]:  [ addr:1000 sz:3 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1000, searched 1 elements
Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1008 sz:8 ] [ addr:1016 sz:84 ]

ptr[5] = Alloc(7) returned 1008, searched 3 elements
Free List [ Size 4 ]:  [ addr:1002 sz:1 ] [ addr:1003 sz:5 ] [ addr:1015 sz:1 ] [ addr:1016 sz:84 ]

```

4. For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some policies. Use the different free list orderings to see how the policies and the list orderings interact.

   - BEST: (incorrect) this algorithm searches for all valid chunks and chooses the smallest of them, so SIZESORT+ would put the smallest chunk in the front of the list so it wouldn't have to sort through as much. The time complexity is O(n), where n is the number of free chunks.
     - This is incorrect ^. I made the assumption that BEST could return early if the list was sorted, but there is no such conditional, so no matter what, the allocator will search through the entire list to find the smallest of the valid chunks.
   - WORST: (incorrect) this algorithm searches for the biggest chunk and uses it, so SIZESORT- would put the largest chunk in the front of the list. The time complexity is O(1).
     - This is incorrect for the same reason as above.
   - FIRST: this algorithm uses the first chunk that is big enough. ADDRSORT combined with coalescing would speed it up the most. The optimizations are compounding. Using ADDRSORT allows you to coalesce the list more quickly, and coalescing the list also reduces the number of iterations over the free list when searching it.

5. Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing. What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case? By the way, I used this to get the average list size: `./malloc.py -n 1000 -H 0 -p FIRST -s 0 -C -c | grep -o 'Free List \[ Size [0-9]* \]' | sed 's/[^0-9]*//g' | awk '{sum+=$1} END {print sum/NR}'`.

   SUMMARY:

   - Coalescing majorly reduces the average list size.
   - Coalescing majorly reduces the number of failed allocations.
   - Ordering of the list matters for the first-fit policy with ADDRSORT combined with coalescing. Sort order doesn't matter otherwise. You have to search fewer elements that way.
   - `grep -o 'searched [0-9]* elements' | awk '{sum+=$2; count+=1} END {if (count > 0) print sum/count; else print 0}'`
   - I don't think ordering will matter for BEST or WORST for the reasons I explained above, but coalescing does help them because there are fewer elements to search.

   DATA:

   - `./malloc.py -n 1000 -H 0 -p FIRST -s 0 -c | grep "returned -1" | wc -l`:
     - Without coalescing:
       - 210 failed.
       - Average list size: 40
       - Average # of searched elements: 26
     - With coalescing (added -C):
       - 33 failed.
       - Average list size: 3
       - Average # of searched elements: 2
   - `./malloc.py -n 1000 -H 0 -p BEST -s 0 -c | grep "returned -1" | wc -l`:
     - Without coalescing:
       - 177 failed.
       - Average list size: 30.
       - Average # of searched elements: 30
     - With coalescing (added -C):
       - 29 failed.
       - Average list size: 3.
       - Average # of searched elements: 3
   - `./malloc.py -n 1000 -H 0 -p WORST -s 0 -c | grep "returned -1" | wc -l`:
     - Without coalescing:
       - 658 failed.
         - This makes sense because of what I observed about the worst-fit algorithm. Worst-fit causes the free list to be longer, with smaller fragments, and for the longest free chunk to shrink compared to other algorithms.
       - Average list size: 78.
       - Average # of searched elements: 81
     - With coalescing (added -C):
       - 34 failed.
       - Average list size: 4.
       - Average # of searched elements: 4.
