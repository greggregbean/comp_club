# comp_club

## Description
These programm is prototype of a system that monitors the work of the computer club, processes events and calculates the revenue for the day and the time of activity of each table.

## Input data
All the input data one should be written in some text file and then transfer it as a second command line argument after the name of executable (will be shown below).

* The first line contains the number of tables as a positive integer.
* The second line specifies the start and end time of the computer club, separated by a space.
* The third line specifies the cost per hour in the computer club as a positive integer.
* Then a list of incoming events is set, separated by a line break. Inside the string, a single space is used as a separator between the elements. 

_Incoming events_:
1. _Client enter_
2. _Client take the table_
3. _Client is waiting_
4. _Client quit_

The example of input data:
```
3
09:00 19:00
10
08:48 1 client1
09:41 1 client1
09:48 1 client2
09:52 3 client1
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:45 3 client4
12:33 4 client1
12:43 4 client2
15:52 4 client4
```

## Output data

If the input data is incorrect, the program should output the first line with a mistake and shut down. Else should output the following result:
* The first line shows the start time.
* The following lists all the events that occurred during the working day (incoming and outgoing), each on a separate line.
* After the list of events, the end time is printed on a separate line.
* For each table, the following parameters are separated by a space on a separate line: table number, revenue for the day and the time it was active during the working day.

_Outgoing events (generating during execution):_

11. _Client quit_
22. _Client take the table_
33. _Error_

The output for input data from example:
```
09:00
08:48 1 client1
08:48 13 NotOpenYet
09:41 1 client1
09:48 1 client2 
09:52 3 client1
09:52 13 ICanWaitNoLonger!
09:54 2 client1 1
10:25 2 client2 2
10:58 1 client3 
10:59 2 client3 3
11:30 1 client4
11:35 2 client4 2
11:35 13 PlaceIsBusy
11:45 3 client4
12:33 4 client1
12:33 12 client4 1
12:43 4 client2
15:52 4 client4
19:00 11 client3
19:00
1 70 05:58 
2 30 02:18
3 90 08:01 
```

## Structure
Project contains 2 parts:
* _comp_club_
* _input_check_

__include__ folder contains __*.h__ files of these parts, __src__ contains __*.cpp__ ones and __main.cpp__. _input_check_ is responsible for correctness data, if input data is correct, _comp_club_ starts it's work. The __test_files__ folder contains 5 examples of input data text files. 
## Build 
You can compile this programm with g++ (gcc in Linux or MinGw in Windows):
```
g++ -Wall -Wextra -Wpedantic ./src/comp_club.cpp ./src/input_check.cpp ./src/main.cpp -o run
```
or build with CMake (target executable is called __run__) for Linux:
```
mkdir build
cd build
cmake ..
cmake --build .
```
for Windows:
```
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build .
```

## Run
As mentioned earlier, you should transfer a file with input_data as a second command line argument, like this:
```
./run ./test_files/tst_file.txt
```

