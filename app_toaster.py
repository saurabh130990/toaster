import time
import threading
import signal
import os
import Queue
from functools import partial

# TIMER MODULE
def timer(timer_q):
    start_timer = time.time()
    while True:
        time.sleep(1)
        end_timer = time.time()
        timer_q.put(int(end_timer - start_timer))
    return

# READER MODULE
def reader(reader_q, signum_r, frame_r):
    m_status = 2
    if signum_r == 10:
        m_status = 1
    if signum_r == 12:
        m_status = 2
    reader_q.put(m_status)
    return

# CONTROLLER MODULE
def controller(timer_q, reader_q, controller_q):
    controller_dict = {'t' : 0, 'mesh' : 'OFF'}
    i = 0
    while True:
        controller_dict['t'] = timer_q.get(True)
        try:
            c_status = reader_q.get(False)
        except Queue.Empty:
            if i == 10:
                c_status = 2
                i = 0

        if c_status == 1:
            controller_dict['mesh'] = "ON"
            i = i + 1
        if c_status == 2:
            controller_dict['mesh'] = "OFF"
            i = 0
        controller_q.put(controller_dict)
    return

# WRITER MODULE
#def writer(controller_q, writer_q):
def writer(controller_q):
    while True:
        var = controller_q.get()
        print "%(t)d MESH %(mesh)s" % var
    return

# MAIN PROGRAM
def main():
    signum = 0
    frame = 0

    # CREATE QUEUES FOR DIFFERENT THREADS
    timer_q = Queue.Queue()
    reader_q = Queue.Queue()
    controller_q = Queue.Queue()
    #writer_q = Queue.Queue()

    #print 'My PID:', os.getpid()
    # WRITING PID TO FILE (USED BY trigger.py)
    f = open("pid", "w")
    f.write(str(os.getpid()))
    f.close()

    # DECLARING SIGNALS FOR LEVER AND CANCEL BUTTON
    signal.signal(signal.SIGUSR1, partial(reader, reader_q))
    signal.signal(signal.SIGUSR2, partial(reader, reader_q))

    # CREATING THREADS FOR TIMER, CONTROLLER, READER AND WRITER
    t1 = threading.Thread(target=timer, args=(timer_q,))
    t1.start()

    t4 = threading.Thread(target=reader, args=(reader_q, signum, frame,))
    t4.start()

    t2 = threading.Thread(target=controller, args=(timer_q, reader_q, controller_q,))
    t2.start()

    #t3 = threading.Thread(target=writer, args=(controller_q, writer_q))
    t3 = threading.Thread(target=writer, args=(controller_q,))
    t3.start()

    # CONTINUOUSLY SCAN FOR SIGNALS
    while True:
        signal.pause()

if __name__ == '__main__':
    main()
