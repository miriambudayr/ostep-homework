# Definitions

- Turnaround time: time_of_COMPLETION - time_of_ARRIVAL
- Response time: time_of_ARRIVEL - time_of_first_run
- Assumption: all jobs arrive at same time, and jobs run to completion
  - FIFO (first in first out): first job to arrive is the first job to be run
  - Cons: one long job can block a lot of small jobs
  - SFJ (shortest job first): shortest job goes first
- Assumption: jobs can arrive at ANY time, and jobs can be interrupted
  - STCF (shortest time to completion first): any time a new job arrives, CPU runs the job with LEAST amount of time left
  - Round Robin/time-clicing: the most fair, gives each consecutive job the same amount of CPU time until the jobs are done
    - Time slice: the amount of time the round robin is set to run each job for
    - Cons: if the time slice is too short, the CPU will incur a lot of context-switching costs

# Questions

1. Compute the response time and turnaround time when running
   three jobs of length 200 with the SJF and FIFO schedulers.

   - `./scheduler.py -p SJF -l 200,200,200`
   - `./scheduler.py -p FIFO -l 200,200,200`
   - Observation: the times are the same for both SJF and FIFO, if the jobs are the same length.

2. Now do the same but with jobs of different lengths: 100, 200, and 300

   - `./scheduler.py -p SJF -l 100,200,300`
   - `./scheduler.py -p FIFO -l 300,200,100`
   - Observation: I tried running this experiment with the jobs in this order: 100,200,300. The runs between both scheduling algorithms resulted in the same metrics. I realized that if they were in the same order, the drawbacks of using FIFO would not be apparent, so I changed the order.

3. Now do the same, but also with the RR scheduler and a time-slice
   of 1.

   - `./scheduler.py -q 1 -p RR -l 1,1,1`
   - `./scheduler.py -q 1 -p RR -l 2,2,2`

4. For what types of workloads does SJF deliver the same turnaround
   times as FIFO?: when times are the same when the workloads are the same, and in the same order.
5. For what types of workloads and quantum lengths does SJF deliver
   the same response times as RR?: if the shortest jobs are shorter or equal to the quantum length, and they are also in the same order. If they aren't in the same order, they may end up being run last in the RR which would delay the response time.
6. What happens to response time with SJF as job lengths increase?: response time increases because response time is a function of completion time for earlier jobs. If jobs are longer, then they have to wait longer to be able to get CPU time.
   Can you use the simulator to demonstrate the trend?
7. What happens to response time with RR as quantum lengths increase? Can you write an equation that gives the worst-case response time, given N jobs?: the response time increases because each job has to wait longer to get their first round of CPU time. The worst-case scenario for a given job is if that job gets CPU time last.

worst_case_response_time = quantum_length x (N - 1)
