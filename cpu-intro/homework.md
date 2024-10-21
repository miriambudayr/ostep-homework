# Key takeaways

- In this homework, it took some CPU to start and end IOs (1 unit --- this isn't accurate to reality but it's a decent mental model for now).

- SWITCH_ON_END: the system will NOT switch to another process while one is doing I/O, instead waiting until the process is completely finished.
- SWITCH_ON_IO: the system WILL switch to another process whenever one is WAITING for I/O
- IO_RUN_LATER: when an I/OP completes, the process that issued it is not necessarily run right away; rather, whatever was running at the time keeps running.
- IO_RUN_IMMEDIATE: immediately runs the process that issued the I/O, interrupting whatever process is currently on the CPU.
- Combinations:

  - SWITCH_ON_END with IO_RUN_LATER
    - IO first: IO_RUN_LATER does not affect this. IO runs to completion, then CPU runs to completion, then second IO runs to completion. No parallelism.
      - `-l 2:0,4:100 -c -p -L 3 -S SWITCH_ON_END -I IO_RUN_LATER`
    - CPU first: CPU runs to completion, then both IO blocks run to completion. No parallelism.
      - `-l 4:100,2:0 -c -p -L 3 -S SWITCH_ON_END -I IO_RUN_LATER`
  - SWITCH_ON_END with IO_RUN_IMMEDIATE
    - IO first: IO runs to completion, then CPU runs to completion. No parallelism.
      - `-l 2:0,4:100 -c -p -L 3 -S SWITCH_ON_END -I IO_RUN_IMMEDIATE`
    - CPU first: CPU runs to completion, then IO runs to completion. No parallelism.
      - `-l 4:100,2:0 -c -p -L 3 -S SWITCH_ON_END -I IO_RUN_IMMEDIATE`
  - SWITCH_ON_IO with IO_RUN_LATER

    - IO first: fisrt IO and CPU run together, so there is an amount of parallelism. Second IO runs by itself. About 10% more CPU utilization than the four combos above this one.
      - `-l 2:0,4:100 -c -p -L 3 -S SWITCH_ON_IO -I IO_RUN_LATER`
    - CPU first: CPU runs then IO runs, no parallelism. CPU utilization is ~57%.
      - `-l 4:100,2:0 -c -p -L 3 -S SWITCH_ON_IO -I IO_RUN_LATER`

  - SWITCH_ON_IO with IO_RUN_IMMEDIATE

    - IO first: IO and CPU run together, so there is an amount of parallelism. As soon as the first IO is done, the CPU-only process is paused to start another IO, so then the last CPU instruction on the CPU-only process is run with an IO. This maximizes parallelism. CPU utilization is 80%.

      - `-l 2:0,4:100 -c -p -L 3 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE`

    - CPU first: no parallelism because the CPU starts first and runs to completion. Notice all of these options modify whether IO is done in parallel with CPU instructions, and if the CPU switches once IO is done. To benefit from these flags, starting with IO is best.
      - `-l 4:100,2:0 -c -p -L 3 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE`

# Homework notes

1. I was correct
2. Same
3. This was interesting. When I switched the order of the processes, my calculation was incorrect. There were still a total of 9 instructions, but some of them ran in parallel. Specifically, the IO instruction was started (which takes 1 CPU unit and 0 I/O units). Then execution is given to the other process where 4 CPU instructions are run. During the first three CPU instructions, the 3 I/O instructions also run. This is surprising.
4. Did as I expected
5. I was right, yay
6. `.process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_LATER -c -p`. It seems this is the default behavior. The system resources seem to be well-utilized. CPU is at 100% and IO is at 50%. This means 50% of the instructions are happening in parallel.
   - SWITCH_ON_IO: CPU (100%), IO (50%)
   - SWITCH_ON_END: CPU (66.67%), IO (33.33%)
7. `.process-run.py -l 3:0,5:100,5:100,5:100 -S SWITCH_ON_IO -I IO_RUN_IMMEDIATE -c -p`.
   - IO_RUN_LATER: if you don't need the IO to return to the process as soon as it is done, you could use this flag. The IO finishes and then a bunch of other CPU instructions for other processes might run before the process that issued the IO runs again. One side-effect of this is that there was only 77% CPU usage for this command. It also takes more time. This is because many processes can run their instructions before the process that issued the IO command can issue the next IO command.
   - IO_RUN_IMMEDIATE: this utilizes 100% of the CPU. This is because the CPU switches to a non-IO process while waiting for IO, but as soon as IO comes back, it pauses the other process, goes back to the IO process and starts another IO right away, then switches back to the process that needs to get on CPU while it waits. This is more efficient, but it does cause you to have to switch processes more often.
8. `.process-run.py -s 1 -l 3:50,3:50 -c -p`
   - I don't really get this exercise because I don't fully understand what the seed argument or the percentages actually do. It seems to run deterministically, but the description makes it sound like both these settings inject randomness. I am confused.
