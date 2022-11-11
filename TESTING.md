## CS50 Blackjack Project
## Asher Vogel, Rory Doyle, Eli Rosenberg, Nate Roe
## Testing Specification

Testing for this project was extensive. Since we broke the project into modules to be completed seperately initially, we unit tested each method written in each module. We then integrated the methods together to test for normal functionality before integrating all the modules and testing their integration. 

Once the modules were integrated, the testing mainly comprised of testing over the server. This required the group to all test together, and it was extensive testing. The memory leaks were also found anf fixed while working together over the server. This can be seen in *testing.out*. 

We then had to test using Pierson's given server and dealer code. This turned out to be an issue: we were too slow to accomodate Pierson's speed. To fix this, we optimized and reduced our delay. 

For training our algorithm, we did tens of thousands of tests. This was made possible by using two terminals and training over night on a laptop. We trained the algorithm over night two consecutive nights. 