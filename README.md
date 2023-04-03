<h1>Shearsort Algorithm</h1>

<h2>Description</h2>
A C program intended to show familiarity using threads and semaphores, this program reads in 16 integers into a 2-dimensional array and performs a Shearsort algorithm using threads and semaphores to synchronize the phases of the algorithm. 
<br />


<h2>Languages and Utilities Used</h2>

- <b>C</b> 

<h2>Program walk-through:</h2>

<p align="center">
Below is an example of how a shearsort assembles a set of numbers. The algorithm executes a series of phases, each of phase consist of sorting each column in ascending order along with each odd row while each even row is ordered in descending order until all of the numbers are ordered in a snake-like pattern. For a n x n matrix, a shearsort algorithm will require log(n) + 1 phases: <br/>
<img src="https://imgur.com/9aqyG5x.png" height="50%" width="50%" alt="Shearsort"/>
<br />
<br />
The program will first prompt the user to enter a random set of 16 integers:  <br/>
 <br />
<img src="https://imgur.com/9miBznU.png" height="25%" width="25%" alt="Shearsort"/>
<br />
<br />
The program returns the original array along with the ordered array:  <br/>
<br />
<img src="https://imgur.com/m26J2oO.png" height="25%" width="25%" alt="Shearsort"/>
<br />
<br />
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>
