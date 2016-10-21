# MechMania-2016-AI
  AI made for the MechMania competition at Reflections|Projections 2016. 
  
  Uses a decision tree with minimax algorithm combined with alpha-beta pruning.
  Also times itself for particularly computation intensive moves to make sure it responds in the required time. 
  Interfaces with as a subroutine to a python client from [here](https://github.com/timchoh585/mm22).
  Has some unit tests written with the Google Test framework to verify correctness and a sample json data file.
  
### Building and running
In the build directory run the following commands:
```
cmake build ..
make
./runDecisionTreeTests
./decision_tree_run < ../testinput.json
```
