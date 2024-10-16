1. ✅ Run a few randomly-generated problems with just two jobs and
   two queues; compute the MLFQ execution trace for each. Make
   your life easier by limiting the length of each job and turning off
   I/Os: `./mlfq.py --numJobs=2 --numQueues=2 --seed=50 --maxio=0 --iotime=0 --maxlen=30`

   See this link for my answer: https://docs.google.com/spreadsheets/d/1D0baKJ1OwMK056kj7ch85a2ZRW7IAFIuBpKco0iKSs8/edit?usp=sharing

2. How would you run the scheduler to reproduce each of the examples in the chapter?
   - Long-running job with a time-slice of 10, 3 queues, time=200 (see figure 8.2): `./mlfq.py --numJobs=1 --numQueues=3 0 --allotment=1 --quantum=10 --maxio=0 --iotime=0 -c`
   - One long-running job and one short-running job. See figure 8.3a: `./mlfq.py --jlist=0,200,0:100,20,0 --numQueues=3 0 --allotment=1 --quantum=10 --maxio=0 --iotime=0 -c`
   - Same as above, but stay at same priority level after issuing an I/O: `./mlfq.py --jlist=0,220,0:50,17,1 --stay --numQueues=3 0 --allotment=1 --quantum=10 --iotime=10 -c`
3. How would you configure the scheduler parameters to behave just
   like a round-robin scheduler?
   `./mlfq.py --numJobs=3 --numQueues=1 --allotment=1 --quantum=1 --maxio=0 --iotime=0 --maxlen=20 -c`
4. Craft a workload with two jobs and scheduler parameters so that
   one job takes advantage of the older Rules 4a and 4b (turned on
   with the -S flag) to game the scheduler and obtain 99% of the CPU
   over a particular time interval.

   `./mlfq.py --stay --jlist=0,100,0:0,100,9  --numQueues=3 --allotment=1 --quantum=10 --maxio=0 --iotime=0 --maxlen=20 -c`

5. Given a system with a quantum length of 10 ms in its highest queue,
   how often would you have to boost jobs back to the highest priority
   level (with the -B flag) in order to guarantee that a single longrunning (and potentially-starving) job gets at least 5% of the CPU?

   `./mlfq.py --stay --boost=95 --jlist=0,100,0:0,200,9 --allotment=1 --quantumList=10,5 --iotime=0 -c`

6. One question that arises in scheduling is which end of a queue to
   add a job that just finished I/O; the -I flag changes this behavior
   for this scheduling simulator. Play around with some workloads
   and see if you can see the effect of this flag
   - What I think happens is: imagine a process is doing a lot of I/O and keeps getting put back at the front of the queue, and then it starts dropping down the queue list because it is doing more CPU stuff. If it starts doing I/O again, it will just stay in the same queue, and never get re-prioritized to the top queue again. That seems problematic if the user is running a program that occasionally requires a lot of user input interspersed with times when it is doing a lot of CPU batch jobs.
