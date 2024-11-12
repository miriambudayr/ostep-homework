# Notes

I found this chapter a little difficult to parse. The graph at the end of the book was confusing until I saw this video explanation:

https://youtu.be/ulWFbm-QhrE?si=733yD-KOOJispUrW&t=1764

To find each instruction, you have to consult the page table. So every instruction has at least 1 memory reference.

When the `mov` instruction has been fetched and is being executed, it needs to look for the target memory location (%eax times 4) in the array to move the number 0 to, which requires another page table lookup to translate the virtual address into the array to the physical address.

That's a lot of memory references....

The drawback of using page tables like this is that the page table itself takes up memory, and accessing the page table requires additional references. This explodes the time complexity considerably.

# README notes

```
  [       0]  0x8000000c  <- PTBR
  [       1]  0x00000000
  [       2]  0x00000000
  [       3]  0x80000006

Virtual address: 0x00003229 (binary: 11001000101001)

11                              001000101001

VPN (index into the table)      offset (offset within page)


VPN is binary 11 => decimal 3

Address of PTE(VPN=>3) is 0x80000006

80000006 => 10000000000000000000000000000110

high bit: 1 => valid
PFN (physical frame number): 110 => 6 => 0x6
offset: 001000101001 => 0x229
physical address => 0x6229

```

# Homework

1. . Before doing any translations, let’s use the simulator to study how linear page tables change size given different parameters. Compute the size of linear page tables as different parameters change. Some suggested inputs are below; by using the -v flag, you can see how many page-table entries are filled. First, to understand how linear page table size changes as the address space grows, run with these flags:
   - `-P 1k -a 1m -p 512m -v -n 0`
     - Address space is 1MB which is 1000 KB
     - Page size is 1KB
     - Number of PTEs (some valid some not): 1024
       - 515 are filled
       - 509 are not filled
   - `-P 1k -a 2m -p 512m -v -n 0`
     - Number of PTEs (some valid some not): 2048
       - 1035 are filled
       - 1013 are not filled
   - `-P 1k -a 4m -p 512m -v -n 0`
   - Number of PTEs (some valid some not): 4096
     - 2062 are filled
     - 2034 are not filled

Summary:

Playing around with this for a while, here are some invariants:

- The physical memory size has to be at least as big as the address space.
- The page size has to be a factor of the address space.
- You can continue to increase the physical memory size and it doesn't change the number of PTEs in the table.
- As you increase the address space, the PTE grows. PTEs = address_space/page_size. For example if the page size is 1K and the address space is 4M (=> 4_000_000), the number of PTEs is 4_000_000/1000.
