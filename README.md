#### CS 240 - Spring 2019
# Program 3 - Let's Find Life
## Due Date: 11:59 p.m., May 10th, 2019

*All programs will be tested on the machines in the Q22 lab. If your code does not run on the system in this lab, it is considered non-functioning EVEN IF IT RUNS ON YOUR PERSONAL COMPUTER. Always check that your code runs on the lab machines before submitting.*

:no_entry: _If you do not notify the TA who your teammate is by the end of lab, one will be assigned to you. Working with a partner is a requirement. You cannot complete this assignment on your own. If you complete the project on your own, without a partner, you will receive a 0._

***

_Replace anything surrounded by the `<< >>` symbols._

## SUMMARY:
 Group Members:<< your names >>

 << Provide a short description of your program's functionality. No more than a couple sentences. >>

## OPTIMIZATION:
 << What, if anything, did you do to optimize your code? You must complete this to be eligible for extra credit. >>

## KNOWN BUGS AND INCOMPLETE PARTS:
 << What parts of the project you were not able to complete >>

## REFERENCES:
 << List any outside resources used >>

## MISCELLANEOUS COMMENTS:
<< Anything you would like the grader to know >>

***

### Policies

#### Getting Help

Please follow the debugging guidelines outlined [here](https://docs.google.com/document/d/1lbMdo-61lScAAho4UDGJ6HtkAlLXMjABbBqPL9r-w-o/edit?usp=sharing). We will try to answer questions and provide help within 24 hours of your request. If you do not receive a response in 24 hours, please send the request again.

Although we will answer questions, provide clarification, and give general help where possible up until the deadline, we will not help you debug specific code within 24 hours of the deadline. We will not provide any help after the deadline.

#### Extensions

No extensions will be provided for the final project.

#### Guidelines

This is a pair programming assignment. You and a partner can divide up the work. Although both of you may not work on all parts of the program you should understand and be able to fully explain every portion of the code. Outside of your team, it is permissible to consult with classmates to ask general questions about the assignment, to help discover and fix specific bugs, and to talk about high level approaches in general terms. It is not permissible to give or receive answers or solution details from fellow students.

You may research online for additional resources; however, you may not use code that was written specifically to solve the problem you have been given, and you may not have anyone else help you or your partner write the code or solve the problem. You may use code snippets found online, providing that they are appropriately and clearly cited, within your submitted code.

If you or your partner are found to have plagiarized any part of the assignment, both will receive a 0 and be reported.

*By submitting this assignment, you agree that you have followed the above guidelines regarding collaboration and research.*


***


### Provided Files and Expected Output
* _Files_
    * Driver
       * program3.cpp
    * Test files
       * planetsA.dat
       * planetsB.dat
* _Expected Command > Output_
    * Test Commands we will run
        * make
        * make run
        * make memcheck
        * make clean
    * Sample Output:
```shell
    TEST #0: Read file of Planets and build your adjacency list (for testing)
    ========================PASS========================
    TEST #1: Testing Galaxy and Planet Interface
    ========================PASS========================
    TEST #2: Test Adjacencies
    ========================PASS========================
    TEST #3: Simple Shortest Path
    ========================PASS========================
    TEST #4: Less Simple Shortest Path
    ========================PASS========================
    TEST #5: Shortest Path between a single point
    ========================PASS========================
    TEST #6: Shortest Path with multiple midpoints
    ========================PASS========================
    TEST #7: Shortest Path with more edges
    ========================PASS========================
    TEST #8: No Path
    There is no path, no escape. You are doomed. Doomed. DOOMED.
    ========================PASS========================
    TEST #9: Distance of no path is inf
    There is no path, no escape. You are doomed. Doomed. DOOMED.
    ========================PASS========================
    TEST #10: Distance from a single planet (should be 0)
    ========================PASS========================
    TEST #11: Distance between two planets
    ========================PASS========================
    TEST #12: Distance with two equal paths
    ========================PASS========================
    TEST #13: Shortest Path Performance
    Beginning profile time
    Completed profile time = 1.000000
    ========================PASS========================
```

### Grading Rubric
__Total: 60 points__
* __Part A__
    * Test 1: 3 points
        * Read file a list of Planets and their locations
    * Test 2: 5 points
        * Test Adjacencies
* __Part B__
    * Test 3-5: 5 points each
        * Simple Shortest Path
        * Less Simple Shortest Path
        * Shortest Path between a single point
    * Test 6-8: 6 points each
        * Complex Shortest Path on Galaxy
        * Another Complex Shortest Path on Galaxy
        * No Path
    * Test 9: 4 points
        * Distance of no path is inf
    * Test 10-12: 5 points each
        * Distance from a single planet (should be 0)
        * Distance between two planets
        * Distance between two planets with more edges
* __Part C: EXTRA CREDIT__
    * Test 13: 10 points
        * Highest Performance
* __Part D__
    * If memory error, memory leak, no 'memcheck' target [-5 points]
    * Repository includes .o files or binary [-1 point]
    * Does not follow [Style guidelines](https://drive.google.com/open?id=1a5I7XhhCDRHoS8LUfILu3y2la4wW8HHh4olO30YvMVk)[-3 points]
    * Your submission will not be accepted if:
        * Does not follow requested project structure and submission format
        * Does not compile

***

For our final program we are going to visit the stars (virtually). We have gathered all the data we need, and now we are going to visit each planet that contains life; however, our craft is very simple and cannot travel too far without refueling, so we will have to plot our course as efficiently as possible. You are going to create a library that reads in a file with a list a planets and their coordinates in space. The driver code will input a starting planet and destination planet, and you will return the shortest path between the two as a vector of planet names along with the path. Then we are going to test the performance of your path finding algorithm, and possibly give you extra credit.

## Part A: Making a Graph

For Part A you will read in a text containing planets and their x, y, and z coordinates in 3 dimensional space. The file format will be as follows:

```
Kepler-1049b -25 13 8
HAT-P-27b 8 27 23
HD116029b 9 -35 -5
```

Planet names will not contain whitespace and will be uniquely named. Input files will be well-formed (no need for error checking). You will need to build an undirected, weighted graph using the x, y, and z coordinates.

Each planet will have 4 adjacent planets. These should be the 4 closest planets in space. Not all adjacencies will be symmetric. This means the graph is a directed graph. So the algorithm for building the adjacency list will be to find the distance for all planets, but set only the 4 closest as adjacent.

You should use an array or vector to store the planets. To hold edges you will need to implement an adjacency list or an adjacency matrix (you may use the STL list or vector class).

To help you visualize the graph, I have created the following:
[planetsB.dat](http://graphonline.ru/en/?graph=CkibCDSMVdSIOfrV)

### Planet Public Interface
* `Planet(string planetName, long xCoor, long yCoor, long zCoor)`
* `std::string getName()`
     * Returns the planet name
* `int getXCoor()`
     * Returns the x coordinate
* `int getYCoor()`
     * Returns the y coordinate
 * `int getZCoor()`
      * Returns the z coordinate
* `list<Planet*> getAdjacent()`
     * Returns an adjacency list for the planet

### Galaxy Public Interface
* `Galaxy(string filename)`
    * Takes in a filename and build a list of planets with adjacencies
* `unsigned int size()`
    * The number of planets currently contained in the galaxy
* `Planet* findByName(std::string planetName)`
    * Returns the planet object with the associated name

__Show your TA your working Part A code by the end of lab on May 2nd.__

_You may continue to work on the remainder of the project on your own time or in lab_

## Part B: Finding the Shortest Path

In order to travel between planets, we have to stop at nearby planets to refuel. You will need to implement Dijkstra’s shortest path algorithm to determine the shortest path between two planets. If you want to implement a different shortest path algorithm, you must clear it with me first. You must use only "adjacent" planets when finding the path. In other words, planetA may have 4 adjacencies, but also may not be an adjacent to any other planet. That means there is no path to planetA.

You should add the following public method to your Galaxy class:
* `vector<Planet *> shortestPath(Planet * start, Planet * dest)`
    * The method should return the shortest path between two planets by returning a list of the planets you will need to travel through in order.

You will also need a second method that gives the distance (in light years) between two planets on the graph:
* `double pathDistance(Planet * start, Planets * dest)`
    * The method should return the total distance (based on the path you must take) between the two planets.
    * The method should return `inf` if there is no path.
        * take a look at [LDBL_MAX](http://www.cplusplus.com/reference/cfloat/), which is equal to `inf`

## Part C - EXTRA CREDIT: Optimizing Dijkstra's Algorithm

Part of the complexity of Dijkstra's algorithm comes from finding the next closest, unvisited vertex. Typically, you can increase the speed of Dijkstra's shortest path algorithm by storing the data in a simple priority queue, such as a heap.

There are several other ways we can improve performance, which I will leave up to you. The top 3 best performance times as measured by test 13 will receive 10 points extra credit.

## Part D: Code Organization and Submission
* Required code organization:
    * program3.cpp
    * Planet.h/.cpp
    * Galaxy.h/.cpp
    * makefile
        * executable should be called: program3
        * You must have the following targets in your makefile:
            * `program3` - only compiles your source code using separate compilation for each .cpp file
            * `clean` - removes all object files and binary executables
            * `run` - compiles if necessary and runs your executable
            * `memcheck` - compiles your source if necessary, then runs your executable with valgrind
        * `program3.cpp` is set up to allow you to skip specified tests. To select tests to skip, you should set a preprocessor define directive in your makefile, using the -D flag. This sets the preprocessing variable in your makefile when you compile `program3.cpp` to an object file. Below is an example of skipping tests 4-11:
            * `g++ -g -std=c++14 -c -D TEST4 -D TEST5 -D TEST6 -D TEST7 -D TEST8 -D TEST9 -D TEST10 -D TEST11 program3.cpp -o program3.o`

Below is just a reminder of the commands you should use to submit your code. If you cannot remember the exact process, please review lab 1.

_These commands all presume that your current working directory is within the directory tracked by `git`._

You will need to do the following when your submission is ready for grading. :warning: Make sure you have added all files to your repo.

```shell
git commit -am "final commit"
git push
```

To complete your submission, you must copy and paste the commit hash into MyCourses. Go to MyCourses, select CS240, and then assignments. Select Program 3, and where it says text submission, paste your commit hash. You can get your latest commit hash with the following command:

```shell
git rev-parse HEAD
```

:warning: Remember, you __MUST__ make a submission on mycourses before the deadline to be considered on time.
