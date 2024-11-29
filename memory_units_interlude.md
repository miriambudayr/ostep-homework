# How to measure memory

I experienced some confusion about how to think about memory addresses.

Here is some terminology:

- 1 byte of memory has 8 bits in it.
- If I have a 1-byte address space, I can store 1 address which points to 1 memory location, and that memory location can store 8 bits.
- A byte is the smallest unit of addressable memory space in modern computing systems. This means for 1 address, it will point to 1 byte of memory.
- A kilobyte is equal to 1024 bytes. This is because the prefix "kilo" in this context means "multiply by 1024" due to it using a binary system. If I have a 1-kilobyte address space, that space has 1024 addresses (because "byte" is synonymous with "addresses", in a sense). The length of the address for this address space has to be 10 bits long in order to accommodate all the addresses. If the address length is fewer than 10 bits long, you will only be able to represent a portion of the addresses. The length of the address must be log2(1024) which is 10.
- Memory address space: if the address space is 16KB, that means there are 16 x 1024 = 16384 addresses since 16KB is equal to 16384 addresses. Notice that 16384 is 16 times larger than 1024. Every time you add a bit, you double the number of memory addresses you can create. If 10 bits accommodates 1024 addresses, then 11 bits accommodates, 2048 addresses, 12 bits accommodates 4096 addresses, 13 bits accommodates 8192 addresses, and 14 bits accommodates 16384 addresses. Another way to think of this is to ask "how many times do I need to double 1024 to get to 16384?" You can also ask: "how many times do I need to double 1 to get to 16384" if you want to jump directly to the solution rather than thinking about the 10-bit address space first.
- "8-bit address space": this means the maximum length of an address is 8 bits. This is 2^8 total addresses, which is 256 unique memory locations.
- Number of addressable bytes: in an 8-bit address space, you have 256 unique memory locations, and each of those memory locations contains a byte. So you have 256 bytes of memory.
- The number of pages in a system equals the number of addressable bytes divided by the size of the pages.
  - If addressable memory is 256 and the page size is 16, then the number of pages is 16.

# How do I know how many bits a binary numbers has?

Use this:

`printf 11001000101001 | wc -c`

# Conversions

- Convert from hex to binary:
  - `echo "obase=2; ibase=16; 00003229" | bc`
  - https://www.inchcalculator.com/hex-to-binary-converter/
